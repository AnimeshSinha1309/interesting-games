#include "mcts.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../environments/game_2048/game_state.hpp"
#include "memory.hpp"

TEST(MonteCarloTreeSearchTests, BasicTreeGeneration) {
  MonteCarloTreeSearch<GameState2048<4>, GameState2048<4>::ActionType,
                       SimpleMemory<GameState2048<4>>>
      searcher;
}
