#include <iostream>
#include <vector>

#include "game_2048/game_state.hpp"


int main() {
    GameState game(4);
    game.set_board({
                           { 0,  0,  0,  0},
                           { 0, 32, 16,  0},
                           { 0, 64,  8,  0},
                           { 0,  0,  0,  0},
                   });
    game.move(GameState::Move::UP);
    std::vector<std::vector<int>> expected_state = {
            { 0, 32, 16,  0},
            { 0, 64,  8,  0},
            { 0,  0,  0,  0},
            { 0,  0,  0,  0},
    };
    std::vector<std::vector<int>> obtained_state = game.get_board();

    for (auto el : obtained_state) {
        for (auto it : el) {
            std::cout << it << ' ';
        }
        std::cout << std::endl;
    }
}
