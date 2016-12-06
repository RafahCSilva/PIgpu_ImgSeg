#ifndef TEMPO_H
#define TEMPO_H

#include <iostream>
#include <stack>
#include <ctime>

using namespace std;

static stack<clock_t> tictoc_stack;

void TEMPO_tic() {
  tictoc_stack.push(clock());
}

void TEMPO_toc() {
  cout << "Tempo decorrido: "
       << ((double)(clock() - tictoc_stack.top())) / CLOCKS_PER_SEC
       << " s"
       << endl;
  tictoc_stack.pop();
}

double TEMPO_toc_bench() {
  double t = ((double)(clock() - tictoc_stack.top())) / CLOCKS_PER_SEC;
  tictoc_stack.pop();
  return t * 1000;
}

#endif // TEMPO_H
