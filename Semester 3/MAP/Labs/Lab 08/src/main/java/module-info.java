module ubb.lab08 {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires com.dlsc.formsfx;
    requires org.kordamp.bootstrapfx.core;

    opens ubb to javafx.fxml;
    //exports ubb;
    exports ubb.business;
    opens ubb.business to javafx.fxml;
    exports ubb.presentation.gui;
    opens ubb.presentation.gui to javafx.fxml;
    exports ubb.business.view_controllers;
    opens ubb.business.view_controllers to javafx.fxml;
}