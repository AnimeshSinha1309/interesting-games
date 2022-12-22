#include "game_state.hpp"

#include <cstdlib>
#include <stdexcept>


template<std::size_t size>
GameState2048<size>::GameState2048() {
    this->num_occupied_tiles = 0;
    for (int i = 0; i < static_cast<int>(size); i++) {
        for (int j = 0; j < static_cast<int>(size); j++) {
            this->tiles[i][j] = 0;
        }
    }
    place_new_tile();
    place_new_tile();
}

template<std::size_t size>
GameState2048<size>::GameState2048(std::vector<std::vector<int>> board) {
    num_occupied_tiles = 0;
    if (board.size() != size) {
        throw std::length_error("The number of rows in the board has to equal board-size of the game");
    }
    for (int i = 0; i < static_cast<int>(size); i++) {
        if (board[i].size() != size) {
            throw std::length_error("The number of rows in the board has to equal board-size of the game");
        }

        for (int j = 0; j < static_cast<int>(size); j++) {
            if (__builtin_popcount(board[i][j]) > 1 || board[i][j] < 0) {
                throw std::domain_error("The elements of the board must be 0 or a power of 2");
            }
            tiles[i][j] = board[i][j];
            if (tiles[i][j] != 0) {
                num_occupied_tiles++;
            }
        }
    }
}

template<std::size_t size>
void GameState2048<size>::place_new_tile() noexcept {
    int num_empty_tiles = size * size - num_occupied_tiles;
    int chosen_value = rand() < 0.9 ? 2 : 4;
    int chosen_position = rand() % num_empty_tiles + 1;
    for (int i = 0; i < static_cast<int>(size); i++) {
        for (int j = 0; j < static_cast<int>(size); j++) {
            if (tiles[i][j] == 0) {
                chosen_position--;
                if (chosen_position == 0) {
                    tiles[i][j] = chosen_value;
                    num_occupied_tiles++;
                    return;
                }
            }
        }
    }
}

template<std::size_t size>
void GameState2048<size>::push_and_merge(GameState2048<size>::Move move) noexcept {
    for (int i = 0; i < static_cast<int>(size); i++) {
        std::array<int, size> current_file;
        bool merge_with_previous_possible = false;  // If no tiles in file or previous 2 were merged already
        int position_writing_to = -1;
        // Compute the pushes and merges in the current file
        for (int j = 0; j < static_cast<int>(size); j++) {
            int current_tile;
            switch (move) {
                case GameState2048<size>::Move::UP:
                    current_tile = this->tiles[j][i];
                    break;
                case GameState2048<size>::Move::DOWN:
                    current_tile = this->tiles[size - 1 - j][i];
                    break;
                case GameState2048<size>::Move::LEFT:
                    current_tile = this->tiles[i][j];
                    break;
                case GameState2048<size>::Move::RIGHT:
                    current_tile = this->tiles[i][size - 1 - j];
                    break;
            }
            if (current_tile != 0) {
                if (merge_with_previous_possible && current_file[position_writing_to] == current_tile) {
                    current_file[position_writing_to] += current_tile;
                    merge_with_previous_possible = false;
                } else {
                    position_writing_to++;
                    current_file[position_writing_to] = current_tile;
                    merge_with_previous_possible = true;
                }
            }
        }
        for (position_writing_to++; position_writing_to < static_cast<int>(size); position_writing_to++) {
            current_file[position_writing_to] = 0;
        }
        // Assign the gathered current file to back to the board
        for (int j = 0; j < static_cast<int>(size); j++) {
            switch (move) {
                case GameState2048<size>::Move::UP:
                    this->tiles[j][i] = current_file[j];
                    break;
                case GameState2048<size>::Move::DOWN:
                    this->tiles[size - 1 - j][i] = current_file[j];
                    break;
                case GameState2048<size>::Move::LEFT:
                    this->tiles[i][j] = current_file[j];
                    break;
                case GameState2048<size>::Move::RIGHT:
                    this->tiles[i][size - 1 - j] = current_file[j];
                    break;
            }
        }
    }
}

template<std::size_t size>
[[nodiscard]] int GameState2048<size>::score() noexcept {
    int total = 0;
    for (int i = 0; i < static_cast<int>(size); i++) {
        for (int j = 0; j < static_cast<int>(size); j++) {
            total += this->tiles[i][j];
        }
    }
    return total;
}

template<std::size_t size>
void GameState2048<size>::move(GameState2048<size>::Move move) noexcept {
    push_and_merge(move);
    place_new_tile();
}

template<std::size_t size>
[[nodiscard]] std::vector<std::vector<int>> GameState2048<size>::get_board() {
    std::vector<std::vector<int>> board(size, std::vector<int>(size));
    for (int i = 0; i < static_cast<int>(size); i++) {
        for (int j = 0; j < static_cast<int>(size); j++) {
            board[i][j] = this->tiles[i][j];
        }
    }
    return board;
}

template class GameState2048<4>;
