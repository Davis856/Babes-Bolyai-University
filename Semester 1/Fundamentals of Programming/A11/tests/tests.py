import unittest

from ai.ai import AI
from board.board import Board


class Tests(unittest.TestCase):
    def setUp(self):
        self.__board = Board(6)
        self.__ai = AI()

    def test_move(self):
        self.__board.move("A0", "b")
        self.assertEqual(str(self.__board.data[0]), "['b', 0, 0, 0, 0, 0]")
        with self.assertRaises(Exception):
            self.__board.move("E110", "b")
        with self.assertRaises(Exception):
            self.__board.move("A0", "b")

    def test_empty_squares(self):
        self.__board.move("A0", "b")
        self.assertEqual(str(self.__board.empty_squares()),
                         "[(0, 1), (0, 2), (0, 3), (0, 4), (0, 5), (1, 0), (1, 1), (1, 2), (1, 3), (1, 4), (1, 5), (2, 0), (2, 1), (2, 2), (2, 3), (2, 4), (2, 5), (3, 0), (3, 1), (3, 2), (3, 3), (3, 4), (3, 5), (4, 0), (4, 1), (4, 2), (4, 3), (4, 4), (4, 5), (5, 0), (5, 1), (5, 2), (5, 3), (5, 4), (5, 5)]")

    def test_check(self):
        self.__board.move("A0", "b")
        self.__board.move("B0", "b")
        self.__board.move("C0", "b")
        self.__board.move("D0", "b")
        self.__board.move("E0", "b")
        self.assertEqual(
            self.__board.check(self.__board.data[0][4 - 4], self.__board.data[0][4 - 3], self.__board.data[0][4 - 2],
                               self.__board.data[0][4 - 1], self.__board.data[0][4], "b"), True)
        self.assertEqual(
            self.__board.check(self.__board.data[0][4 - 4], self.__board.data[0][4 - 3], self.__board.data[0][4 - 2],
                               self.__board.data[0][4 - 1], self.__board.data[1][4], "b"), False)

    def test_checkwin_true(self):
        self.__board.move("A0", "●")
        self.__board.move("B0", "●")
        self.__board.move("C0", "●")
        self.__board.move("D0", "●")
        self.__board.move("E0", "●")
        self.assertEqual(self.__board.checkwin(), True)

    def test_checkwin_false(self):
        self.__board.move("A0", "b")
        self.__board.move("B0", "b")
        self.__board.move("C0", "b")
        self.__board.move("D0", "b")
        self.assertEqual(self.__board.checkwin(), False)

    def test_ai_move_random(self):
        self.__board.move(self.__ai.move(self.__board), "○")
        self.assertNotEqual(self.__board.data, [[0, 0, 0, 0, 0],
                                                [0, 0, 0, 0, 0],
                                                [0, 0, 0, 0, 0],
                                                [0, 0, 0, 0, 0],
                                                [0, 0, 0, 0, 0]])

    def test_board_str(self):
        self.assertEqual(str(self.__board), "+---+---+---+---+---+---+---+\n"
                                            "| / | A | B | C | D | E | F |\n"
                                            "+===+===+===+===+===+===+===+\n"
                                            "| 0 |   |   |   |   |   |   |\n"
                                            "+---+---+---+---+---+---+---+\n"
                                            "| 1 |   |   |   |   |   |   |\n"
                                            "+---+---+---+---+---+---+---+\n"
                                            "| 2 |   |   |   |   |   |   |\n"
                                            "+---+---+---+---+---+---+---+\n"
                                            "| 3 |   |   |   |   |   |   |\n"
                                            "+---+---+---+---+---+---+---+\n"
                                            "| 4 |   |   |   |   |   |   |\n"
                                            "+---+---+---+---+---+---+---+\n"
                                            "| 5 |   |   |   |   |   |   |\n"
                                            "+---+---+---+---+---+---+---+")

        self.__board.move("A0", "b")

        self.assertEqual(str(self.__board), "+---+---+---+---+---+---+---+\n"
                                            "| / | A | B | C | D | E | F |\n"
                                            "+===+===+===+===+===+===+===+\n"
                                            "| 0 | b |   |   |   |   |   |\n"
                                            "+---+---+---+---+---+---+---+\n"
                                            "| 1 |   |   |   |   |   |   |\n"
                                            "+---+---+---+---+---+---+---+\n"
                                            "| 2 |   |   |   |   |   |   |\n"
                                            "+---+---+---+---+---+---+---+\n"
                                            "| 3 |   |   |   |   |   |   |\n"
                                            "+---+---+---+---+---+---+---+\n"
                                            "| 4 |   |   |   |   |   |   |\n"
                                            "+---+---+---+---+---+---+---+\n"
                                            "| 5 |   |   |   |   |   |   |\n"
                                            "+---+---+---+---+---+---+---+")

    def test_ai_move_check(self):
        self.__board.move("A0", "●")
        self.__board.move("B0", "●")
        self.__board.move("C0", "●")
        self.__board.move("D0", "●")
        self.__board.move(self.__ai.move(self.__board), "○")
        self.assertEqual(self.__board.data, [['●', '●', '●', '●', '○', 0],
                                             [0, 0, 0, 0, 0, 0],
                                             [0, 0, 0, 0, 0, 0],
                                             [0, 0, 0, 0, 0, 0],
                                             [0, 0, 0, 0, 0, 0],
                                             [0, 0, 0, 0, 0, 0]])

    def test_ai_can_win(self):
        self.__board.move("A0", "○")
        self.__board.move("B0", "○")
        self.__board.move("C0", "○")
        self.__board.move("D0", "○")
        self.__board.move(self.__ai.move(self.__board), "○")
        self.assertEqual(self.__board.data, [['○', '○', '○', '○', '○', 0],
                                             [0, 0, 0, 0, 0, 0],
                                             [0, 0, 0, 0, 0, 0],
                                             [0, 0, 0, 0, 0, 0],
                                             [0, 0, 0, 0, 0, 0],
                                             [0, 0, 0, 0, 0, 0]])

    def test_ai_can_win_else(self):
        self.__board.move("A0", "○")
        self.__board.move("B0", "○")
        self.__board.move("C0", "○")
        self.__board.move("D0", "○")
        self.__board.move("E0", "●")
        self.__board.move(self.__ai.move(self.__board), "○")
        self.assertNotEqual(self.__board.data, [['○', '○', '○', '○', '●', 0],
                                                [0, 0, 0, 0, 0, 0],
                                                [0, 0, 0, 0, 0, 0],
                                                [0, 0, 0, 0, 0, 0],
                                                [0, 0, 0, 0, 0, 0]])

    def test_ai_can_win_else_2(self):
        self.__board.move("A0", "○")
        self.__board.move("B0", "○")
        self.__board.move("C0", "○")
        self.__board.move("D0", "○")
        self.__board.move("E0", "●")
        self.__board.move("E1", "●")
        self.__board.move(self.__ai.move(self.__board), "○")
        self.assertNotEqual(self.__board.data, [['○', '○', '○', '○', '●', '●'],
                                                [0, 0, 0, 0, '●', 0],
                                                [0, 0, 0, 0, 0, 0],
                                                [0, 0, 0, 0, 0, 0],
                                                [0, 0, 0, 0, 0, 0]])
