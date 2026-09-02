#include "gates.cuh"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

__global__ void pauliX(cuDoubleComplex* data, size_t total_states, int target_qubit) {
    size_t i = blockIdx.x * blockDim.x + threadIdx.x;
    
    size_t target = 1ULL << target_qubit;

    if (i < total_states && (i & target) == 0) {
        size_t pair = i | target;
        cuDoubleComplex provisional = data[i];

        data[i] = data[pair];
        data[pair] = provisional;
    }
}

__global__ void pauliY(cuDoubleComplex* data, size_t total_states, int target_qubit) {
    size_t i = blockIdx.x * blockDim.x + threadIdx.x;
    
    size_t target = 1ULL << target_qubit;

    if (i < total_states && (i & target) == 0) {
        size_t pair = i | target;
        cuDoubleComplex provisional = data[i];

        cuDoubleComplex plusi = make_cuDoubleComplex(0.0, 1.0);
        cuDoubleComplex minusi = make_cuDoubleComplex(0.0, -1.0);

        data[i] = cuCmul(minusi, data[pair]);
        data[pair] = cuCmul(plusi, provisional);
    }
}

__global__ void pauliZ(cuDoubleComplex* data, size_t total_states, int target_qubit) {
    size_t i = blockIdx.x * blockDim.x + threadIdx.x;
    
    size_t target = 1ULL << target_qubit;

    if (i < total_states && (i & target) != 0) {
        cuDoubleComplex factor = make_cuDoubleComplex(-1.0, 0.0);
        
        data[i] = cuCmul(factor, data[i]);
    }
}

__global__ void hadamard(cuDoubleComplex* data, cuDoubleComplex* data_out, size_t total_states, int target_qubit, cuDoubleComplex factor) {
    size_t i = blockIdx.x * blockDim.x + threadIdx.x;
    
    size_t target = 1ULL << target_qubit;

    if (i < total_states) {
        size_t pair = i ^ target;
        cuDoubleComplex data1 = data[i];
        cuDoubleComplex data2 = data[pair];

        if ((i & target) == 0) {
            data_out[i] = cuCmul(factor, cuCadd(data1, data2));
        }
        else {
            data_out[i] = cuCmul(factor, cuCsub(data2, data1));
        }
    }
}

__global__ void cnot(cuDoubleComplex* data, cuDoubleComplex* data_out, size_t total_states, int target_qubit, int control_qubit) {
    size_t i = blockIdx.x * blockDim.x + threadIdx.x;
    
    size_t target = 1ULL << target_qubit;
    size_t control = 1ULL << control_qubit;

    if (i < total_states) {
        size_t pair = i ^ target;
        if ((i & control) != 0) {
            data_out[i] = data[pair];
        }
        else {
            data_out[i] = data[i];
        }
    }
}

__global__ void Sgate(cuDoubleComplex* data, size_t total_states, int target_qubit) {
    size_t i = blockIdx.x * blockDim.x + threadIdx.x;
    
    size_t target = 1ULL << target_qubit;

    if (i < total_states && (i & target) != 0) {
        cuDoubleComplex factor = make_cuDoubleComplex(0.0, 1.0);
        data[i] = cuCmul(data[i], factor);
    }
}

__global__ void Tgate(cuDoubleComplex* data, size_t total_states, int target_qubit) {
    size_t i = blockIdx.x * blockDim.x + threadIdx.x;
    
    size_t target = 1ULL << target_qubit;

    if (i < total_states && (i & target) != 0) {
        cuDoubleComplex multiply = make_cuDoubleComplex(cos(M_PI/4.0), sin(M_PI/4));
        data[i] = cuCmul(data[i], multiply);
    }
}

__global__ void S_Dager_gate(cuDoubleComplex* data, size_t total_states, int target_qubit) {
    size_t i = blockIdx.x * blockDim.x + threadIdx.x;
    
    size_t target = 1ULL << target_qubit;

    if (i < total_states && (i & target) != 0) {
        cuDoubleComplex factor = make_cuDoubleComplex(0.0, -1.0);
        data[i] = cuCmul(data[i], factor);
    }
}

__global__ void T_Dager_gate(cuDoubleComplex* data, size_t total_states, int target_qubit) {
    size_t i = blockIdx.x * blockDim.x + threadIdx.x;
    
    size_t target = 1ULL << target_qubit;

    if (i < total_states && (i & target) != 0) {
        cuDoubleComplex multiply = make_cuDoubleComplex(cos(M_PI/4.0), -sin(M_PI/4));
        data[i] = cuCmul(data[i], multiply);
    }
}

