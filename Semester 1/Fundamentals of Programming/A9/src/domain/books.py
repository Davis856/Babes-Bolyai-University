class Book:
    def __init__(self, book_id, title, author):
        """
        Constructor for Book class
        """
        self.__book_id = book_id
        self.__book_title = title
        self.__book_author = author

    @property
    def id(self):
        return self.__book_id

    @property
    def title(self):
        return self.__book_title

    @title.setter
    def title(self, new_value):
        self.__book_title = new_value

    @property
    def author(self):
        return self.__book_author

    @author.setter
    def author(self, new_value):
        self.__book_author = new_value

    def __str__(self):
        return "id: " + str(self.__book_id) + " title: " + str(self.__book_title) + " author: " + str(
            self.__book_author)
