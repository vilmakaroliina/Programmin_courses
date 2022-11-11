/* Kurssikeskus
 *
 * Kuvaus:
 *   Ohjelma toteuttaa kurssikeskuksen, annetun tiedoston perusteella.
 *   Ensin tiedosto tarkistetaan, jonka jälkeen sen tiedot tallennetaan
 *   mappiin kurssin teeman mukaan. Keskuksesta on mahdollista hakea tietoa
 *   järjestettävistä kursseista. Kursseja voi myös perua kurssikeskuksen
 *   kautta.
 *
 *   Kaikki kurssien teemat on mahdollista tulostaa. Tulostaa voidaan
 *   myös tietyn paikkakunnan tai teeman kurssit sekä kaikki
 *   kurssit joilla on vielä tilaa osallistujille. Kaikki tulostukset
 *   tulevat aakkosjärjestyksessä.
 *
 *   Ohjelma kysyy käyttäjältä niin kauean eri komentoja, kunnes
 *   tämä syöttää ohjelmalle käskyn quit.
 *
 * Ohjelman kirjoittaja
 * Nimi:Vilma Lehto
 * Opiskelijanumero: 050044139
 * Käyttäjätunnus: ttvile
 * E-Mail: vilma.lehto@tuni.fi
 *
 *
 * */


//--------------------------------------------------
//  COMP.CS.110 Ohjelmointi 2: Rakenteet -pohjakoodi
//  Copyright © 2021
//--------------------------------------------------

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <utility>
#include <set>


int COURSE_FULL = 50;

struct Course {
    std::string kurssin_nimi;
    std::string paikkakunta;
    int osallistujien_maara;
};

// Jakaa annetun merkkijonon str annetun merkin delimiter erottelemiin osiin
// ja palauttaa osat vektorissa.
// Jos erotinmerkki on lainausmerkkien sisällä, erotinmerkistä ei välitetä,
// eli osaa olla erottelematta lainausmerkkien sisällä olevan tekstin.
//
// Splits the given string str into parts separated by the given delimiter
// and returns the parts in a vector.
// If the delimiter appears inside quatation, ignores delimiter,
// i.e. does not split quoted text.

std::vector<std::string> split_ignoring_quoted_delim(const std::string& str,
                                                     char delimiter)
{
    std::vector<std::string> result = {""};
    bool inside_quotation = false;
    for(char current_char : str)
    {
        if(current_char == '"')
        {
            inside_quotation = not inside_quotation;
        }
        else if(current_char == delimiter and not inside_quotation)
        {
            result.push_back("");
        }
        else
        {
            result.back().push_back(current_char);
        }
    }
    if(result.back() == "")
    {
        result.erase(--result.end());
    }
    return result;
}


/* Funktio ottaa parametrinaan avattavan tiedoston nimen ja
 * vektorin johon tiedoston rivit palautetaan. Funktio
 * avaa tiedoston ja tallentaa sen sisällön. Paluuarvona
 * funktio antaa tottusarvon sen perusteella onnistuiko
 * tiedoston avaaminen vai ei.
 */
bool open_file (std::string tiedoston_nimi, std::vector <std::string>& tiedoston_rivit) {

    std::ifstream tiedosto(tiedoston_nimi);
    if (not tiedosto) {
        return false;
    }
    else {
        std::string rivi;
       while( getline(tiedosto, rivi)) {
           tiedoston_rivit.push_back(rivi);
       }
    }
    return true;
}



/*Funktio saa parametrina vektorin, joka sisältää kaikki
 * tiedoston rivin osat. Funkti otarkistaa osien määrän
 * ja niiden perusteella palauttaa totuusarvon.
 */
bool check_field_count (const std::vector <std::string> osat) {


    if (osat.size() != 4) {
        return false;
    }else {
        return true;
    }
}



