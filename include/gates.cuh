#ifndef GATES_CUH
#define GATES_CUH

#include <cuComplex.h>

__global__ void pauliX(cuDoubleComplex* data, size_t total_states, int target_qubit);
__global__ void pauliY(cuDoubleComplex* data, size_t total_states, int target_qubit);
__global__ void pauliZ(cuDoubleComplex* data, size_t total_states, int target_qubit);

__global__ void hadamard(cuDoubleComplex* data, cuDoubleComplex* data_out, size_t total_states, int target_qubit, cuDoubleComplex factor);

__global__ void cnot(cuDoubleComplex* data, cuDoubleComplex* data_out, size_t total_states, int target_qubit, int control_qubit);

__global__ void Sgate(cuDoubleComplex* data, size_t total_states, int target_qubit);
__global__ void Tgate(cuDoubleComplex* data, size_t total_states, int target_qubit);
__global__ void S_Dager_gate(cuDoubleComplex* data, size_t total_states, int target_qubit);
__global__ void T_Dager_gate(cuDoubleComplex* data, size_t total_states, int target_qubit);

__global__ void Rz(cuDoubleComplex* data, size_t total_states, int target_qubit, cuDoubleComplex multiplier);
__global__ void Rx(cuDoubleComplex* data, cuDoubleComplex* data_out, size_t total_states, int target_qubit, cuDoubleComplex cosinus, cuDoubleComplex sinus);
__global__ void Ry(cuDoubleComplex* data, cuDoubleComplex* data_out, size_t total_states, int target_qubit, cuDoubleComplex cosinus, cuDoubleComplex sinus);

__global__ void CZgate(cuDoubleComplex* data, size_t total_states, int target_qubit, int control_qubit);
__global__ void SWAP(cuDoubleComplex* data, cuDoubleComplex* data_out, size_t total_states, int target_qubit1, int target_qubit2);

__global__ void toffoli(cuDoubleComplex* data, cuDoubleComplex* data_out, size_t total_states, int target_qubit, int control_qubit1, int control_qubit2);
__global__ void fredkin(cuDoubleComplex* data, cuDoubleComplex* data_out, size_t total_states, int target_qubit1, int target_qubit2, int control_qubit);

__global__ void ControlledPhase(cuDoubleComplex* data, size_t total_states, int target_qubit, int control_qubit, cuDoubleComplex multiplier);

#endif