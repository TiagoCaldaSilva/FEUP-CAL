#include "exercises.h"
#include <algorithm>

void pastSolution(int*** solutions, unsigned int n, int actual_value, int actual_coin){
    for (int i = 0; i <= n + 1; i++) {
        solutions[actual_coin][actual_value][i] = solutions[actual_coin - 1][actual_value][i];
    }
}

void change(int*** solutions, unsigned int n, int actual_value, int actual_coin, int coins_used, int temp) {
    for (int i = 0; i <= n; i++) {
        solutions[actual_coin][actual_value][i] = solutions[actual_coin][temp][i];
    }
    solutions[actual_coin][actual_value][actual_coin] += coins_used;
    solutions[actual_coin][actual_value][n] = 1;
    solutions[actual_coin][actual_value][n + 1] = coins_used + solutions[actual_coin][temp][n + 1];
}

bool changeMakingDP(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    // INIT
    int *** solutions = (int ***) malloc(sizeof(int **) * T + 1);
    for(int k = 0; k < n; k++) {
        solutions[k] = (int **)malloc(sizeof(int **) * T + 1);
        for (int i = 0; i <= T; i++) {
            solutions[k][i] = (int *) malloc(sizeof(int) * n + 2);

            for (int j = 0; j <= n; j++) {
                solutions[k][i][j] = 0;
            }

            solutions[k][i][n + 1] = INT_MAX; //Solutions[i][n + 1] will have the number of coins of the solution i
        }
        solutions[k][0][n] = 1; //Solutions[i][n] = 1, if solutions[i] is a possible solution to i
        solutions[k][0][n + 1] = 0;
    }

    for(int actual_coin = 0; actual_coin < n; actual_coin++) {
        for(int actual_value = 1; actual_value <= T; actual_value++) {
            int coins_used = std::min(Stock[actual_coin], actual_value / C[actual_coin]);
            int temp = actual_value- (int) C[actual_coin] * coins_used;

            if (temp < 0) {
                if (actual_coin != 0 && solutions[actual_coin - 1][actual_value][n]) pastSolution(solutions, n, actual_value, actual_coin); // If the other solution is better
                continue;
            }
            //Possible solution with the actual coin
            if (solutions[actual_coin][temp][n] && (Stock[actual_coin] >= coins_used + solutions[actual_coin][temp][actual_coin])) {
                if(actual_coin == 0) change(solutions, n, actual_value, actual_coin, coins_used, temp); //If it is solution
                else {
                    if (solutions[actual_coin - 1][actual_value][n + 1] > coins_used + solutions[actual_coin][temp][n + 1])
                        change(solutions, n, actual_value, actual_coin, coins_used, temp); //If the new solution is better than the other
                    else pastSolution(solutions, n, actual_value, actual_coin); // If the other solution is better
                }
            } else if (actual_coin != 0 && solutions[actual_coin - 1][temp][n] &&
                        solutions[actual_coin - 1][actual_value][n + 1] >= coins_used + solutions[actual_coin - 1][temp][n + 1]) { //Better solution with other coins
                for (int i = 0; i < n; i++) {
                    solutions[actual_coin][actual_value][i] = solutions[actual_coin - 1][temp][i];
                }
                solutions[actual_coin][actual_value][actual_coin] += coins_used;
                solutions[actual_coin][actual_value][n] = 1;
                solutions[actual_coin][actual_value][n + 1] = solutions[actual_coin - 1][temp][n + 1] + coins_used;

            } else if(actual_coin != 0 && solutions[actual_coin - 1][actual_value][n]) pastSolution(solutions, n, actual_value, actual_coin);
        }
    }

    if(solutions[n - 1][T][n]) {
        for (int i = 0; i < n; i++) {
            usedCoins[i] = solutions[n - 1][T][i];
        }
        return true;
    }
    return false;
}


/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex3, hasChangeCanonical) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {1,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingDP(C,Stock,n,13,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    unsigned int Stock2[] = {1,2,4,2};
    EXPECT_EQ(changeMakingDP(C,Stock2,n,38,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 3);
    EXPECT_EQ(usedCoins[3], 2);

    unsigned int Stock3[] = {10,2,4,2};
    EXPECT_EQ(changeMakingDP(C,Stock3,n,10,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);
}


TEST(TP4_Ex3, hasChangeNonCanonical) {
    unsigned int C[] = {1,4,5};
    unsigned int Stock[] = {2,2,1};
    unsigned int n = 3;
    unsigned int usedCoins[3];

    EXPECT_EQ(changeMakingDP(C,Stock,n,6,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingDP(C,Stock,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);

    unsigned int Stock2[] = {8,2,1};
    EXPECT_EQ(changeMakingDP(C,Stock2,n,7,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 2);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingDP(C,Stock2,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);
}

TEST(TP4_Ex3, hasNoChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {0,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingDP(C,Stock,n,18,usedCoins), false);
    EXPECT_EQ(changeMakingDP(C,Stock,n,1,usedCoins), false);
}

