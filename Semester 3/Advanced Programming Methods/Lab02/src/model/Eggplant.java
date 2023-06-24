package model;

public class Eggplant implements IVegetables {

    private float weight;
    private int price;

    public Eggplant(float weight, int price) {
        this.weight = weight;
        this.price = price;
    }

    @Override
    public float getWeight() {
        return this.weight;
    }

    @Override
    public void setWeight(float weight) {
        this.weight = weight;
    }

    @Override
    public String toString() {
        return "Eggplant has the weight: " + this.weight + " kg and the price: " + this.price;
    }

    @Override
    public int getPrice() {
        return price;
    }

    @Override
    public void setPrice(int price) {
        this.price = price;
    }
}
