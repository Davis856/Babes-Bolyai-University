#include "undoredo.h"

UndoRedoAdd::UndoRedoAdd(const Coat& Coat, Repository& newRepo) : addedCoat(Coat), repo(newRepo) {

}

void UndoRedoAdd::undo() {
    int index = this->repo.FindElemBySize(this->addedCoat.getSize());
    this->repo.removeCoat(index);
}

void UndoRedoAdd::redo() {
    this->repo.addCoat(this->addedCoat);
}

UndoRedoRemove::UndoRedoRemove(const Coat& Coat, Repository& newRepo) : removedCoat(Coat), repo(newRepo) {

}

void UndoRedoRemove::undo() {
    this->repo.addCoat(this->removedCoat);
}

void UndoRedoRemove::redo() {
    int index = this->repo.FindElemBySize(this->removedCoat.getSize());
    this->repo.removeCoat(index);
}

UndoRedoUpdate::UndoRedoUpdate(const Coat& oldCoat, const Coat& newCoat, Repository& newRepo) : oldCoat(oldCoat), newCoat(newCoat), repo(newRepo) {

}

void UndoRedoUpdate::undo() {
    int index = this->repo.FindElemBySize(this->newCoat.getSize());
    this->repo.updateSize(index, this->oldCoat.getSize());
    this->repo.updateColour(index, this->oldCoat.getColour());
    this->repo.updateQuantity(index, this->oldCoat.getQuantity());
    this->repo.updatePrice(index, this->oldCoat.getPrice());
    this->repo.updatePhotograph(index, this->oldCoat.getPhotograph());
}

void UndoRedoUpdate::redo() {
    int index = this->repo.FindElemBySize(this->oldCoat.getSize());
    this->repo.updateSize(index, this->newCoat.getSize());
    this->repo.updateColour(index, this->newCoat.getColour());
    this->repo.updateQuantity(index, this->newCoat.getQuantity());
    this->repo.updatePrice(index, this->newCoat.getPrice());
    this->repo.updatePhotograph(index, this->newCoat.getPhotograph());
}

UndoRedoUser::UndoRedoUser(const Coat& adoptedCoat, Repository& newRepo, Basket* newUserRepo) : boughtCoat(boughtCoat), repo(newRepo) {
    this->userRepo = newUserRepo;
}

void UndoRedoUser::undo() {
    this->userRepo->deleteUserRepo(adoptedCoat);
}

void UndoRedoUser::redo() {
    int index = this->repo.FindElemBySize(this->boughtCoat.getSize());
    this->userRepo->addCoatToBasket(boughtCoat);
}