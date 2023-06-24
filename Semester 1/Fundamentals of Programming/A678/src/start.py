from src.repository.repository import BookRepository
from src.repository.repository import ClientRepository
from src.repository.repository import RentalRepository
from src.services.bookservice import BookService
from src.services.clientservice import ClientService
from src.services.rentalservice import RentalService
from src.services.undoservice import UndoService
from src.ui.ui import UI
from src.ui.gui import GUI


book_repo = BookRepository()
client_repo = ClientRepository()
rental_repo = RentalRepository()

undo_service = UndoService()
rental_service = RentalService(rental_repo, book_repo, client_repo, undo_service)
book_service = BookService(book_repo, undo_service)
client_service = ClientService(client_repo, undo_service)

print("UI or GUI? or exit")
while True:
    option = input()
    if option == 'UI':
        ui = UI(book_service, client_service, rental_service, undo_service)
        ui.start()
    elif option == 'GUI':
        gui = GUI(book_service, client_service, rental_service, undo_service)
        gui.start()
    elif option == 'exit':
        break
    else:
        print("Bad command!")