/* Funktio saa parametrinaan vektorin, joka sisältää
 * kaikki tiedot yhdeltä tiedoston riviltä. Jos jokin
 * vektroin osa on tyhjä palauttaa funktio false,
 * muuten se palauttaa true.
 */
bool check_empty_fields (std::vector <std::string> osat) {


    for (const std::string& osa : osat) {
        if (osa.empty()) {
            return false;
        }
    }
    return true;
}


/* Funktio ottaa parametrina vektorin, joka sisältää kaikki
 * tiedoston rivit sekä mapin, johon tiedot tulee tallentaa.
 * Funktio tarkistaa, että tiedostossa on oikea sisältö
 * ja sen perusteella palauttaa totuusarvon.
 */

bool check_file (std::vector <std::string> tiedoston_rivit,
                 std::map<std::string, std::vector <Course>>& kurssit) {

    //tarkistetaan osien määrä ja että jokaisessa on jotain sisältöä
    for (const std::string& rivi : tiedoston_rivit) {
        std::vector <std::string> osat = split_ignoring_quoted_delim(rivi, ';');
        if (not check_field_count(osat) or not check_empty_fields(osat)) {
            return false;
        }

        //tarkistetaan, että osallistujamäärä on oikena
        int osallistujat = 0;
        if (osat.at(3) == "full" ) {
            osallistujat = COURSE_FULL;
        } else {
            osallistujat = stoi(osat.at(3));
        }

        //luodaan struct rakenne
        Course uusi_kurssi = {osat[1], osat[2], osallistujat};
        kurssit.try_emplace({osat[0], {}});

        //tarkistetaan onko kurssi jo olemassa
        auto it = kurssit[osat[0]].begin();
        for ( ; it != kurssit[osat[0]].end(); ++it) {
            if (it ->kurssin_nimi == uusi_kurssi.kurssin_nimi
                    && it ->paikkakunta == uusi_kurssi.paikkakunta) {
                break;
            }
        }

        //jos kurssi löytyy poistetaan se ensin
        //muuten kurssi vain lisätään settiin
        if (it != kurssit[osat[0]].end()) {
            kurssit[osat[0]].erase(it);}

        kurssit[osat[0]].push_back(uusi_kurssi);

    }
    return true;
}



/* Funktio ottaa parametrinaa mapin joka sisältää kaikki kurssi.
 * Funktio iteroi mapin läpi ja tulostaa jokaisen teeman. FUnktiolla
 * ei ole paluuarvoa.
 */
void print_out_themes (std::map <std::string, std::vector <Course>> kurssit) {

    //tehdään iteraattori, jonka avulla käydään map läpi
    std::map < std::string, std::vector<Course>>::iterator i;
    i = kurssit.begin();

    while (i != kurssit.end()) {
        std::cout << i->first << std::endl;
        ++i;
    }
    }


/*Funktio ottaa parametrinaan mapin, joka sisältää kaikki kurssit
 * sekä teeman string muodossa. Funktio käy mapin läpi
 * ja jos haluttu teema löytyy mapista se palauttaa true
 * ja muuten false
 */
bool check_theme(std::map<std::string, std::vector<Course>> kurssit, std::string teema) {

    //jos teemaa ei ole kurssien joukossa palautetaan false
    if (kurssit.find(teema) == kurssit.end()) {
        return false;
    }
    //muuten palautetaan true
    else {
    return true;
    }
}



/*Funktio ottaa parametrinaan mapin, joka sisältää kaikki kurssit ja
 * halutun paikkakunnan stirng muodossa. Funktio iteroi mapin
 * läpi ja jos löytyy kurssi, joka on halutulla paikkakunnalla
 * se palauttaa true ja muuten false.
 */
