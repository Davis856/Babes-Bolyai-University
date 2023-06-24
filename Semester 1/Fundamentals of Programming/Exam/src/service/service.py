from src.domain.domain import City
import random


class CityService:
    def __init__(self):
        self.__data = City(0, 0, 100, 1000, 3, 200, 20, 2800)

    def data(self):
        """
        Function to get the whole city object
        :return: City object
        """
        return self.__data

    def acres_check(self, amount):
        """
        Checks if the user input is valid
        :param amount: This year's user input amount of acres to buy/sell
        :return: ValueErrors if the user input is not valid.
        """
        if amount < 0:
            if self.__data.land - (-amount) < 0:
                raise ValueError("You cannot sell more land than you have!")
        elif amount >= 0:
            if self.__data.land_price * amount > self.__data.grain_stocks:
                raise ValueError("You cannot buy more land than you have grain for!")

    def feed_check(self, amount):
        """
        Checks if the user input is valid
        :param amount: This year's user input amount of units to feed the population
        :return: ValueErrors if the user input is not valid.
        """
        if self.__data.grain_stocks <= amount:
            raise ValueError("You cannot feed people with grain you do not have!")

    def plant_check(self, amount):
        """
        Checks if the user input is valid
        :param amount: This year's user input amount of acres to plant
        :return: ValueErrors if the user input is not valid.
        """
        if self.__data.land < amount:
            raise ValueError("You cannot plant more acres than you have!")
        people = amount // 10
        if self.__data.population - people < 0:
            raise ValueError("Too many acres to plant!")

    def acres_trade(self, amount):
        """
        Buy/sell acres of land.
        :param amount: How many acres to buy/sell
        :return: A new amount of acres
        """
        self.__data.grain_stocks -= self.__data.land_price * amount
        self.__data.land += amount
        self.__data.land_price = random.randint(15, 25)
        return self.__data.land

    def feed_population(self, amount):
        """
        How much grain used to feed population
        :param amount: Amount used to feed population
        :return: A new amount of grain or False if half of the population will starve
        """
        current_people = self.__data.population  # so that we fix the more people died than existed bug
        to_feed = amount // 20  # how many people can we feed from our amount
        fed = to_feed - self.__data.population  # if the number is negative that means that some people starve
        if fed < 0:
            self.__data.starved = -fed
            if self.__data.starved >= self.__data.population // 2:
                return False
            self.__data.population -= self.__data.starved
            if self.__data.population > current_people:
                self.__data.starved = current_people
                self.__data.population = 0
        new_res = random.randint(0, 10)
        self.__data.new_residents = new_res
        self.__data.population += new_res
        self.__data.grain_stocks -= amount
        return self.__data.grain_stocks

    def harvest(self, acres):
        """
        How much grain is harvested through the year
        :param acres: How many planted acres to harvest
        :return:
        """
        unit = random.randint(1, 6)
        self.__data.harvest = unit
        self.__data.grain_stocks += self.__data.harvest * acres
        return self.__data.grain_stocks

    def rat_chance(self):
        """
        Rats have 20% chance of eating some of the grains, max 10%.
        :return: Amount of grains eaten
        """
        chance_eaten = random.randint(1, 100)
        if chance_eaten <= 20:
            chance_eat = random.randint(1, 10)
            percentage = 100 * (chance_eat // self.__data.grain_stocks)
            self.__data.grain_stocks -= percentage
            self.__data.eaten = percentage
        else:
            self.__data.eaten = 0
        return self.__data.eaten