__global__ void Rz(cuDoubleComplex* data, size_t total_states, int target_qubit, cuDoubleComplex multiplier) {
    size_t i = blockIdx.x * blockDim.x + threadIdx.x;
    
    size_t target = 1ULL << target_qubit;

    if (i < total_states && (i & target) != 0) {
        data[i] = cuCmul(data[i], multiplier);
    }
}

__global__ void Rx(cuDoubleComplex* data, cuDoubleComplex* data_out, size_t total_states, int target_qubit, cuDoubleComplex cosinus, cuDoubleComplex sinus) {
    size_t i = blockIdx.x * blockDim.x + threadIdx.x;
    
    size_t target = 1ULL << target_qubit;

    if (i < total_states) {
        size_t pair = i ^ target;
        cuDoubleComplex data1 = data[i];
        cuDoubleComplex data2 = data[pair];

        data_out[i] = cuCadd(cuCmul(cosinus, data1), cuCmul(sinus, data2));
    }
}

__global__ void Ry(cuDoubleComplex* data, cuDoubleComplex* data_out, size_t total_states, int target_qubit, cuDoubleComplex cosinus, cuDoubleComplex sinus) {
    size_t i = blockIdx.x * blockDim.x + threadIdx.x;
    
    size_t target = 1ULL << target_qubit;

    if (i < total_states) {
        size_t pair = i ^ target;
        cuDoubleComplex data1 = data[i];
        cuDoubleComplex data2 = data[pair];

        if ((i & target) == 0) {
            data_out[i] = cuCsub(cuCmul(cosinus, data1), cuCmul(sinus, data2));
        }
        else {
            data_out[i] = cuCadd(cuCmul(sinus, data2), cuCmul(cosinus, data1));
        }
    }
}

__global__ void CZgate(cuDoubleComplex* data, size_t total_states, int target_qubit, int control_qubit) {
    size_t i = blockIdx.x * blockDim.x + threadIdx.x;
    
    size_t target = 1ULL << target_qubit;
    size_t control = 1ULL << control_qubit;

    if (i < total_states && (i & control) != 0 && (i & target) != 0) {
        cuDoubleComplex factor = make_cuDoubleComplex(-1.0, 0.0);
        data[i] = cuCmul(data[i], factor);
    }
}

__global__ void SWAP(cuDoubleComplex* data, cuDoubleComplex* data_out, size_t total_states, int target_qubit1, int target_qubit2) {
    size_t i = blockIdx.x * blockDim.x + threadIdx.x;
    
    size_t target1 = 1ULL << target_qubit1;
    size_t target2 = 1ULL << target_qubit2;

    if (i < total_states) {
        size_t pair = (i ^ target1) ^ target2;

        if (((i & target1) == 0) != ((i & target2) ==0)) {
            data_out[i] = data[pair];
        }
        else {
            data_out[i] = data[i];
        }
    }
}

__global__ void toffoli(cuDoubleComplex* data, cuDoubleComplex* data_out, size_t total_states, int target_qubit, int control_qubit1, int control_qubit2) {
    size_t i = blockIdx.x * blockDim.x + threadIdx.x;
    
    size_t control = (1ULL << control_qubit1) | (1ULL << control_qubit2);

    if (i < total_states) {
        if ((i & control) == control) {
            size_t target = 1ULL << target_qubit;
            size_t pair = i ^ target;
            data_out[i] = data[pair];
        }
        else {
            data_out[i] = data[i];
        }
    }
}

__global__ void fredkin(cuDoubleComplex* data, cuDoubleComplex* data_out, size_t total_states, int target_qubit1, int target_qubit2, int control_qubit) {
    size_t i = blockIdx.x * blockDim.x + threadIdx.x;
    
    size_t target1 = 1ULL << target_qubit1;
    size_t target2 = 1ULL << target_qubit2;
    size_t control = 1ULL << control_qubit;

    if (i < total_states) {
        if ((i & control) != 0 && ((i & target1) == 0) != ((i & target2) == 0)) {
            size_t pair = (i ^ target1) ^ target2;
            data_out[i] = data[pair];
        }
        else {
            data_out[i] = data[i];
        }
    }
}

__global__ void ControlledPhase(cuDoubleComplex* data, size_t total_states, int target_qubit, int control_qubit, cuDoubleComplex multiplier) {
    size_t i = blockIdx.x * blockDim.x + threadIdx.x;
    
    size_t target = 1ULL << target_qubit;
    size_t control = 1ULL << control_qubit;

    if (i < total_states && (i & control) != 0 && (i & target) != 0) {
        data[i] = cuCmul(data[i], multiplier);
    }
}