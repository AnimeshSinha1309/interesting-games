#ifndef INTERESTING_GAMES_MCTS_H
#define INTERESTING_GAMES_MCTS_H

#include <array>
#include <memory>

using reward_t = double;

template <typename GameStateClass, typename ActionEnum, typename MemoryClass>
class MonteCarloTreeSearch {
private:
    template <typename StateClass>
    struct TreeNode {
        std::unique_ptr<StateClass> state;
        reward_t r_previous;
        std::array<reward_t, StateClass::NUM_ACTIONS> q_value;
        std::array<int, StateClass::NUM_ACTIONS> n_value;
        std::weak_ptr<TreeNode<StateClass>> parent;
        std::array<std::shared_ptr<TreeNode<StateClass>>, StateClass::NUM_ACTIONS> children;
    };

    std::shared_ptr<TreeNode<GameStateClass>> root;
    MemoryClass memory;

    /**
     * Performs the SELECT stage of MCTS
     * Iteratively moves down the tree to find a leaf node with highest
     * upper confidence bound value in each layer.
     * @return a pointer to the selected node
     */
    auto select() -> std::shared_ptr<TreeNode<GameStateClass>>;

    /**
     * Performs the EXPAND stage of MCTS
     * Creates a new node as the child of the given node corresponding to
     * the given action.
     * @param node: the node that needs to be expanded
     * @param action: action that we are taking from the given node
     */
    void expand(std::shared_ptr<TreeNode<GameStateClass>> node, ActionEnum action);

    /**
     * Performs the ROLLOUT stage of MCTS
     * Gets and approximate estimate of the value of the state in the
     * given node.
     * @param node: the node for which we are estimating the rollout value
     * @return the estimated long-term reward (value-function) from the state
     */
    reward_t rollout(std::shared_ptr<TreeNode<GameStateClass>> node);

    /**
     * Performs the BACKUP stage of MCTS
     * Iteratively updates all the ancestors with the new rewards obtained at
     * the leaves.
     * @param node: node we are starting the backup from
     * @param reward: value estimate obtained at the leaf from rollout
     */
    void backup(std::shared_ptr<TreeNode<GameStateClass>> node, reward_t reward);

public:
    /**
     * Creates a Monte Carlo Tree Search Object using the default
     * constructor of game state.
     * Templated to accept the GameStateClass and ActionClass so that
     * this can be customized to arbitrary games.
     * TODO: Ensure that GameStateClass and ActionClass implement the
     * interfaces MetaGameState and MetaDiscreteAction.
     */
    MonteCarloTreeSearch();

    /**
     * Runs the tree search and returns the best action that can be
     * taken from the root.
     * @param n_mcts: number of MCTS iterations to run for
     * @return the best action form the root state
     */
    [[nodiscard]] ActionEnum search(int n_mcts = 1000) noexcept;

    /**
     * Changes the root to one that is a child of the current root,
     * corresponding to the given action.
     * This action should preferrably be the one returned by search.
     * @param action: action taken from the root
     */
    void next(ActionEnum action);
};

#endif //INTERESTING_GAMES_MCTS_H
