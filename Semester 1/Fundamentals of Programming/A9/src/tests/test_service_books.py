import unittest
from src.services.bookservice import BookService
from src.repository.repository import BookRepository
from src.services.undoservice import UndoService
from src.repository.repository import RepositoryException


class BookServiceTest(unittest.TestCase):
    def setUp(self):
        self._bookrepo = BookRepository()
        self._undoserv = UndoService()
        self._service = BookService(self._bookrepo, self._undoserv)
        self._service.add_book(1, 'Title100', 'Author100', -1)
        self._service.add_book(2, 'Title101', 'Author101', -1)

    def test_add_book(self):
        self.assertEqual(self._service[0].id, 1)
        self.assertEqual(self._service[0].title, 'Title100')
        self.assertEqual(self._service[0].author, 'Author100')
        self.assertEqual(self._service[1].id, 2)
        self.assertEqual(self._service[1].title, 'Title101')
        self.assertEqual(self._service[1].author, 'Author101')
        with self.assertRaises(ValueError):
            self._service.add_book(3, "Title100", "author e", -1)
        with self.assertRaises(ValueError):
            self._service.add_book(3, "Title100", "Author e", -1)

    def test_show_book(self):
        test_repo = [[1, 'Title100', 'Author100'], [2, 'Title101', 'Author101']]
        new_list = self._service.show_book()
        compare_list = []
        for i in range(len(new_list)):
            compare_list.append([new_list[i].id, new_list[i].title, new_list[i].author])

        self.assertEqual(test_repo, compare_list)

    def test_replace_book(self):
        new_value = [2, 'Title200', 'Author200']
        self._service.replace_book(2, 'Title200', 'Author200')
        test_repo = [self._service[1].id, self._service[1].title, self._service[1].author]
        self.assertEqual(new_value, test_repo)
        with self.assertRaises(ValueError):
            self._service.replace_book(2, "Title100", "author e")
        with self.assertRaises(ValueError):
            self._service.replace_book(2, "Title100", "Author e")

    def test_delete_book(self):
        test_value = [[1, 'Title100', 'Author100']]
        self._service.remove_book(2)
        new_list = []
        for i in range(len(self._service)):
            new_list.append([self._service[i].id, self._service[i].title, self._service[i].author])
        self.assertEqual(test_value, new_list)
        with self.assertRaises(RepositoryException):
            self._service.remove_book(200)

    def test_last_index(self):
        index = 3
        new = self._service.last_index()
        self.assertEqual(index, new)

    def test_generate_books(self):
        self._service.generate_books()

    def test_search_book(self):
        test1 = [[1, "Title100", "Author100"]]
        search1 = self._service.search_book("title", "Title100")
        compare1 = []
        for i in range(len(search1)):
            compare1.append([search1[i].id, search1[i].title, search1[i].author])
        self.assertEqual(test1, compare1)

        test2 = [[1, "Title100", "Author100"]]
        search2 = self._service.search_book("id", 1)
        compare2 = []
        for i in range(len(search2)):
            compare2.append([search2[i].id, search2[i].title, search2[i].author])
        self.assertEqual(test2, compare2)

        test3 = [[1, "Title100", "Author100"]]
        search3 = self._service.search_book("author", "Author100")
        compare3 = []
        for i in range(len(search3)):
            compare3.append([search3[i].id, search3[i].title, search3[i].author])
        self.assertEqual(test3, compare3)
