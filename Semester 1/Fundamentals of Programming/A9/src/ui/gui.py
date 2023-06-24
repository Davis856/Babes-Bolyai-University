from src.services.clientservice import ClientService
from src.services.bookservice import BookService
from src.services.rentalservice import RentalService
from src.repository.repository import RepositoryException
from src.services.undoservice import *
import datetime
import PySimpleGUI as Gui


class GUI:
    def __init__(self, book_service, client_service, rental_service, undo_service):
        self.__book_service = book_service
        self.__client_service = client_service
        self.__rental_service = rental_service
        self.__undo_service = undo_service
        self.__book_func = BookService(self.__book_service, self.__undo_service)
        self.__client_func = ClientService(self.__client_service, self.__undo_service)
        self.__rental_func = RentalService(self.__rental_service, self.__book_service, self.__client_service,
                                           self.__undo_service)

    @staticmethod
    def __main_menu():
        """print("Library Database")
        print("Choose an option below")
        print("1. Add book")
        print("2. Show books")
        print("3. Remove book")
        print("4. Replace book details")
        print("5. Add client")
        print("6. Show clients")
        print("7. Remove client")
        print("8. Replace client details")
        print("9. Rent a book")
        print("10. Return a book")
        print("11. Show current rentals")
        print("12. Search books")
        print("13. Search clients")
        print("14. Most books sold")
        print("15. Best-seller Author")
        print("16. Most active client")
        print("0. Exit")
        """
        Gui.theme("DarkBlue1")
        layout = [[Gui.Button("Add book", size=(15, 1))],
                  [Gui.Button("Show books", size=(15, 1))],
                  [Gui.Button("Remove book", size=(15, 1))],
                  [Gui.Button("Replace book details", size=(15, 1))],
                  [Gui.Button("Add client", size=(15, 1))],
                  [Gui.Button("Show clients", size=(15, 1))],
                  [Gui.Button("Remove client", size=(15, 1))],
                  [Gui.Button("Replace client details", size=(15, 1))],
                  [Gui.Button("Rent a book", size=(15, 1))],
                  [Gui.Button("Return a book", size=(15, 1))],
                  [Gui.Button("Show current rentals", size=(15, 1))],
                  [Gui.Button("Rentals history list", size=(15, 1))],
                  [Gui.Button("Search books", size=(15, 1))],
                  [Gui.Button("Search clients", size=(15, 1))],
                  [Gui.Button("Most books rented", size=(15, 1))],
                  [Gui.Button("Best-seller author", size=(15, 1))],
                  [Gui.Button("Most active client", size=(15, 1))],
                  [Gui.Button("Undo", size=(15, 1))],
                  [Gui.Button("Redo", size=(15, 1))]]

        window = Gui.Window("Library Management", layout)
        return window

    def _show_books(self):
        Gui.theme('DarkBlue1')
        books = self.__book_service.show_book()
        column_list = []
        for i in range(len(books)):
            column_list.append([str(books[i].id), books[i].title, books[i].author])
        headings = ["ID", "Title", "Author"]
        layout = [
            [Gui.Table(values=column_list[0:], headings=headings, def_col_width=25, row_height=25,
                       auto_size_columns=False, key="-BOOK-TABLE-", size=(27, 27))],
            [Gui.Button("Back")]
        ]

        window = Gui.Window("Clients", layout, size=(750, 750))
        button, values = window.read()
        if button == "Back":
            window.close()

    def _add_books(self):
        Gui.theme('DarkBlue1')
        layout = [
            [Gui.Text("Title: ", size=(15, 1)), Gui.InputText()],
            [Gui.Text("Author: ", size=(15, 1)), Gui.InputText()],
            [Gui.Button("Add", size=(15, 1))],
            [Gui.Button("Back", size=(15, 1))]
        ]
        window = Gui.Window("Add Book", layout)
        event, value = window.read()
        index = self.__book_service.last_index()
        if event == "Add":
            try:
                self.__book_service.add_book(index, value[0], value[1], -1)
                Gui.popup_timed("Added successfully")
                window.close()
            except ValueError:
                Gui.popup_timed("Author error: Author is not a name, but a number, please input a real name.")
                window.close()
        elif event == "Back":
            window.close()

    def _remove_books(self):
        Gui.theme("DarkBlue1")
        layout = [
            [Gui.Text("ID of the book you want to remove", size=(50, 1)), Gui.InputText()],
            [Gui.Button("Remove", size=(15, 1))],
            [Gui.Button("Back", size=(15, 1))]
        ]
        window = Gui.Window("Remove Book", layout)
        event, value = window.read()
        if event == "Remove":
            try:
                operation = self.__book_service.remove_book(int(value[0]))
                save = self.__rental_service.remove_book_rental(int(value[0]))
                #for i in range(len(save)):
                    #undo = FunctionCall(self.__rental_service.rent_book, save[i][0], save[i][1],
                     #                   save[i][2], save[i][3], -1, 0)
                    #redo = FunctionCall(self.__rental_service.return_book, save[i][0], save[i][1], "Not yet")
                    #operation.add(Operation(undo, redo))
                #self.__undo_service.record_operation(operation)
                Gui.popup_timed("Removed successfully")
                window.close()
            except RepositoryException:
                Gui.popup_timed("Wrong ID, check it again!")
                window.close()
        elif event == "Back":
            window.close()

    def _replace_book(self):
        Gui.theme("DarkBlue1")
        layout = [
            [Gui.Text("ID of the book you want to replace details of:", size=(50, 1)), Gui.InputText()],
            [Gui.Text("New title: ", size=(15, 1)), Gui.InputText()],
            [Gui.Text("New author: ", size=(15, 1)), Gui.InputText()],
            [Gui.Button("Replace", size=(15, 1))],
            [Gui.Button("Back", size=(15, 1))]
        ]
        window = Gui.Window("Replace book details", layout)
        event, values = window.read()
        if event == "Replace":
            try:
                self.__book_service.replace_book(int(values[0]), values[1], values[2])
                Gui.popup_timed("Replaced successfully")
                window.close()
            except ValueError:
                Gui.popup_timed("Author error or incorrect position, please try again.")
                window.close()
        elif event == "Back":
            window.close()

    def _show_client(self):
        Gui.theme('DarkBlue1')
        client = self.__client_service.show_client()
        column_list = []
        for i in range(len(client)):
            column_list.append([str(client[i].id), client[i].name])
        headings = ["ID", "Name"]
        layout = [
            [Gui.Table(values=column_list[0:], headings=headings, def_col_width=25, row_height=25,
                       auto_size_columns=False, key="-CLIENT-TABLE-", size=(17, 17))],
            [Gui.Button("Back")]
        ]

        window = Gui.Window("Clients", layout, size=(500, 500))
        button, values = window.read()
        if button == "Back":
            window.close()

    def _add_client(self):
        Gui.theme('DarkBlue1')
        layout = [
            [Gui.Text("Name: ", size=(15, 1)), Gui.InputText()],
            [Gui.Button("Add", size=(15, 1))],
            [Gui.Button("Back", size=(15, 1))]
        ]
        window = Gui.Window("Add Client", layout)
        event, value = window.read()
        index = self.__client_service.last_index()
        if event == "Add":
            try:
                self.__client_service.add_client(index, value[0], -1)
                Gui.popup_timed("Added successfully")
                window.close()
            except ValueError:
                Gui.popup_timed("Wrong name format, please try again.")
                window.close()
        elif event == "Back":
            window.close()

    def _remove_client(self):
        Gui.theme("DarkBlue1")
        layout = [
            [Gui.Text("ID of the client you want to remove", size=(50, 1)), Gui.InputText()],
            [Gui.Button("Remove", size=(15, 1))],
            [Gui.Button("Back", size=(15, 1))]
        ]
        window = Gui.Window("Remove Client", layout)
        event, value = window.read()
        if event == "Remove":
            try:
                operation = self.__client_service.remove_client(int(value[0]))
                save = self.__rental_service.remove_client_rental(int(value[0]))
                #for i in range(len(save)):
                 #   undo = FunctionCall(self.__rental_service.rent_book, save[i][0], save[i][1],
                  #                      save[i][2], save[i][3], -1, 0)
                   # redo = FunctionCall(self.__rental_service.return_book, save[i][0], save[i][1], "Not yet")
                    #operation.add(Operation(undo, redo))
                #self.__undo_service.record_operation(operation)
                Gui.popup_timed("Removed successfully")
                window.close()
            except RepositoryException:
                Gui.popup_timed("Wrong ID, check it again!")
                window.close()
        elif event == "Back":
            window.close()

    def _replace_client(self):
        Gui.theme("DarkBlue1")
        layout = [
            [Gui.Text("ID of the client you want to replace details of:", size=(50, 1)), Gui.InputText()],
            [Gui.Text("New name: ", size=(50, 1)), Gui.InputText()],
            [Gui.Button("Replace", size=(15, 1))],
            [Gui.Button("Back", size=(15, 1))]
        ]
        window = Gui.Window("Replace client details", layout)
        event, values = window.read()
        if event == "Replace":
            try:
                self.__client_service.replace_client(int(values[0]), values[1])
                Gui.popup_timed("Replaced successfully")
                window.close()
            except ValueError:
                Gui.popup_timed("Wrong name format or incorrect position, please try again.")
                window.close()
        elif event == "Back":
            window.close()

    def _rent_book(self):
        Gui.theme("DarkBlue1")
        layout = [
            [Gui.Text("ID of the book you want to rent: ", size=(50, 1)), Gui.InputText()],
            [Gui.Text("Client ID: ", size=(50, 1)), Gui.InputText()],
            [Gui.Button("Rent", size=(15, 1))],
            [Gui.Button("Back", size=(15, 1))]
        ]
        window = Gui.Window("Rent book", layout)
        event, values = window.read()
        d = datetime.date(2021, 11, 25)
        rental_id = self.__rental_service.last_index()
        if event == "Rent":
            try:
                self.__client_service.check_id(int(values[1]))
                try:
                    self.__rental_service.rent_book(rental_id, int(values[0]), int(values[1]), d, -1, 1)
                    Gui.popup_timed("Rent successful")
                    window.close()
                except RepositoryException:
                    Gui.popup_timed("Error: could not rent, check if the book is available or not.")
                    window.close()
            except ValueError:
                Gui.popup_timed("Client or Book ID error: ID does not exist")
                window.close()
        elif event == "Back":
            window.close()

    def _return_book(self):
        Gui.theme("DarkBlue1")
        layout = [
            [Gui.Text("ID of the rental: ", size=(35, 1)), Gui.InputText()],
            [Gui.Button("Return", size=(15, 1))],
            [Gui.Button("Back", size=(15, 1))]
        ]
        window = Gui.Window("Return book", layout)
        event, values = window.read()
        d = datetime.date.today()
        # for history_list in service
        history_list = self.__rental_service.history_list()
        book_id = history_list[int(values[0]) - 1][0]
        ##
        if event == "Return":
            try:
                self.__rental_service.return_book(int(values[0]), book_id, d)
                Gui.popup_timed("Return successful")
                window.close()
            except RepositoryException:
                Gui.popup_timed(
                    "Error: could not return,"
                    " check if the book is available or not or if the Rental ID is correct.")
                window.close()
        elif event == "Back":
            window.close()

    def _show_rentals(self):
        Gui.theme('DarkBlue1')
        rentals = self.__rental_service.show_rental()
        column_list = []
        for i in range(len(rentals)):
            column_list.append(
                [rentals[i].rental_id, rentals[i].book_id, rentals[i].client_id, rentals[i].rented_date,
                 rentals[i].returned_date])
        headings = ["ID", "Book ID", "Client ID", "Rent Date", "Return Date"]
        layout = [
            [Gui.Table(values=column_list[0:], headings=headings, def_col_width=15, row_height=25,
                       auto_size_columns=False, key="-RENTALS-TABLE-", size=(27, 27))],
            [Gui.Button("Back")]
        ]

        window = Gui.Window("Clients", layout)
        button, values = window.read()
        if button == "Back":
            window.close()

    def _search_book(self):
        Gui.theme("DarkBlue1")
        layout = [
            [Gui.Text("What do you want to search it by? (id, title, author)", size=(50, 1)), Gui.InputText()],
            [Gui.Button("Search", size=(15, 1))],
            [Gui.Button("Back", size=(15, 1))]
        ]
        window = Gui.Window("Search book", layout)
        event, values = window.read()
        search_list = []
        show_list = False
        if event == "Search":
            if values[0] == "id":
                show_list = True
                id_layout = [[Gui.Text("Type the ID that you want to search: ", size=(50, 1)), Gui.InputText()],
                             [Gui.Button("Search", size=(15, 1))]]
                id_window = Gui.Window("Search by ID", id_layout)
                search, value = id_window.read()
                if search == "Search":
                    search_list = self.__book_service.search_book(values[0], value[0])
                    id_window.close()
                    window.close()
            elif values[0] == "title":
                show_list = True
                title_layout = [[Gui.Text("Type the title that you want to search: ", size=(50, 1)), Gui.InputText()],
                                [Gui.Button("Search", size=(15, 1))]]
                title_window = Gui.Window("Search by ID", title_layout)
                search, value = title_window.read()
                if search == "Search":
                    search_list = self.__book_service.search_book(values[0], value[0])
                    title_window.close()
                    window.close()
            elif values[0] == "author":
                show_list = True
                author_layout = [[Gui.Text("Type the author that you want to search: ", size=(50, 1)), Gui.InputText()],
                                 [Gui.Button("Search", size=(15, 1))]]
                author_window = Gui.Window("Search by ID", author_layout)
                search, value = author_window.read()
                if search == "Search":
                    search_list = self.__book_service.search_book(values[0], value[0])
                    author_window.close()
                    window.close()
            else:
                Gui.popup_timed("Wrong type!")
                window.close()

        if show_list:
            column_list = []
            for i in range(len(search_list)):
                column_list.append([str(search_list[i].id), search_list[i].title, search_list[i].author])
            headings = ["ID", "Title", "Author"]
            layout2 = [
                [Gui.Table(values=column_list[0:], headings=headings, def_col_width=25, row_height=25,
                           auto_size_columns=False, key="-SEARCH-BOOK-TABLE-", size=(27, 27))],
                [Gui.Button("Back")]
            ]

            window2 = Gui.Window("Books", layout2, size=(750, 750))
            button, values = window2.read()
            if button == "Back":
                window2.close()
        else:
            pass

    def _search_client(self):
        Gui.theme("DarkBlue1")
        layout = [
            [Gui.Text("What do you want to search it by?(id, name)", size=(50, 1)), Gui.InputText()],
            [Gui.Button("Search", size=(15, 1))],
            [Gui.Button("Back", size=(15, 1))]
        ]
        window = Gui.Window("Search book", layout)
        event, values = window.read()
        search_list = []
        show_list = False
        if event == "Search":
            if values[0] == "id":
                show_list = True
                id_layout = [[Gui.Text("Type the ID that you want to search: ", size=(50, 1)), Gui.InputText()],
                             [Gui.Button("Search", size=(15, 1))]]
                id_window = Gui.Window("Search by ID", id_layout)
                search, value = id_window.read()
                if search == "Search":
                    search_list = self.__client_service.search_client(values[0], value[0])
                    id_window.close()
                    window.close()
            elif values[0] == "name":
                show_list = True
                title_layout = [[Gui.Text("Type the name that you want to search: ", size=(50, 1)), Gui.InputText()],
                                [Gui.Button("Search", size=(15, 1))]]
                title_window = Gui.Window("Search by ID", title_layout)
                search, value = title_window.read()
                if search == "Search":
                    search_list = self.__client_service.search_client(values[0], value[0])
                    title_window.close()
                    window.close()
            else:
                Gui.popup_timed("Wrong type!")
                window.close()

        if show_list:
            column_list = []
            for i in range(len(search_list)):
                column_list.append([str(search_list[i].id), search_list[i].name])
            headings = ["ID", "Name"]
            layout2 = [
                [Gui.Table(values=column_list[0:], headings=headings, def_col_width=25, row_height=25,
                           auto_size_columns=False, key="-SEARCH-CLIENT-TABLE-", size=(17, 17))],
                [Gui.Button("Back")]
            ]

            window2 = Gui.Window("Books", layout2, size=(500, 500))
            button, values = window2.read()
            if button == "Back":
                window2.close()
        else:
            pass

    def _book_statistic(self):
        Gui.theme("DarkBlue1")
        column_list = self.__rental_service.sold_books_number()
        show = []
        show_list = True
        if len(column_list) == 0:
            show_list = False
        if show_list:
            for i in range(len(column_list)):
                if column_list[i][1] > 0:
                    show.append(column_list[i])
            headings = ["ID", "Rents"]
            layout = [
                [Gui.Table(values=show[0:], headings=headings, def_col_width=25,
                           row_height=25,
                           auto_size_columns=False, key="-SEARCH-CLIENT-TABLE-", size=(17, 17))],
                [Gui.Button("Back")]
            ]
            window = Gui.Window("Top books", layout)
            button, values = window.read()
            if button == "Back":
                window.close()
        else:
            pass

    def _author_stats(self):
        Gui.theme("DarkBlue1")
        column_list = self.__rental_service.most_books_author()
        show = []
        show_list = True
        if len(column_list) == 0:
            show_list = False
        if show_list:
            for i in range(len(column_list)):
                if column_list[i][1] > 0:
                    show.append(column_list[i])
            headings = ["Name", "Rentals"]
            layout = [
                [Gui.Table(values=show[0:], headings=headings, def_col_width=25,
                           row_height=25,
                           auto_size_columns=False, key="-SEARCH-CLIENT-TABLE-", size=(17, 17))],
                [Gui.Button("Back")]
            ]
            window = Gui.Window("Top authors", layout)
            button, values = window.read()
            if button == "Back":
                window.close()
        else:
            pass

    def _client_stats(self):
        Gui.theme("DarkBlue1")
        column_list = self.__rental_service.client_day_stat()
        show = []
        show_list = True
        if len(column_list) == 0:
            show_list = False
        if show_list:
            for i in range(len(column_list)):
                if column_list[i][1] > 0:
                    show.append(column_list[i])
            headings = ["Name", "Days"]
            layout = [
                [Gui.Table(values=show[0:], headings=headings, def_col_width=25,
                           row_height=25,
                           auto_size_columns=False, key="-SEARCH-CLIENT-TABLE-", size=(17, 17))],
                [Gui.Button("Back")]
            ]
            window = Gui.Window("Top authors", layout)
            button, values = window.read()
            if button == "Back":
                window.close()
        else:
            pass

    def _history(self):
        Gui.theme("DarkBlue1")
        column_list = self.__rental_service.history_list()
        show = []
        show_list = True
        if len(column_list) == 0:
            show_list = False
        if show_list:
            for i in range(len(column_list)):
                if column_list[i][1] > 0:
                    show.append(column_list[i])
            headings = ["Book ID", "Client ID", "Title", "Author", "Rent date", "Return date"]
            layout = [
                [Gui.Table(values=show[0:], headings=headings, def_col_width=25,
                           row_height=25,
                           auto_size_columns=False, key="-SEARCH-CLIENT-TABLE-", size=(17, 17))],
                [Gui.Button("Back")]
            ]
            window = Gui.Window("Top authors", layout)
            button, values = window.read()
            if button == "Back":
                window.close()
        else:
            pass

    def _undo(self):
        try:
            self.__undo_service.undo()
            Gui.popup_timed("Undo successfully!")
        except UndoException:
            Gui.popup_timed("No things to undo")

    def _redo(self):
        try:
            self.__undo_service.redo()
            Gui.popup_timed("Redo successfully!")
        except UndoException:
            Gui.popup_timed("No things to redo")

    def start(self):
        # self.__book_func.generate_books()
        # self.__client_func.generate_client()
        window = self.__main_menu()

        while True:
            event, values = window.read()
            if event == "Add book":
                self._add_books()
            elif event == "Show books":
                self._show_books()
            elif event == "Remove book":
                self._remove_books()
            elif event == "Replace book details":
                self._replace_book()
            elif event == "Add client":
                self._add_client()
            elif event == "Show clients":
                self._show_client()
            elif event == "Remove client":
                self._remove_client()
            elif event == "Replace client details":
                self._replace_client()
            elif event == "Rent a book":
                self._rent_book()
            elif event == "Return a book":
                self._return_book()
            elif event == "Show current rentals":
                self._show_rentals()
            elif event == "Rentals history list":
                self._history()
            elif event == "Search books":
                self._search_book()
            elif event == "Search clients":
                self._search_client()
            elif event == "Most books rented":
                self._book_statistic()
            elif event == "Best-seller author":
                self._author_stats()
            elif event == "Most active client":
                self._client_stats()
            elif event == "Undo":
                self._undo()
            elif event == "Redo":
                self._redo()
            elif event == Gui.WIN_CLOSED:
                break
            else:
                print("Bad option!")
