#ifndef TEMPO_H
#define TEMPO_H

#include <iostream>
#include <stack>
#include <chrono>
#include <ctime>

using namespace std;

static stack<std::chrono::time_point<std::chrono::high_resolution_clock> > tictoc_stack;

void TEMPO_tic() {
  tictoc_stack.push(std::chrono::high_resolution_clock::now());
}

void TEMPO_toc() {
  std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
  start = tictoc_stack.top();
  end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed_seconds = end-start;
  double t =  elapsed_seconds.count();

  cout << "Tempo decorrido: "
       << t
       << " s"
       << endl;
  tictoc_stack.pop();
}

void TEMPO_toc_TD() {
  std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
  start = tictoc_stack.top();
  tictoc_stack.pop();
  end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed_seconds = end-start;
  double t =  elapsed_seconds.count();

  cout << t;
}

double TEMPO_toc_bench() {
  std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
  start = tictoc_stack.top();
  end = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> elapsed_seconds = end-start;
  double t =  elapsed_seconds.count();
  return t;
}

#endif // TEMPO_H
