#include <iostream>
#include <stdio.h>
#include <cstring>
#include <cuda_runtime_api.h>
#include <cuda.h>
#include "PBM1d.cpp"
#include "PICUDA.cu"

#define BLOCK_SIZE 16
#define RAIO 1

using namespace std;

void chamaKernelTD_global(PBM1d* in, PBM1d* out, int N, size_t sizeMat);
__global__ void vet_td_gpu_g_kernel(int* IN, int* OUT);
void chamaKernelTD_shared(PBM1d* in, PBM1d* out, int N, size_t sizeMat);
__global__ void vet_td_gpu_s_kernel(int* IN, int* OUT);


void PICUDA::TD2D_multGPU(PBM1d* img) {
  PBM1d* out;

  // Nas duas gpu
  int devicesCount, deviceIndex;
  cudaGetDeviceCount(&devicesCount);
  for( deviceIndex = 0; deviceIndex < devicesCount; ++deviceIndex) {
    cudaDeviceProp deviceProperties;
    cudaGetDeviceProperties(&deviceProperties, deviceIndex);
    cudaSetDevice(deviceIndex);
    printf("%s \n", deviceProperties.name );

    // GPU global memory
    TEMPO_tic();
    PBM1d* imgG = PICUDA::TD2D_GLOBAL(img1);
    TEMPO_toc_TD();
    cout << " ";
    delete imgG;

    // GPU shared memory
    TEMPO_tic();
    PBM1d* imgS = PICUDA::TD2D_SHARED(img1);
    TEMPO_toc_TD();
    cout << endl;
    delete imgS;
  }

}


/// =============================== GLOBAL MEMORY

/// TRANSFORMADA DA DISTANCIA em 2D com GLOBAL MEMORY
PBM1d* PICUDA::TD2D_GLOBAL(PBM1d* img) {
  int i;
  int HEIGTH = img->getHeight();
  int WIDTH = img->getWidth();
  int N = img->getTam();

  PBM1d* in = new PBM1d();
  in->copyOf(img);
  PBM1d* out = new PBM1d();
  out->zerado( HEIGTH, WIDTH);

  int ALTO = HEIGTH * WIDTH;
  for(i = 0; i < ALTO; i++) {
    in->set1(i, in->get1(i)*ALTO);
  }

  // tamanho de bytes da img (ela eh mod 16)
  size_t sizeMat = (sizeof (int) * in->getTam() );

  /// chama Horizontalmente
  chamaKernelTD_global(in, out, N, sizeMat);

  // copia OUT -> IN
  memcpy(in->getMat(), out->getMat(), sizeMat);

  // faz a transposta da img
  in->transpose();

  /// chama Verticalmente
  chamaKernelTD_global(in, out, N, sizeMat);

  // faz a transposta da img
  out->transpose();

  delete in;
  return out;
}

void chamaKernelTD_global(PBM1d* in, PBM1d* out, int N, size_t sizeMat) {
  int ite = 0;
  while(1) {
    // Aloca o IN e o OUT na GPU
    int* d_IN;
    int* d_OUT;
    cudaMalloc((void**)&d_IN, sizeMat);
    cudaMalloc((void**)&d_OUT, sizeMat);

    // Copia o IN da CPU para a GPU
    cudaMemcpy(d_IN, (void*)in->getMat(), sizeMat, cudaMemcpyHostToDevice);

    // Lanca Kernel
    dim3 dimBlock(BLOCK_SIZE, 1);
    dim3 dimGrid( N / dimBlock.x, 1);
    vet_td_gpu_g_kernel <<< N / BLOCK_SIZE, BLOCK_SIZE >>> (d_IN + RAIO, d_OUT + RAIO);

    // Copia o OUT da GPU para a CPU
    cudaMemcpy((void*)out->getMat(), d_OUT, sizeMat, cudaMemcpyDeviceToHost);

    // Desaloca da GPU
    cudaFree(d_IN);
    cudaFree(d_OUT);

    // verifica se nao houve mudanca ( se IN==OUT entao PARA)
    if( PBM1d::imgIGUAL(in, out) ) break;

    // copia OUT -> IN
    memcpy(in->getMat(), out->getMat(), sizeMat);

    if(ite > in->getWidth() + 1) {
      break;
    }
  }
}

