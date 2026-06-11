#pragma once
#include <vector>
#include <complex>
using namespace std;
using comp = complex<double>;

// Quantum gates
void pauliX(vector<comp>& data, int target_qubit);
void pauliY(vector<comp>& data, int target_qubit);
void pauliZ(vector<comp>& data, int target_qubit);

void hadamard(vector<comp>& data, int taget_qubit);

void cnot(vector<comp>& data, int target_qubit, int control_cubit);