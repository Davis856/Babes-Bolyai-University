import random
from src.services.undoservice import FunctionCall, Operation, CascadedOperation


class BookService:
    def __init__(self, book_repo, undo_service):
        self.__repo = book_repo
        self.__titles = ["Title1", "Title2", "Title3", "Title4", "Title5", "Title6"]
        self.__authors = ["Author1", "Author2", "Author3", "Author4", "Author5", "Author6"]
        self.__history = undo_service
        self.__id = len(self.__repo) + 1

    def last_index(self):
        """
        To be used in the UI as a counter
        :return:
        """
        return self.__id

    def add_book(self, id, title, author, index):
        """
        Adds a book to the list
        :param id: Book ID
        :param title: Book Title
        :param author: Book Author
        :param index: Index to insert back the book when redo after remove
        :return:
        """
        if not "A" <= author[0] <= "Z":
            raise ValueError("Author error: Author is not a name, please input a real name.")
        else:
            for i in range(len(author)):
                if author[i] == " ":
                    if not "A" <= author[i + 1] <= "Z":
                        raise ValueError("Author error: Author is not a name,please input a real name.")
        self.__repo.add_book(id, title, author, index)
        self.__id += 1

        undo = FunctionCall(self.remove_book, id)
        redo = FunctionCall(self.add_book, id, title, author, -1)
        self.__history.record_operation(Operation(undo, redo))

    def generate_books(self):
        """
        Generates 20 books
        :return: List of 20 books
        """
        self.__history.flag_setter()
        for i in range(20):
            self.__repo.add_book(self.__id, random.choice(self.__titles), random.choice(self.__authors), -1)
            self.__id += 1
        self.__history.flag_setter()

    def remove_book(self, book_pos):
        """
        Removes a book from a spot
        :param book_pos: Position of the book
        :return:
        """
        # operation = CascadedOperation()
        book = self.__repo.remove_book(book_pos)
        # undo = FunctionCall(self.add_book, book_pos, book.title, book.author, book_pos - 1)
        # redo = FunctionCall(self.remove_book, book_pos)
        # operation.add(Operation(undo, redo))
        # self.__history.record_operation(operation)
        # return operation

    def replace_book(self, pos, title, author):
        """
        Update function for book
        :param pos: Position of the book
        :param title: Title of the book
        :param author: Author of the book
        :return: Updated book
        """
        if not "A" <= author[0] <= "Z":
            raise ValueError("Author error: Name and surname must start with a big letter.")
        else:
            for i in range(len(author)):
                if author[i] == " ":
                    if not "A" <= author[i + 1] <= "Z":
                        raise ValueError("Author error: Name and surname must start with a big letter.")
        #redo = FunctionCall(self.replace_book, pos, title, author)
        book = self.__repo.replace_book(pos, title, author)
        #undo = FunctionCall(self.replace_book, book[0], book[1], book[2])
        #self.__history.record_operation(Operation(undo, redo))

    def show_book(self):
        """
        Returns the list of books to be shown by the UI
        :return:
        """
        return self.__repo

    def search_book(self, search_type, search_args):
        """
        Functions that searches a book based on any one of their fields
        :return:
        """
        search_list = []
        if search_type == "id":
            for r in self.__repo:
                if str(search_args) in str(r.id):
                    search_list.append(r)
        elif search_type == "title":
            for r in self.__repo:
                if str.lower(search_args) in str.lower(r.title):
                    search_list.append(r)
        elif search_type == "author":
            for r in self.__repo:
                if str.lower(search_args) in str.lower(r.author):
                    search_list.append(r)
        return search_list

    def __getitem__(self, item):
        return self.__repo[item]

    def __len__(self):
        index = 0
        while index < len(self.__repo):
            index += 1
        return index
