#include "exercises.h"

#include <vector>
#include <fstream>
#include <algorithm>

int editDistance(std::string pattern, std::string text) {
    std::vector<int> D;
    if(pattern.length() == 1)
        return pattern != text ? 1 : 0;
    for(int j = 0; j <= text.length(); j++) {
        D.push_back(j);
    }

    for(int i = 1; i <= pattern.length(); i++) {
        int old = D[0];
        int _new;
        D[0] = i;
        for(int j = 1; j <= text.length(); j++) {
            _new = ( pattern[i - 1] == text[j - 1]) ? old:1 + std::min(old, std::min(D[j], D[j - 1]));
            old = D[j];
            D[j] = _new;
        }
    }
    return D[text.length()];
}

float numApproximateStringMatching(std::string filename, std::string toSearch) {
    std::ifstream in = std::ifstream(filename);
    if(!in.is_open()) {
        perror("File");
    }
    std::string text;
    float counter = 0;
    float words = 0.0;
    while(getline(in, text, '\n')) {
        words++;
        counter += editDistance(text, toSearch);
    }

    in.close();

    return counter / words;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP10_Ex2, testEditDistance) {
    EXPECT_EQ(3, editDistance("abcdefghijkl", "bcdeffghixkl"));
    EXPECT_EQ(3, editDistance("bcdeffghixkl", "abcdefghijkl"));

    EXPECT_EQ(1, editDistance("", "b"));
    EXPECT_EQ(1, editDistance("a", ""));
    EXPECT_EQ(1, editDistance("a", "b"));
    EXPECT_EQ(0, editDistance("", ""));
    EXPECT_EQ(0, editDistance("a", "a"));
}

#define REL_PATH std::string("../TP10/") // relative path to the tests

TEST(TP10_Ex2, testNumApproximateStringMatching) {
    const float delta = 0.01;

    const float expected1 = 7.76;
    float dist1 = numApproximateStringMatching(REL_PATH + "text1.txt", "estrutur");
    ASSERT_LE(expected1-delta, dist1);
    ASSERT_GE(expected1+delta, dist1);

    const float expected2 = 7.49;
    float dist2 = numApproximateStringMatching(REL_PATH + "text2.txt", "estrutur");
    ASSERT_LE(expected2-delta, dist2);
    ASSERT_GE(expected2+delta, dist2);
}
