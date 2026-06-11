#include "gates.h"
#include <cmath>

void pauliX(vector<comp>& data, int target_qubit) {
    int target = 1 << target_qubit;

    for (int i = 0; i < data.size(); i++) {
        if ((i & target) == 0) {
            int pair = i | target;
            comp provisional = data[i];
            data[i] = data[pair];
            data[pair] = provisional;
        }
    }
}

void pauliY(vector<comp>& data, int target_qubit) {
    int target = 1 << target_qubit;

    for (int i = 0; i < data.size(); i++) {
        if ((i & target) == 0) {
            int pair = i | target;
            comp provisional = data[i];
            data[i] = comp(0, -1.0) * data[pair];
            data[pair] = comp(0, 1.0) * provisional;
        }
    }
}

void pauliZ(vector<comp>& data, int target_qubit) {
    int target = 1 << target_qubit;

    for (int i = 0; i < data.size(); i++) {
        if ((i & target) != 0) {
            data[i] *= -1.0;
        }
    }
}

void hadamard(vector<comp>& data, int target_qubit) {
    int target = 1 << target_qubit;

    for (int i = 0; i < data.size(); i++) {
        if ((i & target) == 0) {
            int pair = i | target;
            comp data1 = data[i];
            comp data2 = data[pair];

            data[i] = (1.0/sqrt(2)) * (data1 + data2);
            data[pair] = (1.0/sqrt(2)) * (data1 - data2);
        }
    }
}

void cnot(vector<comp>& data, int target_qubit, int control_cubit) {
    int target = 1 << target_qubit;
    int control = 1 << control_cubit;

    for (int i = 0; i < data.size(); i++) {
        if ((i & control) != 0 && (i & target) == 0) {
            int pair = i | target;
            comp provisional = data[i];
            data[i] = data[pair];
            data[pair] = provisional;
        }
    }
}