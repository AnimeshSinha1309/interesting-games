#include "game_state.hpp"

#include <fmt/core.h>

#include <cstdlib>
#include <stdexcept>

template <std::size_t size>
GameState2048<size>::GameState2048() {
  total_score = 0;
  for (int i = 0; i < static_cast<int>(size); i++) {
    for (int j = 0; j < static_cast<int>(size); j++) {
      tiles[i][j] = 0;
    }
  }
  place_new_tile();
  place_new_tile();
}

template <std::size_t size>
GameState2048<size>::GameState2048(std::vector<std::vector<int>> board,
                                   int score) {
  total_score = score;
  if (board.size() != size) {
    throw std::length_error(
        "The number of rows in the board has to equal board-size of the game");
  }
  for (int i = 0; i < static_cast<int>(size); i++) {
    if (board[i].size() != size) {
      throw std::length_error(
          "The number of rows in the board has to equal board-size of the "
          "game");
    }

    for (int j = 0; j < static_cast<int>(size); j++) {
      if (__builtin_popcount(board[i][j]) > 1 || board[i][j] < 0) {
        throw std::domain_error(
            "The elements of the board must be 0 or a power of 2");
      }
      tiles[i][j] = board[i][j];
    }
  }
}

template <std::size_t size>
int GameState2048<size>::place_new_tile() {
  int num_empty_tiles = 0;
  for (int i = 0; i < static_cast<int>(size); i++) {
    for (int j = 0; j < static_cast<int>(size); j++) {
      if (tiles[i][j] == 0) {
        num_empty_tiles++;
      }
    }
  }
  int chosen_value = ((double)rand() / RAND_MAX) < 0.9 ? 2 : 4;
  int chosen_position = rand() % num_empty_tiles + 1;
  for (int i = 0; i < static_cast<int>(size); i++) {
    for (int j = 0; j < static_cast<int>(size); j++) {
      if (tiles[i][j] == 0) {
        chosen_position--;
        if (chosen_position == 0) {
          tiles[i][j] = chosen_value;
          return chosen_value;
        }
      }
    }
  }
  throw std::logic_error("No new tiles were added");
}

template <std::size_t size>
int GameState2048<size>::push_and_merge(GameState2048<size>::ActionType move) {
  int total_score = 0;
  for (int i = 0; i < static_cast<int>(size); i++) {
    std::array<int, size> current_file;
    bool merge_with_previous_possible =
        false;  // If no tiles in file or previous 2 were merged already
    int position_writing_to = -1;
    // Compute the pushes and merges in the current file
    for (int j = 0; j < static_cast<int>(size); j++) {
      int current_tile;
      switch (move) {
        case GameState2048<size>::ActionType::UP:
          current_tile = this->tiles[j][i];
          break;
        case GameState2048<size>::ActionType::DOWN:
          current_tile = this->tiles[size - 1 - j][i];
          break;
        case GameState2048<size>::ActionType::LEFT:
          current_tile = this->tiles[i][j];
          break;
        case GameState2048<size>::ActionType::RIGHT:
          current_tile = this->tiles[i][size - 1 - j];
          break;
      }
      if (current_tile != 0) {
        if (merge_with_previous_possible &&
            current_file[position_writing_to] == current_tile) {
          current_file[position_writing_to] += current_tile;
          total_score += current_tile * 2;
          merge_with_previous_possible = false;
        } else {
          position_writing_to++;
          current_file[position_writing_to] = current_tile;
          merge_with_previous_possible = true;
        }
      }
    }
    for (position_writing_to++; position_writing_to < static_cast<int>(size);
         position_writing_to++) {
      current_file[position_writing_to] = 0;
    }
    // Assign the gathered current file to back to the board
    for (int j = 0; j < static_cast<int>(size); j++) {
      switch (move) {
        case GameState2048<size>::ActionType::UP:
          this->tiles[j][i] = current_file[j];
          break;
        case GameState2048<size>::ActionType::DOWN:
          this->tiles[size - 1 - j][i] = current_file[j];
          break;
        case GameState2048<size>::ActionType::LEFT:
          this->tiles[i][j] = current_file[j];
          break;
        case GameState2048<size>::ActionType::RIGHT:
          this->tiles[i][size - 1 - j] = current_file[j];
          break;
      }
    }
  }
  return total_score;
}

template <std::size_t size>
[[nodiscard]] int GameState2048<size>::score() noexcept {
  return total_score;
}

template <std::size_t size>
int GameState2048<size>::step(GameState2048<size>::ActionType move) {
  int score_added = push_and_merge(move);
  place_new_tile();
  total_score += score_added;
  return score_added;
}

template <std::size_t size>
bool GameState2048<size>::is_done() noexcept {
  for (int i = 0; i < static_cast<int>(size); i++) {
    for (int j = 0; j < static_cast<int>(size); j++) {
      if (tiles[i][j] == 0) {
        return false;
      }
    }
  }
  for (int i = 0; i < static_cast<int>(size) - 1; i++) {
    for (int j = 0; j < static_cast<int>(size); j++) {
      if (tiles[i][j] == tiles[i + 1][j]) {
        return false;
      }
    }
  }
  for (int i = 0; i < static_cast<int>(size); i++) {
    for (int j = 0; j < static_cast<int>(size) - 1; j++) {
      if (tiles[i][j] == tiles[i][j - 1]) {
        return false;
      }
    }
  }
  return true;
}

template <std::size_t size>
[[nodiscard]] std::vector<std::vector<int>>
GameState2048<size>::get_state() noexcept {
  std::vector<std::vector<int>> board(size, std::vector<int>(size));
  for (int i = 0; i < static_cast<int>(size); i++) {
    for (int j = 0; j < static_cast<int>(size); j++) {
      board[i][j] = tiles[i][j];
    }
  }
  return board;
}

template <std::size_t size>
[[nodiscard]] std::string GameState2048<size>::to_string() noexcept {
  std::string representation = "";
  for (int i = 0; i < static_cast<int>(size); i++) {
    for (int j = 0; j < static_cast<int>(size); j++) {
      representation += fmt::format("{} ", tiles[i][j]);
    }
    representation += "\n";
  }
  return representation;
}

template class GameState2048<4>;
