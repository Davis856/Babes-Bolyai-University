from src.service.service import CityService


class UI:
    def __init__(self):
        self.__service = CityService()

    def start(self):
        data = self.__service.data()
        for i in range(0, 5):
            print("In year " + str(i + 1) + ", " + str(data.starved) + " people starved." + "\n" +
                  str(data.new_residents) + " came to the city." + "\n" + "City population is " + str(
                data.population) + "\n" + "City owns " + str(
                data.land) + " acres of land." + "\n" + "Harvest was " + str(
                data.harvest) + " units per acre." + "\n" + "Rats ate " + str(
                data.eaten) + " units." + "\n" + "Land price is " + str(
                data.land_price) + " units per acre." + "\n" + "Grain stocks are " + str(data.grain_stocks) + " units.")
            print("Acres to buy/sell(+/-) -> ")
            acres = int(input())
            try:
                self.__service.acres_check(acres)
                self.__service.acres_trade(acres)
            except ValueError:
                print("Error: check if the amount of acres that you want to buy/sell is okay.")
            print("Units to feed the population ->")
            units = int(input())
            try:
                self.__service.feed_check(units)
                feed = self.__service.feed_population(units)
            except ValueError:
                print("Error: check if the amount of grain units is correct!")
            print("Acres to plant -> ")
            acres_p = int(input())
            try:
                self.__service.plant_check(acres_p)
                self.__service.harvest(acres_p)
            except ValueError:
                print("Error: check if the amount of acres you want to plant is correct!")
            if feed is False:
                print("Half or more of your people starved. Game over!")
                return
            self.__service.rat_chance()
        if data.population >= 100 and data.land >= 1000:
            print("Congratulations! You won the game!")
        else:
            print("Defeat!")


ui = UI()
ui.start()
