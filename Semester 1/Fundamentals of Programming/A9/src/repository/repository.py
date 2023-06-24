from src.domain.books import Book
from src.domain.client import Client
from src.domain.rental import Rental
from src.services.undoservice import *
import unittest
import datetime
import pickle
from src.struct import struct


class RepositoryException(Exception):
    """
    Exception class to implement our own exceptions
    """
    pass


class BookRepository:
    def __init__(self):
        """
        Constructor for Repository class
        """
        self.__data = []
        self.__book_data = struct(self.__data)

    def add_book(self, id, title, author, index=-1):
        """
        Adds a book to the list
        :param id: Book ID
        :param title: Book Title
        :param author: Book Author
        :param index: Index to insert back the book when redo after remove
        :return:
        """
        # for i in range(len(self.__book_data)):
        # if entity.id == self.__book_data[i]:
        # raise RepositoryException("Test")
        entity = Book(id, title, author)
        self.__book_data.append(entity) if index == -1 else self.__book_data.insert(index, entity)

    def remove_book(self, book_pos):
        """
        Removes a book from a spot
        :param book_pos: Position of the book
        :return:
        """
        # for random IDs, ID != position
        for i in range(len(self.__book_data)):
            if book_pos == self.__book_data[i].id:
                book_pos = i + 1
        if book_pos - 1 < len(self.__book_data):  # and book_pos - 1 == self.__book_data[book_pos - 1].id:
            book = self.__book_data.pop(book_pos - 1)
            return book
        else:
            raise RepositoryException("ID does not exist")

    def replace_book(self, book_position, book_title, book_author):
        """
        Update function for book
        :param book_position: Position of the book
        :param book_title: Title of the book
        :param book_author: Author of the book
        :return: Updated book
        """
        # for random IDs, ID != position
        for i in range(len(self.__book_data)):
            if book_position == self.__book_data[i].id:
                book_position = i + 1
        compare_book = []
        for i in range(len(self.__book_data)):
            compare_book.append(self.__book_data[i].id)
        book_id_add = book_position - (compare_book.index(book_position) + 1)
        if 0 <= book_position - 1 <= len(self.__book_data) and book_position + book_id_add == self.__book_data[
            book_position - 1].id:
            old = [self.__book_data[book_position - 1].id,
                   self.__book_data[book_position - 1].title,
                   self.__book_data[book_position - 1].author]
            self.__book_data[book_position - 1].title = book_title
            self.__book_data[book_position - 1].author = book_author
            return old
        else:
            raise RepositoryException("ID does not exist")

    def show_book(self):
        """
        Returns the list of books to be shown by the UI
        :return:
        """
        return self.__book_data

    # for bin
    def append_book(self, entity):
        self.__book_data.append(entity)

    def __getitem__(self, item):
        return self.__book_data[item]

    def __len__(self):
        index = 0
        while index < len(self.__book_data):
            index += 1
        return index


class BookRepositoryTest(unittest.TestCase):
    def setUp(self):
        self._repo = BookRepository()
        self._repo.add_book(1, 'Title100', 'Author100')
        self._repo.add_book(2, 'Title101', 'Author101')

    def test_add_book(self):
        self.assertEqual(self._repo[0].id, 1)
        self.assertEqual(self._repo[0].title, 'Title100')
        self.assertEqual(self._repo[0].author, 'Author100')
        self.assertEqual(self._repo[1].id, 2)
        self.assertEqual(self._repo[1].title, 'Title101')
        self.assertEqual(self._repo[1].author, 'Author101')

    def test_show_book(self):
        test_repo = [[1, 'Title100', 'Author100'], [2, 'Title101', 'Author101']]
        new_list = []
        for i in range(len(self._repo)):
            new_list.append([self._repo[i].id, self._repo[i].title, self._repo[i].author])
        self.assertEqual(test_repo, new_list)

    def test_replace_book(self):
        new_value = [1, 'Title200', 'Author200']
        self._repo.replace_book(1, 'Title200', 'Author200')
        test_repo = [self._repo[0].id, self._repo[0].title, self._repo[0].author]
        self.assertEqual(new_value, test_repo)

    def test_delete_book(self):
        test_value = [[1, 'Title100', 'Author100']]
        self._repo.remove_book(2)
        new_list = []
        for i in range(len(self._repo)):
            new_list.append([self._repo[i].id, self._repo[i].title, self._repo[i].author])
        self.assertEqual(test_value, new_list)


