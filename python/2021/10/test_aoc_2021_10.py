import unittest
import aoc_2021_10 as a


class Test_2021_10(unittest.TestCase):
    def setUp(self):
        self.data = a.clean_input(
            a.get_input("test_input.txt", 2021, 10)
        )

    def test_part_1(self):
        self.assertEqual(26397, a.solve_part_1(self.data))

    def test_part_2(self):
        self.assertEqual(288957, a.solve_part_2(self.data))
