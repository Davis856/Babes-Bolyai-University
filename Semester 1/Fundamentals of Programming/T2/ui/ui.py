from service.service import RideServ


class Ui:
    def __init__(self):
        self._serv = RideServ()

    def add_ride(self):
        print("Coordinates of the ride(one on each row):")
        x = int(input())
        y = int(input())
        try:
            self._serv.add_ride(x, y)
            print("Added successfully")
            print("Waiting for a taxi")
            #assign = self._serv.assign()
            #print("Taxi ID: " + str(assign[0]) + "," + " Fare: " + str(assign[1]))
        except ValueError:
            print("Invalid coordinates")

    def show_taxis(self):
        taxis = self._serv.taxis()
        for t in taxis:
            print(str(t))

    def show_rides(self):
        rides = self._serv.rides()
        for r in rides:
            print(str(r))

    @staticmethod
    def main_menu():
        print("1. Add a ride")
        print("2. Show rides")
        print("0. Exit")

    def start(self):
        print("How many taxis to generate?")
        nr = int(input())
        self._serv.generate(nr)
        self.show_taxis()

        while True:
            print("Select option")
            opt = input()
            if opt == "1":
                self.add_ride()
            elif opt == "2":
                self.show_rides()
            elif opt == "0":
                return


ui = Ui()
ui.start()