class ClientRepository:
    def __init__(self):
        """
        Constructor for ClientRepository class
        """
        self.__data = []
        self.__client_data = struct(self.__data)

    def check_id(self, id):
        """
        A small validation function for client IDs
        :param id: ID of the client
        :return:
        """
        if id > len(self.__client_data) or id < 0:
            raise ValueError("ID does not exist")

    def add_client(self, id, name, index=-1):
        """
        Adds a client to the list of clients
        :param id: ID of the client
        :param name: Name of the client
        :param index: Index to insert back the client when redo after remove
        :return:
        """
        entity = Client(id, name)
        self.__client_data.append(entity) if index == -1 else self.__client_data.insert(index, entity)

    def remove_client(self, client_pos):
        """
        Removes a client from the list of clients
        :param client_pos: ID of the client
        :return:
        """
        # for random IDs, ID != position
        for i in range(len(self.__client_data)):
            if client_pos == self.__client_data[i].id:
                client_pos = i + 1
        compare_id = []
        for i in range(len(self.__client_data)):
            compare_id.append(self.__client_data[i].id)
        if client_pos - 1 > len(self.__client_data):  # or client_pos not in compare_id:
            raise RepositoryException("Position does not exist")
        else:
            client = self.__client_data.pop(client_pos - 1)
            return client

    def replace_client(self, client_pos, client_name):
        """
        Replaces a client's credentials
        :param client_pos: ID of the client
        :param client_name: Client name
        :return:
        """
        # for random IDs, ID != position
        for i in range(len(self.__client_data)):
            if client_pos == self.__client_data[i].id:
                client_pos = i + 1
        compare_client = []
        for i in range(len(self.__client_data)):
            compare_client.append(self.__client_data[i].id)
        client_id_add = client_pos - (compare_client.index(client_pos) + 1)
        if client_pos - 1 > len(self.__client_data) or client_pos + client_id_add != self.__client_data[
            client_pos - 1].id:
            raise RepositoryException("Position does not exist")
        else:
            old = [self.__client_data[client_pos - 1].id, self.__client_data[client_pos - 1].name]
            self.__client_data[client_pos - 1].name = client_name
            return old

    def show_client(self):
        """
        Returns the list of the clients to be shown by the UI
        :return:
        """
        return self.__client_data

    # for bin
    def append_client(self, entity):
        self.__client_data.append(entity)

    def __getitem__(self, item):
        return self.__client_data[item]

    def __len__(self):
        index = 0
        while index < len(self.__client_data):
            index += 1
        return index


class ClientRepositoryTest(unittest.TestCase):
    def setUp(self):
        self._repo = ClientRepository()
        self._repo.add_client(1, 'Name1')
        self._repo.add_client(2, 'Name2')

    def test_add_client(self):
        self.assertEqual(self._repo[0].id, 1)
        self.assertEqual(self._repo[0].name, 'Name1')
        self.assertEqual(self._repo[1].id, 2)
        self.assertEqual(self._repo[1].name, 'Name2')

    def test_show_client(self):
        test_repo = [[1, 'Name1'], [2, 'Name2']]
        new_list = []
        for i in range(len(self._repo)):
            new_list.append([self._repo[i].id, self._repo[i].name])
        self.assertEqual(test_repo, new_list)

    def test_replace_client(self):
        new_value = [1, 'Name3']
        self._repo.replace_client(1, 'Name3')
        test_repo = [self._repo[0].id, self._repo[0].name]
        self.assertEqual(new_value, test_repo)

    def test_delete_client(self):
        test_value = [[1, 'Name1']]
        self._repo.remove_client(2)
        new_list = []
        for i in range(len(self._repo)):
            new_list.append([self._repo[i].id, self._repo[i].name])
        self.assertEqual(test_value, new_list)


