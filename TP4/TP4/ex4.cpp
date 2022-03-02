#include "exercises.h"
#include <iostream>
#include <chrono>

std::string calcSum(int sequence[], unsigned long n) {
    // TODO
    auto sum = new (std::nothrow) int[n];
    auto index = new (std::nothrow) int[n];

    for(int i = 0; i < n; i++){
        sum[i] = INT_MAX;
    }

    for(int i = 0; i < n; i++){
        int actual_sum= 0;
        for(int j = i; j < n; j++){
            actual_sum += sequence[j];
            if(sum[j - i] > actual_sum){
                sum[j - i] = actual_sum;
                index[j - i] = i;
            }
        }
    }

    std::string result;
    for(int i = 0; i < n; i++){
        result += std::to_string(sum[i]) + "," + std::to_string(index[i]) + ";";
    }
    return result;
}

void testPerformanceCalcSum() {
    //TODO
    srand(time(0));

    for (unsigned j = 1000; j <= 5000; j += 500) {
        int *n = new int[j];
        for (int i = 0; i < j; ++i)
            n[i] = (rand() % 10) + 1;

        auto start = std::chrono::high_resolution_clock::now();
        calcSum(n, j);
        auto finish = std::chrono::high_resolution_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
        std::cout << "Sequence of " << j << " elements calculated in " << ms << " ms" << std::endl;

        delete[] n;
    }
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex4, CalcSumArrayTest) {
    int sequence[5] = {4,7,2,8,1};
    int sequence2[9] = {6,1,10,3,2,6,7,2,4};

    EXPECT_EQ("1,4;9,1;11,2;18,1;22,0;",calcSum(sequence, 5));
    EXPECT_EQ("1,1;5,3;11,3;16,1;20,3;24,3;31,1;35,1;41,0;",calcSum(sequence2, 9));

	testPerformanceCalcSum();
}
