package controller;

import model.IVegetables;
import repository.IRepository;


public class Controller {
    private final IRepository repository;

    public Controller(IRepository repository) {
        this.repository = repository;
    }

    public void add(IVegetables vegetables) throws Exception {
        this.repository.add(vegetables);
    }

    public void remove(int index) {
        this.repository.remove(index);
    }

    public IVegetables[] getVegetables() {
        return this.repository.getVegetables();

    }

    public int getSize() {
        return this.repository.getSize();
    }

    public IVegetables[] filterVegetablesByWeight(float weight) {
        IVegetables[] vegetablesCopy = new IVegetables[this.repository.getSize()];
        int size = 0;
        for (IVegetables vegetables : this.repository.getVegetables())
            if (vegetables != null)
                if (vegetables.getWeight() > weight)
                    vegetablesCopy[size++] = vegetables;
        IVegetables[] vegReturn = new IVegetables[size];
        System.arraycopy(vegetablesCopy, 0, vegReturn, 0, size);
        return vegReturn;
    }

    public IVegetables[] filterVegetablesByPrice(int price) {
        IVegetables[] vegetablesCopy = new IVegetables[this.repository.getSize()];
        int size = 0;
        for (IVegetables vegetables : this.repository.getVegetables())
            if (vegetables != null)
                if (vegetables.getPrice() > price)
                    vegetablesCopy[size++] = vegetables;
        IVegetables[] vegReturn = new IVegetables[size];
        System.arraycopy(vegetablesCopy, 0, vegReturn, 0, size);
        return vegReturn;
    }
}