class RentalRepository:
    def __init__(self):
        self.__data = []
        self.__rental_data = struct(self.__data)

    def add_rental(self, rental_id, book_id, client_id, rent_date, index, add):
        """
        Adds a rental to the list of rental
        :param rental_id: Rental ID
        :param client_id: Client ID of the rental
        :param book_id: Book ID of the rental
        :param rent_date: Date of the rent
        :param index: Index to insert back the rental when redo after remove
        :param add: Bool to remove the possibility of having rental added to history after undo/redo
        :return:
        """
        rental_ids = []
        for i in range(len(self.__rental_data)):
            rental_ids.append(self.__rental_data[i].book_id)
        if book_id not in rental_ids:
            entity = Rental(rental_id, book_id, client_id, rent_date)
            adding = self.__rental_data.append(entity) if index == -1 else self.__rental_data.insert(index, entity)
            return adding
        else:
            raise RepositoryException("ID exists")

    def remove_rental(self, rental_pos, return_date):
        """
        Removes a rental from the list of rentals
        :param rental_pos: ID of the rental
        :param return_date: Date of the deletion(return)
        :return:
        """
        delete_id = []
        for i in range(len(self.__rental_data)):
            delete_id.append(self.__rental_data[i].rental_id)
        if rental_pos - 1 > len(self.__rental_data) or 0 > rental_pos - 1:
            raise RepositoryException("ID does not exist")
        else:
            if rental_pos in delete_id:
                removal = self.__rental_data.pop(delete_id.index(rental_pos))
                return removal

    def remove_client_rental(self, client_id):
        i = 0
        save = []
        while i < len(self.__rental_data):
            if self.__rental_data[i].client_id == client_id:
                save.append(
                    [self.__rental_data[i].rental_id, self.__rental_data[i].book_id, self.__rental_data[i].client_id,
                     self.__rental_data[i].rented_date])
                del self.__rental_data[i]
            else:
                i += 1
        return save

    def remove_book_rental(self, book_id):
        i = 0
        save = []
        while i < len(self.__rental_data):
            if self.__rental_data[i].book_id == book_id:
                save.append(
                    [self.__rental_data[i].rental_id, self.__rental_data[i].book_id, self.__rental_data[i].client_id,
                     self.__rental_data[i].rented_date])
                del self.__rental_data[i]
            else:
                i += 1
        return save

    def show_rentals(self):
        """
        Returns the list of the clients to be shown by the UI
        :return:
        """
        return self.__rental_data

    # for bin
    def append_rental(self, entity):
        self.__rental_data.append(entity)

    def __getitem__(self, item):
        return self.__rental_data[item]

    def __len__(self):
        index = 0
        while index < len(self.__rental_data):
            index += 1
        return index


class RentalRepositoryTest(unittest.TestCase):
    def setUp(self):
        self._rentalrepo = RentalRepository()
        self._bookrepo = BookRepository()
        self._clientrepo = ClientRepository()
        self._bookrepo.add_book(1, 'Title100', 'Author100')
        self._bookrepo.add_book(2, 'Title101', 'Author101')
        self._clientrepo.add_client(1, 'Name1')
        self._clientrepo.add_client(2, 'Name2')
        self._rentalrepo.add_rental(1, 1, 1, datetime.datetime.today, -1, 1)
        self._rentalrepo.add_rental(2, 2, 2, datetime.datetime(2021, 5, 7), -1, 1)

    def test_add_rental(self):
        self.assertEqual(self._rentalrepo[0].rental_id, 1)
        self.assertEqual(self._rentalrepo[0].book_id, 1)
        self.assertEqual(self._rentalrepo[0].client_id, 1)
        self.assertEqual(self._rentalrepo[0].rented_date, datetime.datetime.today)
        self.assertEqual(self._rentalrepo[0].returned_date, "Not yet")
        self.assertEqual(self._rentalrepo[1].rental_id, 2)
        self.assertEqual(self._rentalrepo[1].book_id, 2)
        self.assertEqual(self._rentalrepo[1].client_id, 2)
        self.assertEqual(self._rentalrepo[1].rented_date, datetime.datetime(2021, 5, 7))
        self.assertEqual(self._rentalrepo[1].returned_date, "Not yet")

    def test_show_rental(self):
        test_repo = [[1, 1, 1, datetime.datetime.today, "Not yet"],
                     [2, 2, 2, datetime.datetime(2021, 5, 7), "Not yet"]]
        new_list = []
        for i in range(len(self._rentalrepo)):
            new_list.append([self._rentalrepo[i].rental_id, self._rentalrepo[i].book_id, self._rentalrepo[i].client_id,
                             self._rentalrepo[i].rented_date, self._rentalrepo[i].returned_date])
        self.assertEqual(test_repo, new_list)

    def test_delete_rental(self):
        test_value = [[1, 1, 1, datetime.datetime.today, "Not yet"]]
        self._rentalrepo.remove_rental(2, datetime.datetime.today)
        new_list = []
        for i in range(len(self._rentalrepo)):
            new_list.append([self._rentalrepo[i].rental_id, self._rentalrepo[i].book_id, self._rentalrepo[i].client_id,
                             self._rentalrepo[i].rented_date, self._rentalrepo[i].returned_date])
        self.assertEqual(test_value, new_list)


