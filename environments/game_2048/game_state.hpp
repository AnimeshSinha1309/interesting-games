#ifndef INTERESTING_GAMES_GAMESTATE2048_H
#define INTERESTING_GAMES_GAMESTATE2048_H

#include <array>
#include <vector>

#include "../meta/games.hpp"


class Action2048 {
public:
    enum class ActionType {
        UP,
        DOWN,
        LEFT,
        RIGHT,
    };
    ActionType action;
    Action2048(ActionType action_type) : action{action_type} {}
};

template<std::size_t size>
class GameState2048 : public MetaGameState<Action2048> {
protected:
    std::array<std::array<int, size>, size> tiles;
    int total_score;

    /**
     * Puts a new tile 2/4 on a random position on the board
     * @return value on the new tile placed
     */
    int place_new_tile();

    /**
     * Pushes all the tiles in one direction, merges pairs with the same value to make higher tiles
     * @param move: the direction we should move in
     * @return score increase in this move
     */
    int push_and_merge(Action2048 move);

public:
    /**
     * Starts a game with 2 tiles on the board
     */
    GameState2048();

    /**
     * Loads a game state by forcing the layout of the game board to match the one
     * specified by a 2-D array.
     * @param board: matrix of numbers 0 (empty), 2, 4, 8, ..., which represents the game state
     * @param score: current score of the game
     */
    GameState2048(std::vector<std::vector<int>> board, int score = 0);

    /**
     * Actuates a move (equivalent to a finger swipe on the game state.
     * @param move: the direction to move in
     * @return score increase in this move
     */
    int step(Action2048 move);

    /**
     * Gets the score of the current game state. The score is defined as the sum of all
     * the tiles that are present on the game board.
     * @return current score of the game state
     */
    [[nodiscard]] int score() noexcept;

    /**
     * Checks if the game state is terminal and no more moves can be made.
     * @return whether or not the game is done
     */
    [[nodiscard]] bool is_done() noexcept;

    /**
     * Gets the current state of the game board as a 2-D matrix.
     * @return 2-D matrix of numbers, 0 for empty, 2, 4, 8, ..., for the tiles
     */
    [[nodiscard]] std::vector<std::vector<int>> get_state() noexcept;

    /**
     * Converts the board to a string representation
     * @return string representation of the board
     */
    [[nodiscard]] virtual std::string to_string() noexcept;
};

#endif //INTERESTING_GAMES_GAMESTATE2048_H
