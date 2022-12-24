#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "game_state.hpp"


class TestBasicMovementActions : public ::testing::TestWithParam<Action2048> {
protected:
    Action2048 move{Action2048::ActionType::UP};
};

TEST_P(TestBasicMovementActions, TestBasicMoveUp) {
    GameState2048<4> game({
            { 0,  0,  0,  0},
            { 0, 32, 16,  0},
            { 0, 64,  8,  0},
            { 0,  0,  0,  0},
    });
    Action2048 move = GetParam();

    game.step(move);
    std::vector<std::vector<int>> obtained_state = game.get_state();

    std::vector<std::vector<int>> expected_state;
    switch (move.action) {
        case Action2048::ActionType::UP:
            expected_state = {
                    { 0, 32, 16,  0},
                    { 0, 64,  8,  0},
                    { 0,  0,  0,  0},
                    { 0,  0,  0,  0},
            };
            break;
        case Action2048::ActionType::DOWN:
            expected_state = {
                    { 0,  0,  0,  0},
                    { 0,  0,  0,  0},
                    { 0, 32, 16,  0},
                    { 0, 64,  8,  0},
            };
            break;
        case Action2048::ActionType::LEFT:
            expected_state = {
                    { 0,  0,  0,  0},
                    {32, 16,  0,  0},
                    {64,  8,  0,  0},
                    { 0,  0,  0,  0},
            };
            break;
        case Action2048::ActionType::RIGHT:
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
                Action2048(Action2048::ActionType::UP),
                Action2048(Action2048::ActionType::DOWN),
                Action2048(Action2048::ActionType::LEFT),
                Action2048(Action2048::ActionType::RIGHT)
                ));


TEST(TestMovementAndMerges, TestMoveUp) {
    GameState2048<4> game({
            {16,  0, 32, 32},
            {16, 32, 64, 16},
            {16,  0, 64,  0},
            {16, 32, 64,  0},
    });
    int score = game.step(Action2048(Action2048::ActionType::DOWN));
    EXPECT_EQ(score, (16 + 16 + 32 + 64) * 2);
    std::vector<std::vector<int>> obtained_state = game.get_state();

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
