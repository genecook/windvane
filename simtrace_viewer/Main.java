package simtrace_viewer;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import javafx.application.Platform;
import javafx.concurrent.Task;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.stage.WindowEvent;

import javafx.animation.FadeTransition;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Screen;
import javafx.stage.Stage;
import javafx.stage.StageStyle;
import javafx.stage.Popup;
import javafx.scene.layout.*;
import javafx.scene.text.*;
import javafx.scene.control.*;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.effect.DropShadow;

import javafx.geometry.Pos;
import javafx.geometry.Rectangle2D;

import javafx.util.Duration;

import java.io.*;
import java.util.*;
import javax.swing.*;
import java.lang.Integer;
import java.net.URL;
import java.net.URI;
import javax.imageio.ImageIO;
import java.net.URISyntaxException;

public class Main extends Application {
    public  Stage mainStage;
    private Pane  splashLayout;
    private static final int SPLASH_WIDTH = 700;
    private static final int SPLASH_HEIGHT = 750;
    private Label someText;

    public static String SimTraceFileArg = "";
    public static int    CoreIndexArg    = -1;
    public static long   ClockArg        = -1;

    @Override
    public void init() {
	//ImageView splash = new ImageView(new Image("file:images/logo.jpg"));
	ImageView splash = new ImageView(new Image(getClass().getResource("images/logo.jpg").toString()));
	//System.out.println("image url:" + getClass().getResource("images/logo.jpg").toString());
        splashLayout = new VBox();
        someText = new Label("Tuleta Software Co. A privately held software company deep in the heart of Texas.");
        splashLayout.getChildren().addAll(splash,someText);
        splashLayout.setEffect(new DropShadow());
    }

    @Override
    public void start(Stage initStage) throws Exception {
        showMainStage();
        showSplash(initStage);
        initStage.toFront();
        FadeTransition fadeSplash = new FadeTransition(Duration.seconds(3.0), splashLayout);
        fadeSplash.setFromValue(10.0);
        fadeSplash.setToValue(0.0);
        fadeSplash.setOnFinished(new EventHandler<ActionEvent>() {
            @Override public void handle(ActionEvent actionEvent) {
              initStage.hide();
            }
        });
        fadeSplash.play();
    }
    
    public static void main(String[] args) {
        if (args.length == 3) {
	    SimTraceFileArg = args[0];
            CoreIndexArg    = Integer.parseInt(args[1]);
            ClockArg        = Long.parseLong(args[2]);

            System.out.println("sim-trace file: '" + SimTraceFileArg + "'");
            System.out.println("core:           " + String.format("%d",CoreIndexArg));
            System.out.println("clock:          " + String.format("%d",ClockArg));
	}
        launch(args);
    }

    private FXMLLoader fxmlLoader; // make instance of FXML loader, to allow controller access at app exit time...

    private void showMainStage() {
        mainStage = new Stage();
        try {
           FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("simtrace_viewer.fxml"));
           Parent root = fxmlLoader.load();

           mainStage.setTitle("A64sim Trace Viewer");
           mainStage.setScene(new Scene(root, 1350, 900));

           mainStage.show();
        } catch (IOException ex) {
            System.out.println("ERROR DUDE!\n");
            ex.printStackTrace(System.out);
        }
    }

    private void showSplash(Stage initStage) {
        Scene splashScene = new Scene(splashLayout);

        initStage.initStyle(StageStyle.TRANSPARENT);
        initStage.setOpacity(0.5);

        final Rectangle2D bounds = Screen.getPrimary().getBounds();
        initStage.setTitle("Tuleta Software Co.");
        initStage.setScene(splashScene);
        initStage.setX(bounds.getMinX() + bounds.getWidth() / 2 - SPLASH_WIDTH/2);
        initStage.setY(bounds.getMinY() + bounds.getHeight() / 2 - SPLASH_HEIGHT/2 - 100);
        initStage.show();
    }

}
