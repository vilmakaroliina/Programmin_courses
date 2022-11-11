package fi.tuni.prog3.calc;

import java.text.DecimalFormat;
import java.util.HashSet;
import java.util.Set;
import javafx.application.Application;
import static javafx.application.Application.launch;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundFill;
import javafx.scene.layout.Border;
import javafx.scene.layout.BorderStroke;
import javafx.scene.layout.BorderStrokeStyle;
import javafx.scene.layout.CornerRadii;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.paint.Color;
import javafx.stage.Stage;


/**
 * JavaFX App
 */
public class Calculator extends Application {

    @Override
    public void start(Stage stage) {
        //luodaan add button
        Button btnAdd = new Button("Add");
        btnAdd.setId("btnAdd");
        
        //luodaan div button
        Button btnDiv = new Button("Divide");
        btnDiv.setId("btnDiv");
        
        //luodaan sub button
        Button btnSub = new Button();
        btnSub.setId("btnSub");
        btnSub.setText("Subtract");
        
        //luodaan mul button
        Button btnMul = new Button();
        btnMul.setId("btnMul");
        btnMul.setText("Multiply");
        
        //luodaan tekstikentta ensimmäiselle numerolle
        TextField field0p1 = new TextField();
        field0p1.setId("fieldOp1");
        //ja kenttaa kuvaava teksti
        Label label0p1 = new Label("First operand:");
        label0p1.setId("labelOp1");
        label0p1.prefWidth(300);
        
        //luodaan tekstikentta toiselle numerolle
        TextField field0p2 = new TextField();
        field0p2.setId("fieldOp2");
        //kenttaa kuvaava teksti
        Label label0p2 = new Label("Second operand:");
        label0p2.prefWidth(300);
        label0p2.setId("labelOp2");
        
        //luodaan grid ja lisataan siihen, kaikki elementit
        GridPane grid = new GridPane();
        grid.add(label0p1, 0, 1);
        grid.add(field0p1, 1, 1);
        
        grid.add(label0p2, 0, 2);
        grid.add(field0p2, 1, 2);
        
        HBox hbox = new HBox(1);
        grid.add(hbox, 1, 3);
        
        hbox.getChildren().add(btnAdd);
        hbox.getChildren().add(btnSub);
        hbox.getChildren().add(btnMul);
        hbox.getChildren().add(btnDiv); 
        
        //tuloskentta
        Label result = new Label("Result:");
        result.prefWidth(300);
        result.setId("labelRes");
        grid.add(result, 0, 4);
        Label resultField = new Label();
        resultField.setId("fieldRes");
        resultField.setMinWidth(250);
        resultField.setMinHeight(20);
        resultField.setBackground(new Background(new BackgroundFill(
                Color.WHITE, new CornerRadii(1), new Insets(1))));
        resultField.setBorder(new Border(new BorderStroke(Color.NAVY, 
                BorderStrokeStyle.SOLID, new CornerRadii(1), BorderStroke.THIN)));
        grid.add(resultField, 1, 4);
        
        Scene scene = new Scene(grid, 400, 150);
        
        DecimalFormat fr = new DecimalFormat("0.#");
        
        btnAdd.setOnAction(new EventHandler<ActionEvent> () {
            @Override
            public void handle(ActionEvent t) {
                var a = Double.parseDouble(field0p1.getText());
                var b = Double.parseDouble(field0p2.getText());
                var c = a+b;
                resultField.setText(String.format("%.1f", c));
            }
            
        });
        
        btnSub.setOnAction(new EventHandler<ActionEvent> () {
            @Override
            public void handle(ActionEvent t){
                var a = Double.parseDouble(field0p1.getText());
                var b = Double.parseDouble(field0p2.getText());
                var c = a-b;
                resultField.setText(String.format("%.1f", c));
            }
        });
        
        btnDiv.setOnAction(new EventHandler<ActionEvent> () {
            @Override
            public void handle(ActionEvent t){
                var a = Double.parseDouble(field0p1.getText());
                var b = Double.parseDouble(field0p2.getText());
                var c = a/b;
                resultField.setText(String.format("%.1f", c));
            }
        });
        
        btnMul.setOnAction(new EventHandler<ActionEvent> () {
            @Override
            public void handle(ActionEvent t){
                var a = Double.parseDouble(field0p1.getText());
                var b = Double.parseDouble(field0p2.getText());
                var c = a*b;
                resultField.setText(String.format("%.2f", c));
            }
        });
        
        stage.setScene(scene);        
        stage.setTitle("Calculator");     
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }

}