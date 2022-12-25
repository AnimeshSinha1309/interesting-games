#include "mcts.hpp"

template <typename GameStateClass, typename ActionEnum, typename MemoryClass>
std::shared_ptr<MonteCarloTreeSearch<GameStateClass, ActionEnum, MemoryClass>::TreeNode<GameStateClass>>
MonteCarloTreeSearch<GameStateClass, ActionEnum, MemoryClass>::select() {
    return root;
}

template <typename GameStateClass, typename ActionEnum, typename MemoryClass>
void
MonteCarloTreeSearch<GameStateClass, ActionEnum, MemoryClass>::expand(
    std::shared_ptr<MonteCarloTreeSearch<GameStateClass, ActionEnum, MemoryClass>::TreeNode<GameStateClass>> node,
    ActionEnum action) {

}

template <typename GameStateClass, typename ActionEnum, typename MemoryClass>
reward_t
MonteCarloTreeSearch<GameStateClass, ActionEnum, MemoryClass>::rollout(
    std::shared_ptr<MonteCarloTreeSearch<GameStateClass, ActionEnum, MemoryClass>::TreeNode<GameStateClass>> node) {
    return 0.0;
}

template <typename GameStateClass, typename ActionEnum, typename MemoryClass>
void
MonteCarloTreeSearch<GameStateClass, ActionEnum, MemoryClass>::backup(
    std::shared_ptr<MonteCarloTreeSearch<GameStateClass, ActionEnum, MemoryClass>::TreeNode<GameStateClass>> node,
    reward_t reward) {

}

template <typename GameStateClass, typename ActionEnum, typename MemoryClass>
MonteCarloTreeSearch<GameStateClass, ActionEnum, MemoryClass>::MonteCarloTreeSearch() {
}

template <typename GameStateClass, typename ActionEnum, typename MemoryClass>
[[nodiscard]] ActionEnum
MonteCarloTreeSearch<GameStateClass, ActionEnum, MemoryClass>::search(
    int n_mcts) noexcept {
    return ActionEnum::UP;
}

template <typename GameStateClass, typename ActionEnum, typename MemoryClass>
void
MonteCarloTreeSearch<GameStateClass, ActionEnum, MemoryClass>::next(
    ActionEnum action) {
}
