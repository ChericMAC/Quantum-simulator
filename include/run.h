#pragma once
#include <complex>
#include <vector>
using namespace std;

using comp = complex<double>;

void generate_results(vector<comp>& data, int num_qubits, int shots, char list, char chart);