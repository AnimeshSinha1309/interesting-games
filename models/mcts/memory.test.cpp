#include "memory.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "../../environments/game_2048/game_state.hpp"

TEST(MemoryTests, SimpleMemoryInputOutput) {
  std::unique_ptr<GameState2048<4>> state_1 =
      std::make_unique<GameState2048<4>>();
  auto tiles_1 = state_1->get_state();
  double value_1 = 12.5;
  std::array<int, 4> counts_1 = {10, 23, 62, 5};

  SimpleMemory<GameState2048<4>> memory;

  memory.store(std::move(state_1), value_1, counts_1);
  decltype(memory)::MemoryItem<GameState2048<4>> replay_1 = memory.next();

  EXPECT_THAT(tiles_1, testing::ElementsAreArray(replay_1.state->get_state()));
  EXPECT_THAT(counts_1, testing::ElementsAreArray(replay_1.counts));
  EXPECT_EQ(value_1, replay_1.value);
}
