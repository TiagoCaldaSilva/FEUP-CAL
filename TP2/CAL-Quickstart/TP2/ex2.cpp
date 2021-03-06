#include "exercises.h"
#include <iostream>
Sudoku::Sudoku() {
    this->initialize();
}

Sudoku::Sudoku(int nums[9][9]): Sudoku() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (nums[i][j] != 0) {
                int n = nums[i][j];
                if (n < 1 || n > 9 || !accepts(i, j, n))
                    throw IllegalArgumentException;
                else
                    place(i, j, n);
            }
        }
    }
}

void Sudoku::initialize() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            for (int n = 0; n < 10; n++) {
                numbers[i][j] = 0;
                lineHasNumber[i][n] = false;
                columnHasNumber[j][n] = false;
                block3x3HasNumber[i / 3][j / 3][n] = false;
            }
        }
    }
    this->countFilled = 0;
}

bool Sudoku::isComplete() const {
    return countFilled == 9 * 9;
}

std::vector<int> Sudoku::possibleNumbersInTheRow(int row){
    std::vector<int> solution;
    bool found = false;
    for(int i = 0; i < 9; i++){
        solution.push_back(i + 1);
        if(!found && numbers[row][i] == 0){
            found = true;
        }
    }
    if(!found){solution.clear(); return solution;}
    for(int i = 0; i < 9; i++){
        auto it = find(solution.begin(), solution.end(), numbers[row][i]);
        if(it != solution.end()){
            solution.erase(it);
        }
    }
    return solution;
}
std::vector<int> Sudoku::possibleNumbersInTheColumn(int col){
    std::vector<int> solution;
    bool found = false;
    for(int i = 0; i < 9; i++){
        solution.push_back(i + 1);
        if(!found && numbers[i][col] == 0){
            found = true;
        }
    }
    if(!found){ solution.clear(); return solution;}
    for(auto & number : numbers){
        auto it = find(solution.begin(), solution.end(), number[col]);
        if(it != solution.end()){
            solution.erase(it);
        }
    }
    return solution;
}
std::vector<int> Sudoku::possibleNumbersInTheBlock(int row, int col){
    row /=3;
    col /= 3;
    std::vector<int> solution;
    for(int i = 1; i <= 9; i++) solution.push_back(i);
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            auto it = find(solution.begin(), solution.end(), numbers[row * 3 + i][col * 3 + j]);
            if(it != solution.end()) solution.erase(it);
        }
    }
    return solution;
}

bool Sudoku::solve() {
    //TODO
    /**
     * Without greedy algorithm
     */
     /*
    if(countFilled == 81) return true;
    for(int row = 0; row < 9; row++){
        std::vector<int> perRow = possibleNumbersInTheRow(row);
        if(!perRow.empty()){
            for(int col = 0; col < 9; col++) {
                if (numbers[row][col] == 0) {
                    std::vector<int> perCol = possibleNumbersInTheColumn(col);
                    std::vector<int> perBlock = possibleNumbersInTheBlock(row, col);
                    std::vector<int> temp;
                    std::set_intersection(perRow.begin(), perRow.end(), perCol.begin(), perCol.end(),
                                          back_inserter(temp));
                    std::vector<int> final;
                    std::set_intersection(temp.begin(), temp.end(), perBlock.begin(), perBlock.end(),
                                          back_inserter(final));
                    if (final.empty()) return false;
                    else {
                        for (int i : final) {
                            place(row, col, i);
                            if (solve()) return true;
                            clear(row, col);
                        }
                        return false;
                    }
                }
            }
        }
    }*/
     /**
      * With greedy algorithm
      */
    std::vector<int> min;
    int r, c;
    bool first = true;
    if(countFilled == 81) return true;
    for(int row = 0; row < 9; row++){
        std::vector<int> perRow = possibleNumbersInTheRow(row);
        if(!perRow.empty()){
            for(int col = 0; col < 9; col++) {
                if (numbers[row][col] == 0) {
                    std::vector<int> perCol = possibleNumbersInTheColumn(col);
                    std::vector<int> perBlock = possibleNumbersInTheBlock(row, col);
                    std::vector<int> temp;
                    std::set_intersection(perRow.begin(), perRow.end(), perCol.begin(), perCol.end(),
                                          back_inserter(temp));
                    std::vector<int> final;
                    std::set_intersection(temp.begin(), temp.end(), perBlock.begin(), perBlock.end(),
                                          back_inserter(final));
                    if (final.empty()) return false;
                    else {
                        if(first || min.size() > final.size()){
                            first = false;
                            min = final;
                            r = row; c = col;
                        }
                    }
                }
            }
        }
    }
    for (int i : min) {
        place(r, c, i);
        if (solve()) return true;
        clear(r, c);
    }
    return false;
}
bool Sudoku::solve2(int &counter) {
    /**
     * With greedy algorithm
     */
    std::vector<int> min;
    int r, c;
    bool first = true;
    if(countFilled == 81) return true;
    for(int row = 0; row < 9; row++){
        std::vector<int> perRow = possibleNumbersInTheRow(row);
        if(!perRow.empty()){
            for(int col = 0; col < 9; col++) {
                if (numbers[row][col] == 0) {
                    std::vector<int> perCol = possibleNumbersInTheColumn(col);
                    std::vector<int> perBlock = possibleNumbersInTheBlock(row, col);
                    std::vector<int> temp;
                    std::set_intersection(perRow.begin(), perRow.end(), perCol.begin(), perCol.end(),
                                          back_inserter(temp));
                    std::vector<int> final;
                    std::set_intersection(temp.begin(), temp.end(), perBlock.begin(), perBlock.end(),
                                          back_inserter(final));
                    if (final.empty()) return false;
                    else {
                        if(first || min.size() > final.size()){
                            first = false;
                            min = final;
                            r = row; c = col;
                        }
                    }
                }
            }
        }
    }
    for (int i : min) {
        place(r, c, i);
        if (solve2(counter)) counter++;
        clear(r, c);
    }
    return false;
}
int Sudoku::countSolutions() {
    //TODO
    int counter = 0;
    solve2(counter);
    return counter;
}

