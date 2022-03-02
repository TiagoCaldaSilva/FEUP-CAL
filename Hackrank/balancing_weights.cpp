#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <climits>

int main() {
    int total_weight;
    std::string temp;

    while(getline(std::cin, temp, '\n')) {
        int temporary_value;
        int max_value = 0;
        int min_value = INT_MAX;
        std::vector<std::vector<int>> solutions;

        // Read values
        std::stringstream ss(temp);
        ss >> total_weight;

        if(total_weight == 0) break;

        std::vector<int> weights_available(total_weight, 0); // Stock of weights
        std::vector<std::vector<std::vector<int>>> weights(total_weight, solutions); // Various solutions

        while(ss >> temporary_value) {
            if(temporary_value > total_weight) continue;
            weights_available[temporary_value - 1] += 1;
            if(temporary_value > max_value) max_value = temporary_value;
            if(temporary_value < min_value) min_value = temporary_value;
        }

        if(min_value <= total_weight) {

            // Processing
            for (int current_weight = 0; current_weight < max_value; current_weight++) {
                if (weights_available[current_weight] == 0) continue;
                for (int i = 1; i <= total_weight; i++) {
                    int need = i - current_weight - 1;
                    if (need < 0) { // Heavier Weight
                        continue;
                    }
                    if (need == 0) {
                        std::vector<int> solution(total_weight, 0);
                        solution[current_weight] = 1;
                        weights[i - 1].push_back(solution);
                        continue;
                    }

                    if(weights[need - 1].empty()) continue;
                    for(int k = 0; k < (int)weights[need - 1].size(); k++) {
                        if(weights_available[current_weight] - 1 - weights[need - 1][k][current_weight] >= 0) {
                            std::vector<int> solution = weights[need - 1][k];
                            solution[current_weight] += 1;
                            weights[i - 1].push_back(solution);
                        }
                    }
                }
            }
        }
        std::cout << "Weights for " << total_weight << ":" << std::endl;
        if(weights[total_weight - 1].empty()) {
            std::cout << "No solutions" << std::endl;
        } else {
            for (int i = weights[total_weight - 1].size() - 1; i >= 0; i--) {
                bool first = true;
                for (int k = (int)weights[total_weight - 1][i].size() - 1; k >= 0; k--) {
                    for (int x = 0; x < weights[total_weight - 1][i][k]; x++) {
                        if (!first) std::cout << " + ";
                        else first = false;
                        std::cout << k + 1;
                    }
                }
                std::cout << std::endl;
            }
        }
    }

    return 0;
}