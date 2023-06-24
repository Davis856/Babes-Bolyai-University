import unittest
from src.services.clientservice import ClientService
from src.repository.repository import ClientRepository
from src.services.undoservice import UndoService


class ClientServiceTest(unittest.TestCase):
    def setUp(self):
        self._clientrepo = ClientRepository()
        self._undoserv = UndoService()
        self._service = ClientService(self._clientrepo, self._undoserv)
        self._service.add_client(1, 'Name1', -1)
        self._service.add_client(2, 'Name2', -1)

    def test_add_client(self):
        self.assertEqual(self._service[0].id, 1)
        self.assertEqual(self._service[0].name, 'Name1')
        self.assertEqual(self._service[1].id, 2)
        self.assertEqual(self._service[1].name, 'Name2')
        with self.assertRaises(ValueError):
            self._service.add_client(3, "name", -1)
        with self.assertRaises(ValueError):
            self._service.add_client(3, "Name e", -1)

    def test_show_client(self):
        test_repo = [[1, 'Name1'], [2, 'Name2']]
        random_list = self._service.show_client()
        new_list = []
        for i in range(len(random_list)):
            new_list.append([random_list[i].id, random_list[i].name])
        self.assertEqual(test_repo, new_list)

    def test_replace_client(self):
        new_value = [2, 'Name3']
        self._service.replace_client(2, 'Name3')
        test_repo = [self._service[1].id, self._service[1].name]
        self.assertEqual(new_value, test_repo)

        with self.assertRaises(ValueError):
            self._service.replace_client(2, "name")
        with self.assertRaises(ValueError):
            self._service.replace_client(2, "Name e")

    def test_delete_client(self):
        test_value = [[1, 'Name1']]
        self._service.remove_client(2)
        new_list = []
        for i in range(len(self._service)):
            new_list.append([self._service[i].id, self._service[i].name])
        self.assertEqual(test_value, new_list)

    def test_last_index(self):
        index = 3
        new = self._service.last_index()
        self.assertEqual(index, new)

    def test_check_id(self):
        with self.assertRaises(ValueError):
            self._service.check_id(100)

    def test_generate_clients(self):
        self._service.generate_client()

    def test_search_client(self):
        test1 = [[1, "Name1"]]
        search1 = self._service.search_client("name", "Name1")
        compare1 = []
        for i in range(len(search1)):
            compare1.append([search1[i].id, search1[i].name])
        self.assertEqual(test1, compare1)

        test2 = [[1, "Name1"]]
        search2 = self._service.search_client("id", 1)
        compare2 = []
        for i in range(len(search2)):
            compare2.append([search2[i].id, search2[i].name])
        self.assertEqual(test2, compare2)
