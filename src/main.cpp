#define _USE_MATH_DEFINES
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include "gate_cache_manager.h"
using namespace std;

int main() {
    cout << "Qunatum computer simulator. Type 'q' to exit, 'h' for information, 'd' to StateVector current state and 'r' to run the circuit." << endl;
    cout << "How many qubits do you want to simulate? (1-20): ";
    int qubits;
    cin >> qubits;
    cin.ignore();
    GateCacheManager cache(qubits);

    string last_command = "";
    string command;
    while (true) {
        cout << "quantum-cli> ";
        
        if (!getline(cin, command)) break;

        if (command == "q") break;

        else if (command == "h") {
            cout << endl;
            cout << "   - PauliX: PX target_qubit[int]" << endl;
            cout << "   - PauliY: PY target_qubit[int]" << endl;
            cout << "   - PauliZ: PZ target_qubit[int]" << endl;
            cout << "   - Hadamard: H target_qubit[int]" << endl;
            cout << "   - CNOT: CNOT target_qubit[int] control_qubit[int]" << endl;
            cout << "   - S Gate: S target_qubit[int]" << endl;
            cout << "   - T Gate: T target_qubit[int]" << endl;
            cout << "   - S Dager Gate: SD target_qubit[int]" << endl;
            cout << "   - T Dager Gate: TD target_qubit[int]" << endl;
            cout << "   - Rx: RX target_qubit[int] theta[double]" << endl;
            cout << "   - Ry: RY target_qubit[int] theta[double]" << endl;
            cout << "   - Rz: RZ target_qubit[int] theta[double]" << endl;
            cout << "   - CZ Gate: CZG target_qubit[int] control_qubit[int]" << endl;
            cout << "   - SWAP: SWAP target_qubit1[int] target_qubit2[int]" << endl;
            cout << "   - Toffoli: TFL target_qubit[int] control_qubit1[int] control_qubit2[int]" << endl;
            cout << "   - Fredkin: FK target_qubit1[int] target_qubit2[int] control_qubit[int]" << endl;
            continue;
        }

        else if (command == "d") {
            cout << endl;
            cache.execute_cache();
            cache.statevector.display();
            continue;
        }
        
        else if (command == "r") {
            cout << endl;
            cache.execute_cache();
            cache.statevector.apply_generate_results();
            break;
        }

        try {
            stringstream ss(command);
            string header;
            ss >> header;

            if (header == "PX") {
                int target;
                char dumper;

                if (!(ss >> target)) {
                    throw runtime_error("Pauli X gate must contain one integer value. Example: PX 2");
                }

                else if (ss >> dumper) {
                    throw runtime_error("Format error. Excesive parameters.");
                }

                cache.add_gate(header, target);
            }
            
            else if (header == "PY") {
                int target;
                char dumper;

                if (!(ss >> target)) {
                    throw runtime_error("Pauli Y gate must contain one integer value. Example: PY 2");
                }

                else if (ss >> dumper) {
                    throw runtime_error("Format error. Excesive parameters.");
                }

                cache.add_gate(header, target);            
            }
            
            else if (header == "PZ") {
                int target;
                char dumper;

                if (!(ss >> target)) {
                    throw runtime_error("Pauli Z gate must contain one integer value. Example: PZ 2");
                }

                else if (ss >> dumper) {
                    throw runtime_error("Format error. Excesive parameters.");
                }

                cache.add_gate("RZ", target, 2 * M_PI);       
            }

            else if (header == "H") {
                int target;
                char dumper;

                if (!(ss >> target)) {
                    throw runtime_error("Hadamard gate must contain one integer value. Example: H 2");
                }

                else if (ss >> dumper) {
                    throw runtime_error("Format error. Excesive parameters.");
                }

                cache.add_gate(header, target);
            }

            else if (header == "CNOT") {
                int control, target;
                char dump;

                if (!(ss >> target >> control)) {
                    throw runtime_error("CNOT gate requires 2 parameters (control & target). Examlpe: CNOT 2 1");
                }
                if (ss >> dump) {
                    throw runtime_error("Format error. Excesive parameters.");
                }
                cache.execute_cache();
                cache.statevector.apply_cnot(target, control);
            }

            else if (header == "S") {
                int target;
                char dumper;

                if (!(ss >> target)) {
                    throw runtime_error("S gate must contain one integer value. Example: S 2");
                }

                else if (ss >> dumper) {
                    throw runtime_error("Format error. Excesive parameters.");
                }
                cache.add_gate("RZ", target, M_PI);
            }

            else if (header == "T") {
                int target;
                char dumper;

                if (!(ss >> target)) {
                    throw runtime_error("T gate must contain one integer value. Example: T 2");
                }

                else if (ss >> dumper) {
                    throw runtime_error("Format error. Excesive parameters.");
                }
                cache.add_gate("RZ", target, M_PI / 2);
            }

            else if (header == "SD") {
                int target;
                char dumper;

                if (!(ss >> target)) {
                    throw runtime_error("S dager gate must contain one integer value. Example: SD 2");
                }

                else if (ss >> dumper) {
                    throw runtime_error("Format error. Excesive parameters.");
                }
                cache.add_gate("RZ", target, -M_PI);
            }

            else if (header == "TD") {
                int target;
                char dumper;

                if (!(ss >> target)) {
                    throw runtime_error("T dager gate must contain one integer value. Example: TD 2");
                }

                else if (ss >> dumper) {
                    throw runtime_error("Format error. Excesive parameters.");
                }
                cache.add_gate("RZ", target, -M_PI / 2);
            }

            else if (header == "RX") {
                int target;
                double theta;
                char dump;

                if (!(ss >> target >> theta)) {
                    throw runtime_error("RX gate requires 2 parameters (target & theta). Example: RX 2 22.5");
                }
                if (ss >> dump) {
                    throw runtime_error("Format error. Excesive parameters.");
                }

                cache.add_gate(header, target, theta);
            }

            else if (header == "RY") {
                int target;
                double theta;
                char dump;

                if (!(ss >> target >> theta)) {
                    throw runtime_error("RX gate requires 2 parameters (target & theta). Example: RX 2 22.5");
                }
                if (ss >> dump) {
                    throw runtime_error("Format error. Excesive parameters.");
                }

                cache.add_gate(header, target, theta);
            }

            else if (header == "RZ") {
                int target;
                double theta;
                char dump;

                if (!(ss >> target >> theta)) {
                    throw runtime_error("RX gate requires 2 parameters (target & theta). Example: RX 2 22.5");
                }
                if (ss >> dump) {
                    throw runtime_error("Format error. Excesive parameters.");
                }

                cache.add_gate(header, target, theta);
            }

            else if (header == "CZG") {
                int control, target;
                char dump;

                if (!(ss >> target >> control)) {
                    throw runtime_error("CZ gate requires 2 parameters (control & target). Examlpe: CZG 2 1");
                }
                if (ss >> dump) {
                    throw runtime_error("Format error. Excesive parameters.");
                }

                cache.execute_cache();
                cache.statevector.apply_CZgate(target, control);
            }

            else if (header == "SWAP") {
                int target1, target2;
                char dump;

                if (!(ss >> target1 >> target2)) {
                    throw runtime_error("SWAP gate requires 2 parameters (target1 & target2). Examlpe: SWAP 2 1");
                }
                if (ss >> dump) {
                    throw runtime_error("Format error. Excesive parameters.");
                }

                cache.execute_cache();
                cache.statevector.apply_swap(target1, target2);
            }

            else if (header == "TFL") {
                int control1, control2, target;
                char dump;

                if (!(ss >> target >> control1 >> control2)) {
                    throw runtime_error("Toffoli gate requires 3 parameters (target, control1, control2). Examlpe: TFL 2 1 0");
                }
                if (ss >> dump) {
                    throw runtime_error("Format error. Excesive parameters.");
                }

                cache.execute_cache();
                cache.statevector.apply_toffoli(target, control1, control2);
            }

            else if (header == "FK") {
                int control, target1, target2;
                char dump;

                if (!(ss >> target1 >> target2 >> control)) {
                    throw runtime_error("Fredkin gate requires 3 parameters (target1, target2, control). Examlpe: TFL 2 1 0");
                }
                if (ss >> dump) {
                    throw runtime_error("Format error. Excesive parameters.");
                }

                cache.execute_cache();
                cache.statevector.apply_fredkin(target1, target2, control);
            }
            
            else {
                throw runtime_error("Non-existing command. Type h to get the list of available gates.");
            }

        }
        catch (const runtime_error& e) {
            cout << "Syntaxis error: " << e.what() << endl;
        }
    }

    cout << "Simulation finished" << endl;
    return 0;
}