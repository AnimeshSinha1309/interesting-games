#include <pybind11/pybind11.h>
#include <pybind11/stl_bind.h>

#include <map>
#include <vector>

#include "environments/game_2048/game_state.hpp"

PYBIND11_MAKE_OPAQUE(std::vector<std::vector<int>>);

PYBIND11_MODULE(reinterest, m) {
  m.doc() = "A simulation environment for the 2048 game with board size 4x4";
  pybind11::class_<GameState2048<4>>(m, "GameState2048")
      .def(pybind11::init<>())
      .def("step", &GameState2048<4>::step)
      .def("score", &GameState2048<4>::score)
      .def("done", &GameState2048<4>::is_done)
      .def("__str__", &GameState2048<4>::to_string);
}
