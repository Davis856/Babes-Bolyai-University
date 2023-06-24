import unittest
from src.services.rentalservice import RentalService
from src.repository.repository import RentalRepository
from src.repository.repository import BookRepository
from src.repository.repository import ClientRepository
from src.services.undoservice import UndoService
import datetime


class RentalServiceTest(unittest.TestCase):
    def setUp(self):
        self._rentalrepo = RentalRepository()
        self._bookrepo = BookRepository()
        self._clientrepo = ClientRepository()
        self._undoserv = UndoService()
        self._service = RentalService(self._rentalrepo, self._bookrepo, self._clientrepo, self._undoserv)
        self._bookrepo.add_book(1, 'Title100', 'Author100')
        self._bookrepo.add_book(2, 'Title101', 'Author101')
        self._clientrepo.add_client(1, 'Name1')
        self._clientrepo.add_client(2, 'Name2')
        self._service.rent_book(1, 1, 1, datetime.date(2021, 11, 29), -1, 1)
        self._service.rent_book(2, 2, 2, datetime.date(2021, 5, 7), -1, 1)
        self._history_list = self._service.history_list()

    def test_add_rental(self):
        self.assertEqual(self._service[0].rental_id, 1)
        self.assertEqual(self._service[0].book_id, 1)
        self.assertEqual(self._service[0].client_id, 1)
        self.assertEqual(self._service[0].rented_date, datetime.date(2021, 11, 29))
        self.assertEqual(self._service[0].returned_date, "Not yet")
        self.assertEqual(self._service[1].rental_id, 2)
        self.assertEqual(self._service[1].book_id, 2)
        self.assertEqual(self._service[1].client_id, 2)
        self.assertEqual(self._service[1].rented_date, datetime.date(2021, 5, 7))
        self.assertEqual(self._service[1].returned_date, "Not yet")
        with self.assertRaises(ValueError):
            self._service.rent_book(3, 100, 100, datetime.datetime.today, -1, 1)

    def test_show_rental(self):
        test_repo = [[1, 1, 1, datetime.date(2021, 11, 29), "Not yet"],
                     [2, 2, 2, datetime.date(2021, 5, 7), "Not yet"]]
        random_list = self._service.show_rental()
        new_list = []
        for i in range(len(random_list)):
            new_list.append([random_list[i].rental_id, random_list[i].book_id, random_list[i].client_id,
                             random_list[i].rented_date, random_list[i].returned_date])
        self.assertEqual(test_repo, new_list)

    def test_delete_rental(self):
        test_value = [[1, 1, 1, datetime.date(2021, 11, 29), "Not yet"]]
        self._service.return_book(2, 2, datetime.datetime.today)
        new_list = []
        for i in range(len(self._service)):
            new_list.append([self._service[i].rental_id, self._service[i].book_id, self._service[i].client_id,
                             self._service[i].rented_date, self._service[i].returned_date])
        self.assertEqual(test_value, new_list)

    def test_last_index(self):
        id = 3
        new = self._service.last_index()
        self.assertEqual(id, new)

    def test_remove_client_rental(self):
        new = self._service.remove_client_rental(1)
        compare = [[1, 1, 1, datetime.date(2021, 11, 29)]]
        self.assertEqual(new, compare)

    def test_remove_book_rental(self):
        compare = [[1, 1, 1, datetime.date(2021, 11, 29)]]
        new = self._service.remove_book_rental(1)
        self.assertEqual(new, compare)

    def test_sold_books_number(self):
        compare = [[1, 1], [2, 1]]
        new = self._service.sold_books_number()
        self.assertEqual(new, compare)

    def test_client_day_stat(self):
        compare = [[2, 213], [1, 7]]
        new = self._service.client_day_stat()
        self.assertEqual(compare, new)

    def test_most_books_author(self):
        compare = [['Author100', 1], ['Author101', 1]]
        new = self._service.most_books_author()
        self.assertEqual(compare, new)

