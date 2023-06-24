class City:
    def __init__(self, starved, new_residents, population, land, harvest, eaten, land_price, grain_stocks):
        self.__starved = starved
        self.__new_residents = new_residents
        self.__population = population
        self.__land = land
        self.__harvest = harvest
        self.__eaten = eaten
        self.__land_price = land_price
        self.__grain_stocks = grain_stocks

    @property
    def starved(self):
        return self.__starved

    @starved.setter
    def starved(self, new):
        self.__starved = new

    @property
    def new_residents(self):
        return self.__new_residents

    @new_residents.setter
    def new_residents(self, new):
        self.__new_residents = new

    @property
    def population(self):
        return self.__population

    @population.setter
    def population(self, new):
        self.__population = new

    @property
    def land(self):
        return self.__land

    @land.setter
    def land(self, new):
        self.__land = new

    @property
    def harvest(self):
        return self.__harvest

    @harvest.setter
    def harvest(self, new):
        self.__harvest = new

    @property
    def eaten(self):
        return self.__eaten

    @eaten.setter
    def eaten(self, new):
        self.__eaten = new

    @property
    def land_price(self):
        return self.__land_price

    @land_price.setter
    def land_price(self, value):
        self.__land_price = value

    @property
    def grain_stocks(self):
        return self.__grain_stocks

    @grain_stocks.setter
    def grain_stocks(self, value):
        self.__grain_stocks = value

    # for testing purposes
    def __str__(self):
        return "Starved: " + str(self.__starved) + "\n" + "New: " + str(
            self.__new_residents) + "\n" + "Population: " + str(self.__population) + "\n" + "Land: " + str(
            self.__land) + "\n" + "Harvest: " + str(self.__harvest) + "\n" + "Eaten: " + str(
            self.__eaten) + "\n" + "Land price: " + str(self.__land_price) + "\n" + "Grain stocks: " + str(
            self.__grain_stocks)


