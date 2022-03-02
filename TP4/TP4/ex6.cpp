#include "exercises.h"

#include <chrono>
#include <iostream>
#include <algorithm>

int maxSubsequenceDP(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
    // TODO
    int best_sum = INT_MIN, current_sum = INT_MIN;
    int i_current = 0, j_current = 0;


    for(int index = 0; index < n; index++){

        // If the current number is greater than the sum
        if(A[index] > current_sum + A[index]) {
            current_sum = A[index];
            i_current = index;
            j_current = index;
            if(current_sum > best_sum) {
                i = i_current;
                j = j_current;
                best_sum = current_sum;
            }
        }

        // If the sum between the current sum and the actual number are greater than que current sum
        // and the actual number is at the right position of the last number added to the current sum
        else if( current_sum + A[index] > current_sum && (index -j_current) == 1) {
            j_current += 1;
            current_sum += A[index];
            if(current_sum > best_sum) {
                i = i_current;
                j = j_current;
                best_sum = current_sum;
            }
        }

        //Add to the current sum
        else {
            j_current += 1;
            current_sum += A[index];
        }
    }
    for(int k = 0; k < n; k++) {
        if( k >= i && k <= j) A[k] = 1;
        else A[k] = 0;
    }
    return best_sum;
}

int maxSubsequenceBF(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
    // TODO
    i = 0; j = 0;
    int best_sum = INT_MIN;
    for(int first = 0; first < n; first++) {
        int sum = A[first];
        if(sum > best_sum){
            i = first; j = first; best_sum = sum;
        }
        for(int last = first + 1; last < n; last++){
            sum += A[last];
            if(sum > best_sum){
                i = first; j = last; best_sum = sum;
            }
        }
    }

    for(unsigned int k = i; k <= j; k++) {
        A[k] = 1;
    }

    return best_sum;
	// Copy-paste your solution for ex2 of TP1 HERE
	return 0;
}

int sumAll(int A[], unsigned int &start, unsigned int &end){
    int sum, middle = (end - start) / 2;

    int sumLeft, sumRight, maxLeft = middle, maxRight = middle;
    bool first;

    sum = 0;
    sumLeft = 0;
    first = true;
    int st = start;
    for(int i = middle; i >= st; i--){
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
int maxSubsequenceRec(int A[], unsigned int n, unsigned int &i, unsigned int &j){
    //TODO
    if(n == 1){ return A[i]; }
    if(n == 2){
        if((A[i] + A[j]) > std::max(A[i], A[j])) return A[i] + A[j];
        else if(A[i] > A[j]){ j = i; return A[i];}
        else { i = j; return A[j];}
    }
    else{
        unsigned int cross_i = i, cross_j = j;
        int sum_cross = sumAll(A, cross_i, cross_j);

        unsigned int middle_l = (i + j) / 2, middle_r = middle_l + 1;

        unsigned int min_left = i, min_right = middle_r, max_left = middle_l, max_right = j;
        int sum_left = maxSubsequenceRec(A, (max_left - min_left) + 1, min_left, max_left);
        int sum_right = maxSubsequenceRec(A, (max_right - min_right) + 1, min_right, max_right);

        if(sum_left > sum_right && sum_left > sum_cross){ i = min_left; j = max_left; return sum_left;}
        else if(sum_right > sum_cross){ i = min_right; j = max_right; return sum_right; }
        i = cross_i; j = cross_j;
        return sum_cross;
    }
}
int maxSubsequenceDC(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
    // TODO
    // Copy-paste your solution for ex2 of TP3 HERE
    i = 0; j = (int)n - 1;
    return maxSubsequenceRec(A, n, i, j);
}

void testPerformanceMaxSubsequence() {
    // TODO
    int A1[] = {1, 2, 3, 4};
    int A2[] = {2, -1, -3, 4};
    int A3[] = {2, -1, 3, 4};
    int A4[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int i, j;

    std::cout << "Brute Force" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    maxSubsequenceBF(A1, 4, i, j);
    maxSubsequenceBF(A2, 4, i, j);
    maxSubsequenceBF(A3, 4, i, j);
    maxSubsequenceBF(A4, 9, i, j);
    auto finish = std::chrono::high_resolution_clock::now();

    auto nBF = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();
    std::cout << "Time Elapsed: " << nBF << " ns" << std::endl;

    std::cout << "Divide & Conquer" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    maxSubsequenceDC(A1, 4, i, j);
    maxSubsequenceDC(A2, 4, i, j);
    maxSubsequenceDC(A3, 4, i, j);
    maxSubsequenceDC(A4, 9, i, j);
    finish = std::chrono::high_resolution_clock::now();

    auto nDC = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();
    std::cout << "Time Elapsed: " << nDC << " ns" << std::endl;

    std::cout << "Dynamic Programming" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    maxSubsequenceDP(A1, 4, i, j);
    maxSubsequenceDP(A2, 4, i, j);
    maxSubsequenceDP(A3, 4, i, j);
    maxSubsequenceDP(A4, 9, i, j);
    finish = std::chrono::high_resolution_clock::now();

    auto nDP = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();
    std::cout << "Time Elapsed: " << nDP << " ns" << std::endl;

}


/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex6, testMaxSubsequence) {
    int A1[] = {1, 2, 3, 4};
    unsigned int n1 = 4;
    unsigned int i, j;
    EXPECT_EQ(maxSubsequenceDP(A1,n1,i,j), 10);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 3);

    int A2[] = {2, -1, -3, 4};
    unsigned int n2 = 4;
    EXPECT_EQ(maxSubsequenceDP(A2,n2,i,j), 4);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 3);

    int A3[] = {2, -1, 3, 4};
    unsigned int n3 = 4;
    EXPECT_EQ(maxSubsequenceDP(A3,n3,i,j), 8);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 3);

    int A4[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int n4 = 9;
    EXPECT_EQ(maxSubsequenceDP(A4,n4,i,j), 6);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 6);

    testPerformanceMaxSubsequence();
}