class BookRepositoryTxt(BookRepository):
    def __init__(self, file_name):
        super().__init__()
        self._file_name = file_name
        self._load()

    def _load(self):
        f = open(self._file_name, "rt")
        for line in f.readlines():
            book_id, title, author = line.split(maxsplit=2, sep=" | ")
            author = author.strip()
            self.add_book(book_id, title, author, -1)
        f.close()

    def _save(self):
        f = open(self._file_name, "wt")
        data = self.show_book()
        for book in data:
            f.write(str(book.id) + " | " + book.title + " | " + book.author + "\n")
        f.close()

    def add_book(self, id, title, author, index=-1):
        super(BookRepositoryTxt, self).add_book(id, title, author, index)
        self._save()

    def remove_book(self, book_pos):
        super(BookRepositoryTxt, self).remove_book(book_pos)
        self._save()

    def replace_book(self, book_position, book_title, book_author):
        super(BookRepositoryTxt, self).replace_book(book_position, book_title, book_author)
        self._save()


class ClientRepositoryTxt(ClientRepository):
    def __init__(self, file_name):
        super().__init__()
        self._file_name = file_name
        self._load()

    def _load(self):
        f = open(self._file_name, "rt")
        for line in f.readlines():
            book_id, name = line.split(maxsplit=1, sep=" | ")
            name = name.strip()
            self.add_client(book_id, name, -1)
        f.close()

    def _save(self):
        f = open(self._file_name, "wt")
        data = self.show_client()
        for client in data:
            f.write(str(client.id) + " | " + client.name + "\n")
        f.close()

    def add_client(self, id, name, index=-1):
        super(ClientRepositoryTxt, self).add_client(id, name, index)
        self._save()

    def remove_client(self, client_pos):
        super(ClientRepositoryTxt, self).remove_client(client_pos)
        self._save()

    def replace_client(self, client_pos, client_name):
        super(ClientRepositoryTxt, self).replace_client(client_pos, client_name)
        self._save()


class RentalRepositoryTxt(RentalRepository):
    def __init__(self, file_name):
        super().__init__()
        self._file_name = file_name
        self._load()

    def _load(self):
        f = open(self._file_name, "rt")
        for line in f.readlines():
            rental_id, book_id, client_id, rent_date, return_date = line.split(maxsplit=4, sep=" | ")
            return_date = return_date.strip()
            self.add_rental(rental_id, book_id, client_id, rent_date, -1, 1)
        f.close()

    def _save(self):
        f = open(self._file_name, "wt")
        data = self.show_rentals()
        for rental in data:
            f.write(str(rental.rental_id) + " | " + str(rental.book_id) + " | " + str(rental.client_id) + " | " + str(
                rental.rented_date) + " | " + str(rental.returned_date) + "\n")
        f.close()

    def add_rental(self, rental_id, book_id, client_id, rent_date, index, add):
        super(RentalRepositoryTxt, self).add_rental(rental_id, book_id, client_id, rent_date, index, add)
        self._save()

    def remove_rental(self, rental_pos, return_date):
        super(RentalRepositoryTxt, self).remove_rental(rental_pos, return_date)
        self._save()

    def remove_book_rental(self, book_id):
        super(RentalRepositoryTxt, self).remove_book_rental(book_id)
        self._save()

    def remove_client_rental(self, client_id):
        super(RentalRepositoryTxt, self).remove_client_rental(client_id)
        self._save()


