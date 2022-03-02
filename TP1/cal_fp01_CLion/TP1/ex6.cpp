// By: Gonçalo Leão

#include "exercises.h"
#include <algorithm>
#include <iostream>

bool Activity::operator==(const Activity &a2) const {
    return start == a2.start && finish == a2.finish;
}

bool Activity::operator<(const Activity &a2) const {
    return finish < a2.finish;
}

std::vector<Activity> earliestFinishScheduling(std::vector<Activity> A) {
    //TODO...

    std::vector<Activity> res, temp;
    int next_beginning;
    std::sort(A.begin(), A.end());
    while(A.size()){

        //Como o vetor está ordenado pelo tempo de termino, o primeiro elemento
        //é a atividade que termina primeiro
        next_beginning = A[0].finish;
        res.push_back(A[0]);

        //Vetor que vai auxiliar o processo
        temp.clear();

        //Para retirar todos aqueles elementos que já não podem ser incluídos:
        //Pois ou são o elemento já incluído, ou começam antes da atividade escolhida acabar
        for(auto elem: A){
            if(elem == A[0] or elem.start < next_beginning) continue;
            temp.push_back(elem);
        }
        A = temp;
    }

    return res;
}

/// TESTS ///
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(TP1_Ex6, activityScheduling) {

    std::cout << "EX6" << std::endl;

    std::vector<Activity> A = {{10,20}, {30, 35}, {5, 15}, {10, 40}, {40, 50}};
    std::vector<Activity> V = earliestFinishScheduling(A);
    EXPECT_EQ(V.size(), 3 );
    ASSERT_THAT(earliestFinishScheduling(A),  ::testing::ElementsAre(Activity(5, 15), Activity(30, 35), Activity(40, 50)));
}
