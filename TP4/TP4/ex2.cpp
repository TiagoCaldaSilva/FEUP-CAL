#include "exercises.h"

bool changeMakingUnlimitedDP(unsigned int C[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    auto first = new (std::nothrow) bool[T + 1];
    auto last_coin = new (std::nothrow) unsigned int[T + 1];
    auto number_coins = new (std::nothrow) unsigned int[T + 1];
    for(int i = 0; i <= T; i++){
        last_coin[i] = 0;
        number_coins[i] = 0;
        first[i] = true;
    }

    for(int i = 0; i < n; i++) {
        for(unsigned int j = 1; j <= T; j++) {
            unsigned int n1 = j / C[i]; //número de moedas C[i]
            if (n1 > 0) {
                unsigned int n2 = j % C[i]; //O que sobra
                if (first[j] || number_coins[j] > (n1 + number_coins[n2])){
                    first[j] = false;
                    number_coins[j] = n1 + number_coins[n2];
                    last_coin[j] = C[i];
                }
            }
        }
    }
    if(number_coins[T] != 0){
        for(int i = (int)n - 1; i >= 0; i--){
            if(T == 0 || last_coin[T] != C[i]) usedCoins[i] = 0;
            else{
                usedCoins[i] = T / C[i];
                T %= C[i];
            }
        }
        return true;
    }
	return false;
}



/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex2, hasChangeCanonical) {
    unsigned int C[] = {1,2,5,10};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,13,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,38,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 1);
    EXPECT_EQ(usedCoins[3], 3);

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,10,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);
}

TEST(TP4_Ex2, hasChangeNonCanonical) {
    unsigned int C[] = {1,4,5};
    unsigned int n = 3;
    unsigned int usedCoins[3];

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,6,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,7,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 2);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);
}

TEST(TP4_Ex2, hasNoChange) {
    unsigned int C[] = {5,10};
    unsigned int n = 2;
    unsigned int usedCoins[2];

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,1,usedCoins), false);
}
