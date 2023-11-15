import controller.Controller;
import repository.InMemoryRepository;
import view.View;

public class Main {
    public static void main(String[] args) {
        InMemoryRepository repo = new InMemoryRepository();
        Controller ctrl = new Controller(repo);
        View view = new View(ctrl);

        view.mainMenu();
    }
}