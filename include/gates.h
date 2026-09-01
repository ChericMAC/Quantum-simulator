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

void Sgate(vector<comp>& data, int target_qubit);
void Tgate(vector<comp>& data, int target_qubit);
void S_Dager_gate(vector<comp>& data, int target_qubit);
void T_Dager_gate(vector<comp>& data, int target_qubit);

void Rz(vector<comp>& data, int target_qubit, double theta);
void Rx(vector<comp>& data, int target_qubit, double theta);
void Ry(vector<comp>& data, int target_qubit, double theta);

void CZgate(vector<comp>& data, int target_qubit, int control_qubit);
void SWAP(vector<comp>& data, int target_qubit1, int target_qubit2);

void toffoli(vector<comp>& data, int target_qubit, int control_qubit1, int control_qubit2);
void fredkin(vector<comp>& data, int target_qubit1, int target_qubit2, int control_qubit);

void ControlledPhase(vector<comp>& data, int target_qubit, int control_qubit, double theta);