import uuid
from domain.taxi import Taxi
from domain.ride import Ride
import random


class RideServ:
    def __init__(self):
        self._taxis = []
        self._rides = []

    @staticmethod
    def distance(x, y):
        return sum(abs(x - y))

    def generate(self, n):
        for i in range(n):
            self._taxis.append(Taxi(uuid.uuid4(), 0, random.randint(0, 100), random.randint(0, 100)))

    def taxis(self):
        return self._taxis

    def add_ride(self, x, y):
        if 0 <= x <= 100 and 0 <= y <= 100:
            self._rides.append(Ride(x, y))
        else:
            raise ValueError("Coordinates error")

    def rides(self):
        return self._rides

    def assign(self):
        taxi = 0
        maxd = 100
        for i in range(len(self._taxis)):
            distance = self.distance(self._taxis[i].x, self._taxis[i].y)
            if distance < maxd:
                maxd = distance
                taxi = i
        self._taxis[taxi].fare = maxd
        return [self._taxis[taxi].id, self._taxis[taxi].fare]


