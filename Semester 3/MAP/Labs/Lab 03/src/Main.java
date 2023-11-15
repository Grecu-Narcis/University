import business.Controller;
import infrastructure.ProgramsRepository;
import presentation.View;

public class Main {
    public static void main(String[] args)
    {
        ProgramsRepository repo = new ProgramsRepository();
        Controller ctrl = new Controller(repo);
        View view = new View(ctrl);

        view.mainMenu();
    }
}