bool Sudoku::solve3(int &counter, int solutions) {
    /**
     * With greedy algorithm
     */
    std::vector<int> min;
    int r, c;
    bool first = true;
    if(countFilled == 81) return true;
    for(int row = 0; row < 9; row++){
        std::vector<int> perRow = possibleNumbersInTheRow(row);
        if(!perRow.empty()){
            for(int col = 0; col < 9; col++) {
                if (numbers[row][col] == 0) {
                    std::vector<int> perCol = possibleNumbersInTheColumn(col);
                    std::vector<int> perBlock = possibleNumbersInTheBlock(row, col);
                    std::vector<int> temp;
                    std::set_intersection(perRow.begin(), perRow.end(), perCol.begin(), perCol.end(),
                                          back_inserter(temp));
                    std::vector<int> final;
                    std::set_intersection(temp.begin(), temp.end(), perBlock.begin(), perBlock.end(),
                                          back_inserter(final));
                    if (final.empty()) return false;
                    else {
                        if(first || min.size() > final.size()){
                            first = false;
                            min = final;
                            r = row; c = col;
                        }
                    }
                }
            }
        }
    }
    for (int i : min) {
        place(r, c, i);
        if (solve3(counter, solutions)){counter++;}
        clear(r, c);
        if(counter > solutions) return true;
    }
    return false;
}
void Sudoku::generate(int solutions) {
	//TODO
	int row = 0, col = 0;
	int counter;
	while(true){
	    counter = 0;

	    while(numbers[row][col] != 0){
	        row = rand() % 9;
	        col = rand() % 9;
	    }

        std::vector<int> perRow = possibleNumbersInTheRow(row);
        std::vector<int> perCol = possibleNumbersInTheColumn(col);
        std::vector<int> perBlock = possibleNumbersInTheBlock(row, col);
        std::vector<int> temp;
        std::set_intersection(perRow.begin(), perRow.end(), perCol.begin(), perCol.end(),
                              back_inserter(temp));
        std::vector<int> final;
        std::set_intersection(temp.begin(), temp.end(), perBlock.begin(), perBlock.end(),
                              back_inserter(final));

        if(!final.empty()){
            place(row, col, final[rand() % final.size()]);
            if(!solve3(counter, solutions)){
                if(counter == solutions)
                    return;
                clear(row, col);
            }
        }
	}
}

int** Sudoku::getNumbers() {
    int** ret = new int*[9];
    for (int i = 0; i < 9; i++) {
        ret[i] = new int[9];
        for (int a = 0; a < 9; a++)
            ret[i][a] = numbers[i][a];
    }
    return ret;
}

