package repository;

import model.IVegetables;

public interface IRepository {
    void add(IVegetables vegetables) throws Exception;
    void remove(int index);
    IVegetables[] getVegetables();
    int getSize();

}
