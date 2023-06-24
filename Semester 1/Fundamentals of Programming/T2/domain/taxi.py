class Taxi:
    def __init__(self, id, fare, x, y):
        self._y = y
        self._x = x
        self._fare = fare
        self._id = id

    @property
    def id(self):
        return self._id

    @property
    def fare(self):
        return self._fare

    @fare.setter
    def fare(self, new):
        self._fare = new

    @property
    def x(self):
        return self._x

    @x.setter
    def x(self, new):
        self._x = new

    @property
    def y(self):
        return self._y

    @y.setter
    def y(self, new):
        self._y = new

    def __str__(self):
        return "Taxi: " + str(self._id) + " Fare: " + str(self._fare) + " Location: " + (str(self._x) + " " + str(self._y))