package model;

public class Tomato implements IVegetables {

    private float weight;
    private int price;

    public Tomato(float weight, int price) {
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
        return "Tomato has the weight: " + this.weight + " kg and the price: " + this.price;
    }

    @Override
    public void setPrice(int price) {
        this.price = price;
    }

    @Override
    public int getPrice() {
        return price;
    }
}
