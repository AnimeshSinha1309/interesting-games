#include <pybind11/pybind11.h>
#include "environments/game_2048/game_state.hpp"

PYBIND11_MODULE(game_2048, m) {
    m.doc() = "A simulation environment for the 2048 game";
    pybind11::class_<GameState2048<4>>(m, "GameState2048")
        .def(pybind11::init<int>())
        .def("score", &GameState2048<4>::score);
}
