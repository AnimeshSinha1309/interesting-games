#ifndef INTERESTING_GAMES_GAMES_HPP
#define INTERESTING_GAMES_GAMES_HPP

#include <iostream>


class MetaDiscreteAction {
    int num_actions();
    MetaDiscreteAction get_action(int index);
};

template <typename ActionSpace>
class MetaGameState {
public:
    /**
     * Actuates a move (equivalent to a finger swipe on the game state.
     * @param move: the direction to move in
     * @return score increase in this move
     */
    virtual int step(ActionSpace move) = 0;

    /**
     * Gets the score of the current game state. The score is defined as the sum of all
     * the tiles that are present on the game board.
     * @return current score of the game state
     */
    [[nodiscard]] virtual int score() noexcept = 0;

    /**
     * Checks if the game state is terminal and no more moves can be made.
     * @return whether or not the game is done
     */
    [[nodiscard]] virtual bool is_done() noexcept = 0;

    /**
     * Converts the board to a string representation
     * @return string representation of the board
     */
    [[nodiscard]] virtual std::string to_string() = 0;
};


#endif //INTERESTING_GAMES_GAMES_HPP
