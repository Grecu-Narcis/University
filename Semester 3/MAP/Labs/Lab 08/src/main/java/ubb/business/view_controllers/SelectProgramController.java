package ubb.business.view_controllers;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.Region;
import javafx.stage.Stage;
import ubb.exceptions.InterpreterException;
import ubb.models.adts.MyDictionary;
import ubb.presentation.gui.Main;
import ubb.models.statements.IStatement;
import ubb.presentation.Examples;

import java.io.IOException;

public class SelectProgramController {
    @FXML
    private ListView<IStatement> programsList;

    @FXML
    private Button selectButton;

    @FXML
    public void initialize()
    {
        ObservableList<IStatement> allPrograms = FXCollections.observableArrayList(Examples.getAllExamples());
        programsList.setItems(allPrograms);
        programsList.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);

        programsList.setOnMouseClicked(
                event -> {
                    if (event.getClickCount() == 2)
                        selectButtonHandler();
                }
        );
    }

    private void openProgramWindow(IStatement selectedProgram)
    {
        try {
            FXMLLoader programLoader = new FXMLLoader(Main.class.getResource("/ubb/program-view.fxml"));
            Parent root;

            selectedProgram.typeCheck(new MyDictionary<>());

            root = programLoader.load();

            ProgramController controller = programLoader.getController();
            controller.setProgramStatement(selectedProgram);

            Stage programStage = new Stage();
            programStage.setTitle("Program window!");
            programStage.setScene(new Scene(root));
            programStage.show();
        }
        catch (IOException | InterpreterException e)
        {
            Alert alert = new Alert(Alert.AlertType.ERROR, e.getMessage(), ButtonType.OK);
            alert.getDialogPane().setMinHeight(Region.USE_PREF_SIZE);
            alert.showAndWait();
        }
    }

    @FXML
    public void selectButtonHandler() {
        int index = programsList.getSelectionModel().getSelectedIndex();
        if (index < 0)
            return;

        IStatement selectedProgram = Examples.getAllExamples().get(index);

        if (selectedProgram == null)
            return;

        this.openProgramWindow(selectedProgram);
    }

}
