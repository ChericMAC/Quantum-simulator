#ifndef STATEVECTOR_CUH
#define STATEVECTOR_CUH

#include <vector>
#include <complex>
#include <cuComplex.h>
using namespace std;

class StateVector {
    private:
        int num_qubits;
        size_t total_states;
        cuDoubleComplex* data = nullptr;
        cuDoubleComplex* data_out = nullptr;

    public:
        StateVector(int qubits);
        ~StateVector();

        void display();

        void apply_pauliX(int target_qubit);
        void apply_pauliY(int target_quubit);
        void apply_pauliZ(int target_qubit);

        void apply_hadamard(int target_qubit);

        void apply_cnot(int target_qubit, int control_qubit);

        void apply_Sgate(int target_qubit);
        void apply_Tgate(int target_qubit);
        void apply_S_Dager_gate(int target_qubit);
        void apply_T_Dager_gate(int target_qubit);

        void apply_Rz(int target_qubit, double theta);
        void apply_Rx(int target_qubit, double theta);
        void apply_Ry(int target_qubit, double theta);

        void apply_CZgate(int target_qubit, int control_qubit);
        void apply_swap(int target_qubit1, int target_qubit2);

        void apply_toffoli(int target_qubit, int control_qubit1, int control_qubit2);
        void apply_fredkin(int target_qubit1, int target_qubit2, int control_qubit);
        
        void apply_ControlledPhase(int target_qubit, int control_qubit, double theta);

        void apply_generate_results(int shots, char list, char chart);

        vector<cuDoubleComplex> get_statevector();
};

#endif