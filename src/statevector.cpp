#include "statevector.h"
#include "gates.h"
#include "run.h"
#include <iostream>
#include <bitset>
#include <cmath>

// Function that initializes the primal state of the quantum values
StateVector::StateVector(int qubits) {
    // Set the private variable for the number of qubits to the specified value
    num_qubits = qubits;
    if (qubits < 1) {
        cout << "Error: Minimum number of qubits per vector is 1. Setting StateVector to one qubit." << endl;
        num_qubits = 1;
    }
    else if (qubits > 25) {
        cout << "Error: Maximum number of qubits per vector is 25. Setting StateVector to 25 qubits." << endl;
        num_qubits = 25;
    }

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
    else if (control_qubit == target_qubit) {
        cout << "Error: Target qubit can't be equal to control qubit" << endl;
        return;
    }
    cnot(data, target_qubit, control_qubit);
}

void StateVector::apply_Sgate(int target_qubit) {
    if (target_qubit < 0 || target_qubit >= num_qubits) {
        cout << "Error: Target out of range!" << endl;
        return;
    }
    Sgate(data, target_qubit);
}

void StateVector::apply_Tgate(int target_qubit) {
    if (target_qubit < 0 || target_qubit >= num_qubits) {
        cout << "Error: Target out of range!" << endl;
        return;
    }
    Tgate(data, target_qubit);
}

void StateVector::apply_S_Dager_gate(int target_qubit) {
    if (target_qubit < 0 || target_qubit >= num_qubits) {
        cout << "Error: Target out of range!" << endl;
        return;
    }
    S_Dager_gate(data, target_qubit);
}

void StateVector::apply_T_Dager_gate(int target_qubit) {
    if (target_qubit < 0 || target_qubit >= num_qubits) {
        cout << "Error: Target out of range!" << endl;
        return;
    }
    T_Dager_gate(data, target_qubit);
}

void StateVector::apply_Rz(int target_qubit, double theta) {
    if (target_qubit < 0 || target_qubit >= num_qubits) {
        cout << "Error: Target out of range!" << endl;
        return;
    }
    Rz(data, target_qubit, theta);
}

void StateVector::apply_Rx(int target_qubit, double theta) {
    if (target_qubit < 0 || target_qubit >= num_qubits) {
        cout << "Error: Target out of range!" << endl;
        return;
    }
    Rx(data, target_qubit, theta);
}

void StateVector::apply_Ry(int target_qubit, double theta) {
    if (target_qubit < 0 || target_qubit >= num_qubits) {
        cout << "Error: Target out of range!" << endl;
        return;
    }
    Ry(data, target_qubit, theta);
}

void StateVector::apply_CZgate(int target_qubit, int control_qubit) {
    if (target_qubit < 0 || target_qubit >= num_qubits) {
        cout << "Error: Target out of range!" << endl;
        return;
    }
    else if (control_qubit < 0 || control_qubit >= num_qubits) {
        cout << "Error: Target out of range!" << endl;
        return;
    }
    else if (control_qubit == target_qubit) {
        cout << "Error: Target qubit can't be equal to control qubit" << endl;
        return;
    }
    CZgate(data, target_qubit, control_qubit);
}

void StateVector::apply_swap(int target_qubit1, int target_qubit2) {
    if (target_qubit1 < 0 || target_qubit1 >= num_qubits) {
        cout << "Error: Target1 out of range!" << endl;
        return;
    }
    if (target_qubit2 < 0 || target_qubit2 >= num_qubits) {
        cout << "Error: Target2 out of range!" << endl;
        return;
    }
    SWAP(data, target_qubit1, target_qubit2);
}

void StateVector::apply_toffoli(int target_qubit, int control_qubit1, int control_qubit2) {
    if (target_qubit < 0 || target_qubit >= num_qubits) {
        cout << "Error: Target out of range!" << endl;
        return;
    }
    else if (control_qubit1 < 0 || control_qubit1 >= num_qubits) {
        cout << "Error: Control1 out of range!" << endl;
        return;
    }
    else if (control_qubit2 < 0 || control_qubit2 >= num_qubits) {
        cout << "Error: Control2 out of range!" << endl;
        return;
    }
    else if (control_qubit1 == control_qubit2 || control_qubit1 == target_qubit || control_qubit2 == target_qubit) {
        cout << "All thre parameters must be different" << endl;
        return;
    }

    toffoli(data, target_qubit, control_qubit1, control_qubit2);
}

void StateVector::apply_fredkin(int target_qubit1, int target_qubit2, int control_qubit) {
    if (target_qubit1 < 0 || target_qubit1 >= num_qubits) {
        cout << "Error: Target1 out of range!" << endl;
        return;
    }
    else if (target_qubit2 < 0 || target_qubit2 >= num_qubits) {
        cout << "Error: Target2 out of range!" << endl;
        return;
    }
    else if (control_qubit < 0 || control_qubit >= num_qubits) {
        cout << "Error: Control out of range!" << endl;
        return;
    }
    else if (target_qubit1 == target_qubit2 || target_qubit1 == control_qubit || target_qubit2 == control_qubit) {
        cout << "All thre parameters must be different" << endl;
        return;
    }

    fredkin(data, target_qubit1, target_qubit2, control_qubit);
}

void StateVector::apply_ControlledPhase(int target_qubit, int control_qubit, double theta) {
    if (target_qubit < 0 || target_qubit >= num_qubits) {
        cout << "Error: Target out of range!" << endl;
        return;
    }
    else if (control_qubit < 0 || control_qubit >= num_qubits) {
        cout << "Error: Target out of range!" << endl;
        return;
    }
    else if (control_qubit == target_qubit) {
        cout << "Error: Target qubit can't be equal to control qubit" << endl;
        return;
    }

    ControlledPhase(data, target_qubit, control_qubit, theta);
}

void StateVector::apply_generate_results(int shots, char list, char chart) {
    generate_results(data, num_qubits, shots, list, chart);
}
