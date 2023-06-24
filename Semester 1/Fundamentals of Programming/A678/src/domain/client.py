class Client:
    def __init__(self, client_id, name):
        """
        Constructor for Client class
        """
        self.__client_id = client_id
        self.__client_name = name

    @property
    def id(self):
        return self.__client_id

    @property
    def name(self):
        return self.__client_name

    @name.setter
    def name(self, new_value):
        self.__client_name = new_value

    def __str__(self):
        return "ID: " + str(self.__client_id) + " Name: " + str(self.__client_name)
