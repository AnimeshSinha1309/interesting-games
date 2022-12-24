#ifndef INTERESTING_GAMES_MEMORY_H
#define INTERESTING_GAMES_MEMORY_H

#include <array>
#include <queue>

#include "../../environments/meta/games.hpp"

template<typename GameStateClass, int num_actions>
class SimpleMemory {

    struct MemoryItem {
        GameStateClass state;
        reward_t q_value;
        std::array<int, num_actions> n_values;
    };

    std::deque<MemoryItem> data;
    size_t size;

    MemoryItem next() {
        MemoryItem item = data.front();
        data.pop_front();
        size -= 1;
        return item;
    }

    void store(GameStateClass s, reward_t v, std::array<int, num_actions> n) {
        MemoryItem item { .state = s, .q_value = v, .n_values = n };
        size += 1;
        data.push_back(item);
    }
};

#endif //INTERESTING_GAMES_MEMORY_H