void Sudoku::print() const {
    for (const auto & number : this->numbers) {
        for (int a = 0; a < 9; a++)
            std::cout << number[a] << " ";
        std::cout << std::endl;
    }
}

bool Sudoku::accepts(int i, int j, int n) {
	//TODO
    return !(lineHasNumber[i][n] && columnHasNumber[j][n] && block3x3HasNumber[i / 3][j / 3][n]);
}

void Sudoku::place(int i, int j, int n) {
    if (numbers[i][j] != 0)
        return;

    numbers[i][j] = n;
    lineHasNumber[i][n] = true;
    columnHasNumber[j][n] = true;
    block3x3HasNumber[i / 3][j / 3][n] = true;
    countFilled++;
}

int Sudoku::clear(int i, int j) {
    int n = numbers[i][j];

    numbers[i][j] = 0;
    lineHasNumber[i][n] = false;
    columnHasNumber[j][n] = false;
    block3x3HasNumber[i / 3][j / 3][n] = false;
    countFilled--;

    return n;
}

void Sudoku::clear() {
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (numbers[i][j] != 0)
                clear(i, j);
}


/// TESTS ///
#include <gtest/gtest.h>

void compareSudokus(int in[9][9], int out[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int a = 0; a < 9; a++)
            ASSERT_EQ(in[i][a], out[i][a]);
    }
}
/*
TEST(TP2_Ex2, testSudokuAlreadySolved) {
    int in[9][9] =
            {{8, 6, 2, 3, 4, 1, 7, 9, 5},
             {1, 5, 4, 9, 7, 6, 3, 8, 2},
             {9, 3, 7, 8, 2, 5, 1, 4, 6},
             {5, 7, 6, 1, 3, 8, 9, 2, 4},
             {2, 1, 8, 5, 9, 4, 6, 3, 7},
             {3, 4, 9, 7, 6, 2, 8, 5, 1},
             {6, 2, 3, 4, 8, 7, 5, 1, 9},
             {7, 8, 5, 2, 1, 9, 4, 6, 3},
             {4, 9, 1, 6, 5, 3, 2, 7, 8}};

    Sudoku s(in);

    EXPECT_EQ(s.solve(), true);

    int out[9][9];
    int** res = s.getNumbers();

    for (int i = 0; i < 9; i++)
        for (int a = 0; a < 9; a++)
            out[i][a] = res[i][a];

    compareSudokus(in, out);
}

TEST(TP2_Ex2, testSudokuNoneBackStepsRequired) {
    int in[9][9] =
            {{8, 6, 0, 0, 0, 0, 0, 9, 0},
             {0, 0, 4, 0, 7, 6, 3, 0, 0},
             {9, 0, 0, 0, 2, 5, 1, 0, 0},
             {0, 7, 6, 1, 3, 0, 0, 2, 0},
             {2, 1, 0, 0, 0, 0, 0, 3, 7},
             {0, 4, 0, 0, 6, 2, 8, 5, 0},
             {0, 0, 3, 4, 8, 0, 0, 0, 9},
             {0, 0, 5, 2, 1, 0, 4, 0, 0},
             {0, 9, 0, 0, 0, 0, 0, 7, 8}};

    int out[9][9] =
            {{8, 6, 2, 3, 4, 1, 7, 9, 5},
             {1, 5, 4, 9, 7, 6, 3, 8, 2},
             {9, 3, 7, 8, 2, 5, 1, 4, 6},
             {5, 7, 6, 1, 3, 8, 9, 2, 4},
             {2, 1, 8, 5, 9, 4, 6, 3, 7},
             {3, 4, 9, 7, 6, 2, 8, 5, 1},
             {6, 2, 3, 4, 8, 7, 5, 1, 9},
             {7, 8, 5, 2, 1, 9, 4, 6, 3},
             {4, 9, 1, 6, 5, 3, 2, 7, 8}};

    Sudoku s(in);

    EXPECT_EQ(s.solve(), true);

    int sout[9][9];
    int** res = s.getNumbers();

    for (int i = 0; i < 9; i++)
        for (int a = 0; a < 9; a++)
            sout[i][a] = res[i][a];

    compareSudokus(out, sout);
}

TEST(TP2_Ex2, testSudokuSomeBackStepsRequired) {
    int in[9][9] =
            {{7, 0, 5, 2, 6, 3, 4, 0, 9},
             {0, 0, 0, 0, 0, 0, 0, 3, 0},
             {0, 0, 0, 0, 8, 0, 0, 0, 0},
             {0, 0, 9, 5, 0, 4, 0, 0, 2},
             {5, 0, 6, 0, 0, 0, 7, 0, 8},
             {2, 0, 0, 8, 0, 0, 1, 0, 0},
             {0, 0, 0, 0, 1, 0, 0, 0, 0},
             {0, 2, 0, 0, 0, 0, 0, 0, 0},
             {3, 0, 8, 7, 2, 9, 6, 0, 4}};

    int out[9][9] =
            {{7, 1, 5, 2, 6, 3, 4, 8, 9},
             {8, 6, 4, 9, 5, 7, 2, 3, 1},
             {9, 3, 2, 4, 8, 1, 5, 7, 6},
             {1, 8, 9, 5, 7, 4, 3, 6, 2},
             {5, 4, 6, 1, 3, 2, 7, 9, 8},
             {2, 7, 3, 8, 9, 6, 1, 4, 5},
             {4, 9, 7, 6, 1, 5, 8, 2, 3},
             {6, 2, 1, 3, 4, 8, 9, 5, 7},
             {3, 5, 8, 7, 2, 9, 6, 1, 4}};

    Sudoku s(in);

    EXPECT_EQ(s.solve(), true);

    int sout[9][9];
    int** res = s.getNumbers();

    for (int i = 0; i < 9; i++)
        for (int a = 0; a < 9; a++)
            sout[i][a] = res[i][a];

    compareSudokus(out, sout);
}

TEST(TP2_Ex2, testSudokuManyBackStepsRequired) {
    int in[9][9] =
            {{1, 0, 0, 0, 0, 7, 0, 0, 0},
             {0, 7, 0, 0, 6, 0, 8, 0, 0},
             {2, 0, 0, 0, 4, 0, 6, 0, 0},
             {7, 6, 4, 0, 0, 0, 9, 0, 0},
             {0, 0, 0, 0, 2, 0, 5, 6, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 1, 0, 0, 3, 0, 0, 0, 0},
             {4, 0, 0, 1, 0, 0, 0, 0, 5},
             {0, 5, 0, 0, 0, 4, 0, 9, 0}};

    int out[9][9] =
            {{1, 4, 6, 8, 5, 7, 2, 3, 9},
             {3, 7, 9, 2, 6, 1, 8, 5, 4},
             {2, 8, 5, 9, 4, 3, 6, 7, 1},
             {7, 6, 4, 3, 1, 5, 9, 2, 8},
             {8, 3, 1, 4, 2, 9, 5, 6, 7},
             {5, 9, 2, 6, 7, 8, 4, 1, 3},
             {9, 1, 8, 5, 3, 2, 7, 4, 6},
             {4, 2, 7, 1, 9, 6, 3, 8, 5},
             {6, 5, 3, 7, 8, 4, 1, 9, 2}};

    Sudoku s(in);

    EXPECT_EQ(s.solve(), true);

    int sout[9][9];
    int **res = s.getNumbers();

    for (int i = 0; i < 9; i++)
        for (int a = 0; a < 9; a++)
            sout[i][a] = res[i][a];

    compareSudokus(out, sout);
}

TEST(TP2_Ex2, testSudokuWithMinimalClues) {
    int in[9][9] =
            {{7, 0, 0, 1, 0, 8, 0, 0, 0},
             {0, 9, 0, 0, 0, 0, 0, 3, 2},
             {0, 0, 0, 0, 0, 5, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 1, 0, 0},
             {9, 6, 0, 0, 2, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 8, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 5, 0, 0, 1, 0, 0, 0},
             {3, 2, 0, 0, 0, 0, 0, 0, 6}};

    int out[9][9] =
            {{7, 5, 2, 1, 3, 8, 6, 9, 4},
             {1, 9, 8, 7, 4, 6, 5, 3, 2},
             {4, 3, 6, 2, 9, 5, 7, 8, 1},
             {2, 8, 3, 4, 5, 9, 1, 6, 7},
             {9, 6, 1, 8, 2, 7, 3, 4, 5},
             {5, 7, 4, 6, 1, 3, 8, 2, 9},
             {6, 1, 9, 3, 7, 2, 4, 5, 8},
             {8, 4, 5, 9, 6, 1, 2, 7, 3},
             {3, 2, 7, 5, 8, 4, 9, 1, 6}};

    Sudoku s(in);

    EXPECT_EQ(s.solve(), true);

    int sout[9][9];
    int** res = s.getNumbers();

    for (int i = 0; i < 9; i++)
        for (int a = 0; a < 9; a++)
            sout[i][a] = res[i][a];

    compareSudokus(out, sout);
}

TEST(TP2_Ex2, testSudokuWithMultipleSolutions) {
    int in[9][9] =
            {{0
*//*7*/
/*
, 0, 0, 1, 0, 8, 0, 0, 0},
             {0, 9, 0, 0, 0, 0, 0, 3, 2},
             {0, 0, 0, 0, 0, 5, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 1, 0, 0},
             {9, 6, 0, 0, 2, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 8, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 5, 0, 0, 1, 0, 0, 0},
             {3, 2, 0, 0, 0, 0, 0, 0, 6}};

    Sudoku s(in);
    EXPECT_EQ(s.solve() && s.isComplete(), true);
    int** out = s.getNumbers();
    for (int i=0; i<9; i++)
        for (int j=0; j<9; j++)
            if (in[i][j] != 0)
                EXPECT_EQ(in[i][j], out[i][j]);
}

TEST(TP2_Ex2, testSudokuEmpty) {
    int in[9][9] =
            {{0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0}};

    Sudoku s(in);
    EXPECT_EQ(s.solve(), true);
    EXPECT_EQ(s.isComplete(), true);
}

TEST(TP2_Ex2, testSudokuImpossible) {
    int in[9][9] =
            {{7, 0, 0, 1, 0, 8, 0, 0, 0},
             {4
*//*0*/
/*
, 9, 0, 0, 0, 0, 0, 3, 2},
             {0, 0, 0, 0, 0, 5, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 1, 0, 0},
             {9, 6, 0, 0, 2, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 8, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 5, 0, 0, 1, 0, 0, 0},
             {3, 2, 0, 0, 0, 0, 0, 0, 6}};

    Sudoku s(in);

    EXPECT_EQ(s.solve(), false);

    int out[9][9];
    int** res = s.getNumbers();

    for (int i = 0; i < 9; i++)
        for (int a = 0; a < 9; a++)
            out[i][a] = res[i][a];

    compareSudokus(in, out);
}

TEST(TP2_Ex2, testSudokuVariousSolutions) {
    int in[9][9] =
            {{2,9,5,7,4,3,8,6,1},
             {4,3,1,8,6,5,9,0,0},
             {8,7,6,1,9,2,5,4,3},
             {3,8,7,4,5,9,2,1,6},
             {6,1,2,3,8,7,4,9,5},
             {5,4,9,2,1,6,7,3,8},
             {7,6,3,5,2,4,1,8,9},
             {9,2,8,6,7,1,3,5,4},
             {1,5,4,9,3,8,6,0,0}};

    Sudoku s(in);
    //EXPECT_EQ(s.countSolutions(), 2);

    int in2[9][9] =
            {{5, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 3, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 4, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 2, 0, 0, 0, 0, 0, 1},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0}};

    Sudoku s2(in2);
    //EXPECT_EQ(s2.countSolutions(), 308);
}
*/
TEST(TP2_Ex2, testegenerator){
    int in[9][9] =
            {{0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0, 0}};

    Sudoku s(in);

    int solutions = 1;

    s.generate(solutions);

    s.print();

    EXPECT_EQ(s.countSolutions(), solutions);

    int in2[9][9] = {{4, 6, 9, 3, 8, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 0, 1, 0},
                     {0, 0, 0, 6, 0, 0, 0, 8, 4},
                     {9, 0, 4, 5, 7, 6, 1, 2, 8},
                     {0, 1, 0, 0, 0, 0, 0, 0, 0},
                     {7, 0, 0, 0, 0, 0, 0, 6, 3},
                     {8, 0, 2, 0, 0, 5, 0, 0, 0},
                     {3, 0, 0, 0, 6, 0, 0, 0, 0},
                     {0, 0, 6, 2, 0, 0, 7, 9, 5}};

    Sudoku s2(in2);


    EXPECT_EQ(s2.countSolutions(), solutions);

}

