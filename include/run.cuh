#pragma once
#include <complex>
#include <vector>
#include <cuComplex.h>
using namespace std;

using comp = complex<double>;

void generate_results(vector<cuDoubleComplex>& data, int num_qubits, int shots, char list, char chart);