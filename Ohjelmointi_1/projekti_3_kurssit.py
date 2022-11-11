"""COMP.CS.100 ohjelma kertoo yliopiston eri laitoksille järjestettävistä
kursseista ja niiden opintopisteistä.
Ohjelam kysyy käyttäjältä komennon ja toimii tämän mukaa, joko lisäten kursseja,
poistaen kursseja, kertomalla kurssine opintopistemääriä tai tulostamalla
kurssit.
tekijä:Vilma Lehto
opiskelijanumero:050044139"""
def read_file(tiedosto):
    """Funktio avaa käyttäjän valitseman tiedoston ja muodostaa sekä palauttaa
    tiedostosta sanakirjan.
    Sanakirjassa on avaimina eri aineet ja hyötykuormina uude sanakirjat,
    jotka sisältävät tiedon aineen kursseista ja niiden opintopisteitä"""
    try:
        #avataan tiedosto
        tiedot=open(tiedosto, mode="r")
    except OSError:
        print("Error opening file!")
        return False

    oppiaineet={}
    for line in tiedot:
        #poistetaan rivistä enter lopusta ja jaetaan se osiin
        line=line.rstrip()
        osat=line.split(";")
        #0 on aineennimi, 1 on kurssin nimi, 2 on opintopisteet


        try:
            osat[2]
        except IndexError:
            print("Error in file!")
            return False

        kurssit={}
        #muodostetaan sanakirja kurssin nimestä ja sen opintopistemäärästä
        if osat[0] in oppiaineet:
            #jos oppiaine on jo olemassa lisätään siihen vain kurssi
            oppiaineet[osat[0]][osat[1]]=osat[2]

        else:
            #kun oppiainetta ei ole olemassa, pitää ensin luoda sanakirja
            #lisättävästä kurssista ja sitten lisätä oppiaine ja kurssi
            #lopulliseen sanakirjaan
            kurssit[osat[1]]=osat[2]
            oppiaineet[osat[0]]=kurssit
    tiedot.close()
    return oppiaineet


def print_all(kurssit):
    """Funktio ottaa parametrina sanakirjan kurssit ja tulostaa sen.
    Ensin tulostetaan osaston nimi ja sitten kaikki osaston kurssit
    aakkosjärjestyksessä"""
    for word in sorted(kurssit):
        #ensin tulostetaan osaston nimi
        print(f"*{word}*")
        for key in sorted(kurssit[word]):
            #sitten jokainen kurssi ja sitä vastaava opintopistemäärä
            print(f"{key} : {kurssit[word][key]} cr")

def print_department(kurssit, toiminto):
    """Funktio ottaa parametrina sanakirjan kurssit ja käyttäjän anatama
    toimintokäskyn. Sitten funktio tulostaa käyttäjän ilmoittaman
    osaston kurssit aakkosjärjestyksessä."""
    osat=toiminto.split()
    #osat[0] on käysky r ja osat[1] on osaston nimi
    if osat[1] in kurssit:
        print(f"*{osat[1]}*")
        #tulostetaan osaston nimi
        #ja sitten silmukan avulla jokainen osaston kurssi
        #ja vastaava opintopiste määrä
        for kurssi in sorted(kurssit[osat[1]]):
            print(f"{kurssi} : {kurssit[osat[1]][kurssi]} cr")

    else:
        print("Department not found!")

def credits(kurssit, toiminto):
    """Funktio ottaa parametrina kurssit sanakirjan ja käyttäjän anataman
    toimintokäskyn. Sitten funktio laskee montako opintopistettä
    halutulla osastolla on mahdollista saada"""
    osat=toiminto.split()
    #0 on käsky c ja 1 on osaston nimi
    if osat[1] in kurssit:
        opintopisteet=0
        #lasketaan silmukan avulla jokaisen kurssin opintopistemäärät yhteen
        for kurssi in kurssit[osat[1]]:
            opintopisteet_kurssista=int(kurssit[osat[1]][kurssi])
            opintopisteet+=opintopisteet_kurssista

        print(f"Department {osat[1]} has to offer {opintopisteet} cr.")

    else:
        print("Department not found!")

