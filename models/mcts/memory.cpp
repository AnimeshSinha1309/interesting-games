#include "memory.hpp"

template<typename GameStateClass>
SimpleMemory<GameStateClass>::MemoryItem<GameStateClass>
SimpleMemory<GameStateClass>::next() {
    SimpleMemory<GameStateClass>::MemoryItem<GameStateClass> item = data.front();
    data.pop_front();
    size -= 1;
    return item;
}

template<typename GameStateClass>
void SimpleMemory<GameStateClass>::store(
    std::unique_ptr<GameStateClass> state,
    reward_t value,
    std::array<int, GameStateClass::NUM_ACTIONS> counts) {
    size += 1;
    data.emplace_back(std::move(state), value, counts);
}
