/* Ristinolla
 *
 * Kuvaus:
 *   Ohjelma toteuttaa ristinollapelin, jossa pelialuetta pystyy
 * laajentamaan. Alussa peliruudukko on kooltaan 3 x 3. Peliruudukossa
 * on kolmenlaisia merkkejä: risti (X), nolla (0) ja tyhjä (.).
 *   Pelivuorossa ovat vuorotellen risti ja nolla, risti aloittaa.
 * Joka kierroksella vuorossa olevalle merkille kysytään koordinaatteja
 * eli kahta lukua. Vuorossa oleva merkki sijoitetaan peliruudukolla
 * annettuihin koordinaatteihin, ja vuoro siirtyy toiselle merkille.
 *   Pelin voittaa merkki, jolla saadaan ensimmäiseksi täytettyä peliruudukon
 * kokonainen rivi, kokonainen sarake tai kokonainen diagonaali.
 * Peli voi päättyä myös sellaiseen tilanteeseen, että peliruudukko on
 * täynnä merkkejä, mutta kumpikaan merkki ei voittanut.
 *   Ohjelma tarkistaa annetut koordinaatit. Koordinaattien pitää olla
 * peliruudukon sisällä, tai koordinaatit saavat ylittyä tai alittua
 * korkeintaan yhdellä. Jos annettu x- tai y-koordinaatti (rivi tai sarake)
 * ylittyy yhdellä, peliruudukko laajenee oikealle ja alaspäin. Jos taas
 * x- tai y-koordinaatti alittuu yhdelle, peliruudukko laajenee vasemmalle
 * ja alaspäin. Peliruudukko siis pysyy aina neliön muotoisena.
 *   Pelin päättyessä kerrotaan, kumpi voitti, vai voittiko kumpikaan.
 *
 * Ohjelman kirjoittaja
 * Nimi:Vilma Lehto
 * Opiskelijanumero: 050044139
 * Käyttäjätunnus: ttvile
 * E-Mail: vilma.lehto@tuni.fi
 *
 * Huomioita ohjelmasta ja sen toteutuksesta:
 *
 * */


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>



using namespace std;

std::vector <std::vector<char>> initBoard() {
    /*Funktio alustaa ja palauttaa pelilaudan
     */

    //alustetaan lauta
    std::vector<std::vector <char>> board;
   for (int j = 0; j < 3; j++) {
       //luodaan rivit
       std::vector < char> new_row;
       for (int i = 0; i < 3; i++) {
           char new_char = '.';
           new_row.push_back(new_char);
       }

       //lisätään rivit lautaan
       board.push_back(new_row);
   }
   return board;
}

void print_board(std::vector <std::vector<char>> board) {
    /* Funktio ottaa parametrina pelilaudan. Se käydään läpi rivi
     * kerrallaan tulostetaan. Funktiolla ei ole paluuarvoa
     */

    //selvitetään vektorien pituus
    std::vector < std::vector <char>>::size_type pituus = 0;
    pituus = board.at(0).size();

    //tulostetaan numerot x-akselille
    std::cout << "  ";
    for ( std::vector < std::vector <char>>::size_type x = 1; x <= pituus; ++x ){
        std::cout << x % 10 << " ";
    }

    std::cout << std::endl;

    int rivi = 1;

    //tulostetaan muut rivit
    //riville tulostetaan ensin y:n numero ja sitten rivin merkit
    for (std::vector <char> row : board) {
        std::cout << rivi << " ";
        rivi += 1;

       for (char character : row) {
           std::cout << character << " ";
        }
         std::cout<<std::endl;
    }

}

void expand_board_right(std::vector <std::vector<char>> &board){
    /*Funktio ottaa parametrina pelilaudan. Jokaiseen laudan riviin
     * lisätään yksi tyhjä merkki ja lopuksi lautaan lisätään
     * yksi tyhjä rivi. Funktiolla ei ole paluuarvoa.
     */


    //selvitetään olemassa olevien vektorien pituus
    std::vector < std::vector <char>>::size_type pituus = 0;
    pituus = board.at(0).size();

    //lisätään jokaiseen vektoriin merkki
    for (unsigned long int i = 0; i < pituus; i++) {
        char new_char = '.';
        board.at(i).push_back(new_char);
    }

    //luodaan uusi vektori
    std::vector <char> new_row(pituus+1, '.');

    //lisätään uusi rivi lautaan
    board.push_back(new_row);


    }

