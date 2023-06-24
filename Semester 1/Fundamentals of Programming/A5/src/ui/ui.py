from src.services.functions import Functions


class Ui:
    def __init__(self):
        self._func = Functions()

    def _main_menu(self):
        print("1. Add expense")
        print("2. Show expenses")
        print("3. Filter expenses")
        print("4. Undo")
        print("5. Exit")

    def _show_expenses(self):
        expenses = self._func.show_expenses()
        for e in expenses:
            print(str(e))

    def _add_expenses(self):
        print("Day: ")
        day = int(input())
        print("Expense: ")
        expense = input()
        print("Type: ('food', 'car', 'housekeeping', 'books')")
        t = input()
        if (t == 'food' or t == 'car' or t == 'housekeeping' or t == 'books') and (0 < day < 31):
            self._func.add_expense(day, expense, t)
        else:
            print("Unknown type or invalid day!")

    def _filter_expenses(self):
        print("Insert the value to compare the list of expenses with")
        n = int(input())
        result = self._func.filter_expense(n)
        print("Here is your list")
        for r in result:
            print(str(r))

    def _undo(self):
        self._func.undo()

    def start(self):
        self._func.generate_expenses()
        self._show_expenses()

        count = 0

        while True:
            self._main_menu()
            opt = input()
            if opt == '1':
                self._add_expenses()
                count += 1
            elif opt == '2':
                self._show_expenses()
            elif opt == '3':
                self._filter_expenses()
                count += 1
            elif opt == '4':
                if count == 0:
                    print("No more steps to undo")
                else:
                    self._undo()
                    count -= 1
            elif opt == '5':
                return
            else:
                print("Unknown option!")


console = Ui()

console.start()