class BookRepositoryBin(BookRepository):
    def __init__(self, file_name):
        super().__init__()
        self._file_name = file_name
        self._load()

    def _load(self):
        with open(self._file_name, "rb") as f:
            while True:
                try:
                    self.append_book(pickle.load(f))
                except EOFError:
                    break

    def _save(self):
        books = self.show_book()
        with open(self._file_name, "wb") as f:
            for b in books:
                pickle.dump(b, f)
        f.close()

    def add_book(self, id, title, author, index=-1):
        super(BookRepositoryBin, self).add_book(id, title, author, index)
        self._save()

    def remove_book(self, book_pos):
        super(BookRepositoryBin, self).remove_book(book_pos)
        self._save()

    def replace_book(self, book_position, book_title, book_author):
        super(BookRepositoryBin, self).replace_book(book_position, book_title, book_author)
        self._save()


class ClientRepositoryBin(ClientRepository):
    def __init__(self, file_name):
        super().__init__()
        self._file_name = file_name
        self._load()

    def _load(self):
        with open(self._file_name, "rb") as f:
            while True:
                try:
                    self.append_client(pickle.load(f))
                except EOFError:
                    break

    def _save(self):
        books = self.show_client()
        with open(self._file_name, "wb") as f:
            for b in books:
                pickle.dump(b, f)
        f.close()

    def add_client(self, id, name, index=-1):
        super(ClientRepositoryBin, self).add_client(id, name, index)
        self._save()

    def remove_client(self, client_pos):
        super(ClientRepositoryBin, self).remove_client(client_pos)
        self._save()

    def replace_client(self, client_pos, client_name):
        super(ClientRepositoryBin, self).replace_client(client_pos, client_name)
        self._save()


class RentalRepositoryBin(RentalRepository):
    def __init__(self, file_name):
        super().__init__()
        self._file_name = file_name
        self._load()

    def _load(self):
        with open(self._file_name, "rb") as f:
            while True:
                try:
                    self.append_rental(pickle.load(f))
                except EOFError:
                    break

    def _save(self):
        books = self.show_rentals()
        with open(self._file_name, "wb") as f:
            for b in books:
                pickle.dump(b, f)
        f.close()

    def add_rental(self, rental_id, book_id, client_id, rent_date, index, add):
        super(RentalRepositoryBin, self).add_rental(rental_id, book_id, client_id, rent_date, index, add)
        self._save()

    def remove_rental(self, rental_pos, return_date):
        super(RentalRepositoryBin, self).remove_rental(rental_pos, return_date)
        self._save()

    def remove_client_rental(self, client_id):
        super(RentalRepositoryBin, self).remove_client_rental(client_id)
        self._save()

    def remove_book_rental(self, book_id):
        super(RentalRepositoryBin, self).remove_book_rental(book_id)
        self._save()


def test_book_repository():
    repo = BookRepository()

    id = 100
    title = "Title"
    author = "Author"
    repo.add_book(id, title, author)
    string = str(repo[0])
    repo[0].author = "Test Author 2"
    assert repo[0].author == "Test Author 2"
    assert string == "id: 100 title: Title author: Author"


def test_client_repository():
    repo = ClientRepository()

    id = 100
    name = "Name1"
    repo.add_client(id, name)
    string = str(repo[0])
    repo[0].name = "Name10"
    assert repo[0].name == "Name10"
    assert string == "ID: 100 Name: Name1"


def test_rental_repository():
    repo = RentalRepository()

    id = 100
    client_id = 1
    book_id = 20
    rent_date = "November 22, 2021 12:02:22"
    repo.add_rental(id, client_id, book_id, rent_date, -1, 1)
    repo[0].book_id = 70
    repo[0].rent_date = "November 23, 2021 12:02:22"
    repo[0].client_id = 3
    string = str(repo[0])
    assert repo[0].client_id == 3
    assert repo[0].book_id == 70
    assert repo[0].rent_date == "November 23, 2021 12:02:22"
    assert string == "ID: 100 Book ID: 70 Client ID: 3 Rented date: November 22, 2021 12:02:22 Returned date: Not yet"


test_book_repository()
test_client_repository()
test_rental_repository()
