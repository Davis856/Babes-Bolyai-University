class struct:
    def __init__(self, list):
        self._data = list
        self._length = len(list)

    @property
    def list(self):
        return self._data

    @property
    def length(self):
        return self._length

    @length.setter
    def length(self, new):
        self._length = new

    def append(self, elem):
        self._data.append(elem)
        self._length += 1

    def insert(self, index, elem):
        self._data.insert(index, elem)
        self._length += 1

    def copy(self):
        copied = self._data.copy()
        return struct(copied)

    def __getitem__(self, key):
        if key < 0:
            raise IndexError
        else:
            return self._data[key]

    def __setitem__(self, key, value):
        if key < 0:
            raise IndexError
        else:
            self._data[key] = value

    def __delitem__(self, key):
        if key < 0:
            raise IndexError
        else:
            self._length -= 1
            self._data.pop(key)

    def __next__(self):
        # Stop iteration when other elements are not available
        if self.__iterator == len(self._data):
            raise StopIteration()
        # Move to the next element
        self.__iterator += 1
        return self._data[self.__iterator - 1]

    def __iter__(self):
        self.__iterator = 0
        return self

    def __len__(self):
        index = 0
        while index < len(self._data):
            index += 1
        return index

    def pop(self, key):
        self._data.pop(key)

    # for filter tests
    def even(self, n, y):
        return n % y == 0

    def odd(self, n, y):
        return n % y == 1

    def value(self, a):
        return a

    def filter(self, field, y):
        i = iter(self)
        x = next(i)
        a = 0

        while a < self._length:
            if field(x, y) == 0:
                del self[a]
                if a < self._length - 1:
                    i = iter(self)
                    x = next(i)
                    a = 0
            else:
                x = next(i)
                a += 1

    def sort(self, list, reverse):
        """
        Gnome sort
        Gnome sort way of sorting makes sure that whatever is behind the current index is sorted
        :return:
        """
        index = 0
        while index < self._length:
            if reverse == 1:
                if index == 0 or list(self[index]) <= list(self[index - 1]):
                    index = index + 1
                else:
                    aux = self[index]
                    self[index] = self[index - 1]
                    self[index - 1] = aux
                    index -= 1
            else:
                if index == 0 or list(self[index]) >= list(self[index - 1]):
                    index = index + 1
                else:
                    aux = self[index]
                    self[index] = self[index - 1]
                    self[index - 1] = aux
                    index -= 1
        return self._data
