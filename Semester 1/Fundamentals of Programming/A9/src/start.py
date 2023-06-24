from src.repository.repository import BookRepository
from src.repository.repository import ClientRepository
from src.repository.repository import RentalRepository
from src.repository.repository import BookRepositoryTxt
from src.repository.repository import ClientRepositoryTxt
from src.repository.repository import RentalRepositoryTxt
from src.repository.repository import BookRepositoryBin
from src.repository.repository import ClientRepositoryBin
from src.repository.repository import RentalRepositoryBin
from src.services.bookservice import BookService
from src.services.clientservice import ClientService
from src.services.rentalservice import RentalService
from src.services.undoservice import UndoService
from src.ui.ui import UI
from src.ui.gui import GUI

config = []

with open("settings.properties", "rt") as f:
    for r in f.readlines():
        label, value = r.split("=", 1)
        config.append(value.strip())

if config[0] == "inmemory":
    book_repo = BookRepository()
    client_repo = ClientRepository()
    rental_repo = RentalRepository()
elif config[0] == "txt":
    book_repo = BookRepositoryTxt(config[1])
    client_repo = ClientRepositoryTxt(config[2])
    rental_repo = RentalRepositoryTxt(config[3])
elif config[0] == "bin":
    book_repo = BookRepositoryBin(config[1])
    client_repo = ClientRepositoryBin(config[2])
    rental_repo = RentalRepositoryBin(config[3])

option = config[4]

undo_service = UndoService()
rental_service = RentalService(rental_repo, book_repo, client_repo, undo_service)
book_service = BookService(book_repo, undo_service)
client_service = ClientService(client_repo, undo_service)

if option == 'UI':
    ui = UI(book_service, client_service, rental_service, undo_service)
    ui.start()
elif option == 'GUI':
    gui = GUI(book_service, client_service, rental_service, undo_service)
    gui.start()