__global__ void vet_td_gpu_g_kernel(int* IN, int* OUT) {
  int id = threadIdx.x + blockIdx.x * blockDim.x;

  // aplica
  int menor = INT_MAX;
  if(IN[id] == 0) {
    // se o analizado eh 0
    OUT[id] = 0;
  } else {
    // escolhe o menor de seus 2 vizinhos
    for (int vizinho = -RAIO ; vizinho <= RAIO ; vizinho++)
      menor = min(menor, IN[id + vizinho]);

    // Salva o menor + 1
    if(menor >= IN[Lid] ) { // (sem estourar o limite, no cazo de dimensao grande)
      OUT[id] = IN[Lid];
    } else {
      OUT[id] = menor + 1;
    }
  }
}


/// =============================== SHARED MEMORY

/// TRANSFORMADA DA DISTANCIA em 2D com SHARED MEMORY
PBM1d* PICUDA::TD2D_SHARED(PBM1d* img) {
  int i;
  int HEIGTH = img->getHeight();
  int WIDTH = img->getWidth();
  int N = img->getTam();

  PBM1d* in = new PBM1d();
  in->copyOf(img);
  PBM1d* out = new PBM1d();
  out->zerado( HEIGTH, WIDTH);

  int ALTO = HEIGTH * WIDTH;
  for(i = 0; i < ALTO; i++) {
    in->set1(i, in->get1(i)*ALTO);
  }

  // tamanho de bytes da img (ela eh mod 16)
  size_t sizeMat = (sizeof (int) * in->getTam() );

  /// chama Horizontalmente
  chamaKernelTD_shared(in, out, N, sizeMat);

  // copia OUT -> IN
  memcpy(in->getMat(), out->getMat(), sizeMat);

  // faz a transposta da img
  in->transpose();

  /// chama Verticalmente
  chamaKernelTD_shared(in, out, N, sizeMat);

  // faz a transposta da img
  out->transpose();

  delete in;
  return out;
}

void chamaKernelTD_shared(PBM1d* in, PBM1d* out, int N, size_t sizeMat) {
  int ite = 0;
  while(1) {
    // Aloca o IN e o OUT na GPU
    int* d_IN;
    int* d_OUT;
    cudaMalloc((void**)&d_IN, sizeMat);
    cudaMalloc((void**)&d_OUT, sizeMat);

    // Copia o IN da CPU para a GPU
    cudaMemcpy(d_IN, (void*)in->getMat(), sizeMat, cudaMemcpyHostToDevice);

    // Lanca Kernel
    dim3 dimBlock(BLOCK_SIZE, 1);
    dim3 dimGrid( N / dimBlock.x, 1);
    vet_td_gpu_s_kernel <<< N / BLOCK_SIZE, BLOCK_SIZE >>> (d_IN + RAIO, d_OUT + RAIO);

    // Copia o OUT da GPU para a CPU
    cudaMemcpy((void*)out->getMat(), d_OUT, sizeMat, cudaMemcpyDeviceToHost);

    // Desaloca da GPU
    cudaFree(d_IN);
    cudaFree(d_OUT);

    // verifica se nao houve mudanca ( se IN==OUT entao PARA)
    if( PBM1d::imgIGUAL(in, out) ) break;

    // copia OUT -> IN
    memcpy(in->getMat(), out->getMat(), sizeMat);

    if(ite > in->getWidth() + 1) {
      break;
    }
  }
}

__global__ void vet_td_gpu_s_kernel(int* IN, int* OUT) {
  __shared__ int temp[BLOCK_SIZE + 2 * RAIO];
  int Gid = threadIdx.x + blockIdx.x * blockDim.x;
  int Lid = threadIdx.x + RAIO;

  // Adiciona os elementos na memoria Shared
  temp[Lid] = IN[Gid];
  if (threadIdx.x < RAIO) {
    temp[Lid - RAIO] = IN[Gid - RAIO];
    temp[Lid + BLOCK_SIZE] = IN[Gid + BLOCK_SIZE];
  }

  // Sincroniza pra garantir q todos so dados vao estar disponivel
  __syncthreads();

  // aplica
  int menor = INT_MAX;
  if(temp[Lid] == 0) {
    // se o analizado eh 0
    OUT[Gid] = 0;
  } else {
    // escolhe o menor de seus 2 vizinhos
    for (int vizinho = -RAIO ; vizinho <= RAIO ; vizinho++)
      menor = min(menor, temp[Lid + vizinho]);

    // Salva o menor + 1
    if(menor >= temp[Lid] ) { // (sem estourar o limite, no cazo de dimensao grande)
      OUT[Gid] = temp[Lid];
    } else {
      OUT[Gid] = menor + 1;
    }
  }
}
