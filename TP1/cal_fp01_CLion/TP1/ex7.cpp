// By: Gonçalo Leão

#include "exercises.h"

#include <algorithm>
#include <vector>

double minimumAverageCompletionTime(std::vector<unsigned int> tasks, std::vector<unsigned int> &orderedTasks) {
    //TODO...
    orderedTasks = tasks;
    std::sort(orderedTasks.begin(), orderedTasks.end());
    double result = 0, current = 0;
    for(auto elem: orderedTasks){
        result += elem + current;
        current += elem;
    }
    return result / orderedTasks.size();
}

/// TESTS ///
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(TP1_Ex7, taskOrdering) {

    std::cout << "EX7" << std::endl;

    std::vector<unsigned int> tasks = {15, 8, 3, 10};
    std::vector<unsigned int> orderedTasks;
    double averageTime = minimumAverageCompletionTime(tasks, orderedTasks);
    EXPECT_EQ(orderedTasks.size(), 4 );
    ASSERT_NEAR(averageTime, 17.75, 0.00001);
    ASSERT_THAT(orderedTasks,  ::testing::ElementsAre(3,8,10,15));
}
