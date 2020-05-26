#include "../functions.cpp"
#include <gtest/gtest.h>

struct TicTacToeTests
    : public::testing::Test
{
    virtual void SetUp() override {
        for (int i=0; i<27; i++) {
            emptyBoard[i] = i;
        }

        for (int i=0; i<27; i++) {
            fullBoard[i] = 'X';
        }
    }

    int emptyBoard[27];
    int fullBoard[27]; 
};

TEST_F(TicTacToeTests, isFullTest) {
    // corner cases: empty and full board
    EXPECT_FALSE(isFull(emptyBoard));
    EXPECT_TRUE(isFull(fullBoard));

    // random additional tests 
    int i = rand() % 27;
    emptyBoard[i] = 'O';
    EXPECT_FALSE(isFull(emptyBoard));
    SetUp();    
    i = rand() % 27;
    emptyBoard[i] = 'X';
    EXPECT_FALSE(isFull(emptyBoard));
    i = rand() % 27;
    fullBoard[i] = i+1;
    EXPECT_FALSE(isFull(fullBoard));
}

TEST_F(TicTacToeTests, verticalWinTest) {
    ASSERT_FALSE(verticalWin(emptyBoard));
    emptyBoard[9] = 'X';
    emptyBoard[12] = 'X';
    emptyBoard[15] = 'X';
    EXPECT_TRUE(verticalWin(emptyBoard));
}

TEST_F(TicTacToeTests, horizontalWinTest) {
    ASSERT_FALSE(horizontalWin(emptyBoard));
    emptyBoard[21] = 'X';
    emptyBoard[22] = 'X';
    emptyBoard[23] = 'X';
    EXPECT_TRUE(horizontalWin(emptyBoard));
}

TEST_F(TicTacToeTests, diagonalWinTest) {
    ASSERT_FALSE(diagonalWin(emptyBoard));
    emptyBoard[9] = 'X';
    emptyBoard[13] = 'X';
    emptyBoard[17] = 'X';
    EXPECT_TRUE(diagonalWin(emptyBoard));
}

TEST_F(TicTacToeTests, win3DTest) {
    // corner case: empty board
    ASSERT_FALSE(win3D(emptyBoard));
    // same spot accross 3 boards
    emptyBoard[3] = 'X';
    emptyBoard[12] = 'X';
    emptyBoard[21] = 'X';
    EXPECT_TRUE(win3D(emptyBoard));
    SetUp();
    // 3D horizontal win
    emptyBoard[6] = 'X';
    emptyBoard[16] = 'X';
    emptyBoard[26] = 'X';
    EXPECT_TRUE(win3D(emptyBoard));
    SetUp();
    // 3D vertical win
    emptyBoard[1] = 'X';
    emptyBoard[13] = 'X';
    emptyBoard[25] = 'X';
    EXPECT_TRUE(win3D(emptyBoard));
    SetUp();
    // 3D diagonal win
    emptyBoard[6] = 'X';
    emptyBoard[13] = 'X';
    emptyBoard[20] = 'X';
    EXPECT_TRUE(win3D(emptyBoard));
    SetUp();
}