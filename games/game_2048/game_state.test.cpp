#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "game_state.hpp"

TEST(GameStateTest, TestBasicMoveUp) {
    GameState game(4);
    game.set_board({
        { 0,  0,  0,  0},
        { 0, 32, 16,  0},
        { 0, 64,  8,  0},
        { 0,  0,  0,  0},
    });
    game.move(GameState::Move::UP);
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
    GameState game(4);
    game.set_board({
       { 0,  0,  0,  0},
       { 0, 32, 16,  0},
       { 0, 64,  8,  0},
       { 0,  0,  0,  0},
    });
    game.move(GameState::Move::DOWN);
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
    GameState game(4);
    game.set_board({
       { 0,  0,  0,  0},
       { 0, 32, 16,  0},
       { 0, 64,  8,  0},
       { 0,  0,  0,  0},
    });
    game.move(GameState::Move::LEFT);
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
    GameState game(4);
    game.set_board({
       { 0,  0,  0,  0},
       { 0, 32, 16,  0},
       { 0, 64,  8,  0},
       { 0,  0,  0,  0},
    });
    game.move(GameState::Move::RIGHT);
    std::vector<std::vector<int>> obtained_state = game.get_board();

    std::vector<std::vector<int>> expected_state = {
        { 0,  0,  0,  0},
        { 0,  0, 32, 16},
        { 0,  0, 64,  8},
        { 0,  0,  0,  0},
    };

    EXPECT_THAT(obtained_state, testing::ElementsAreArray(expected_state));
}
