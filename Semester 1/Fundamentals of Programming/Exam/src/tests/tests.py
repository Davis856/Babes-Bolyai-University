import unittest
from src.domain.domain import City
from src.service.service import CityService


class Tests(unittest.TestCase):
    def setUp(self):
        self.__city = City(0, 0, 100, 1000, 3, 200, 20, 2800)
        self.__service = CityService()

    def test_acres_check(self):
        amount_neg = -10000
        amount_pos = 10000
        with self.assertRaises(ValueError):
            self.__service.acres_check(amount_neg)
            self.__service.acres_check(amount_pos)

    def test_feed_check(self):
        amount = 3000
        with self.assertRaises(ValueError):
            self.__service.feed_check(amount)

    def test_plant_check(self):
        amount = 10000
        with self.assertRaises(ValueError):
            self.__service.plant_check(amount)

    def test_acres_trade(self):
        amount = 10000
        result = 11000
        self.assertEqual(result, self.__service.acres_trade(amount))

    def test_feed_population(self):
        amount = 2000
        result = 800
        self.assertEqual(result, self.__service.feed_population(amount))
        amount_error = 10
        self.assertEqual(False, self.__service.feed_population(amount_error))

    # random test, might not work as intended
    def test_harvest(self):
        amount = 1000
        result = 7800
        self.assertEqual(result, self.__service.harvest(amount))

    # random test, might not function 80% of cases
    def test_rat_chance(self):
        result = 200
        self.assertEqual(result, self.__service.rat_chance())

