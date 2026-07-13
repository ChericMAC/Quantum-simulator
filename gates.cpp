#define _USE_MATH_DEFINES
#include "gates.h"
#include <math.h>
#include <cmath>
#include <numbers>

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

void cnot(vector<comp>& data, int target_qubit, int control_qubit) {
    int target = 1 << target_qubit;
    int control = 1 << control_qubit;

    for (int i = 0; i < data.size(); i++) {
        if ((i & control) != 0 && (i & target) == 0) {
            int pair = i | target;
            comp provisional = data[i];

            data[i] = data[pair];
            data[pair] = provisional;
        }
    }
}

void Sgate(vector<comp>& data, int target_qubit) {
    int target = 1 << target_qubit;

    for (int i = 0; i < data.size(); i++) {
        if ((i & target) != 0) {
            data[i] *= comp(0.0, 1.0);
        }
    }
}

void Tgate(vector<comp>& data, int target_qubit) {
    int target = 1 << target_qubit;
    comp multiply = comp(cos(M_PI/4.0), sin(M_PI/4));

    for (int i = 0; i < data.size(); i++) {
        if ((i & target) != 0) {
            data[i] *= multiply;
        }
    }
}

void S_Dager_gate(vector<comp>& data, int target_qubit) {
    int target = 1 << target_qubit;

    for (int i = 0; i < data.size(); i++) {
        if ((i & target) != 0) {
            data[i] *= comp(0.0, -1.0);
        }
    }
}

void T_Dager_gate(vector<comp>& data, int target_qubit) {
    int target = 1 << target_qubit;
    comp multiply = comp(cos(M_PI/4.0), -sin(M_PI/4));

    for (int i = 0; i < data.size(); i++) {
        if ((i & target) != 0) {
            data[i] *= multiply;
        }
    }
}

void Rz(vector<comp>& data, int target_qubit, double theta) {
    int target = 1 << target_qubit;
    comp multiplier = comp(cos(theta/2.0), sin(theta/2.0));

    for (int i = 0; i < data.size(); i++) {
        if ((i & target) != 0) {
            data[i] *= multiplier;
        }
    }
}

void Rx(vector<comp>& data, int target_qubit, double theta) {
    int target = 1 << target_qubit;
    double cosinus = cos(theta/2.0);
    double sinus = sin(theta/2.0);

    for (int i = 0; i < data.size(); i++) {
        if ((i & target) == 0) {
            int pair = i | target;
            comp data1 = data[i];
            comp data2 = data[pair];

            data[i] = cosinus * data1 + comp(0.0, -sinus) * data2;
            data[pair] = cosinus * data2 + comp(0.0, -sinus) * data1;
        }
    }
}
void Ry(vector<comp>& data, int target_qubit, double theta) {
    int target = 1 << target_qubit;
    double cosinus = cos(theta/2.0);
    double sinus = sin(theta/2.0);

    for (int i = 0; i < data.size(); i++) {
        if ((i & target) == 0) {
            int pair = i | target;
            comp data1 = data[i];
            comp data2 = data[pair];

            data[i] = cosinus * data1 - sinus * data2;
            data[pair] = sinus * data1 + cosinus * data2;
        }
    }
}

void CZgate(vector<comp>& data, int target_qubit, int control_qubit) {
    int target = 1 << target_qubit;
    int control = 1 << control_qubit;

    for (int i = 0; i < data.size(); i++) {
        if ((i & control) != 0 && (i & target) != 0) {
            data[i] *= -1.0;
        }
    }
}

void SWAP(vector<comp>& data, int target_qubit1, int target_qubit2) {
    int target1 = 1 << target_qubit1;
    int target2 = 1 << target_qubit2;

    for (int i = 0; i < data.size(); i++) {
        if ((i & target1) == 0 && (i & target2) !=0) {
            int pair = (i | target1) ^ target2;
            comp provisional = data[i];

            data[i] = data[pair];
            data[pair] = provisional;
        }
    }
}

void toffoli(vector<comp>& data, int target_qubit, int control_qubit1, int control_qubit2) {
    int target = 1 << target_qubit;
    int control = (1 << control_qubit1) | (1 << control_qubit2);

    for (int i = 0; i < data.size(); i++) {
        if ((i & control) == control && (i & target) == 0) {
            int pair = i | target;
            comp provisional = data[i];

            data[i] = data[pair];
            data[pair] = provisional;
        }
    }
}

void fredkin(vector<comp>& data, int target_qubit1, int target_qubit2, int control_qubit) {
    int target1 = 1 << target_qubit1;
    int target2 = 1 << target_qubit2;
    int control = 1 << control_qubit;

    for (int i = 0; i < data.size(); i++) {
        if ((i & control) != 0 && (i & target1) == 0 && (i & target2) != 0) {
            int pair = (i | target1) ^ target2;
            comp provisional = data[i];

            data[i] = data[pair];
            data[pair] = provisional;
        }
    }
}