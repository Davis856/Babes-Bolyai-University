import random
from src.domain.expenses import Expense


class Functions:
    def __init__(self):
        """
        Constructor for Functions class
        """
        self._expense_list = []
        self._type_list = []
        self._history = 0
        self._history_list = []
        self._history_list_copy = []
        self._undo_list = []
        self.generate_list_type()

    def generate_list_type(self):
        """
        Generates a list of types to be used in randomising and adding
        :return:
        """
        self._type_list = ['food', 'car', 'housekeeping', 'books']

    def generate_expenses(self):
        """
        Generates 10 expenses at startup
        :return: The list
        """
        for i in range(10):
            self._expense_list.append(
                Expense(random.randint(1, 30), random.randint(1, 1000), random.choice(self._type_list)))
        return self._expense_list

    def add_expense(self, day, amount, t):
        """
        Adds a new expense to the list
        :param day: Day
        :param amount: Expense amount
        :param t: Type
        :return: None
        """
        self._history += 1
        self._undo_list.append([self._history, 'remove'])
        exp = Expense(day, amount, t)
        self._expense_list.append(exp)

    def filter_expense(self, value):
        """
        Filters the list so that it contains only expenses above a certain value read from the console.
        :param value: Certain value
        :return: List that contains only expenses above a certain value
        """
        self._history += 1
        self._history_list = self._expense_list.copy()
        self._history_list_copy.append(self._history_list.copy())
        self._undo_list.append([self._history, 'remove_filter'])
        ok = False
        while not ok:
            ok = True
            for exp in self._expense_list:
                if int(exp.amount) < value:
                    self._expense_list.remove(exp)
                    ok = False
        return self._expense_list

    def show_expenses(self):
        """
        Shows the list
        :return:
        """
        return self._expense_list

    def undo(self):
        """
        Undoes
        :return: A step-back
        """
        param = self._undo_list[-1]
        if param[1] == 'remove':
            self._expense_list.pop()
            self._history -= 1
            self._undo_list.pop()
        elif param[1] == 'remove_filter':
            self._expense_list = self._history_list_copy[-1].copy()
            self._history_list_copy.pop()
            self._history -= 1
            self._undo_list.pop()


def get_day(e):
    return e.day


def get_amount(e):
    return e.amount


def get_type(e):
    return e.t


def test_add_expenses():
    """
    Test function for add function
    :return:
    """
    x = Functions()
    l = [Expense(20, 50, 'books'), Expense(30, 70, 'books')]
    x.add_expense(20, 50, 'books')
    x.add_expense(30, 70, 'books')

    for i in range(len(l)):
        assert get_day(x._expense_list[i]) == l[i].day
        assert get_amount(x._expense_list[i]) == l[i].amount
        assert get_type(x._expense_list[i]) == l[i].t


test_add_expenses()
