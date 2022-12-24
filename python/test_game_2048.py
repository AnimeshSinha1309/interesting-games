import unittest

import reinterest


class GameTests(unittest.TestCase):

    def test_score(self):
        board = reinterest.GameState2048()
        print(str(board))
        self.assertLessEqual(board.score(), 0)


if __name__ == "__main__":
    unittest.main()
