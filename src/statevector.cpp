#include "statevector.h"
#include <iostream>
#include <bitset>
#include <cmath>
using namespace std;
using comp=complex<double>;

// Function that initializes the primal state of the quantum values
StateVector::StateVector(int qubits) {
    // Set the private variable for the number of qubits to the specified value
    num_qubits = qubits;

    // Create the state vector with the number of possible quantum states, being 2^(number of qubits)
    data = vector<comp> (pow(2, qubits), comp(0.0, 0.0));

    // Initialize the state vector to the starting value, having |000> a 100% appearance rate
    data[0] = comp(1.0, 0.0);
}

// Function that displays the current state of the quantum system
void StateVector::display() {
    cout << "Number of qubits: " << num_qubits << endl;
    cout << "Current quantum state:" << endl;

    for (int i = 0; i < data.size(); i++) {
        // Get the binary representation of the state represented in each index
        string binary_representation = bitset<32>(i).to_string().substr(32-num_qubits);

        // Get quantum values of each possible state
        double real = data[i].real();
        double imag = data[i].imag();

        cout << "|" << binary_representation << ">:" << real << "+" << imag << "i" << endl;
    }
}