#ifndef INTERESTING_GAMES_GAMESTATE_H
#define INTERESTING_GAMES_GAMESTATE_H

#include <vector>

int do_something();

class GameState {
private:
    std::vector<int> tiles;
    std::size_t board_size;
    int num_occupied_tiles;

    void place_new_tile();

public:
    enum Move {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    GameState(int board_size);

    /**
     * Actuates a move (equivalent to a finger swipe on the game state.
     * @param move: the direction to move in
     */
    void move(Move move);

    /**
     * Gets the score of the current game state. The score is defined as the sum of all
     * the tiles that are present on the game board.
     * @return current score of the game state
     */
    [[nodiscard]] int score() noexcept;

    /**
     * Loads a game state by forcing the layout of the game board to match the one
     * specified by a 2-D array.
     * @param board: matrix of numbers 0 (empty), 2, 4, 8, ..., which represents the game state
     */
    void set_board(std::vector<std::vector<int>> board);

    /**
     * Gets the current state of the game board as a 2-D matrix.
     * @return 2-D matrix of numbers, 0 for empty, 2, 4, 8, ..., for the tiles
     */
    [[nodiscard]] std::vector<std::vector<int>> get_board();
};

#endif //INTERESTING_GAMES_GAMESTATE_H
