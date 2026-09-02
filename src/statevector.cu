#include "statevector.cuh"
#include "gates.cuh"
#include "run.cuh"
#include <cuda_runtime.h>
#include <iostream>
#include <bitset>
#include <complex>
#include <utility>

StateVector::StateVector(int qubits) {
    num_qubits = qubits;
    if (qubits < 1) {
        cout << "Error: Minimum number of qubits per vector is 1. Setting StateVector to one qubit." << endl;
        num_qubits = 1;
    }
    else if (qubits > 25) {
        cout << "Error: Maximum number of qubits per vector is 25. Setting StateVector to 25 qubits." << endl;
        num_qubits = 25;
    }
    total_states = 1ULL << num_qubits;

    cudaDeviceReset();

    cudaMalloc((void**)&data, total_states * sizeof(cuDoubleComplex));
    cudaMalloc((void**)&data_out, total_states * sizeof(cuDoubleComplex));

    cudaMemset(data_out, 0, total_states * sizeof(cuDoubleComplex));

    vector<cuDoubleComplex> initial(total_states, make_cuDoubleComplex(0.0, 0.0));
    initial[0] = make_cuDoubleComplex(1.0, 0.0);

    cudaMemcpy(data, initial.data(), total_states * sizeof(cuDoubleComplex), cudaMemcpyHostToDevice);

    cudaDeviceSynchronize();
}

vector<cuDoubleComplex> StateVector::get_statevector() {
    vector<cuDoubleComplex> cpu_statevector(total_states);

    cudaMemcpy(cpu_statevector.data(), data, total_states * sizeof(cuDoubleComplex), cudaMemcpyDeviceToHost);
    cudaDeviceSynchronize();

    return cpu_statevector;
}

void StateVector:: display() {
    vector<cuDoubleComplex> statevector = get_statevector();

    cout << "Number of qubits: " << num_qubits << endl;
    cout << "Current quantum state:" << endl;

    for (int i = 0; i < total_states; i++) {
        string binary_representation = bitset<32>(i).to_string().substr(32-num_qubits);

        double real = statevector[i].x;
        double imag = statevector[i].y;

        char operation = '+';
        if (imag < 0) {
            operation = '-';
            imag *= -1;
        }

        cout << "|" << binary_representation << ">:" << real << operation << imag << "i" << endl;
    }
}

void StateVector::apply_pauliX(int target_qubit) {
    if (target_qubit < 0 || target_qubit >= num_qubits) {
        cout << "Error: Target out of range!" << endl;
        return;
    }

    int threadsPerBlock = 256;
    int blocksPerGrid = (total_states + threadsPerBlock - 1) / threadsPerBlock;

    pauliX<<<blocksPerGrid, threadsPerBlock>>>(data, total_states, target_qubit);
}

void StateVector::apply_pauliY(int target_qubit) {
    if (target_qubit < 0 || target_qubit >= num_qubits) {
        cout << "Error: Target out of range!" << endl;
        return;
    }

    int threadsPerBlock = 256;
    int blocksPerGrid = (total_states + threadsPerBlock - 1) / threadsPerBlock;

    pauliY<<<blocksPerGrid, threadsPerBlock>>>(data, total_states, target_qubit);
}

void StateVector::apply_pauliZ(int target_qubit) {
    if (target_qubit < 0 || target_qubit >= num_qubits) {
        cout << "Error: Target out of range!" << endl;
        return;
    }

    int threadsPerBlock = 256;
    int blocksPerGrid = (total_states + threadsPerBlock - 1) / threadsPerBlock;

    pauliZ<<<blocksPerGrid, threadsPerBlock>>>(data, total_states, target_qubit);
}

void StateVector::apply_hadamard(int target_qubit) {
    if (target_qubit < 0 || target_qubit >= num_qubits) {
        cout << "Error: Target out of range!" << endl;
        return;
    }

    cuDoubleComplex factor = make_cuDoubleComplex(1.0/sqrt(2.0), 0.0);

    int threadsPerBlock = 256;
    int blocksPerGrid = (total_states + threadsPerBlock - 1) / threadsPerBlock;

    hadamard<<<blocksPerGrid, threadsPerBlock>>>(data, data_out, total_states, target_qubit, factor);

    std::swap(data, data_out);
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

    int threadsPerBlock = 256;
    int blocksPerGrid = (total_states + threadsPerBlock - 1) / threadsPerBlock;

    cnot<<<blocksPerGrid, threadsPerBlock>>>(data, data_out, total_states, target_qubit, control_qubit);

    std::swap(data, data_out);
}

void StateVector::apply_Sgate(int target_qubit) {
    if (target_qubit < 0 || target_qubit >= num_qubits) {
        cout << "Error: Target out of range!" << endl;
        return;
    }

    int threadsPerBlock = 256;
    int blocksPerGrid = (total_states + threadsPerBlock - 1) / threadsPerBlock;

    Sgate<<<blocksPerGrid, threadsPerBlock>>>(data, total_states, target_qubit);
}

void StateVector::apply_Tgate(int target_qubit) {
    if (target_qubit < 0 || target_qubit >= num_qubits) {
        cout << "Error: Target out of range!" << endl;
        return;
    }

    int threadsPerBlock = 256;
    int blocksPerGrid = (total_states + threadsPerBlock - 1) / threadsPerBlock;

    Tgate<<<blocksPerGrid, threadsPerBlock>>>(data, total_states, target_qubit);
}

