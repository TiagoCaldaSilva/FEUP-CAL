#include "exercises.h"

unsigned long s_recursive(unsigned int n, unsigned int k) {
    // TODO
    if(k > n) return 0;
    if(k == n || k == 1) return 1;
    return s_recursive(n-1, k-1) + k * s_recursive(n-1, k);
}

unsigned long b_recursive(unsigned int n) {
    // TODO
    unsigned long sum = 0;
    for(int i = 1; i <= n; i++){
        sum += s_recursive(n, i);
    }
    return sum;
}

#include <vector>
unsigned long s_dynamic(unsigned int n, unsigned int k) {
    // TODO
    if(n == k) return 1;
    int maxj = n - k;
    std::vector<int> c(maxj + 1, 1);
    std::vector<int> old(maxj + 1, 1);
    int ind = 1;
    for(int row = 1; row <= k; row++){
        ind++;
        for(int col = 1; col <= maxj; col++) {
            old[col - 1] = c[col - 1];
            c[col] += ind * c[col - 1];
        }
        if(row != k) old[maxj] = c[maxj];
    }
    return old[maxj];
}

unsigned long b_dynamic(unsigned int n) {
    // TODO
    unsigned long sum = 0;
    for(int i = 1; i <= n; i++){
        sum += s_recursive(n, i);
    }
    return sum;
}


/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex5, testPartitioningRecursive) {
    EXPECT_EQ(1,s_recursive(3,3));
    EXPECT_EQ(3025,s_recursive(9,3));
    EXPECT_EQ(22827,s_recursive(10,6));

    EXPECT_EQ(5,b_recursive(3));
    EXPECT_EQ(203,b_recursive(6));
    EXPECT_EQ(1382958545,b_recursive(15));
}

TEST(TP4_Ex5, testPartitioningDynamic) {
    EXPECT_EQ(3, s_dynamic(3, 2));
    EXPECT_EQ(1,s_dynamic(3,3));
    EXPECT_EQ(15, s_dynamic(5, 2));
    EXPECT_EQ(25, s_dynamic(5, 3));
    EXPECT_EQ(10, s_dynamic(5, 4));

    EXPECT_EQ(3025,s_dynamic(9,3));
    EXPECT_EQ(22827,s_dynamic(10,6));

    EXPECT_EQ(5,b_dynamic(3));
    EXPECT_EQ(203,b_dynamic(6));
    EXPECT_EQ(1382958545,b_dynamic(15));
}
