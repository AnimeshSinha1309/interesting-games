#ifndef INTERESTING_GAMES_MEMORY_H
#define INTERESTING_GAMES_MEMORY_H

#include <array>
#include <memory>
#include <queue>

using reward_t = double;

template <typename GameStateClass>
class SimpleMemory {
 public:
  template <typename StateClass>
  struct MemoryItem {
    std::unique_ptr<StateClass> state;
    reward_t value;
    std::array<int, StateClass::NUM_ACTIONS> counts;

    MemoryItem(std::unique_ptr<StateClass> s, reward_t v,
               std::array<int, StateClass::NUM_ACTIONS> c)
        : state(std::move(s)), value(v), counts(c) {}
  };

 protected:
  std::deque<MemoryItem<GameStateClass>> data;
  std::size_t size;

 public:
  /**
   * Returns the next experience from the replay buffer
   * @return the experience item
   */
  MemoryItem<GameStateClass> next();

  /**
   * Stores a single experience in the replay buffer
   * @param state: the state associated with this experience
   * @param value: value function of the state
   * @param counts: visitation counts for each action
   */
  void store(std::unique_ptr<GameStateClass> state, reward_t value,
             std::array<int, GameStateClass::NUM_ACTIONS> counts);
};

#endif  // INTERESTING_GAMES_MEMORY_H
