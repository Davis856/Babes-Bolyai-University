class Expense:
    def __init__(self, day, amount, t):
        """
        Constructor for expense class
        :param day: day
        :param amount: amount
        :param t: type
        """
        if day < 1 or day > 30:
            raise ValueError("Day must be between 1 and 30!")
        self._expense_day = day
        self._expense_amount = amount
        self._expense_type = t

    @property
    def day(self):
        return self._expense_day

    @day.setter
    def day(self, new_value):
        self._expense_day = new_value

    @property
    def amount(self):
        return self._expense_amount

    @amount.setter
    def amount(self, new_value):
        self._expense_amount = new_value

    @property
    def t(self):
        return self._expense_type

    @t.setter
    def t(self, new_value):
        self._expense_type = new_value

    def __str__(self):
        return "day: " + str(self._expense_day) + " amount: " + str(self._expense_amount) + " type: " + str(
            self._expense_type)