void expand_board_left(std::vector <std::vector<char>> &board) {
    /*Funktio ottaa parametrina pelilaudan. Sitten luodaan uusi
     * isompi pelilauta, jonka jälkeen vanha pelilauta
     * käydään läpi ja merkit kopioidaan uuteen pelilautaa.
     * Lopuksi uusi pelilauta merkitään vanhaksi pelilaudaksi.
     * Funktiolla ei ole paluuarvoa.
     */
    //selvitetään olemassa olevan laudan koko
    std::vector < std::vector <char>>::size_type pituus = 0;
    pituus = board.at(0).size();

    //alustetaan tyhjä lauta
    std::vector<std::vector <char>> empty_board;
   for (unsigned long int j = 0; j < pituus+1; j++) {
       //luodaan rivit
       std::vector < char> new_row;
       for (unsigned long int i = 0; i < pituus+1; i++) {
           char new_char = '.';
           new_row.push_back(new_char);
       }

       //lisätään rivit lautaan
       empty_board.push_back(new_row);
}


       //käydään vanhan laudan ruudut läpi ja kopioidaan ne
       //uuteen tyhjään lautaan
   for (unsigned long int i = 0; i < pituus ; i++) {
       for (unsigned long int j =0; j < pituus; j++){
           empty_board.at(j+1).at(i+1) = board.at(j).at(i);

           }
       }


   board=empty_board;
       }

bool is_the_square_empty(std::vector <std::vector<char>> board, int x, int y){
    /* Funktio ottaa parametrinaan pelilaudan ja koordinaatit int muodossa.
     * Funktio tarkistaa onko kyseisillä koordinaateilla oleva ruutu vielä vapaa
     * ja palauttaa true jos se on ja false jos laudassa on siinä kohdassa
     * jo jokin merkki.
     */

    if (board.at(y-1).at(x-1) == '.'){
        return true;
     }
    else {
        return false;
    }
}

bool is_number(std::string x) {
    /* Funktio ottaa parametrinaan string muotoisen syötteen.
     * Käy kaikki sen alkiot läpi isdigit komennolla ja palauttaa
     * true, jos kaikki merkit olivat numeroita ja false
     * jos seassa oli jotain muuta.
     */

    for (char character : x) {
        if (std::isdigit(character) == 0) {
            return false;
        }
    }
    return true;
}

std::vector<std::string> read_command(std::vector <std::vector<char>> &board, char in_turn) {
    /*Funktio ottaa parametrinaan laudan ja merkin joka kertoo kumpi X vai 0 on vuorossa.
     * Funktio antaa paluuarvona vektorin, joka sisältää hyväksytyn syötteen.
     * Aluksi kysytään käyttäjältä koordinaatit ja sitten niitä aletaan tarkistamaan.
     * Hyväksytty syöte on numero tai pelkkä q. Numeron myös pitää olla
     * pelilaudalla tai tarpeeksi lähellä sitä. Annetut koordinaatit eivät
     * myöskään saa olla jo varatut.
     */

    //alustetaan palautus vektori
    std::vector<std::string> return_vector;

    //selvitetään vektorien pituus
    std::vector < std::vector <char>>::size_type pituus = 0;
    pituus = board.at(0).size();

    //silmukkaa toistetaan, kunnes saadaan kelvollinen syöte
    std::string input = "";

    while(true) {
        //kysytään koordinaatit ja talleteaan ne erikseen
        std::string x_s = "";
         std::string y_s = "";
        std::cout << "For " <<in_turn<< ", enter coordinates: x y> ";
        std::cin >> x_s;

        //tarkistetaan onko se q
        if (x_s == "q") {
            std::cout << "Why on earth you are giving up the game?" << std::endl;
            return_vector.push_back(x_s);
            return return_vector;
            break;
            }


        std::cin >> y_s;
        //tarkistetaan ovatko koordinaatit lukuja
        if (is_number(x_s) == false) {
            std::cout<< "Coordinate outside the board" << std::endl;

        }



        else if (is_number(y_s) == false) {
            std::cout<< "Coordinate outside the board" << std::endl;
        }

        else{
        int x_int = 0;
        int y_int = 0;
        x_int= stoi(x_s);
        y_int= stoi(y_s);

        //tarkistetaan onko koordinaatit negatiivisia
        if (x_int < 0 or y_int < 0) {
             std::cout << "Coordinate outside the board" << std::endl;
        }

        else {

        //muutetaan koordinaattien muotoa
        unsigned long int x = x_int;
        unsigned long int y = y_int;

        //tarkistetaan ovatko koordinaatiti laudalla tai tarpeeksi lähellä sitä
        if ( x > (pituus+1) or y > (pituus +1)){
            std::cout << "Coordinate outside the board" << std::endl;

        }
        else if (x == 0 and y == (pituus + 1)) {
            std::cout << "Coordinate outside the board" << std::endl;
        }

        else if (y == 0 and x == (pituus +1) ) {
            std::cout << "Coordinate outside the board" <<std::endl;
        }


        //jos jompi kumpi koordinaateista on laudan ulkopuolella
        //lautaa laajennetaan ja palautetaan koordinaatit
        else if (y == pituus+1 or x ==pituus+1) {

                return_vector.push_back(x_s);
                return_vector.push_back(y_s);
                return return_vector;
                break;
        }
        else if (y == 0 or x == 0) {
            return_vector.push_back(x_s);
            return_vector.push_back(y_s);
            return return_vector;
            break;
        }

        else {
        //tarkistetaan ovatko koordinaatit jo varattu
        if(is_the_square_empty(board, x, y) == false){
            std::cout << "The given place is already occupied" << std::endl;
        }

        //jos ei kaadu mihkään näistä koordinaatit on oikeat ja ne voidaan palauttaa
         else{

            return_vector.push_back(x_s);
            return_vector.push_back(y_s);
            return return_vector;
            break;
          }
        }
        }

        }
        }
    }

