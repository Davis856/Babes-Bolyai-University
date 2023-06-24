import random
import unittest
from src.repository.repository import ClientRepository
from src.services.undoservice import FunctionCall, Operation, CascadedOperation


class ClientService:
    def __init__(self, client_repo, undo_service):
        self.__repo = client_repo
        self.__client_name = ["Name1", "Name2", "Name3", "Name4"]
        self.__id = 1
        self.__history = undo_service

    def last_index(self):
        """
        To be used in the UI as a counter
        :return:
        """
        return self.__id

    def add_client(self, id, name, index):
        """
        Adds a client to the list
        :param id: Client ID
        :param name: Client Name
        :param index: Index to insert back the client when redo after remove
        :return:
        """
        if not "A" <= name[0] <= "Z":
            raise ValueError("NameError.")
        else:
            for i in range(len(name)):
                if name[i] == " ":
                    if not "A" <= name[i + 1] <= "Z":
                        raise ValueError("NameError.")
        self.__repo.add_client(id, name, index)
        self.__id += 1

        undo = FunctionCall(self.remove_client, id)
        redo = FunctionCall(self.add_client, id, name, -1)
        self.__history.record_operation(Operation(undo, redo))

    def generate_client(self):
        """
        Generates 20 clients
        :return: List of 20 clients
        """
        self.__history.flag_setter()
        for i in range(20):
            self.__repo.add_client(self.__id, random.choice(self.__client_name), -1)
            self.__id += 1
        self.__history.flag_setter()

    def remove_client(self, client_pos):
        """
        Removes a client from a spot
        :param client_pos: Position of the client
        :return:
        """
        operation = CascadedOperation()
        client = self.__repo.remove_client(client_pos)
        undo = FunctionCall(self.add_client, client_pos, client.name, client_pos - 1)
        redo = FunctionCall(self.remove_client, client_pos)
        operation.add(Operation(undo, redo))
        self.__history.record_operation(operation)
        return operation

    def replace_client(self, pos, name):
        """
        Update function for client
        :param pos: Position of the client
        :param name: Name of the client
        :return: Updated client
        """
        if not "A" <= name[0] <= "Z":
            raise ValueError("Incorrect name.")
        else:
            for i in range(len(name)):
                if name[i] == " ":
                    if not "A" <= name[i + 1] <= "Z":
                        raise ValueError("Name Error.")
        redo = FunctionCall(self.replace_client, pos, name)
        client = self.__repo.replace_client(pos, name)
        undo = FunctionCall(self.replace_client, client[0], client[1])
        self.__history.record_operation(Operation(undo, redo))

    def check_id(self, id):
        """
        A small validation function to check in the UI if the ID is valid or not
        :param id: ID of the client
        :return:
        """
        return self.__repo.check_id(id)

    def show_client(self):
        """
        Returns the list of client to be shown by the UI
        :return:
        """
        return self.__repo

    def search_client(self, search_type, search_args):
        """
        Functions that searches a book based on any one of their fields
        :return:
        """
        search_list = []
        if search_type == "id":
            for r in self.__repo:
                if str(search_args) in str(r.id):
                    search_list.append(r)
        elif search_type == "name":
            for r in self.__repo:
                if str.lower(search_args) in str.lower(r.name):
                    search_list.append(r)
        return search_list

    def __getitem__(self, item):
        return self.__repo[item]

    def __len__(self):
        index = 0
        while index < len(self.__repo):
            index += 1
        return index
