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
};