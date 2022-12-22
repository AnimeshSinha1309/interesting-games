#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "game_state.hpp"

TEST(GameStateTest, TestBasicMoveUp) {
    GameState2048<4> game({
        { 0,  0,  0,  0},
        { 0, 32, 16,  0},
        { 0, 64,  8,  0},
        { 0,  0,  0,  0},
    });

    game.move(GameState2048<4>::Move::UP);
    std::vector<std::vector<int>> obtained_state = game.get_board();

    std::vector<std::vector<int>> expected_state = {
        { 0, 32, 16,  0},
        { 0, 64,  8,  0},
        { 0,  0,  0,  0},
        { 0,  0,  0,  0},
    };

    EXPECT_THAT(obtained_state, testing::ElementsAreArray(expected_state));
}

TEST(GameStateTest, TestBasicMoveDown) {
    GameState2048<4> game({
       { 0,  0,  0,  0},
       { 0, 32, 16,  0},
       { 0, 64,  8,  0},
       { 0,  0,  0,  0},
    });
    game.move(GameState2048<4>::Move::DOWN);
    std::vector<std::vector<int>> obtained_state = game.get_board();
    std::vector<std::vector<int>> expected_state = {
        { 0,  0,  0,  0},
        { 0,  0,  0,  0},
        { 0, 32, 16,  0},
        { 0, 64,  8,  0},
    };
    EXPECT_THAT(obtained_state, testing::ElementsAreArray(expected_state));
}

TEST(GameStateTest, TestBasicMoveLeft) {
    GameState2048<4> game({
       { 0,  0,  0,  0},
       { 0, 32, 16,  0},
       { 0, 64,  8,  0},
       { 0,  0,  0,  0},
    });
    game.move(GameState2048<4>::Move::LEFT);
    std::vector<std::vector<int>> obtained_state = game.get_board();
    std::vector<std::vector<int>> expected_state = {
        { 0,  0,  0,  0},
        {32, 16,  0,  0},
        {64,  8,  0,  0},
        { 0,  0,  0,  0},
    };
    EXPECT_THAT(obtained_state, testing::ElementsAreArray(expected_state));
}

TEST(GameStateTest, TestBasicMoveRight) {
    GameState2048<4> game({
       { 0,  0,  0,  0},
       { 0, 32, 16,  0},
       { 0, 64,  8,  0},
       { 0,  0,  0,  0},
    });
    game.move(GameState2048<4>::Move::RIGHT);
    std::vector<std::vector<int>> obtained_state = game.get_board();
    std::vector<std::vector<int>> expected_state = {
        { 0,  0,  0,  0},
        { 0,  0, 32, 16},
        { 0,  0, 64,  8},
        { 0,  0,  0,  0},
    };
    EXPECT_THAT(obtained_state, testing::ElementsAreArray(expected_state));
}
