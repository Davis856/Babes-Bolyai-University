import unittest

from src.services.undoservice import *
from src.services.rentalservice import RentalService
from src.services.bookservice import BookService
from src.services.clientservice import ClientService
from src.repository.repository import *


class UndoServiceTest(unittest.TestCase):
    def setUp(self):
        self._undoserv = UndoService()
        self._bookrepo = BookRepository()
        self._clientrepo = ClientRepository()
        self._bookserv = BookService(self._bookrepo, self._undoserv)
        self._clientserv = ClientService(self._clientrepo, self._undoserv)

    def test_flag_setter(self):
        flag = False
        new = self._undoserv.flag_setter()
        self.assertEqual(flag, new)

    def test_service_undo(self):
        redo_list = [[1, "Title100", "Author100"], [2, "Title200", "Author200"]]
        redo_compare_list = []
        undo_list = [[1, "Title100", "Author100"]]
        undo_compare_list = []
        self._bookserv.add_book(1, "Title100", "Author100", -1)
        self._bookserv.add_book(2, "Title200", "Author200", -1)
        undo = FunctionCall(self._bookserv.remove_book, 2)
        redo = FunctionCall(self._bookserv.add_book, 2, "Title200", "Author200", 1)
        self._undoserv.record_operation(Operation(undo, redo))
        self._undoserv.undo()
        for i in range(len(self._bookserv)):
            undo_compare_list.append([self._bookserv[i].id, self._bookrepo[i].title, self._bookrepo[i].author])
        self.assertEqual(undo_list, undo_compare_list)
        self._undoserv.redo()
        for i in range(len(self._bookserv)):
            redo_compare_list.append([self._bookserv[i].id, self._bookrepo[i].title, self._bookrepo[i].author])
        self.assertEqual(redo_list, redo_compare_list)