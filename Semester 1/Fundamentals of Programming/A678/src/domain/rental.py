import datetime
import time


class Rental:
    def __init__(self, rental_id, book_id, client_id, rented_date="00/00/0000 00:00:00",
                 returned_date="Not yet"):
        self.__rental_id = rental_id
        self.__book_id = book_id
        self.__client_id = client_id
        self.__rented_date = rented_date
        self.__returned_date = returned_date

    @property
    def rental_id(self):
        return self.__rental_id

    @property
    def book_id(self):
        return self.__book_id

    @book_id.setter
    def book_id(self, new_value):
        self.__book_id = new_value

    @property
    def client_id(self):
        return self.__client_id

    @client_id.setter
    def client_id(self, new_value):
        self.__client_id = new_value

    @property
    def rented_date(self):
        return self.__rented_date

    @rented_date.setter
    def rented_date(self, new_value):
        self.__rented_date = new_value

    @property
    def returned_date(self):
        return self.__returned_date

    @returned_date.setter
    def returned_date(self, new_value):
        self.__returned_date = new_value

    def __str__(self):
        return "ID: " + str(self.__rental_id) + " Book ID: " + str(self.__book_id) + " Client ID: " + str(
            self.__client_id) + " Rented date: " + str(self.__rented_date) + " Returned date: " + str(
            self.__returned_date)