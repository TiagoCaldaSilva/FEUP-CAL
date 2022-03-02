#include "exercises.h"

bool Activity::operator==(const Activity &a2) const {
    return start == a2.start && finish == a2.finish;
}

bool Activity::overlaps(const Activity &a2) const {
    return (start < a2.finish) && (a2.start < finish);
}

void activitySelectorRec(std::vector<Activity> selection, std::vector<Activity> total, std::vector<Activity> &bestSolution){
    if(total.empty()) {
        if(selection.size() > bestSolution.size()) bestSolution = selection;
        return;
    }
    Activity temp = total[0];

    total.erase(total.begin());

    activitySelectorRec(selection, total, bestSolution);
    selection.push_back(temp);
    int index = 0;
    while(index != total.size()){
        if(temp.overlaps(total[index])) total.erase(total.begin() + index);
        else index++;
    }
    activitySelectorRec(selection, total, bestSolution);
}

std::vector<Activity> activitySelectionBacktracking(std::vector<Activity> A) {
    //TODO
    std::sort(A.begin(), A.end(), [](const Activity &a1, const Activity &a2) -> bool {return a1.start < a2.start;});
    std::vector<Activity> result, temporary;
    activitySelectorRec(temporary, A, result);
    A = result;
    return A;
}


/// TESTS ///
#include <gtest/gtest.h>
#include <gmock/gmock.h>

bool noOverlaps(const std::vector<Activity> &acts) {
    for(unsigned int i = 0; i < acts.size(); i++) {
        Activity A1 = acts.at(i);
        for(unsigned int j = i + 1; j < acts.size(); j++) {
            Activity A2 = acts.at(j);
            if(A1.overlaps(A2)) return false;
        }
    }
    return true;
}

TEST(TP2_Ex4, activityScheduling) {
    std::vector<Activity> A = {{10,20}, {30, 35}, {5, 15}, {10, 40}, {40, 50}};
    std::vector<Activity> V = activitySelectionBacktracking(A);
    EXPECT_EQ(V.size(), 3 );
    EXPECT_EQ(noOverlaps(V), true);
}