void change_mark(std::vector <std::vector<char>> &board, char char_in_turn, int x, int y) {
    /* Funktio ottaa parametrina pelilaudan, koordinaatit ja tiedon kumpi X vai 0 on vuorossa.
     * Sitten funktio muuttaa kyseisissä koordinaateissa sijaitsevan
     * merkin oikeaksi merkiksi X tai 0.
     */

    board.at(y-1).at(x-1) = char_in_turn;

}

bool board_is_full(std::vector <std::vector<char>> board) {
    /* Funtkio ottaa parametrina pelilaudan ja käy sen läpi ruutu kerrallaan.
     * Jos löytyy ruutu, jossa on vielä merkkinä . palauttaa funktio false,
     * mutta jos kaikki ruudut on jo varattu palauttaa se true.
     */

    //selvitetään olemassa olevan laudan koko
    std::vector < std::vector <char>>::size_type pituus = 0;
    pituus = board.at(0).size();

    //käydään kaikki ruudut läpi ja katsotaan onko ne tyhjiä
    for (unsigned long int i = 0; i < pituus ; i++) {
        for (unsigned long int j =0; j < pituus; j++){
            if (board.at(j).at(i) == '.') {

                return false;
            }

            }
        }
    std::cout <<"No empty places" << std::endl;
    std::cout << "Game over!" << std::endl;
    return true;
}

bool is_all_same(std::vector < char> vector, char char_in_turn) {
    /*Funktio ottaa parametrina vektorin ja vuorossa olevan merkin.
     * Sitten se tarkistaa onko vektorissa kaikki merkit kyseistä vuorossa
     * olevaa merkkiä vai ei. Jos on palauttaa se true jos ei
     * palauttaa se false.
     */
    if (char_in_turn == 'X') {
        if (std::find(vector.begin(), vector.end(), '0') == vector.end()
                and std::find(vector.begin(), vector.end(), '.') == vector.end() ){
         return true;
        }
    }

    //ja jos vuorossa on 0
    else if (char_in_turn == '0') {
        if (std::find(vector.begin(), vector.end(), 'X') == vector.end()
                and std::find(vector.begin(), vector.end(), '.') == vector.end() ){
         return true;
        }
    }
    return false;
}

