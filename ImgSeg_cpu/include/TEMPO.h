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

#endif // TEMPO_H