bool check_location(std::map <std::string, std::vector < Course >> kurssit,
                    std::string haluttu_paikkakunta) {

        //luodaan vektori johon tallennetaan kurssit oikealta paikkakunnalta
        std::vector <Course> paikkakunnan_kurssit;

        //käydään map iteraatiolla läpi
        std::map < std::string, std::vector<Course>>::iterator it;
        it = kurssit.begin();

        while ( it != kurssit.end()) {
         //silmukoidaan indeksin avulla teemaa vastaavan vektorin läpi
         for (unsigned int i = 0; i < it -> second.size(); i++) {

             //jos löydetään kurssi, jonka paikka kunta on haluttu paikkakunta
             //tallnnetaan se vektoriin
             if (it -> second.at(i).paikkakunta == haluttu_paikkakunta) {
                 paikkakunnan_kurssit.push_back(it -> second.at(i));
             }
         }
         ++it;
        }

        //kun kaikki teemat ja niiden kurssit on käyty läpi
        //tarkistetaan muodostuneen vektorin tilanne
        // jos se on tyhjä, ei kyseistä paikkakuntaa ollut
        //ja palautetaan false

        if(paikkakunnan_kurssit.empty()) {
            return false;
        }
        //muuten palautetaan true
        else{
        return true;
        }

    }



/*Funktio ottaa parametrinaa stirng muodossa halutun paikkakunnan ja teeman
 * sekä mapin joka sisältää kaikki kurssit. Ensin funktio
 * tarkistaa, että annetut paikkakunta ja teema ovat oikein. Sitten
 * se käy koko mapin läpi ja kerää oikeat kurssit settiin.
 * Ja lopuksi se käy setin läpi ja tulostaa kurssit. Funktiolla
 * ei ole paluuarvoa.
 */
void print_courses(std::string haluttu_paikkakunta, std::string haluttu_teema,
                   std::map <std::string, std::vector <Course>> kurssit) {

    //tarkistetaan ensin syötteestä paikkakunta
    if (check_theme(kurssit, haluttu_teema) == false) {
        std::cout << "Error: unknown theme" << std::endl;
    }

    //seuraavaksi syötteestä tarkistetaan teema
    else if (check_location(kurssit, haluttu_paikkakunta) == false) {
        std::cout << "Error: unknown location" << std::endl;
    }


    //jos molemmat ovat oikeellisia aletaan kursseja käydä läpi
    else{
    std::set <std::pair< std::string, int>> halutut_kurssit;
    for ( auto kurssi : kurssit.at(haluttu_teema)) {

        //jos löydetään kurssi joka on halutulla paikkakunnalla
        //muodostetaan sen tiedoista pari ja lisätään settiin
        if (kurssi.paikkakunta == haluttu_paikkakunta) {
            std::pair <std::string, int> kurssin_tiedot = {kurssi.kurssin_nimi, kurssi.osallistujien_maara};
            halutut_kurssit.insert(kurssin_tiedot);
        }
    }

    //viimeinen virhetarkastu, jos halututta paikkakunnalla ei
    //ollut yhtään halutun teeman kurssi
    if (halutut_kurssit.empty()) {
        std::cout << "Error: unknown location" << std::endl;
    }

    else {
    std::set <std::pair<std::string, int>>::iterator it;
    it = halutut_kurssit.begin();

    //lopuksi kurssit tulostetaan
    while (it != halutut_kurssit.end()) {
        std::cout << it->first << " --- ";
        if (it->second == 50) {
            std::cout << "full" << std::endl;
        } else {
            std::cout << it ->second << " enrollments" << std::endl;
    }
        ++it;
    }
    }
    }
}



/*Funktio ottaa parametrinaan mapin kaikista kursseista ja string
 * muodossa halutun paikkakunnan nimen. Funktio tarkistaa
 * paikkakunnan oikeellisuuden ja se käy koko mapin läpi ja vertaa
 * kurssien paikkakuntia haluttuun paikkakuntaan. Jos löytyy kurssi
 * halutulta paikkakunnalta se lisätään vektoriin. Lopuksi tulostetaan
 * vektori. Funktio ei anna paluuarvona mitään.
 */
