package repository;

import model.IVegetables;

public class Repository implements IRepository {

    private IVegetables[] vegetables;
    private int numberOfVegetables;

    public Repository(int size) {
        if (size <= 0)
            throw new ArithmeticException("The capacity of the repository cannot be 0 or less.");
        this.vegetables = new IVegetables[size];
        this.numberOfVegetables = 0;
    }

    @Override
    public void add(IVegetables vegetables) throws Exception {
        if (this.numberOfVegetables == this.vegetables.length)
            throw new Exception("Cannot add. The capacity of the repository is full.");
        this.vegetables[numberOfVegetables] = vegetables;
        numberOfVegetables++;
    }

    @Override
    public void remove(int index) {
        IVegetables[] vegetablesCopy = new IVegetables[this.numberOfVegetables - 1];
        for (int i = 0, j = 0; i < this.numberOfVegetables; i++) {
            if (i != index) {
                vegetablesCopy[j] = this.vegetables[i];
                j++;
            }
        }
        this.vegetables = vegetablesCopy;
        this.numberOfVegetables--;
    }

    @Override
    public IVegetables[] getVegetables() {
        return this.vegetables;
    }

    @Override
    public int getSize() {
        return this.numberOfVegetables;
    }
}
