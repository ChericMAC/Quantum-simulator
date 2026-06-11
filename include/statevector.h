#pragma once
#include <vector>
#include <complex>
using namespace std;

using comp = complex<double>;

class StateVector {
    private:
        int num_qubits;
        vector<comp> data;
    
    public:
        StateVector(int qubits);
        void display();

        // Quantum gate functions
        void apply_pauliX(int target_qubit);
        void apply_pauliY(int target_quubit);
        void apply_pauliZ(int target_qubit);

        void apply_hadamard(int target_qubit);

        void apply_cnot(int target_qubit, int control_qubit);
};