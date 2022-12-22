import unittest

import game_2048

class GameTests(unittest.TestCase):

    def test_score(self):
        board = game_2048.GameState2048(4)
        self.assertEqual(board.score(), 0)

if __name__ == "__main__":
    unittest.main()
