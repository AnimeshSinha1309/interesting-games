#ifndef INTERESTING_GAMES_GAMES_HPP
#define INTERESTING_GAMES_GAMES_HPP

#include <iostream>


using reward_t = double;

class MetaDiscreteAction {
    /**
     * Get total number of function in the action space
     * TODO: Make this static
     * @return the number of actions
     */
    virtual int num_actions() = 0;
    
    /**
     * Get the action corresponding to a given index
     * TODO: Make this static
     * @param index: index for which we want the action
     * @return the action corresponding to the given index
     */
    virtual MetaDiscreteAction get_action(int index) = 0;

    /**
     * Get the index corresponding to a given action
     * TODO: Make this static, take action as parameter
     * @return the index corresponding to the given action
     */
    virtual int get_index() = 0;
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
