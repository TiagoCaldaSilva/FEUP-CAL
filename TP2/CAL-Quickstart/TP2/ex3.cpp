#include "exercises.h"
#include <iostream>

// Call initially: sumOfSubsets(0, 0, sum(w,n))
void sumOfSubsets(int i, unsigned int sumSel, unsigned int sumLeft,  unsigned int T, unsigned int n, const std::vector<unsigned int> &coins, std::vector<bool> &selectedCoins, bool &found, std::vector<bool> &solution, unsigned int &minim_coins) {
    // if solution found, print and terminate
    if (sumSel == T){
        if(!found){
            found = true;
            minim_coins = 0;
            for(int j = 0; j < n; j++){
                if(selectedCoins[j]){
                    minim_coins++;
                    solution[j] = true;
                }
            }
        }
        else{
            unsigned int tempCoins = 0;
            for(int j = 0; j < n; j++){
                if(selectedCoins[j]) tempCoins++;
            }
            if(tempCoins < minim_coins){
                minim_coins = tempCoins;
                solution = selectedCoins;
            }
        }
        return;
    }
    // if there is no child to explore, just backtrack
    if (i == n) return;
    // if not a promising state, prune the search
    if (sumSel + sumLeft < T || sumSel + coins[i] > T) return;
    // explore item W[i] (try using and not using) (choice point)
    selectedCoins[i] = true;
    sumOfSubsets(i+1, sumSel + coins[i], sumLeft - coins[i], T, n, coins, selectedCoins, found, solution, minim_coins);
    selectedCoins[i] = false;
    sumOfSubsets(i+1, sumSel, sumLeft - coins[i], T, n, coins, selectedCoins, found, solution, minim_coins);
}

bool changeMakingBacktracking(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    //TODO
    std::vector<unsigned int> coins;
    std::vector<bool> selectedCoins, result;
    unsigned int totalCoins = 0;
    unsigned int sumLeft = 0;
    unsigned int minimCoins = 0;
    bool found = false;
    for(int i = 0; i < n; i++){
        usedCoins[i] = 0;
        totalCoins += Stock[i];
        coins.insert(coins.end(), Stock[i], C[i]);
        selectedCoins.insert(selectedCoins.end(), Stock[i], false);
        result.insert(result.end(), Stock[i], false);
        sumLeft += Stock[i] * C[i];
    }

    int index = 0, value = coins[0];
    while(C[index] != value) index++;
    sumOfSubsets(0, 0, sumLeft,  T, totalCoins, coins, selectedCoins, found, result, minimCoins);
    if(found){
        for(int i = 0; i < totalCoins; i++){
            if(coins[i] != value){
                index++;
                value = coins[i];
            }
            if(result[i]) usedCoins[index]++;
        }
        return true;
    }
    return false;
}


/// TESTS ///
#include <gtest/gtest.h>

TEST(TP2_Ex3, hasBFChangeCanonical) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {1,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingBacktracking(C,Stock,n,13,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    unsigned int Stock2[] = {1,2,4,2};
    EXPECT_EQ(changeMakingBacktracking(C,Stock2,n,38,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 3);
    EXPECT_EQ(usedCoins[3], 2);

    unsigned int Stock3[] = {10,2,4,2};
    EXPECT_EQ(changeMakingBacktracking(C,Stock3,n,10,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);
}

TEST(TP2_Ex3, hasBFChangeNonCanonical) {
    unsigned int C[] = {1,4,5};
    unsigned int Stock[] = {2,2,1};
    unsigned int n = 3;
    unsigned int usedCoins[3];

    EXPECT_EQ(changeMakingBacktracking(C,Stock,n,6,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingBacktracking(C,Stock,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);

    unsigned int Stock2[] = {8,2,1};
    EXPECT_EQ(changeMakingBacktracking(C,Stock2,n,7,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 2);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingBacktracking(C,Stock2,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);
}

TEST(TP2_Ex3, hasNoBFChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {0,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingBacktracking(C,Stock,n,18,usedCoins), false);
    EXPECT_EQ(changeMakingBacktracking(C,Stock,n,1,usedCoins), false);
}
