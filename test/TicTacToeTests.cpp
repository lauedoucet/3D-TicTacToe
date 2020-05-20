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
    
    virtual void TearDown() override {
        for (int i=0; i<27; i++)
        {
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
    EXPECT_FALSE(isFull(emptyBoard));
    EXPECT_TRUE(isFull(fullBoard));

    emptyBoard[4] = 'O';
    EXPECT_FALSE(isFull(emptyBoard));
}