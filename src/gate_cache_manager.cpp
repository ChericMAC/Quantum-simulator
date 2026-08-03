#define _USE_MATH_DEFINES
#include "gate_cache_manager.h"
#include <iostream>

GateCacheManager::GateCacheManager(int qubits) : statevector(qubits) {   
}

void GateCacheManager::clear_cache() {
    manager1.clear();
    manager2.clear();
}

void GateCacheManager::execute_cache() {
    if (current_type == "RZ") {
        for (auto& [target, theta] : manager2) {
            statevector.apply_Rz(target, theta);
        }
    }

    else if (current_type == "RX") {
        for (auto& [target, theta] : manager2) {
            statevector.apply_Rx(target, theta);
        }
    }
    
    else if (current_type == "RY") {
        for (auto& [target, theta] : manager2) {
            statevector.apply_Ry(target, theta);
        }
    }

    else if (current_type == "PX") {
        for (auto& [target, state] : manager1) {
            statevector.apply_pauliX(target);
        }
    }

    else if (current_type == "PY") {
        for (auto& [target, state] : manager1) {
            statevector.apply_pauliY(target);
        }
    }

    else if (current_type == "H") {
        for (auto& [target, state] : manager1) {
            statevector.apply_hadamard(target);
        }
    }
    clear_cache();
}

void GateCacheManager::add_gate(string code, int target, double theta) {
    if (code == current_type) {
        if (code == "RZ" || code == "RY" || code == "RX") {
            manager2[target] += theta;
            if (abs(manager2[target]) < 1e-9) manager2.erase(target);
        }
        else {
            manager1[target] = !manager1[target];
            if (!manager1[target]) manager1.erase(target);
        }
    }
    else {
        execute_cache();

        if (code == "PX" || code == "PY"|| code == "H") {
            current_type = code;
            manager1[target] = true;
        }
        else{
            current_type = code;
            manager2[target] = theta;
        }
    }
}