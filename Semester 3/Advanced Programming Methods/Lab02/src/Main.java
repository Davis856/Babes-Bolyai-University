import controller.Controller;
import repository.Repository;
import view.View;
;

public class Main {
    public static void main(String[] args) {
        try {
            Repository repository = new Repository(10);
            Controller controller = new Controller(repository);
            View view = new View(controller);
            view.start();
        } catch (ArithmeticException arithmeticException) {
            System.out.println(arithmeticException.getMessage());
        }
    }
}