void courses_in_location (std::map <std::string, std::vector <Course>> kurssit,
                          std::string haluttu_paikkakunta) {

    if (not check_location(kurssit, haluttu_paikkakunta)) {
       std::cout << "Error: unknown location" << std::endl;
    }

    std::vector <std::string> paikkakunnan_kurssit;
    for (auto& tietopari : kurssit) {
        std::vector <Course> kurssien_tiedot = tietopari.second;
        for (auto& kurssi : kurssien_tiedot) {
            if (kurssi.paikkakunta == haluttu_paikkakunta) {
                paikkakunnan_kurssit.push_back(kurssi.kurssin_nimi);
            }
        }
    }

    sort(paikkakunnan_kurssit.begin(), paikkakunnan_kurssit.end());
    for (std::string& kurssin_nimi : paikkakunnan_kurssit) {
        std::cout << kurssin_nimi<<std::endl;
    }
}


/*Funktio ottaa parametrinaan mapin, joka sisältää kaikki kurssit ja
 * halutun teeman string muodossa. Halutun teeman kurssit käydään
 * silmukalla läpi ja niistä tallennetaan tarvittavat tiedot uuteen
 * mappiin. Tämän jälkeen muodostettu map käydään läpi
 * ja kurssit tulostetaan. Funktiolla ei ole paluuarvoa.
 */
void courses_in_theme(std::map <std::string, std::vector <Course>> kurssit,
                      std::string haluttu_teema) {

    if (not check_theme(kurssit, haluttu_teema)) {
        std::cout << "Error: unknown theme" << std::endl;
    }

    std::map < std::string, std::vector <std::string>> halutut_kurssit;
    for (Course& kurssi : kurssit[haluttu_teema]) {
        halutut_kurssit.try_emplace({kurssi.paikkakunta, {}});
        halutut_kurssit[kurssi.paikkakunta].push_back(kurssi.kurssin_nimi);
    }

    for (auto& paikkakunnan_kurssit: halutut_kurssit) {
        for (unsigned i = 0; i < paikkakunnan_kurssit.second.size(); ++i) {
            std::cout << paikkakunnan_kurssit.first << " : ";
            std::cout << paikkakunnan_kurssit.second[i] << std::endl;
        }
    }


}


/*Funktio ottaa paramtrinaan vain mapin, joka sisältää kaikki kurssit. Mappi
 * käydään läpi ja kursseista, jotka eivät ole täynnä luodaan uusi mappi.
 * Tämä uusi mappin sitten käydään sitten automaattisella for silmukalla läpi
 * ja tulostetaan. Funktiolla ei ole paluuarvoa
 */
void available(const std::map <std::string, std::vector <Course>> kurssit) {

    std::map < std::string, std::set <std::string>> saatavat_kurssit;
    for (auto& teema : kurssit) {
        for (const Course& kurssi : teema.second) {
            if (kurssi.osallistujien_maara < 50) {
                std::string kurssin_tiedot = kurssi.paikkakunta + " : "
                + kurssi.kurssin_nimi;
                saatavat_kurssit.try_emplace({teema.first, {}});
                saatavat_kurssit[teema.first].insert(kurssin_tiedot);
            }
        }
    }

    for (auto& teema : saatavat_kurssit) {
        for (const std::string& kurssi : teema.second) {
            std::cout << teema.first << " : " << kurssi << std::endl;
        }
    }
}



/*Funktio ottaa parametrinaan mapin, joka sisältää kaikki kurssit. Mappi
 * käydään silmukalla läpi ja kaikkien teemojen osallistujamäärät lasketaan.
 * Osallistuja määristä muodostetaan vektori josta etsitään isoin luku.
 * Sitten kaikkia osallistujamääriä verrataan suurimpaan osallistujamäärään
 * jotta saadaan selville onko olemassa teemoja, jotka ovat yhtä suosittuja.
 * Lopuksi kaikki suositut teemat tulostetaan. Funktiolla ei ole paluuarvoa.
 */
