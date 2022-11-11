package fi.tuni.prog3.wordle;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import javafx.application.Application;
import static javafx.application.Application.launch;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundFill;
import javafx.scene.layout.Border;
import javafx.scene.layout.BorderStroke;
import javafx.scene.layout.BorderStrokeStyle;
import javafx.scene.layout.CornerRadii;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.StackPane;
import javafx.scene.paint.Color;
import javafx.stage.Stage;


/**
 * JavaFX App
 */
public class Wordle extends Application {
    //kaikki tiedoston sanat
    private final ArrayList<String> words = new ArrayList<>();
    //pelikertaan liittyvat muuttujat
    private String correctWord;
    private int wordIndex = -1;
    private int numberOfGuesses = 0;
    private boolean gameOver = true;
    private String guessedWord = "";
    //pelilauta ja ikkunan grid
    private ArrayList<TextField> gameBoard= new ArrayList<>();
    private final GridPane grid = new GridPane();


    @Override
    public void start(Stage stage) throws IOException {
        readFile();
        
        Button startButton = new Button("Start game!");
        startButton.setId("newGameBtn");
        
        Button guessButton = new Button("Guess word!");
        
        Label infoBox = new Label("");
        infoBox.setId("infoBox");
        infoBox.setMinWidth(100);
        Label testBox = new Label();
        
        //lisataan tuotteet griddiin      
        grid.add(startButton, 0, 0);
        grid.add(infoBox, 1, 0);
        grid.add(guessButton, 2, 0);
        grid.add(testBox, 3, 0);
        
        //arvausnappi
        guessButton.setOnAction(new EventHandler<ActionEvent> () {
            @Override
            public void handle(ActionEvent t){
                String info = guessWord();
                infoBox.setText(info);
        }
        });
        
        correctWord = words.get(0);
        for (int i = 0; i < 6; ++i){
                    //sitten seuraavat rivit
                    for (int j = 0; j < correctWord.length(); ++j){                        
                        TextField letter = new TextField("");
                        letter.setMinHeight(50);
                        letter.setMinWidth(50);
                        letter.setId(String.format("%d_%d", i, j));
                        letter.setBorder(new Border(new BorderStroke(
                                Color.BLACK, 
                                BorderStrokeStyle.SOLID, 
                                new CornerRadii(1), BorderStroke.THIN)));
                        letter.setBackground(new Background(new BackgroundFill(
                        Color.WHITE, new CornerRadii(1), new Insets(1))));
                        letter.setText(letter.getId());
                        gameBoard.add(letter);                        
                    }
                }
                addLabels();
                
        //start painikkeen toiminta
        startButton.setOnAction(new EventHandler<ActionEvent> () {
            @Override
            public void handle(ActionEvent t) {
                wordIndex += 1;
                correctWord = words.get(wordIndex);
                gameOver = false;
                numberOfGuesses = 0;
                infoBox.setText("");
                guessedWord = "";
                
                clearBoard();
                gameBoard.clear();
                
                int boardLength = correctWord.length();
                //ensin tavallaan luodaan ensimmainen rivi
                for (int i = 0; i < 6; ++i){
                    //sitten seuraavat rivit
                    for (int j = 0; j < boardLength; ++j){                        
                        TextField letter = new TextField("");
                        letter.setMinHeight(50);
                        letter.setMinWidth(50);
                        String id = String.format("%s_%s", Integer.toString(i), 
                                Integer.toString(j));
                        letter.setId(id);
                        letter.setBorder(new Border(new BorderStroke(
                                Color.BLACK, 
                                BorderStrokeStyle.SOLID, 
                                new CornerRadii(1), BorderStroke.THIN)));
                        letter.setBackground(new Background(new BackgroundFill(
                        Color.WHITE, new CornerRadii(1), new Insets(1))));
                        gameBoard.add(letter);                        
                    }
                }
                addLabels();
            }
        });    
        
        //alustetaan scene ja stage
        var scene = new Scene(grid, 900, 500);
        
        scene.addEventFilter(KeyEvent.KEY_PRESSED, new EventHandler<KeyEvent> () {
            @Override
            public void handle(KeyEvent t) {
                if(t.getCode().equals(KeyCode.ENTER)){
                    String info = guessWord();
                    infoBox.setText(info);                    
                }
                else if (t.getCode().equals(KeyCode.BACK_SPACE)){
                    removeLetter();                
                }
                else if (gameOver == false){
                    addLetter(t);                    
                }
            }            
        });
        
        stage.setScene(scene);
        stage.setTitle("Wordle");
        stage.show();
    }
    
