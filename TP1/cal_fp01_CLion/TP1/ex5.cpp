// By: Gonçalo Leão

#include "exercises.h"

unsigned int sumArray(unsigned int a[], unsigned int n) {
    unsigned int sum = 0;
    for(unsigned int i = 0; i < n; i++) {
        sum += a[i];
    }
    return sum;
}

#include <iostream>

bool isCanonical(unsigned int C[], unsigned int n) {
    //TODO...

    unsigned int greedy_option[n], brute_force_option[n], stock[n];

    //The possible cases where the greedy algorithm can fail are between C[2] + 1 and C[n - 2] + C[n - 1]
    for(int i = C[3] + 1; i <= C[n - 2] + C[n - 1]; i++){
        for(int temp = 0; temp < n; temp++){
            stock[temp] = i;
        }
        if(changeMakingBF(C, stock, n, i, brute_force_option)){
            if(changeMakingGreedy(C, stock, n, i, greedy_option)) {
                for (int j = 0; j < n; j++) if (brute_force_option[j] != greedy_option[j]) return false;
            }
            else{
                return false;
            }
        }
    }
    return true;
}


/// TESTS ///
#include <gtest/gtest.h>
TEST(TP1_Ex5, canonicalTrue) {
    std::cout << "EX5" << std::endl;
    unsigned int C[] = {1,2,5};
    EXPECT_EQ(isCanonical(C,3), true);

    unsigned int C2[] = {1,2,5,10};
    EXPECT_EQ(isCanonical(C2,4), true);
}

TEST(TP1_Ex5, canonicalFalse) {
    unsigned int C[] = {1,4,5};
    EXPECT_EQ(isCanonical(C,3), true);
}
