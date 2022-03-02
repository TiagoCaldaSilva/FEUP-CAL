// By: Gonçalo Leão

#include "exercises.h"

int maxSubsequence(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
    //TODO...
    int maxSum = A[0];
    bool first = false;
    int sum;
    unsigned int a, b, c;
    for(a = 0; a < n; a++){
        for(b = 1; b <= n - a; b++){
            sum = 0;
            for(c = a; c < a + b; c++){
                sum += A[c];
            }
            if(sum > maxSum){ maxSum = sum; i = a; j = c - 1; }
        }
    }
    return maxSum;
}



/// TESTS ///
#include <gtest/gtest.h>

TEST(TP1_Ex2, maxSubsequence) {

    std::cout << "EX2" << std::endl;

    int A[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int n = 9;
    unsigned int i, j;
    EXPECT_EQ(maxSubsequence(A,n,i,j), 6);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 6);
}
