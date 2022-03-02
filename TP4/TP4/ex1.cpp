#include "exercises.h"

//O(n) && S(0)
unsigned long factorialRecurs(unsigned long n) {
    if (n == 0) return 1;
    return n * factorialRecurs((n - 1));
}

//O(n) && S(n)
unsigned long factorialDP(unsigned long n) {
    int *numbers = new (std::nothrow) int[n + 1];
    numbers[0] = 1;
    for(int i = 1; i <= n; i++){ numbers[i] = numbers[i - 1] * i; }
    int result = numbers[n];
    delete[] numbers;
    return result;
}


/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex1, FactorialTest) {
    EXPECT_EQ(1,factorialRecurs(0));
    EXPECT_EQ(1,factorialRecurs(1));
    EXPECT_EQ(2,factorialRecurs(2));
    EXPECT_EQ(6,factorialRecurs(3));
    EXPECT_EQ(24,factorialRecurs(4));
    EXPECT_EQ(120,factorialRecurs(5));
    EXPECT_EQ(3628800,factorialRecurs(10));

    EXPECT_EQ(1,factorialDP(0));
    EXPECT_EQ(1,factorialDP(1));
    EXPECT_EQ(2,factorialDP(2));
    EXPECT_EQ(6,factorialDP(3));
    EXPECT_EQ(24,factorialDP(4));
    EXPECT_EQ(120,factorialDP(5));
    EXPECT_EQ(3628800,factorialDP(10));
}
