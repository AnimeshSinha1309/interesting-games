#include "game_state.hpp"

#include <cstdlib>
#include <stdexcept>
#include <iostream>


GameState::GameState(int board_size) {
    this->board_size = board_size;
    this->num_occupied_tiles = 0;
    this->tiles = *new std::vector<int>(board_size * board_size, 0);
    place_new_tile();
}

void GameState::place_new_tile() {
    int num_empty_tiles = board_size * board_size - num_occupied_tiles;
    int chosen_value = rand() < 0.9 ? 2 : 4;
    int chosen_position = num_empty_tiles * rand() + 1;
    for (auto &tile : tiles) {
        if (tile != 0) {
            chosen_position--;
            if (chosen_position == 0) {
                tile = chosen_value;
                break;
            }
        }
    }
}

[[nodiscard]] int GameState::score() noexcept {
    int total = 0;
    for (auto tile : tiles) {
        total += tile;
    }
    return total;
}

void GameState::move(GameState::Move move) {
    switch (move) {
        case GameState::Move::UP:
            for (int i = 1; i < static_cast<int>(board_size); i++) {
                for (int j = 0; j < static_cast<int>(board_size); j++) {
                    for (int cur_pos = i; cur_pos > 0 && tiles[(cur_pos - 1) * board_size + j] == 0; cur_pos--) {
                        tiles[(cur_pos - 1) * board_size + j] = tiles[cur_pos * board_size + j];
                        tiles[cur_pos * board_size + j] = 0;
                    }
                }
            }
            break;
        case GameState::Move::DOWN:
            for (int i = static_cast<int>(board_size) - 2; i >= 0; i--) {
                for (int j = 0; j < static_cast<int>(board_size); j++) {
                    for (int cur_pos = i; cur_pos < static_cast<int>(board_size) - 1 && tiles[(cur_pos + 1) * board_size + j] == 0; cur_pos++) {
                        tiles[(cur_pos + 1) * board_size + j] = tiles[cur_pos * board_size + j];
                        tiles[cur_pos * board_size + j] = 0;
                    }
                }
            }
            break;
        case GameState::Move::LEFT:
            for (int i = 0; i < static_cast<int>(board_size); i++) {
                for (int j = 1; j < static_cast<int>(board_size); j++) {
                    for (int cur_pos = j; cur_pos > 0 && tiles[i * board_size + (cur_pos - 1)] == 0; cur_pos--) {
                        tiles[i * board_size + (cur_pos - 1)] = tiles[i * board_size + cur_pos];
                        tiles[i * board_size + cur_pos] = 0;
                    }
                }
            }
            break;
        case GameState::Move::RIGHT:
            for (int i = 0; i < static_cast<int>(board_size); i++) {
                for (int j = static_cast<int>(board_size) - 2; j >= 0; j--) {
                    for (int cur_pos = j; cur_pos < static_cast<int>(board_size) - 1 && tiles[i * board_size + (cur_pos + 1)] == 0; cur_pos++) {
                        tiles[i * board_size + (cur_pos + 1)] = tiles[i * board_size + cur_pos];
                        tiles[i * board_size + cur_pos] = 0;
                    }
                }
            }
            break;
    }
}

void GameState::set_board(std::vector<std::vector<int>> board) {
    if (board.size() != board_size) {
        throw std::length_error("The number of rows in the board has to equal board-size of the game");
    }
    for (int i = 0; i < static_cast<int>(board_size); i++) {
        if (board[i].size() != board_size) {
            throw std::length_error("The number of rows in the board has to equal board-size of the game");
        }

        for (int j = 0; j < static_cast<int>(board_size); j++) {
            if (__builtin_popcount(board[i][j]) > 1 || board[i][j] < 0) {
                throw std::domain_error("The elements of the board must be 0 or a power of 2");
            }
            tiles[i * board_size + j] = board[i][j];
        }
    }
}

[[nodiscard]] std::vector<std::vector<int>> GameState::get_board() {
    if (tiles.size() != board_size * board_size) {
        throw std::length_error("The number of rows in the board has to equal board-size of the game");
    }

    std::vector<std::vector<int>> ans(board_size, std::vector<int>(board_size, 0));
    for (int i = 0; i < static_cast<int>(board_size); i++) {
        for (int j = 0; j < static_cast<int>(board_size); j++) {
            ans[i][j] = tiles[i * board_size + j];
        }
    }
    return ans;
}
