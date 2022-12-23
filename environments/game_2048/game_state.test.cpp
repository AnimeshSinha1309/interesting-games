#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "game_state.hpp"


class TestBasicMovementActions : public ::testing::TestWithParam<GameState2048<4>::Move> {
protected:
    GameState2048<4>::Move move;
};

TEST_P(TestBasicMovementActions, TestBasicMoveUp) {
    GameState2048<4> game({
            { 0,  0,  0,  0},
            { 0, 32, 16,  0},
            { 0, 64,  8,  0},
            { 0,  0,  0,  0},
    });
    decltype(game)::Move move = GetParam();

    game.move(move);
    std::vector<std::vector<int>> obtained_state = game.get_board();

    std::vector<std::vector<int>> expected_state;
    switch (move) {
        case decltype(move)::UP:
            expected_state = {
                    { 0, 32, 16,  0},
                    { 0, 64,  8,  0},
                    { 0,  0,  0,  0},
                    { 0,  0,  0,  0},
            };
            break;
        case decltype(move)::DOWN:
            expected_state = {
                    { 0,  0,  0,  0},
                    { 0,  0,  0,  0},
                    { 0, 32, 16,  0},
                    { 0, 64,  8,  0},
            };
            break;
        case decltype(move)::LEFT:
            expected_state = {
                    { 0,  0,  0,  0},
                    {32, 16,  0,  0},
                    {64,  8,  0,  0},
                    { 0,  0,  0,  0},
            };
            break;
        case decltype(move)::RIGHT:
            expected_state = {
                    { 0,  0,  0,  0},
                    { 0,  0, 32, 16},
                    { 0,  0, 64,  8},
                    { 0,  0,  0,  0},
            };
            break;
        default:
            break;
    }

    int count_of_small_tiles = 0;
    for (auto &row : obtained_state) {
        for (auto &element : row) {
            if (element == 2 || element == 4) {
                count_of_small_tiles++;
                element = 0;
            }
        }
    }
    EXPECT_THAT(obtained_state, testing::ElementsAreArray(expected_state));
    EXPECT_EQ(count_of_small_tiles, 1);
}

INSTANTIATE_TEST_SUITE_P(
        TestBasicMovements,
        TestBasicMovementActions,
        ::testing::Values(
                GameState2048<4>::Move::UP,
                GameState2048<4>::Move::DOWN,
                GameState2048<4>::Move::LEFT,
                GameState2048<4>::Move::RIGHT
                ));


TEST(TestMovementAndMerges, TestMoveUp) {
    GameState2048<4> game({
            {16,  0, 32, 32},
            {16, 32, 64, 16},
            {16,  0, 64,  0},
            {16, 32, 64,  0},
    });
    game.move(decltype(game)::Move::DOWN);
    std::vector<std::vector<int>> obtained_state = game.get_board();

    std::vector<std::vector<int>> expected_state = {
            { 0,  0,   0,  0},
            { 0,  0,  32,  0},
            {32,  0,  64, 32},
            {32, 64, 128, 16},
    };
    int count_of_small_tiles = 0;
    for (auto &row : obtained_state) {
        for (auto &element : row) {
            if (element == 2 || element == 4) {
                count_of_small_tiles++;
                element = 0;
            }
        }
    }
    EXPECT_THAT(obtained_state, testing::ElementsAreArray(expected_state));
    EXPECT_EQ(count_of_small_tiles, 1);
}