def add(kurssit, toiminto):
    """Funktio ottaa parametrina kurssit sanakirjan ja käyttäjän antaman
    toimintokäskyn. Sitten funktio käskyn perusteella, joko lisää kokonaan
    uuden osaston tai lisää jo olemassa olevaan osastoon uuden kurssin"""
    osat=toiminto.split()
    maara=len(osat)
    #0 add, 1 on aine, isoin on opintopisteet,
    # ja kaikki siitä välistä on kurrsin nimi

    #muodostetaan kurssin nimi silmukan avulla
    kurssin_nimi=[]
    for index in range(2, maara-1):
        kurssin_nimi.append(osat[index])

    kurssin_nimi=" ".join(kurssin_nimi)

    tiedot = {}

    #jos osasto on olemassa
    #lisätään sinne uusi kurssi
    if osat[1] in kurssit:
        kurssit[osat[1]][kurssin_nimi]=osat[maara-1]
        print(f"Added course {kurssin_nimi} to department {osat[1]}")

    #jos osastoa ei ole olemassa
    #luodaan ensin sanakirja kurssista ja opintopisteitstä
    #ja sitten lisätään osasto ja sitä vastaava sanakirja
    elif maara>2 and osat[1] not in kurssit:
        #joo oli vähän kyseenalainen elif ehto
        # mut en keksiny muuta järkevämpää
        tiedot[kurssin_nimi]=osat[maara-1]
        kurssit[osat[1]]=tiedot
        print(f"Added department {osat[1]} with course {kurssin_nimi}")

    else:
        print("Invalid command!")

def delete(kurssit, toiminto):
    """Funktio ottaa parametrina kurssit sanakirjan ja käyttäjän antaman
    toimintokäskyn. Käyskyn perusteella funktio poistaa joko kokonaisen
    osaston tai vain yhden kurssin"""
    osat=toiminto.split()
    maara=len(osat)

    if maara==2:
        #nyt käskyssä on ollut vain d ja osaston nimi
        try:
            del kurssit[osat[1]]
            print(f"Department {osat[1]} removed.")
        except KeyError:
            print(f"Department {osat[1]} not found!")


    #jos käskyssä on yli kaksi sanaa
    else:
        #muodostetaan kurssin nimi ensin
        kurssin_nimi = []
        for index in range(2, maara):
            kurssin_nimi.append(osat[index])

        kurssin_nimi = " ".join(kurssin_nimi)

        try:
            #sitten poistetaan kurssi
            del kurssit[osat[1]][kurssin_nimi]
            print(f"Department {osat[1]} course {kurssin_nimi} removed.")

        except KeyError:
            #jos kurssia ei ole olemassa tulostetaan virhe ilmoitus
            print(f"Course {kurssin_nimi} from {osat[1]} not found!")





def main():
    tiedosto=input("Enter file name: ")
    kurssit=read_file(tiedosto)
    if not kurssit:
        return



    while True:
        print("[A]dd / [C]redits / [D]elete / [P]rint all / p[R]int department / [Q]uit")
        toiminto_kasky = input("Enter command: ")
        toiminto=toiminto_kasky.split()



        if toiminto[0]=="A" or toiminto[0]=="a":
            print()
            add(kurssit, toiminto_kasky)
            print()

        elif toiminto[0]=="C" or toiminto[0]=="c":
            print()
            credits(kurssit, toiminto_kasky)
            print()

        elif toiminto[0]=="D" or toiminto[0]=="d":
            print()
            delete(kurssit, toiminto_kasky)
            print()

        elif toiminto[0]=="P" or toiminto[0]=="p":
            print()
            print_all(kurssit)
            print()

        elif toiminto[0] =="R" or toiminto[0]=="r":
            print()
            print_department(kurssit, toiminto_kasky)
            print()

        elif toiminto[0]=="Q" or toiminto[0]=="q":
            print("Ending program.")
            break

        else:
            print("Invalid command!")
            print()

main()