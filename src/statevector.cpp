#include "statevector.h"
#include "gates.h"
#include <iostream>
#include <bitset>
#include <cmath>

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

void StateVector::apply_pauliX(int target_qubit) {
    if (target_qubit < 0 || target_qubit >= num_qubits) {
        cout << "Error: Target out of range!" << endl;
        return;
    }
    pauliX(data, target_qubit);
}

void StateVector::apply_pauliY(int target_qubit) {
    if (target_qubit < 0 || target_qubit >= num_qubits) {
        cout << "Error: Target out of range!" << endl;
        return;
    }
    pauliY(data, target_qubit);
}

void StateVector::apply_pauliZ(int target_qubit) {
    if (target_qubit < 0 || target_qubit >= num_qubits) {
        cout << "Error: Target out of range!" << endl;
        return;
    }
    pauliZ(data, target_qubit);
}

void StateVector::apply_hadamard(int target_qubit) {
    if (target_qubit < 0 || target_qubit >= num_qubits) {
        cout << "Error: Target out of range!" << endl;
        return;
    }
    hadamard(data, target_qubit);
}

void StateVector::apply_cnot(int target_qubit, int control_qubit) {
    if (target_qubit < 0 || target_qubit >= num_qubits) {
        cout << "Error: Target out of range!" << endl;
        return;
    }
    else if (control_qubit < 0 || control_qubit >= num_qubits) {
        cout << "Error: Target out of range!" << endl;
        return;
    }
    cnot(data, target_qubit, control_qubit);
}