bool has_won(std::vector <std::vector<char>> board, char char_in_turn){
    /* Funktio ottaa parametrina pelilaudan ja vuorossa olevan merkin.
     * Sitten se tarkistaa ensin rivi kerrallaan, onko voittoja jo löytynyt
     * Sitten se muodostaa diagonaaliset vektroit ja tarksitaa onko niillä voittajaa.
     * Lopuksi se muodostaa pystyriveistä vektorit ja tarkistaa
     * onko niillä voittajaa. Jos voittaja löytyy palauttaa funktio true
     * ja muuten se palauttaa false
     */

    //selvitetään laudan koko
    std::vector < std::vector <char>>::size_type pituus = 0;
    pituus = board.at(0).size();

    //kumpi voittaja olis
    std::string winner;
    if (char_in_turn == 'X') {
        winner = "Cross";
    }
    if (char_in_turn == '0') {
        winner = "Nought";
    }


    //tarksitetaan voitto vaakasuunnassa
    for (unsigned long int a = 0; a < pituus; a++) {

        if (is_all_same(board[a], char_in_turn) == true) {
            std::cout << winner << " won horizontally" << std::endl;
            std::cout << "Game over!" << std::endl;
            return true;
        }
    }


    //tarksitetaan voitto diagonaalisesti vasemmasta yläkulmasta oikeaan alakulmaan
    //ensin muodostetaan vektori diagonaalisista merkeistä
    std::vector<char> left_diagonal;
    for (unsigned long int i = 0; i < pituus; ++i)  {
        left_diagonal.push_back(board.at(i).at(i));
     }

    //kutsutaan is_all_same funktiota ja katsotaan ovatko kaikki merkit diagonaalisesti samoja
    if (is_all_same(left_diagonal, char_in_turn) == true) {
        std::cout << winner << " won diagonally" << std::endl;
        std::cout << "Game over!" << std::endl;
        return true;
    }


    //tarkistetaan voitto diagonaalisesti oikeasta yläkulmasta vasempaan alakulmaan
    //muodostetaan vektori
    std::vector<char> right_diagonal;

    for (unsigned long int j = 0, i = pituus -1; j < pituus; j++) {
        right_diagonal.push_back(board.at(j).at(i));
        i = i-1;
    }

    //ja kutsutaan is_all_same funktiota
    if (is_all_same(right_diagonal, char_in_turn)== true) {
        std::cout << winner << " won diagonally" << std::endl;
        std::cout << "Game over!" << std::endl;
        return true;
    }

    //tarkistetaan voitto pystysuunnassa
    for (unsigned long int i = 0; i < pituus ; i++) {
        std::vector <char> column;

        for (unsigned long int j =0; j < pituus; j++){

            //muodostetaan pystysuuntaiset vektorit
            column.push_back(board.at(j).at(i));

            //jos vektorissa on kaikki pystyrivin merkit
            //kutsutaan is_all_funktiota ja tarkistetaan onko kaikki merkit samoja
            if (column.size() == pituus) {
                if ( is_all_same(column, char_in_turn) == true) {
                    std::cout << winner << " won vertically" << std::endl;
                    std::cout << "Game over!" << std::endl;
                    return true;
                } else {
                    column.clear();
                }
            }
        }
        }



    return false;

}

int main()
{
    //aloitetaan peli ja tulostetaan lauta
    std::cout << "Start game:" << std::endl;

    std::vector < std::vector <char>> board = initBoard();
    print_board(board);
    std::cout<< std::endl;

    int turn = 1;
    char char_in_turn = 'X';

    while (true) {

    //määritetään kumman vuoro on
    if (turn%2 != 0) {
        char_in_turn = 'X';
    }
    else if (turn%2 ==0) {
     char_in_turn = '0';
    }

    //selvitetään laudan nykyinen koko
    std::vector < std::vector <char>>::size_type pituus = 0;
    pituus = board.at(0).size();


    //kutsutaan read_command funktiota, jotta saadaa käyttäjältä koordinaatit
    std::vector<std::string> coordinates = read_command(board, char_in_turn);


    //lopetaan ohjelma, jos palautettiin q
    if(coordinates.at(0) == "q") {
        return EXIT_SUCCESS;
    }

    //nyt kun tiedetään, että koordinaatit ovat numeroita
    //vaihdetaan ne int muotoon
    unsigned long int x = stoi(coordinates.at(0));
    unsigned long int y = stoi(coordinates.at(1));

    //jos jompi kumpi koordinaateista on laudan ulkopuolella
    //laajennetaan lautaa
    if (x == pituus +1 or y == pituus +1) {
        expand_board_right(board);
    }


    //jos jompi kumpi koordinaateista on nolla
    //laajennetaan lautaa eri suuntaan
    if (x == 0 or y == 0) {
        expand_board_left(board);
        x += 1;
        y += 1;
    }


    //muutetaan merkki
    change_mark(board, char_in_turn, x, y);


    //tulostetaan lauta
    print_board(board);
    std::cout<<std::endl;


    //tarkistetaan voittotilanne
    if (has_won(board, char_in_turn) == true) {
        return EXIT_SUCCESS;
    }

    //tarkistetaan onko lauta täynnä
    if (board_is_full(board) == true) {
      return EXIT_SUCCESS;
    }


   turn += 1;
   }


    return EXIT_SUCCESS;
}
