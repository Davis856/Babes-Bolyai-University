package view;

import controller.Controller;
import model.Eggplant;
import model.IVegetables;
import model.Pepper;
import model.Tomato;
import java.util.Scanner;

public class View {

    private final Controller controller;

    public View(Controller controller) {
        this.controller = controller;
    }

    public static void printMenu() {
        System.out.println("Hello! Choose an option from below:");
        System.out.println("1. Show all vegetables currently in the basket.");
        System.out.println("2. Add a new vegetable.");
        System.out.println("3. Delete a vegetable from the basket.");
        System.out.println("4. Filter the vegetables by some weight of your choice.");
        System.out.println("5. Filter the vegetables by some price of your choice.");
        System.out.println("6. Exit");
    }

    public void addVegetable() throws Exception {
        System.out.println("Hello! Enter the type of the vegetable (Eggplant, Tomato or Pepper):");
        Scanner readType = new Scanner(System.in);
        String type = readType.nextLine();
        switch (type.toLowerCase()) {
            case "eggplant" -> {
                System.out.println("Enter the desired weight of the eggplant: ");
                Scanner readWeight = new Scanner(System.in);
                float weight = readWeight.nextFloat();
                System.out.println("Enter the desired price of the eggplant: ");
                Scanner readPrice = new Scanner(System.in);
                int price = readPrice.nextInt();
                IVegetables vegetables = new Eggplant(weight, price);
                if (weight <= 0 || price <= 0) {
                    throw new Exception("Invalid data! Please choose positive numbers.");
                } else {
                    this.controller.add(vegetables);
                    System.out.println("Added successfully!");
                }
            }
            case "tomato" -> {
                System.out.println("Enter the desired weight of the tomato: ");
                Scanner readWeight = new Scanner(System.in);
                float weight = readWeight.nextFloat();
                System.out.println("Enter the desired price of the tomato: ");
                Scanner readPrice = new Scanner(System.in);
                int price = readPrice.nextInt();
                IVegetables vegetables = new Tomato(weight, price);
                if (weight <= 0 || price <= 0) {
                    throw new Exception("Invalid data! Please choose positive numbers.");
                } else {
                    this.controller.add(vegetables);
                    System.out.println("Added successfully!");
                }
            }
            case "pepper" -> {
                System.out.println("Enter the desired weight of the pepper: ");
                Scanner readWeight = new Scanner(System.in);
                float weight = readWeight.nextFloat();
                System.out.println("Enter the desired price of the pepper: ");
                Scanner readPrice = new Scanner(System.in);
                int price = readPrice.nextInt();
                IVegetables vegetables = new Pepper(weight, price);
                if (weight <= 0 || price <= 0) {
                    throw new Exception("Invalid data! Please choose positive numbers.");
                } else {
                    this.controller.add(vegetables);
                    System.out.println("Added successfully!");
                }
            }
            default -> throw new Exception("Invalid type. Please choose one from the list above.");
        }
    }

    public void removeVegetable() throws Exception {
        if (this.controller.getSize() != 0) {
            System.out.println("Enter index: ");
            Scanner readIndex = new Scanner(System.in);
            int index = readIndex.nextInt();
            if (index - 1 >= 0 && index - 1 < this.controller.getSize()) {
                this.controller.remove(index - 1);
            } else {
                throw new Exception("Invalid index!");
            }
        } else {
            throw new Exception("There is nothing to be deleted!");
        }
    }

    public void printVegetables() {
        IVegetables[] vegetables = this.controller.getVegetables();
        if (this.controller.getSize() == 0)
            System.out.println("No vegetables to show!");
        else {
            int index;
            for (index = 0; index < this.controller.getSize(); index++) {
                System.out.println((index + 1) + ". " + vegetables[index].toString());
            }
        }
    }

    public void showFilteredByWeight() throws Exception {
        System.out.println("Enter weight for filtering: ");
        Scanner readWeight = new Scanner(System.in);
        float weight = readWeight.nextFloat();
        if (weight <= 0)
            throw new Exception("Invalid weight selected!");
        else {
            if (this.controller.getSize() != 0) {
                IVegetables[] filterVegetables = this.controller.filterVegetablesByWeight(weight);
                if (filterVegetables.length == 0) {
                    System.out.println("There are no vegetables that have the weight greater than: " + weight + "kg.");
                } else {
                    int index;
                    for (index = 0; index < filterVegetables.length; index++)
                        System.out.println((index + 1) + ". " + filterVegetables[index].toString());
                }
            } else
                throw new Exception("The list is empty!");
        }
    }

    public void showFilteredByPrice() throws Exception {
        System.out.println("Enter price for filtering: ");
        Scanner readPrice = new Scanner(System.in);
        int price = readPrice.nextInt();
        if (price <= 0)
            throw new Exception("Invalid price selected!");
        else {
            if (this.controller.getSize() != 0) {
                IVegetables[] filterVegetables = this.controller.filterVegetablesByPrice(price);
                if (filterVegetables.length == 0) {
                    System.out.println("There are no vegetables that have the price greater than: " + price);
                } else {
                    int index;
                    for (index = 0; index < filterVegetables.length; index++)
                        System.out.println((index + 1) + ". " + filterVegetables[index].toString());
                }
            } else
                throw new Exception("The list is empty!");
        }
    }

    public void start() {
        boolean done = false;
        while (!done) {
            try {
                printMenu();
                Scanner readOption = new Scanner(System.in);
                int option = readOption.nextInt();
                if (option == 1) {
                    this.printVegetables();
                } else if (option == 2) {
                    this.addVegetable();
                } else if (option == 3) {
                    this.removeVegetable();
                } else if (option == 4) {
                    this.showFilteredByWeight();
                } else if (option == 5) {
                    this.showFilteredByPrice();
                } else if (option == 6) {
                    done = true;
                } else {
                    System.out.println("Invalid input!");
                }
            } catch (Exception exception) {
                System.out.println(exception.getMessage());
            }
        }
    }

}