void StateVector::apply_S_Dager_gate(int target_qubit) {
    if (target_qubit < 0 || target_qubit >= num_qubits) {
        cout << "Error: Target out of range!" << endl;
        return;
    }

    int threadsPerBlock = 256;
    int blocksPerGrid = (total_states + threadsPerBlock - 1) / threadsPerBlock;

    S_Dager_gate<<<blocksPerGrid, threadsPerBlock>>>(data, total_states, target_qubit);
}

void StateVector::apply_T_Dager_gate(int target_qubit) {
    if (target_qubit < 0 || target_qubit >= num_qubits) {
        cout << "Error: Target out of range!" << endl;
        return;
    }

    int threadsPerBlock = 256;
    int blocksPerGrid = (total_states + threadsPerBlock - 1) / threadsPerBlock;

    T_Dager_gate<<<blocksPerGrid, threadsPerBlock>>>(data, total_states, target_qubit);
}

void StateVector::apply_Rz(int target_qubit, double theta) {
    if (target_qubit < 0 || target_qubit >= num_qubits) {
        cout << "Error: Target out of range!" << endl;
        return;
    }

    cuDoubleComplex multiplier = make_cuDoubleComplex(cos(theta/2.0), sin(theta/2.0));

    int threadsPerBlock = 256;
    int blocksPerGrid = (total_states + threadsPerBlock - 1) / threadsPerBlock;

    Rz<<<blocksPerGrid, threadsPerBlock>>>(data, total_states, target_qubit, multiplier);
}

void StateVector::apply_Rx(int target_qubit, double theta) {
    if (target_qubit < 0 || target_qubit >= num_qubits) {
        cout << "Error: Target out of range!" << endl;
        return;
    }

    cuDoubleComplex cosinus = make_cuDoubleComplex(cos(theta/2.0), 0.0);
    cuDoubleComplex sinus = make_cuDoubleComplex(0.0, -sin(theta/2.0));


    int threadsPerBlock = 256;
    int blocksPerGrid = (total_states + threadsPerBlock - 1) / threadsPerBlock;
    
    Rx<<<blocksPerGrid, threadsPerBlock>>>(data, data_out, total_states, target_qubit, cosinus, sinus);

    std::swap(data, data_out);
}

void StateVector::apply_Ry(int target_qubit, double theta) {
    if (target_qubit < 0 || target_qubit >= num_qubits) {
        cout << "Error: Target out of range!" << endl;
        return;
    }

    cuDoubleComplex cosinus = make_cuDoubleComplex(cos(theta/2.0), 0.0);
    cuDoubleComplex sinus = make_cuDoubleComplex(sin(theta/2.0), 0.0);

    int threadsPerBlock = 256;
    int blocksPerGrid = (total_states + threadsPerBlock - 1) / threadsPerBlock;

    Ry<<<blocksPerGrid, threadsPerBlock>>>(data, data_out, total_states, target_qubit, cosinus, sinus);

    std::swap(data, data_out);
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

    int threadsPerBlock = 256;
    int blocksPerGrid = (total_states + threadsPerBlock - 1) / threadsPerBlock;

    CZgate<<<blocksPerGrid, threadsPerBlock>>>(data, total_states, target_qubit, control_qubit);
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

    int threadsPerBlock = 256;
    int blocksPerGrid = (total_states + threadsPerBlock - 1) / threadsPerBlock;

    SWAP<<<blocksPerGrid, threadsPerBlock>>>(data, data_out, total_states, target_qubit1, target_qubit2);

    std::swap(data, data_out);
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

    int threadsPerBlock = 256;
    int blocksPerGrid = (total_states + threadsPerBlock - 1) / threadsPerBlock;

    toffoli<<<blocksPerGrid, threadsPerBlock>>>(data, data_out, total_states, target_qubit, control_qubit1, control_qubit2);

    std::swap(data, data_out);
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

    int threadsPerBlock = 256;
    int blocksPerGrid = (total_states + threadsPerBlock - 1) / threadsPerBlock;

    fredkin<<<blocksPerGrid, threadsPerBlock>>>(data, data_out, total_states, target_qubit1, target_qubit2, control_qubit);

    std::swap(data, data_out);
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

    cuDoubleComplex multiplier = make_cuDoubleComplex(cos(theta/2.0), sin(theta/2.0));

    int threadsPerBlock = 256;
    int blocksPerGrid = (total_states + threadsPerBlock - 1) / threadsPerBlock;

    ControlledPhase<<<blocksPerGrid, threadsPerBlock>>>(data, total_states, target_qubit, control_qubit, multiplier);
}

void StateVector::apply_generate_results(int shots, char list, char chart) {
    vector<cuDoubleComplex> statevector = get_statevector();
    generate_results(statevector, num_qubits, shots, list, chart);
}

StateVector::~StateVector() {
    if (data != nullptr) {
        cudaFree(data);
        data = nullptr;
    }
    if (data_out != nullptr) {
        cudaFree(data_out);
        data_out = nullptr;
    }
}