    public void removeLetter(){
        int lastIndex = guessedWord.length()-1;
        guessedWord = guessedWord.substring(0, lastIndex);
            for (TextField l : gameBoard){
                if (l.getId().equals(String.format(
                    "%s_%s", Integer.toString(numberOfGuesses), 
                        lastIndex))){
                        l.setText("");
                }
            }
    }
    
    //syotetaan kirjain peliin
    public void addLetter(KeyEvent t){
        guessedWord += t.getCode();
                    int i = numberOfGuesses;
                    int j = guessedWord.length()-1;
                    for (TextField l : gameBoard){
                        if (l.getId().equals(String.format("%s_%s", i, j))){
                            l.setText(t.getCode().toString());
                        }
                    }
    }
    
    public int getStartIndex() {
        int lineNumber = numberOfGuesses-1;
        int startIndex;
        if (lineNumber == 0){
            startIndex = 0;
        }
        else if (lineNumber == 1){
            startIndex = correctWord.length();
        }
        else if (lineNumber == 2){
            startIndex = correctWord.length()*2;
        }
        else if (lineNumber == 3){
            startIndex = correctWord.length()*3;
        }
        else if (lineNumber == 4){
            startIndex = correctWord.length()*4;
        }
        else{
            startIndex = correctWord.length()*5;
        }
        return startIndex;
    }
    
    public void checkLetters(){
        int lineNumber = numberOfGuesses - 1;
        int startIndex = getStartIndex();        
        
        //esin muutetaan kaikki olemassa olevat kirjaimet keltaiseksi
        for (int i = startIndex; i < startIndex + guessedWord.length(); ++i ){
            TextField l = gameBoard.get(i);
            if (correctWord.contains(l.getText())){
                l.setBackground(new Background(new BackgroundFill(
                Color.ORANGE, new CornerRadii(1), new Insets(1))));
            }
            else {
                l.setBackground(new Background(new BackgroundFill(
                Color.GREY, new CornerRadii(1), new Insets(1))));
            }
        }
        //sitten oikeassa kohdassa olevat vihreaksi
        for (int i = 0; i < guessedWord.length(); ++i){
            if (guessedWord.charAt(i) == correctWord.charAt(i)){
                for (TextField l : gameBoard){
                    if (l.getId().equals(String.format("%s_%s", 
                            Integer.toString(lineNumber), Integer.toString(i)))){
                        l.setBackground(new Background(new BackgroundFill(
                        Color.GREEN, new CornerRadii(1), new Insets(1))));
                    }
                }
            }
        }
    }
    
    //funktio, joka tarkistaa arvatun sanan
    public String guessWord(){
        String result = "";
        if (guessedWord.length() != correctWord.length()){
            result = "Give a complete word before pressing Enter!";
        }
        else {
            
            if (guessedWord.equals(correctWord)){
                numberOfGuesses += 1;
                result = "Congratulations, you won!";
                checkLetters();
                gameOver = true;
            }
            else {
                numberOfGuesses += 1;
                if (numberOfGuesses == 6){
                    result = "Game over, you lost!";
                    gameOver =true;
                }
                else {
                    checkLetters();
                    guessedWord = "";
                }
            }
        }        
        return result;
    }
    
    public void readFile() throws FileNotFoundException, IOException{
        try(BufferedReader input = new BufferedReader(new FileReader("words.txt")))
        {
            String line;
            while ((line = input.readLine()) != null)
            {
                this.words.add(line.toUpperCase());
            }         
        }
    }
    
    public void clearBoard(){
        for (TextField l : gameBoard){
            grid.getChildren().remove(l);
        }        
    }
    
    public void addLabels(){
        for (TextField l : gameBoard){
            int i = l.getId().charAt(0);
            int j;
            if (l.getId().length() == 3) {
                j = l.getId().charAt(2);
            }
            else {
               int s = l.getId().charAt(2);
               int s2 = l.getId().charAt(3);
               String number = String.format("%d%d", s, s2);
               j = Integer.valueOf(number);                
            }
            grid.add(l, j+1, i+1);
        }
    }

    public static void main(String[] args) throws FileNotFoundException, IOException {
        launch();
        
    }

}