void favorite_theme(std::map <std::string, std::vector <Course>> kurssit) {

    //käydään map läpi ja lasketaan osaalistujat
    std::map <std::string, unsigned> teemojen_osallistujat;
    for (auto& teema : kurssit) {
        unsigned osallistujat = 0;
        for (Course& kurssi : teema.second) {
            osallistujat += kurssi.osallistujien_maara;
        }
        teemojen_osallistujat.insert({teema.first, osallistujat});
    }

    //muodostetaan vektori osallistujista ja etsitään isoin luku
    std::vector<unsigned> osallistujat;
    for (auto& tietopari : teemojen_osallistujat) {
        osallistujat.push_back(tietopari.second);
    }
    unsigned max_osallistujat = *max_element(osallistujat.begin(), osallistujat.end());


    //vertaillaan löytyykö toista yhtä isoa lukua
    std::map <std::string, unsigned> suosituimmat_teemat;
    for (auto& teema : teemojen_osallistujat) {
        if(teema.second == max_osallistujat) {
            suosituimmat_teemat.insert({teema.first, teema.second});
        }
    }

    //tulostetaan luvut
    std::cout << max_osallistujat << " enrollments in themes" << std::endl;
    for (auto& teema : suosituimmat_teemat) {
        std::cout << "--- " << teema.first << std::endl;
    }
}



/* Funktio saa parametrinaan mapin, joka sisältää kaikki kurssit ja
 * halutun kurssi nimen string muodossa. Funktio käy mapin läpi ja
 * vertaa siinä olevien kurssien nimiä halutun kurssin nimeen ja
 * kerää vektoriin kaikki oikean nimiset kurssit. Lopuksi
 * se tarkistaa muodostuneen vektorin koon ja palauttaa false,
 * jos yhtäkään kurssia ei tallennettu vektoriin ja true
 * jos vektorissa on jokin kurssi.
 */
bool check_name (std::map <std::string, std::vector <Course>>& kurssit,
                 std::string haluttu_kurssi) {

    //luodaan vektori johon tallennetaan kurssit oikealla nimellä
    std::vector <Course> oikeat_kurssit;

    //käydään map iteraatiolla läpi
    std::map < std::string, std::vector<Course>>::iterator it;
    it = kurssit.begin();

    while ( it != kurssit.end()) {
     //silmukoidaan indeksin avulla teemaa vastaavan vektorin läpi
     for (unsigned int i = 0; i < it -> second.size(); i++) {

         //jos löydetään kurssi, jonka paikka kunta on haluttu paikkakunta
         //tallnnetaan se vektoriin
         if (it -> second.at(i).kurssin_nimi == haluttu_kurssi) {
             oikeat_kurssit.push_back(it -> second.at(i));
         }
     }
     ++it;
    }

    //kun kaikki teemat ja niiden kurssit on käyty läpi
    //tarkistetaan muodostuneen vektorin tilanne
    // jos se on tyhjä, ei kyseistä paikkakuntaa ollut
    //ja palautetaan false

    if(oikeat_kurssit.empty()) {
        return false;
    }
    //muuten palautetaan true
    else{
    return true;
    }

}


/* Funktio saa parametrinaan halutun kurssin nimen string muodossa ja
 * mapin, joka sisältää kaikki kurssit. Funktio tarkistaa ensin onko
 * kurssinnimi oikea ja sitten muodostaa uuden mapin kaikista muista
 * paitsi poistettavista kursseista. Lopuksi tämä uusi mappi
 * asetetaan vanhan kurssit mapin tilalle. Funktiolla
 * ei ole paluuarvoa.
 */
