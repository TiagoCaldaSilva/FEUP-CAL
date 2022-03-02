#include "exercises.h"
#include <algorithm>

int sumAll(int A[], int &start, int &end){
    int sum, middle = (end - start) / 2;

    int sumLeft, sumRight, maxLeft = middle, maxRight = middle;
    bool first;

    sum = 0;
    sumLeft = 0;
    first = true;
    for(int i = middle; i >= start; i--){
        sum += A[i];
        if(first | (sum > sumLeft)){
            first = false;
            sumLeft = sum;
            maxLeft = i;
        }
    }
    start = maxLeft;

    sum = 0;
    sumRight = 0;
    first = true;
    for(int i = middle + 1; i <= end; i++){
        sum += A[i];
        if(first | (sum > sumRight)){
            first = false;
            sumRight = sum;
            maxRight = i;
        }
    }
    end = maxRight;

    return sumLeft + sumRight;
}

int maxSubsequenceRec(int A[], unsigned int n, int &i, int &j){
    //TODO
    if(n == 1){ return A[i]; }
    if(n == 2){
        if((A[i] + A[j]) > std::max(A[i], A[j])) return A[i] + A[j];
        else if(A[i] > A[j]){ j = i; return A[i];}
        else { i = j; return A[j];}
    }
    else{
        int cross_i = i, cross_j = j;
        int sum_cross = sumAll(A, cross_i, cross_j);

        int middle_l = (i + j) / 2, middle_r = middle_l + 1;

        int min_left = i, min_right = middle_r, max_left = middle_l, max_right = j;
        int sum_left = maxSubsequenceRec(A, (max_left - min_left) + 1, min_left, max_left);
        int sum_right = maxSubsequenceRec(A, (max_right - min_right) + 1, min_right, max_right);

        if(sum_left > sum_right && sum_left > sum_cross){ i = min_left; j = max_left; return sum_left;}
        else if(sum_right > sum_cross){ i = min_right; j = max_right; return sum_right; }
        i = cross_i; j = cross_j;
        return sum_cross;
    }
}

int maxSubsequenceDC(int A[], unsigned int n, int &i, int &j) {
    //TODO
    i = 0; j = (int)n - 1;
    return maxSubsequenceRec(A, n, i, j);
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP3_Ex2, testMaxSubsequence) {
    int A1[] = {1, 2, 3, 4};
    unsigned int n1 = 4;
    int i, j;
    EXPECT_EQ(maxSubsequenceDC(A1,n1,i,j), 10);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 3);

    int A2[] = {2, -1, -3, 4};
    unsigned int n2 = 4;
    EXPECT_EQ(maxSubsequenceDC(A2,n2,i,j), 4);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 3);

    int A3[] = {2, -1, 3, 4};
    unsigned int n3 = 4;
    EXPECT_EQ(maxSubsequenceDC(A3,n3,i,j), 8);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 3);

    int A4[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int n4 = 9;
    EXPECT_EQ(maxSubsequenceDC(A4,n4,i,j), 6);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 6);
}
