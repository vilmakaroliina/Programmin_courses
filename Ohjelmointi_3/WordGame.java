/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Other/File.java to edit this template
 */

/**
 *
 * @author Vilma
 */
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public class WordGame {

    public static class WordGameState{
        private String word;
        private int mistakes;
        private int max_mistakes;
        private int unknown_letters;
        private int word_index;
        private ArrayList<Character> guessed_chars = new ArrayList<>();
        
        //rakennin
        private WordGameState(String word, int max_mistakes, int word_index){
            this.word=String.format("_".repeat(word.length()));
            this.max_mistakes = max_mistakes;
            this.word_index = word_index;
            this.mistakes = 0;
            this.unknown_letters = word.length();
        }
        
        
        public String getWord(){
            return this.word;
        }
        
        public int getMistakes(){
            return this.mistakes;
        }
        
        public int getMistakeLimit(){
            return this.max_mistakes;
        }
        
        public int getMissingChars(){
            return this.unknown_letters;
        }
        
        
    }
    
    private ArrayList<String> words = new ArrayList<>();
    private ArrayList<WordGameState> games = new ArrayList<> ();
    private boolean is_game_on;
    
    //rakennin, tallentaa tiedostossa olevat sanat listaa
    WordGame (String filename) throws FileNotFoundException, IOException{
        try(BufferedReader input = new BufferedReader(new FileReader(filename)))
        {
            String line;
            while ((line = input.readLine()) != null)
            {
                this.words.add(line);
            }         
        }
    }
    
    public void initGame(int wordIndex, int mistakeLimit){
        String word = words.get(wordIndex%words.size());
        int true_index = wordIndex%words.size();
        WordGameState state = new WordGameState(word, mistakeLimit, true_index);
        games.add(state);
        this. is_game_on = true;       
        
    }
    
    public  boolean isGameActive(){
        return this.is_game_on;
    }
    
    //palauttaa nykyisen pelin tilaa kuvaavan olion
    public WordGameState getGameState()
        throws GameStateException{
        if (this.is_game_on == false){
            throw new GameStateException("There is currently no active word game!");
        }
        else{
            return this.games.get(games.size()-1);
        }        
    }
    
    public WordGameState guess(char c)
        throws GameStateException{
        if (this.is_game_on == false){
            throw new GameStateException("There is currently no active word game!");
        }
        else
        {
            char c2 = Character.toLowerCase(c);
            WordGameState state = games.get(games.size()-1);
            if (!words.get(state.word_index).contains(Character.toString(c2))){
                state.mistakes += 1;
                if (state.mistakes > state.max_mistakes){
                    state.word = words.get(state.word_index);
                    this.is_game_on = false;
                }
            }
            else if (state.guessed_chars.contains(c2)){
                state.mistakes += 1;
                if (state.mistakes > state.max_mistakes){
                    state.word = words.get(state.word_index);
                    this.is_game_on = false;
                }
            }
            else
            {
                for (int i = 0; i< words.get(state.word_index).length(); ++i){
                    if (words.get(state.word_index).charAt(i) == c2){
                        String old_word = state.getWord();
                        String new_word = String.format("%s%c%s", 
                        old_word.substring(0, i), c2, 
                        old_word.substring(i+1, old_word.length()));
                        state.word = new_word;
                        state.unknown_letters -= 1;
                    } 
                }
                state.guessed_chars.add(c2);
                if (state.unknown_letters == 0){
                    this.is_game_on = false;
                }
                
            }
            return state;
        }
    }
    
    public WordGameState guess(String word)
        throws GameStateException{
        if (this.is_game_on == false){
            throw new GameStateException("There is currently no active word game!");
        }
        else{
            WordGameState state = this.games.get(games.size()-1);
            if (word.equals(words.get(state.word_index))){
                state.unknown_letters = 0;
                state.word = words.get(state.word_index);
                this.is_game_on = false;
            }
            else{
                state.mistakes += 1;
                if (state.mistakes > state.max_mistakes){
                    state.word = words.get(state.word_index);
                    this.is_game_on = false;
                }
            }
            return state;
        }
        
    }
}