void cancel(std::map <std::string, std::vector <Course>>& kurssit,
            std::string haluttu_kurssi) {

    std::map <std::string, std::vector <Course>> uudet_kurssit;
    for (auto& teema : kurssit) {
        for (auto& kurssi : teema.second) {
            if (kurssi.kurssin_nimi != haluttu_kurssi) {
                uudet_kurssit.try_emplace({teema.first, {}});
                uudet_kurssit[teema.first].push_back(kurssi);
            }
        }
    }

    kurssit = uudet_kurssit;
}

int main() {
    //kysytään kopioitavan tiedoston nimi
     std::string tiedoston_nimi = "";
     std::cout << "Input file: ";
     getline(std::cin, tiedoston_nimi);

     //avataan tiedosto
     std::vector <std::string> tiedoston_rivit;
     if (not open_file(tiedoston_nimi, tiedoston_rivit)) {
      std::cout << "Error: the input file cannot be opened" << std::endl;
      return EXIT_FAILURE;
     }

     //tarkistetaan tiedoston sisältö
     std::map <std::string, std::vector <Course>> kurssit;
     if (not check_file(tiedoston_rivit, kurssit)) {
         std::cout << "Error: empty field" << std::endl;
         return EXIT_FAILURE;
     }

     //nyt kun tiedoston sisältö on tarkistettu, kysytään
     //käyttäjältä toiminnot
     while (true) {
         std::string input = "";
         std::cout <<"> ";
         getline(std::cin, input);
         std::vector <std::string> input_osat;
         input_osat = split_ignoring_quoted_delim(input, ' ');

         //jos käyttäjä lopettaa ohjelman
         if (input_osat[0] == "quit") {
             if (input_osat.size() != 1) {
                 std::cout << "Error: error in command " <<
                              input_osat[0] << std::endl;
             } else {
             return EXIT_SUCCESS;
             }
         }

         else if (input_osat[0] =="themes") {
             if (input_osat.size() != 1) {
                 std::cout << "Error: error in command " <<
                              input_osat[0] << std::endl;
             } else {
                 print_out_themes(kurssit);
             }
         }

         else if (input_osat[0] == "courses") {
             if (input_osat.size() != 3) {
                 std::cout << "Error: error in command " <<
                              input_osat[0] << std::endl;
             } else {
                 print_courses(input_osat[1], input_osat[2], kurssit);
             }
         }

         else if (input_osat[0] == "courses_in_location") {
             if (input_osat.size() != 2) {
                 std::cout << "Error: error in command " <<
                              input_osat[0] << std::endl;
             } else {
                 courses_in_location(kurssit, input_osat[1]);
             }
         }

         else if (input_osat[0] == "courses_in_theme") {
             if (input_osat.size() != 2) {
                 std::cout << "Error: error in command " <<
                              input_osat[0] << std::endl;
             } else {
                 courses_in_theme(kurssit, input_osat[1]);
             }
         }

         else if(input_osat[0] == "available") {
             if (input_osat.size() != 1) {
                 std::cout << "Error: error in command " <<
                              input_osat[0] << std::endl;
             } else {
                 available(kurssit);
             }
         }

         else if (input_osat[0] == "favorite_theme") {
             if ( input_osat.size() != 1) {
                 std::cout << "Error: error in command " <<
                              input_osat[0] << std::endl;
             } else if (kurssit.empty()) {
                 std::cout << "No enrollments" << std::endl;
             } else {
                 favorite_theme(kurssit);
             }
         }

         else if (input_osat[0] == "cancel") {
             if (input_osat.size() != 2) {
                 std::cout << "Error: in command " <<
                              input_osat[0] << std::endl;
             } else if (not check_name(kurssit, input_osat[1])) {
                 std::cout << "Error: unknown course" << std::endl;
             } else {
                 cancel(kurssit, input_osat[1]);
                 std::cout << input_osat[1];
                 std::cout << " cancelled in all locations" << std::endl;
             }
         }


         else {
             std::cout << "Error: Unknown command: " <<
                          input_osat[0] << std::endl;
         }


}

    return EXIT_SUCCESS;

}

