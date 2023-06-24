from src.services.clientservice import ClientService
from src.services.bookservice import BookService
from src.services.rentalservice import RentalService
from src.repository.repository import RepositoryException
from src.services.undoservice import *
import datetime


class UI:
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
        print("Library Database")
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
        print("12. Rentals history")
        print("13. Search books")
        print("14. Search clients")
        print("15. Most books sold")
        print("16. Best-seller Author")
        print("17. Most active client")
        print("18. Undo last action")
        print("19. Redo last action")
        print("0. Exit")

    def _show_books(self):
        books = self.__book_service.show_book()
        for b in books:
            print(str(b))

    def _add_books(self):
        print("Title: ")
        title = input()
        print("Author: ")
        author = input()
        index = self.__book_service.last_index()
        try:
            self.__book_service.add_book(index, title, author, -1)
            print("Added successfully")
        except ValueError:
            print("Author error: Author is not a name, but a number, please input a real name.")

    def _remove_books(self):
        print("ID of the book you want to remove")
        book_pos = int(input())
        try:
            operation = self.__book_service.remove_book(book_pos)
            save = self.__rental_service.remove_book_rental(book_pos)
            for i in range(len(save)):
                undo = FunctionCall(self.__rental_service.rent_book, save[i][0], save[i][1],
                                    save[i][2], save[i][3], -1, 0)
                redo = FunctionCall(self.__rental_service.return_book, save[i][0], save[i][1], "Not yet")
                operation.add(Operation(undo, redo))
            self.__undo_service.record_operation(operation)
            print("Removed successfully")
        except RepositoryException:
            print("Wrong ID, check it again!")

    def _replace_book(self):
        print("ID of the book you want to replace details of: ")
        book_pos = int(input())
        print("New title: ")
        book_title = input()
        print("New author: ")
        book_author = input()
        try:
            self.__book_service.replace_book(book_pos, book_title, book_author)
            print("Replaced successfully")
        except ValueError:
            print("Author error or incorrect position, please try again.")

    def _show_client(self):
        client = self.__client_service.show_client()
        for c in client:
            print(str(c))

    def _add_client(self):
        print("Name: ")
        name = input()
        index = self.__client_service.last_index()
        try:
            self.__client_service.add_client(index, name, -1)
            print("Added successfully")
        except ValueError:
            print("Wrong name format, please try again.")

    def _remove_client(self):
        print("ID of the client you want to remove")
        client_pos = int(input())
        try:
            operation = self.__client_service.remove_client(client_pos)
            save = self.__rental_service.remove_client_rental(client_pos)
            for i in range(len(save)):
                undo = FunctionCall(self.__rental_service.rent_book, save[i][0], save[i][1],
                                    save[i][2], save[i][3], -1, 0)
                redo = FunctionCall(self.__rental_service.return_book, save[i][0], save[i][1], "Not yet")
                operation.add(Operation(undo, redo))
            self.__undo_service.record_operation(operation)
            print("Removed successfully")
        except RepositoryException:
            print("Wrong ID, check it again!")

    def _replace_client(self):
        print("ID of the client you want to replace details of: ")
        client_pos = int(input())
        print("New name: ")
        client_name = input()
        try:
            self.__client_service.replace_client(client_pos, client_name)
            print("Replaced successfully")
        except ValueError:
            print("Wrong name format or incorrect position, please try again.")

    def _rent_book(self):
        print("ID of the book you want to rent")
        book_id = int(input())
        print("Client ID: ")
        client_id = int(input())
        d = datetime.date(2021, 11, 25)
        rental_id = self.__rental_service.last_index()
        try:
            self.__client_service.check_id(client_id)
            try:
                self.__rental_service.rent_book(rental_id, book_id, client_id, d, -1, 1)
                print("Rent successful")
            except RepositoryException:
                print("Error: could not rent, check if the book is available or not.")
        except ValueError:
            print("Client or Book ID error: ID does not exist")

    def _return_book(self):
        print("ID of the rental")
        rental_id = int(input())
        d = datetime.date.today()
        # for history_list in service
        history_list = self.__rental_service.history_list()
        book_id = history_list[rental_id - 1][0]
        ##
        try:
            self.__rental_service.return_book(rental_id, book_id, d)
            print("Return successful")
        except RepositoryException:
            print(
                "Error: could not return,"
                " check if the book is available or not or if the Rental ID is correct.")

    def _show_rentals(self):
        rental_list = self.__rental_service.show_rental()
        if len(rental_list) == 0:
            print("No rentals right now!")
        else:
            for r in rental_list:
                print(str(r))

    def _search_book(self):
        print("What do you want to search it by? (id, title, author)")
        search_type = input()
        if search_type == "id":
            print("Type the ID that you want to search: ")
            search_args = int(input())
        elif search_type == "title":
            print("Type the title that you want to search: ")
            search_args = input()
        elif search_type == "author":
            print("Type the author that you want to search: ")
            search_args = input()
        search_list = self.__book_service.search_book(search_type, search_args)
        for s in search_list:
            print(str(s))

    def _search_client(self):
        print("What do you want to search it by? (id, name)")
        search_type = input()
        if search_type == "id":
            print("Type the ID that you want to search: ")
            search_args = int(input())
        elif search_type == "name":
            print("Type the name that you want to search: ")
            search_args = input()
        search_list = self.__client_service.search_client(search_type, search_args)
        for s in search_list:
            print(str(s))

    def _book_statistic(self):
        statistic = self.__rental_service.sold_books_number()
        found = 0
        for s in statistic:
            if s[1] >= 1:
                found = 1
                print("Book ID " + str(s[0]) + " has been rented " + str(s[1]) + " times.")
        if found == 0:
            print("No data yet.")

    def _author_stats(self):
        stats = self.__rental_service.most_books_author()
        found = 0
        for s in stats:
            if s[1] >= 1:
                found = 1
                print("Author Name: " + str(s[0]) + " has " + str(s[1]) + " books rented.")
        if found == 0:
            print("No data yet.")

    def _client_stats(self):
        stats = self.__rental_service.client_day_stat()
        found = 0
        for s in stats:
            if s[1] >= 1:
                found = 1
                print("Client ID " + str(s[0]) + " is the most active with " + str(s[1]) + " days.")
        if found == 0:
            print("No data yet.")

    def _history(self):
        history_list = self.__rental_service.history_list()
        if len(history_list) > 0:
            for i in range(len(history_list)):
                print("Book ID: " + str(
                    history_list[i][0]) + " Client ID: " + str(history_list[i][1]) + " Title: " + str(
                    history_list[i][2]) + " Author: " + str(history_list[i][3]) + " Rent Date " + str(
                    history_list[i][4]) + " Return Date: " + str(history_list[i][5]))
        elif len(history_list) == 0:
            print("No history available!")

    def _undo(self):
        try:
            self.__undo_service.undo()
        except UndoException:
            print("No things to undo")

    def _redo(self):
        try:
            self.__undo_service.redo()
        except UndoException:
            print("No things to redo")

    def start(self):
        self.__book_func.generate_books()
        self.__client_func.generate_client()

        while True:
            self.__main_menu()
            opt = input()
            if opt == '1':
                self._add_books()
            elif opt == '2':
                self._show_books()
            elif opt == '3':
                self._remove_books()
            elif opt == '4':
                self._replace_book()
            elif opt == '5':
                self._add_client()
            elif opt == '6':
                self._show_client()
            elif opt == '7':
                self._remove_client()
            elif opt == '8':
                self._replace_client()
            elif opt == '9':
                self._rent_book()
            elif opt == '10':
                self._return_book()
            elif opt == "11":
                self._show_rentals()
            elif opt == "12":
                self._history()
            elif opt == '13':
                self._search_book()
            elif opt == '14':
                self._search_client()
            elif opt == '15':
                self._book_statistic()
            elif opt == '16':
                self._author_stats()
            elif opt == '17':
                self._client_stats()
            elif opt == '18':
                self._undo()
            elif opt == '19':
                self._redo()
            elif opt == '0':
                return
            else:
                print("Bad option!")
