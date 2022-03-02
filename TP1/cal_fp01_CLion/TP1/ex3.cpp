// By: Gonçalo Leão

#include "exercises.h"

bool changeMakingBF(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    //TODO...
    int current_index, number_coins = 0, temporary_coins, totalValue, temporary_result[n], result[n];
    bool first_time = true;

    //Initialize the array of the temporary result with 0's to increment the positions
    for(int temp = 0; temp < n; temp++){
        temporary_result[temp] = 0;
    }

    while(true) {
        //In the beginning of all the iterations the current index is initialized to
        //Try another alternative by the beginning of the set of coins
        current_index = 0;

        //If the temporary_result[current_index] == Stock[current_index] we already reach the max of
        //coins to that position, so we should advance to another one where we can increment the number
        //of coins on it
        while (temporary_result[current_index] == Stock[current_index]) {
            current_index++;
            if (current_index == n) break;
        }

        //If the current_index == n, we already reach all the possible combinations with this set of coins
        if (current_index == n) break;

        //Otherwise we should find another possible combination (this for cycle ends when it reaches the current
        //position, so we'll put to 0 all the other positions to initiate another cycle
        for(int temp = 0; temp < current_index; temp++){
            temporary_result[temp] = 0;
        }

        //Increment the current position to try another combination (note that all the other position behind
        //the current position are 0's (but the positions after the current position may not be 0's)
        temporary_result[current_index]++;

        //As we have a new combination we should verify if it is a possible final candidate

        totalValue = 0;
        temporary_coins = 0;
        for(int temp = 0; temp < n; temp++){
            temporary_coins += temporary_result[temp];
            totalValue += temporary_result[temp] * (int)C[temp];
            if(totalValue > T) break;
        }


        //Verify if it is a possible alternative
        if(totalValue == T and (temporary_coins < number_coins or first_time)){
            if(first_time) first_time = false;
            number_coins = temporary_coins;
            for(int temp = 0; temp < n; temp++){
                result[temp] = temporary_result[temp];
            }
        }
    }

    if(!first_time){
        for(int temp = 0; temp < n; temp++){
            usedCoins[temp] = result[temp];
        }
        return !first_time;
    }

    return false;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP1_Ex3, hasBFChangeCanonical) {

    std::cout << "EX3" << std::endl;

    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {1,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingBF(C,Stock,n,13,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    unsigned int Stock2[] = {1,2,4,2};
    EXPECT_EQ(changeMakingBF(C,Stock2,n,38,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 3);
    EXPECT_EQ(usedCoins[3], 2);
}

TEST(TP1_Ex3, hasBFChangeNonCanonical) {
    unsigned int C[] = {1,4,5};
    unsigned int Stock[] = {2,2,1};
    unsigned int n = 3;
    unsigned int usedCoins[3];

    EXPECT_EQ(changeMakingBF(C,Stock,n,6,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingBF(C,Stock,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);
}

TEST(TP1_Ex3, hasNoBFChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {0,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingBF(C,Stock,n,18,usedCoins), false);
    EXPECT_EQ(changeMakingBF(C,Stock,n,1,usedCoins), false);
}
