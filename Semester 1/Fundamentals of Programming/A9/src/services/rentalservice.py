import unittest
import datetime
from src.services.undoservice import FunctionCall, Operation, CascadedOperation


class RentalService:
    def __init__(self, rental_repo, book_repo, client_repo, undo_service):
        self.__repo = rental_repo
        self.__client_repo = client_repo
        self.__book_repo = book_repo
        self.__history_list = []
        self.__history = undo_service
        self.__id = len(self.__repo) + 1

    def last_index(self):
        """
        To be used in the UI as a counter
        :return:
        """
        return self.__id

    def rent_book(self, id, book_id, client_id, rent_date, index, add):
        """
        Adds a book to the list
        :param id: Rental ID
        :param client_id: Client ID of the rental
        :param book_id: Book ID of the rental
        :param rent_date: Date of the rent
        :param index: Index to insert back the rental when redo after remove
        :param add: Bool to remove the possibility of having rental added to history after undo/redo
        :return:
        """
        for i in range(len(self.__book_repo)):
            if book_id == self.__book_repo[i].id:
                book_id = i + 1
        for i in range(len(self.__client_repo)):
            if client_id == self.__client_repo[i].id:
                client_id = i + 1
        compare_client = []
        compare_book = []
        for i in range(len(self.__client_repo)):
            compare_client.append(self.__client_repo[i].id)
        for i in range(len(self.__book_repo)):
            compare_book.append(self.__book_repo[i].id)
        if (book_id not in compare_book or client_id not in compare_client) and add != 0:
            raise ValueError("ID error.")
        elif book_id in compare_book and client_id in compare_client:
            book_id_add = book_id - (compare_book.index(book_id) + 1)
            client_id_add = client_id - (compare_client.index(client_id) + 1)
            adding = self.__repo.add_rental(id, book_id + book_id_add, client_id + client_id_add, rent_date, index, add)
            return_date = "Not yet"  # we don't need to know when it's returned as it's rented
            if add == 1:
                self.add_to_history(book_id + book_id_add, client_id + client_id_add,
                                    self.__book_repo[book_id - 1].title,
                                    self.__book_repo[book_id - 1].author, rent_date, return_date)
                self.__id += 1
            undo = FunctionCall(self.return_book, id, book_id + book_id_add, return_date)
            redo = FunctionCall(self.rent_book, id, book_id, client_id, rent_date, id, 0)
            self.__history.record_operation(Operation(undo, redo))
            return adding

    def return_book(self, id, return_date):
        """
        Adds a book to the list
        :param id: Rental ID
        :param return_date: Date of the return
        :return:
        """
        #self.__history_list[id - 1][5] = return_date
        removal = self.__repo.remove_rental(id, return_date)

        #undo = FunctionCall(self.rent_book, id, self.__history_list[id - 1][0], self.__history_list[id - 1][1],
                            #self.__history_list[id - 1][4], id, 0)
        #redo = FunctionCall(self.return_book, id, self.__history_list[id - 1][0], return_date)
        #self.__history.record_operation(Operation(undo, redo))
        #return removal

    def show_rental(self):
        """
        Returns the list of rentals to be shown by the UI
        :return:
        """
        return self.__repo

    def remove_client_rental(self, client_id):
        new = self.__repo.remove_client_rental(client_id)
        return new

    def remove_book_rental(self, book_id):
        new = self.__repo.remove_book_rental(book_id)
        return new

    def sold_books_number(self):
        rental_count = []
        for i in range(len(self.__book_repo)):
            rental_count.append([0, 0])
        for i in range(len(self.__history_list)):
            book_id = self.__history_list[i][0]
            rental_count[book_id - 1][1] += 1
            rental_count[book_id - 1][0] = book_id

        return sorted(rental_count, key=lambda x: x[1], reverse=True)

    def client_day_stat(self):
        client_count = []
        books_per_client = []
        for i in range(len(self.__client_repo)):
            client_count.append([0, 0])
            books_per_client.append([0, 0])
        for i in range(len(self.__history_list)):
            client_id = self.__history_list[i][1]
            days = datetime.date.today() - self.__history_list[i][4]
            books_per_client[client_id - 1][0] = client_id
            books_per_client[client_id - 1][1] += days.days
            client_count[client_id - 1] = [client_id, books_per_client[client_id - 1][1]]

        return sorted(client_count, key=lambda x: x[1], reverse=True)

    def most_books_author(self):
        author_dict = {"Name1": self.__book_repo[0].author, "Book1": []}
        index = 2
        author_names = [author_dict["Name1"]]
        for i in range(len(self.__book_repo)):
            if self.__book_repo[i].author not in author_dict.values():
                author_dict["Name" + str(index)] = self.__book_repo[i].author
                author_dict["Book" + str(index)] = []
                author_names.append(author_dict["Name" + str(index)])
                index += 1

        for i in range(len(self.__book_repo)):
            for j in range(len(author_names)):
                if self.__book_repo[i].author == author_names[j]:
                    author_dict["Book" + str(j + 1)].append(self.__book_repo[i].id)

        author_list = list(author_dict.values())
        pack_into_twos = []
        for i in range(0, len(author_list) - 1, 2):
            pack_into_twos.append([author_list[i], author_list[i + 1]])

        one_more_list = []
        for i in range(0, len(author_list) - 1, 2):
            one_more_list.append([author_list[i], 0])

        for i in range(len(self.__history_list)):
            for j in range(0, len(pack_into_twos)):
                if self.__history_list[i][0] in pack_into_twos[j][1]:
                    one_more_list[j][1] += 1
        # after 9h of python
        final_list_finally = sorted(one_more_list, key=lambda x: x[1], reverse=True)

        return final_list_finally

    def add_to_history(self, book_id, client_id, title, author, rent_date, return_date):
        self.__history_list.append([book_id, client_id, title, author, rent_date, return_date])

    def history_list(self):
        return self.__history_list

    def __getitem__(self, item):
        return self.__repo[item]

    def __len__(self):
        index = 0
        while index < len(self.__repo):
            index += 1
        return index
