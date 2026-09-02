#pragma once
#include <map>
#include <string>
using namespace std;

class StateVector;

class GateCacheManager {
    public:
        GateCacheManager(int qubits);

        StateVector* statevector;
        string current_type = "I";
        map<int, bool> manager1;
        map<int, double> manager2;

        void clear_cache();
        void add_gate(string code, int target, double theta = 0);
        void execute_cache();
};