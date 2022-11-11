package fi.tuni.prog3.sisu2;
//import java.awt.event.ActionEvent;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.JsonArray;
import java.io.File;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.Writer;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.TreeSet;
//import java.util.logging.Level;
//import java.util.logging.Logger;
import javafx.application.Application;
import static javafx.application.Application.launch;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.CheckBox;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.scene.control.ProgressIndicator;
import javafx.scene.control.TextField;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundFill;
import javafx.scene.layout.Border;
import javafx.scene.layout.BorderStroke;
import javafx.scene.layout.BorderStrokeStyle;
import javafx.scene.layout.CornerRadii;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.stage.Stage;
import javafx.scene.text.TextAlignment;


public class Sisu2 extends Application {
    private Student student;
    private ObservableList<String> items = FXCollections.observableArrayList ();
    //mapissa kurssin nimi ja sen alla olevat groupId:t
    private final HashMap<String, ArrayList<String>> moduleInfos = new HashMap<>();
    private final HashMap<String, String> courseInfos = new HashMap<>();
    private HashMap<String, ArrayList<String>> modCour = new HashMap<>();
    private ArrayList<CheckBox> boxes = new ArrayList<>();
    private TreeSet<String> checkedCourses = new TreeSet<>();

    /**
     * Luodaan kayttoliittyman ensimmaisen nakyman elementit ja toteutaan niiden
     * toiminnallisuus. Nakymassa kysytaan opiskelijan tiedot: nimi ja
     * opiskelijanumero. Kun tiedot on annettu, ne tallennetaan yksityisiin
     * muuttujiin ja voidaan siirtya eteenpain ohjelmassa. 
     * @param stage 
     */
    @Override
    public void start(Stage stage) {       
        items.clear();
        var root = new VBox();
        
        var grid = new GridPane();
        grid.setPadding(new Insets(20));
        
        var titleLbl = new Label("Kirjaudu syöttämällä nimi ja opiskelijanumero");
        var nameLbl = new Label("Opiskelijan nimi:");
        nameLbl.setMinWidth(120);
        var numberLbl = new Label("Opiskelijanumero: ");
        numberLbl.setMinWidth(120);
        var nameText = new TextField();
        var numberText = new TextField();
        var continueBtn = new Button("Jatka");
        
        continueBtn.setBorder(new Border(new BorderStroke(
                        Color.DARKGREY, BorderStrokeStyle.SOLID, 
                                new CornerRadii(3), BorderStroke.THIN)));
        continueBtn.setBackground(new Background(new BackgroundFill(
                        Color.POWDERBLUE, new CornerRadii(3), new Insets(1))));
        
        root.setStyle("-fx-background-color: transparent;");
        grid.setStyle("-fx-background-color: transparent;");
        var scene = new Scene(root, 640, 480, Color.ALICEBLUE);
        
        grid.addRow(1, nameLbl, nameText);
        grid.addRow(2, numberLbl, numberText, continueBtn);
        grid.setAlignment(Pos.CENTER);
        
        root.getChildren().add(titleLbl);
        root.getChildren().add(grid);
        root.setAlignment(Pos.CENTER);
        
        stage.setScene(scene);
        stage.setTitle("SISU");

        continueBtn.setOnAction(new EventHandler<javafx.event.ActionEvent> () {
            @Override
            public void handle(javafx.event.ActionEvent t){
                String studentName = nameText.getText();
                String studentNumber = numberText.getText();
                if (studentName.isEmpty() || studentNumber.isEmpty()){
                    Label reminderLbl = new Label("Anna opiskelijan tiedot");
                    grid.add(reminderLbl, 1, 3);
                }
                else{
                    student = new Student(studentName, studentNumber);
                    
                    try {
                        newScene(stage);
                    } catch (FileNotFoundException ex) {
                        ex.printStackTrace();
                    } catch (IOException ex) {
                        ex.printStackTrace();
                    }
                }
        }
        });
        
        stage.show();

    }
    /**
     * Funktio luo kayttoliittyman viimeisen nakyman. Nakynmassa annetaan
     * ilmoitus opintosuunnitelman onnistuneesta tallentamisesta ja 
     * siita on mahdollista siirtya uudelleen aloitusnakymaan, jossa 
     * syotetaan opiskelijan tiedot.
     * @param stage 
     */
    public void finalScene(Stage stage) {
        var root = new VBox(30);
        root.setStyle("-fx-background-color: transparent;");
        root.setAlignment(Pos.CENTER);
        var scene = new Scene(root, 640, 480, Color.ALICEBLUE);
        
        String text1 = String.format("%s: %s", student.getName(), 
                student.getNumber());
        Label lbl1 = new Label(text1);
        lbl1.setFont(new Font(18));
        String text2 = "Opiskelijan tiedot ja kurssivalinnat tallennettu "
                + "tiedostoon!";
        Label lbl2 = new Label(text2);
        Button btn = new Button("Takaisin etusivulle");
        
        btn.setBorder(new Border(new BorderStroke(
                        Color.DARKGREY, BorderStrokeStyle.SOLID, 
                                new CornerRadii(3), BorderStroke.THIN)));
        btn.setBackground(new Background(new BackgroundFill(
                        Color.POWDERBLUE, new CornerRadii(3), new Insets(1))));
        
        btn.setOnAction(new EventHandler<javafx.event.ActionEvent> () {
            @Override
            public void handle(javafx.event.ActionEvent t){
                start(stage);
        }
        });
        
        root.getChildren().add(lbl1);
        root.getChildren().add(lbl2);
        root.getChildren().add(btn);
        
        stage.setScene(scene);
        
    }
    /**
     * Funktio luo kayttoliittyman toisen nakyman elementit ja niiden 
     * toiminnalisuudet. Funktio kutsuu readModuleJsonData ja readCourseData 
     * seka connecCourses funktiota, luodakseen nakyman opintosuunnitelman
     * moduleista ja niiden alaisista kursseista. Kayttaja voi nakymassa
     * avata eri moduulien rakenteita ja valita niiden alta mieluisat kurssinsa.
     * Nakymassa on myos edistymista kuvaava rakenne, joka kertoo montako
     * prosenttia kursseista on valittu.
     * @param stage
     * @throws FileNotFoundException
     * @throws IOException 
     */
    public void newScene(Stage stage) 
            throws FileNotFoundException, IOException {
        
        var root = new VBox();
        modCour.clear();
        //kutustaan funktiota, jolla luetaan tiedot json tiedostoista
        readModuleJsonData();
        readCourseJson();
        connectCourses();
        
        // Asetetaan scene ja taustaväri.
        var grid = new GridPane();
        root.setStyle("-fx-background-color: transparent;");
        grid.setStyle("-fx-background-color: transparent;");
        var scene = new Scene(root, 1300, 700, Color.ALICEBLUE);
        
        // Luodaan opiskelijan tiedot, jotka näytetään näytön yläosassa.
        String info = String.format("Opiskelija\n%s\n%s", student.getName(), 
                student.getNumber());
        var infoLbl = new Label(info);
        infoLbl.setPadding(new Insets(0, 0, 0, 57));
        infoLbl.setTextAlignment(TextAlignment.CENTER);
        infoLbl.setMinWidth(200);
        
        // Luodaan uloskirjautumisnappi ja muotoillaan se. 
        Button signoutBtn = new Button("Kirjaudu ulos");
        signoutBtn.setMinWidth(200);
        signoutBtn.setTextAlignment(TextAlignment.CENTER);
        signoutBtn.setBorder(new Border(new BorderStroke(
                        Color.DARKGREY, BorderStrokeStyle.NONE, 
                                new CornerRadii(3), BorderStroke.THIN)));
        signoutBtn.setBackground(new Background(new BackgroundFill(
                        Color.ALICEBLUE, new CornerRadii(3), new Insets(1))));
        signoutBtn.setTextFill(Color.CORNFLOWERBLUE);
        
        Label emptyRow = new Label("");
        
        root.getChildren().add(infoLbl);
        root.getChildren().add(signoutBtn);
        root.getChildren().add(emptyRow);
        
        // Kirjaa ulos järjestelmästä napin painalluksella.
        signoutBtn.setOnAction(new EventHandler<javafx.event.ActionEvent> () {
            @Override
            public void handle(javafx.event.ActionEvent t){
                modCour.clear();
                start(stage);
        }
        });
        
        //Luotu lista, johon listataan haluttavat opintokokonaisuudet. Näitä
        //voidaan ilmeisesti valita ja mahdollisesti tehdä toimintoja tätä
        // kautta
        ListView<String> list = new ListView<>();
        //ObservableList<String> items = FXCollections.observableArrayList (
                //"Opintokokonaisuus 1: matikka", "Opintokokonaisuus 2: kemia", 
                //"Opintokokonaisuus 3: biologia", 
                //"Opintokokonaisuus 4: ohjelmointi");
        list.setItems(items);
        list.setPrefWidth(470);
        list.setPrefHeight(220);
        list.setMaxWidth(470);
        list.setMaxHeight(220);
        list.setPadding(new Insets(0, 0, 0, 20));
        list.setBorder(new Border(new BorderStroke(
                        Color.DARKGREY, BorderStrokeStyle.NONE, 
                                new CornerRadii(3), BorderStroke.THIN)));
        list.setBackground(new Background(new BackgroundFill(
                        Color.ALICEBLUE, new CornerRadii(3), new Insets(1))));
        
        HBox ListLine = new HBox(10);
        grid.add(ListLine, 1, 2);
        ListLine.getChildren().add(list);
        
        // Luodaan otsikko ja muotoillaan se. 
        var title1Lbl = new Label("Opintokokonaisuudet:");
        title1Lbl.setPadding(new Insets(0, 0, 0, 20));
        title1Lbl.setFont(new Font(18));
        HBox titleLine = new HBox(10);
        grid.add(titleLine, 1, 1);
        titleLine.getChildren().add(title1Lbl);
        
        // Luodaan prosessipalkki
        ProgressIndicator pIndicator = new ProgressIndicator();
        pIndicator.setProgress(0.0f);
        pIndicator.setPadding(new Insets(0, 0, 0, 30));
        HBox processLine = new HBox(10);
        grid.add(processLine, 1, 4);
        processLine.getChildren().add(pIndicator);
        
        //Prosessipalkin otsikko
        var title2Lbl = new Label("Opintojen edistyminen:");
        title2Lbl.setPadding(new Insets(20, 0, 0, 20));
        title2Lbl.setFont(new Font(18));
        HBox title2Line = new HBox(10);
        grid.add(title2Line, 1, 3);
        title2Line.getChildren().add(title2Lbl);
        
        // Lista opintosuunnan kursseista
        VBox courses = new VBox();
        courses.setPrefSize(450, 220);
        courses.setMaxSize(450, 220);
        courses.setPadding(new Insets(0, 0, 0, 20));
        Label courseLbl = new Label("Kurssit:");
        courseLbl.setMinWidth(200);
        courseLbl.setFont(new Font(18));
        grid.add(courses, 2, 2);
        courses.getChildren().add(courseLbl);
        
        // Otsikko valituille kursseille
        var title3Lbl = new Label("Valitut kurssit:");
        title3Lbl.setFont(new Font(18));
        VBox chosenLine = new VBox(10);
        grid.add(chosenLine, 3, 2);
        chosenLine.getChildren().add(title3Lbl);
        
        //Luodaan toiminnalisuus moduulilistaa. Listan elementtia klikkaamalla
        //avautuu kayttajalle lista moduulin alaisista kursseista, joista
        //kayttaja voi valita haluamansa kurssit.
        list.setOnMouseClicked(new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent arg0) {
                String item = list.getSelectionModel().getSelectedItem();
                
                if (!item.equals("")) {
                    courses.getChildren().clear();
                    courses.getChildren().add(courseLbl);
                    
                    Label studies = new Label(item);
                    studies.setMinWidth(200);
                    
                    ArrayList<String> info = modCour.get(item);
                    System.out.print(info);
                    
                    if (info != null) {
                        
                        for (String s : info) {
                            CheckBox checkBox1 = new CheckBox(s);
                            checkBox1.setPadding(new Insets(0, 0, 10, 0));
                            
                            if (student.getCourses().contains(s)) {
                                checkBox1.setSelected(true);
                            }
                            
                            courses.getChildren().add(checkBox1);
                            boxes.add(checkBox1);
                        }
                        Button valinnatBtn = new Button("Tallenna valinnat");
                        courses.getChildren().add(valinnatBtn);
                        //Toiminnallisuus, joka avautuu kun kayttaja on
                        //valinnut itselleen joitakin kursseja. Nappia
                        //painamalla kayttajan valitsemat kurssit tallennetaan
                        //jatkokasittelya varten.
                        valinnatBtn.setOnAction(new 
                            EventHandler<javafx.event.ActionEvent> () {
                            @Override
                            public void handle(javafx.event.ActionEvent t){
                                checkedBoxesNames();
                                
                                chosenLine.getChildren().clear();
                                chosenLine.getChildren().add(title3Lbl);
                                
                                for (String name : student.getCourses()) {
                                    
                                    Label courseLbl = new Label(name);
                                    chosenLine.getChildren().add(courseLbl);
                                }
                                

                                if (!student.getCourses().isEmpty()) {}
                                if (student.getCourses().size() != 0) {
                                    Button saveAll = new Button("Tallenna");
                                    chosenLine.getChildren().add(saveAll);
                                    //Toiminnallisuus, joka avautuu kun kayttaja
                                    //on vahvistanut jonkin kurssi valinnan.
                                    //Nappia painamalla tallennetaan opiskelijan
                                    //luoma opintosuunnitelman json-tiedostoon.
                                    saveAll.setOnAction(new 
                                        EventHandler<javafx.event.ActionEvent> (){
                                        @Override
                                        public void handle(
                                                javafx.event.ActionEvent t){
                                            try {
                                                writeToJson();
                                                finalScene(stage);
                                            } catch (IOException ex) {
                                            }
                                            
                                        }
                                    });
                                }
                                
                                double amount = Double.valueOf(student.
                                        getCourses().size());
                                double max = 15.0;
                                
                                double answer = amount/max;
                                System.out.println(answer);
                                
                                
                                pIndicator.setProgress(answer);
                            
                        }
                        });
                        
                        
                    } else {
                        Label infoLbl = new Label("Ei näytettäviä kursseja");
                        courses.getChildren().add(infoLbl);
                    }
                }
            }

        });  

        root.getChildren().add(grid);
        stage.setScene(scene);
    }
    /**
     * Funktio kirjoittaa opintosuunnitelman json-tiedostoon. Funktiossa luodaan
     * uusi json-tiedosto johon tallennetaan opiskelijan nimi ja
     * opiskelijanumero seka lista opiskelijan valitsemista kursseista.
     * @throws IOException 
     */ 
    public void writeToJson() throws IOException{
        Gson gson = new GsonBuilder().setPrettyPrinting().create();
        Writer writer = new FileWriter("Opintosuunnitelma.json");
        gson.toJson(student, writer);
        writer.close();     

    }
    /**
     * Funktio kay lapi opiskelijan valitsemat kurssit ja tarkistaa nakyyko
     * kayttoliittymassa kurssin valinta oikein.
     */
    public void checkedBoxesNames() {
        
        for (CheckBox b : boxes) {
            if (b.isSelected()) {
                student.addCourses(b.getText());
                
                //Vanha versio
                //checkedCourses.add(b.getText());
            } else {
                student.removeCourses(b.getText());
            }
        }
    }
    /**
     * Funktio lukee json-tiedostot, jotka sisaltavat eri moduulien tiedot.
     * Funktiossa silmukoidaan kaikki moduulitiedostot lapi ja niista otetaan
     * talteen moduulin nimi ja kaikki moduulin alaiset kurssit. Nama tiedot
     * saadaan openCompositeRule, openModuleRule ja openCourseRule funktioiden
     * avulla ja lisataan sanakirjaan moduleInfos.
     * @throws FileNotFoundException 
     */
    public void readModuleJsonData() throws FileNotFoundException{
       
        //luetaan moduletiedostot, silmukan avulla
        for (int i = 1; i < 10; ++i){
            String moduleFile = String.format("module%d.json", i);
            //kasitellaan tiedostot
            JsonElement jsonFile = JsonParser.parseReader(new FileReader(
                    new File(moduleFile)));
            JsonObject fileObject = jsonFile.getAsJsonObject();
            //etsitaan tiedostoista oikea kohta ja tallennetaan se
            JsonObject name = fileObject.get("name").getAsJsonObject();
            String moduleName = name.get("fi").getAsString();
            moduleInfos.put(moduleName, new ArrayList<>());
            
            //lisataan modulen nimi viela items listaan ainakin valiaikaisesti
            items.add(moduleName);
            //alustetaan jsonarray
            JsonArray rules = new JsonArray();
            //ensimmainen rule taso oli kaikissa module tiedostoissa
            JsonObject rule = fileObject.get("rule").getAsJsonObject();
            try{
                //joissakin tiedostoissa heti taman alla oli rules array
                rules = rule.get("rules").getAsJsonArray();
            }
            //jos rulen alla ei ollut suoraan rules arrayta
            //haettiin seuraava rule, jonka alta array loytyi
            catch(NullPointerException e){
                JsonObject rule2 = rule.get("rule").getAsJsonObject();
                rules = rule2.get("rules").getAsJsonArray();
            } //kun array oli loydetty tutkitaan typen perusteella ollaanko 
            //tarpeeksi
            //pitkalla rakenteessa
            finally {    
            for (JsonElement e : rules){
                String type = e.getAsJsonObject().get("type").getAsString();
                if (type.equals("CompositeRule")){
                    openCompositeRule(e, moduleName);                    
                }
                else if (type.equals("ModuleRule")){
                    openModuleRule(e, moduleName);
                }
                else if (type.equals("CourseUnitRule")){
                    openCourseUnitRule(e, moduleName);
                }
                //AnyCourseUnitRule ja CreditsRule
                else{
                }
            }
        }
            
        
    }
    }
    /**
     * Funktio lukee kaikki json-tiedostot, jotka sisaltavat tietoa kursseista.
     * Funktio silmuikoi kaikki kurssitiedostot lapi ja ottaa niista talteen
     * kurssin nimen ja id:n. Kurssin tiedot tallennetaan courseInfos
     * sanakirjaan.
     * @throws FileNotFoundException 
     */    
    public void readCourseJson() throws FileNotFoundException{        
        //luetaan kurssi tiedostot
        for (int j = 1; j < 16; ++j){
            String courseFile = String.format("course%d.json", j);
            JsonObject jsonFile2 = JsonParser.parseReader(new FileReader(
                    new File(courseFile))).getAsJsonObject();
            JsonObject name2 = jsonFile2.getAsJsonObject(
                    "name").getAsJsonObject();
            String courseName = name2.get("fi").getAsString();
            String id = jsonFile2.get("groupId").getAsString();
            courseInfos.put(courseName, id);            
        }
    }
    /**
     * Funkio avaa yhta kurssia kuvaavan jsonelementin ja ottaa elementista
     * talteen kurssin nimen. Kurssin id lisataan oikean moduulin
     * peraan moduleInfos sanakirjaan.
     * @param e Avattavaa jsonelementti
     * @param moduleName Tutkittavan moduulin nimi.
     */
    public void openModuleRule(JsonElement e, String moduleName){
        String moduleId = e.getAsJsonObject().get("moduleGroupId")
                            .getAsString();
        moduleInfos.get(moduleName).add(moduleId);
    }
    /**
     * Funktio avaa jsonelemntin, jonka alla on lista yksittaisia kursseja
     * kuvaavista jsonelementeista. Tarpeen mukaan funktio kutsuu joko
     * openModuleRule -funktiota, openCOurseRule-funktiota tai itseaan 
     * uudelleen. 
     * @param e Avattava jsonelementti
     * @param moduleName Tutkittavan moduulin nimi
     */
    public void openCompositeRule(JsonElement e, String moduleName){
        JsonArray rules = e.getAsJsonObject().get("rules").getAsJsonArray();
        for (JsonElement e2 : rules){
            String type = e2.getAsJsonObject().get("type").getAsString();
            if (type.equals("ModuleRule")){
                openModuleRule(e2, moduleName);
            }
            else if (type.equals("CourseUnitRule")){
                openCourseUnitRule(e2, moduleName);
            }
            else if (type.equals("CompositeRule")){
                openCompositeRule(e2, moduleName);
            }
            else{
            }
        }
    }
    /**
     * Avaa yhta kurssia kuvaavan jsonelementin. Elementista etsitaan kurssin
     * id ja se lisataan moduleInfos sanakirjaan, oikena moduulin alle.
     * @param e Avattava jsonelementti
     * @param moduleName Tutkittavan moduulin nimi
     */
    public void openCourseUnitRule(JsonElement e, String moduleName){
        String courseId = e.getAsJsonObject().get(
                            "courseUnitGroupId").getAsString();
        moduleInfos.get(moduleName).add(courseId);
    }
    /**
     * Funktio kay lapi kaikki kurssit ja vertaa niiden id:ta moduleInfos 
     * sanakirjassa oleviin kurssien id:ihin ja yhdistaa nain kurssit oikeisiin
     * moduleihin.
     */
    public void connectCourses(){
        for(var c : courseInfos.keySet()){
            String id = courseInfos.get(c);
            for (var m : moduleInfos.keySet()){
                if (moduleInfos.get(m).contains(id)){
                    addToList(m, c);
                }
            }
        }
    }
    /**
     * Funktio lisaa moduulin nimen ja kurssin nimen apusanakirjaan modCour.
     * @param module Moduulin nimi
     * @param course Kurssin nimi
     */
    public void addToList(String module, String course){
        if (modCour.keySet().contains(module)){
            modCour.get(module).add(course);
        }
        else {
            modCour.put(module, new ArrayList<>());
            modCour.get(module).add(course);
        }
    }
    /**
     * Käynnistää ohjelman
     * @param args 
     */
    public static void main(String[] args) {
        launch();
    }

}