#include "run.cuh"
#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <string>
#include <bitset>
#include <cstdlib>

void generate_results(vector<cuDoubleComplex>& data, int num_qubits, int shots, char list, char chart) {
    size_t total_states = data.size();
    vector<double> prob(total_states);

    for (int i = 0; i < total_states; i++) {
        prob[i] = (data[i].x * data[i].x) + (data[i].y * data[i].y);
    }

    random_device rd;
    mt19937 gen(rd());
    discrete_distribution<int> dist(prob.begin(), prob.end());

    vector<int> counts(total_states, 0);
    for (int i = 0; i < shots; i++) {
        int sample = dist(gen);
        counts[sample]++;
    }

    fstream file;

    string path = "results/output.csv";

    file.open(path, ios::out | ios::trunc);

    if (list == 'y') {
        cout << "===== RESULTS =====" << endl;
    }

    for (int i = 0; i < total_states; i++) {
        if (counts[i] > 0) {
            string binary_representation = bitset<32>(i).to_string().substr(32-num_qubits);

            if (list == 'y') {
            cout << binary_representation << ": " << counts[i] << endl;
            }
            
            file << binary_representation << "," << counts[i] << endl;
    
        }
    }

    file.close();

    if (list == 'y') {
    cout << "===================" << endl;
    }
    if (chart == 'y') {
        #ifdef _WIN32
            int result = system("python auxiliar/chart.py");
        #else
            int result = system("python3 auxiliar/chart.py");
        #endif
    }
}