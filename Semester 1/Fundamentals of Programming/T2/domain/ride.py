class Ride:
    def __init__(self, x, y):
        self._x = x
        self._y = y

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
        return "Location: " + "(" + str(self._x) + " " + str(self._y) + ")"
