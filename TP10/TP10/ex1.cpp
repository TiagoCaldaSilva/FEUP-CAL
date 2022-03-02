#include "exercises.h"

#include <vector>
#include <iostream>
#include <fstream>

std::vector<int> computePrefix(std::string pattern) {
    unsigned int m = pattern.length();
    std::vector<int> pi;
    pi.push_back(-1);
    int k = -1;
    for(int q = 1; q < m; q++) {
        while(k > -1 && pattern[k + 1] != pattern[q]) {
            k = pi[k];
        }
        k = (pattern[k + 1] == pattern[q]) ? k+1 : k;
        pi.push_back(k);
    }

    return pi;
}

int kmpMatcher(std::string text, std::string pattern) {
    unsigned int n = text.length();
    unsigned int m = pattern.length();
    std::vector<int> pi = computePrefix(pattern);
    int q = -1;
    int result = 0;
    for(int i = 0; i < n; i++) {
        while(q > -1 && pattern[q + 1] != text[i]) {
            q = pi[q];
        }
        q = (pattern[q + 1] == text[i]) ? q+1 : q;
        if(q == m - 1) {
            result++;
            q = pi[q];
        }
    }
    return result;
}

int numStringMatching(std::string filename, std::string toSearch) {
    std::ifstream in = std::ifstream(filename);
    if(!in.is_open()) {
        perror("File");
    }
    std::string text;
    int counter = 0;
    while(getline(in, text, '\n')) {
        counter += kmpMatcher(text, toSearch);
    }

    in.close();

    return counter;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP10_Ex1, testKmpMatcher) {
    EXPECT_EQ(3, kmpMatcher("aaabaabaacaabaa", "aabaa"));

    EXPECT_EQ(0, kmpMatcher("", "a"));
    EXPECT_EQ(1, kmpMatcher("a", "a"));
}

#define REL_PATH std::string("../TP10/") // relative path to the tests

TEST(TP10_Ex1, testNumStringMatching) {
    int num1 = numStringMatching(REL_PATH + "text1.txt", "estrutura de dados");
    EXPECT_EQ(3, num1);

    int num2=numStringMatching(REL_PATH +"text2.txt", "estrutura de dados");
    EXPECT_EQ(2,num2);
}
