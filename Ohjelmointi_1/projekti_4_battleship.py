"""Ohjelma on yksin pelattava laivanupotuspeli. Käyttäjä kertoo ohjelmalle
mihin hän ampuu ja ohjelma kertoo osuiko ammus laivaan vai ei.
Laivat ovat jokainen oma laiva-luokan olionsa.
tekijä:Vilma Lehto
opiskelijanumero:050044139"""

class Laiva:
    def __init__(self, numero, tyyppi, koordinaatit):
        """ :param tyyppi: kertoo mitä tyyppiä laiva on,
        vaihtoehdot ovat battleship, cruiser, destroyer, submarine
        :param koordinaatit: kertoo missä laiva sijaitsee pelilaudalla"""
        self.__numero=numero
        self.__tyyppi=tyyppi
        self.__koordinaatit=koordinaatit
        self.__osumat=[]

    def get_koordinaatit(self):
        return self.__koordinaatit

    def get_osumat(self):
        return self.__osumat

    def get_tyyppi(self):
        return self.__tyyppi

    def get_merkki(self):
        if self.__tyyppi=="battleship":
            return "B"

        if self.__tyyppi=="cruiser":
            return "C"

        if self.__tyyppi=="destroyer":
            return "D"

        if self.__tyyppi=="submarine":
            return "S"

    def ammuttu(self, ammus):
        koordinaatit=self.__koordinaatit
        osumat=self.__osumat

        if ammus in koordinaatit:
            koordinaatit.remove(ammus)
            osumat.append(ammus)
            self.__osumat=osumat
            return "X"

        elif ammus not in koordinaatit:
            return "*"



    def sank(self):
        koordinaatit=self.__osumat
        merkki=self.get_merkki()

        return merkki, koordinaatit






class Lauta:
    def __init__(self):
        """Alustetaan lauta-olio, jokainen laudan rivi on alustettu omakseen"""

        self.__1_rivi =["", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", " ", ":"]
        self.__2_rivi =["0", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "0", ":"]
        self.__3_rivi = ["1", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "1", ":"]
        self.__4_rivi = ["2", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "2", ":"]
        self.__5_rivi = ["3", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "3", ":"]
        self.__6_rivi = ["4", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "4", ":"]
        self.__7_rivi = ["5", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "5", ":"]
        self.__8_rivi = ["6", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "6", ":"]
        self.__9_rivi = ["7", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "7", ":"]
        self.__10_rivi = ["8", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "8", ":"]
        self.__11_rivi = ["9", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "9", ":"]
        self.__12_rivi = ["", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", " ", ":"]



    def print_out_lauta(self):
        """Tulsotetaan lauta rivi kerrallaan"""
        print(" ".join(self.__1_rivi))
        print(" ".join(self.__2_rivi))
        print(" ".join(self.__3_rivi))
        print(" ".join(self.__4_rivi))
        print(" ".join(self.__5_rivi))
        print(" ".join(self.__6_rivi))
        print(" ".join(self.__7_rivi))
        print(" ".join(self.__8_rivi))
        print(" ".join(self.__9_rivi))
        print(" ".join(self.__10_rivi))
        print(" ".join(self.__11_rivi))
        print(" ".join(self.__12_rivi))


    def muuta_merkki(self, merkki, ammus):
        merkki=[merkki]
        x=ammus[0]
        y=int(ammus[1])
        indeksit={"A":1, "B":2, "C":3, "D":4, "E":5, "F":6, "G":7, "H":8, "I":9, "J":10}
        rivit={0:2, 1:3, 2:4, 3:5, 4:6, 5:7, 6:8, 7:9, 8:10, 9:11}
        indeksi=indeksit[x]
        rivi_nro=rivit[y]

        if y==0:
            vanha_rivi=self.__2_rivi
            uusi_rivi=vanha_rivi[:indeksi]+merkki+vanha_rivi[indeksi+1:]
            self.__2_rivi=uusi_rivi

        if y==1:
            vanha_rivi=self.__3_rivi
            uusi_rivi=vanha_rivi[:indeksi]+merkki+vanha_rivi[indeksi+1:]
            self.__3_rivi=uusi_rivi

        if y==2:
            vanha_rivi=self.__4_rivi
            uusi_rivi=vanha_rivi[:indeksi]+merkki+vanha_rivi[indeksi+1:]
            self.__4_rivi=uusi_rivi

        if y==3:
            vanha_rivi=self.__5_rivi
            uusi_rivi=vanha_rivi[:indeksi]+merkki+vanha_rivi[indeksi+1:]
            self.__5_rivi=uusi_rivi

        if y==4:
            vanha_rivi=self.__6_rivi
            uusi_rivi=vanha_rivi[:indeksi]+merkki+vanha_rivi[indeksi+1:]
            self.__6_rivi=uusi_rivi

        if y==5:
            vanha_rivi=self.__7_rivi
            uusi_rivi=vanha_rivi[:indeksi]+merkki+vanha_rivi[indeksi+1:]
            self.__7_rivi=uusi_rivi

        if y==6:
            vanha_rivi=self.__8_rivi
            uusi_rivi=vanha_rivi[:indeksi]+merkki+vanha_rivi[indeksi+1:]
            self.__8_rivi=uusi_rivi

        if y==7:
            vanha_rivi=self.__9_rivi
            uusi_rivi=vanha_rivi[:indeksi]+merkki+vanha_rivi[indeksi+1:]
            self.__9_rivi=uusi_rivi

        if y==8:
            vanha_rivi=self.__10_rivi
            uusi_rivi=vanha_rivi[:indeksi]+merkki+vanha_rivi[indeksi+1:]
            self.__10_rivi=uusi_rivi
        if y==9:
            vanha_rivi=self.__11_rivi
            uusi_rivi=vanha_rivi[:indeksi]+merkki+vanha_rivi[indeksi+1:]
            self.__11_rivi=uusi_rivi




def read_file(tiedosto):
    """Funktio lukee käyttäjän määrittämän tiedoston sisällön ja
    luo jokaisesta rivistä oman olionsa, lisäten olito listaan ja palauttaen
    mainille tämän listan oliosta"""
    sarakkeet = ["A", "B", "C", "D", "E", "F", "G", "H", "I", "J"]
    rivit = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
    try:
        tiedosto = open(tiedosto, mode="r")

    except OSError:
        print("File can not be read!")
        return False

    laivat = []
    kaikki_koordinaatit = []
    numero=1
    for line in tiedosto:
        koordinaatit = []
        rivi = line.rstrip()
        osat = rivi.split(";")
        #osat[0] on laivan tyyppi
        #loput osat ovat koordinaatit
        for index in range(1, len(osat)):

            #tarkistetaan onko koordinaatti sallittu
            kirjain=str(osat[index][0])
            numero=int(osat[index][1])
            if kirjain not in sarakkeet or numero not in rivit:
                print("Error in ship coordinates!")
                return False


            #tarkistetaan onko koordinaatti ilmestynyt itedostossa jo aikasemmin
            #jos on tulostetaan virheilmoitus ja lopetetaan ohjelma
            elif osat[index] in kaikki_koordinaatit:
                print("There are overlapping ships in the input file!")
                return False

            #jos ei lisätään koordinaatti listoihin ja luodaan uusi olio
            else:
                koordinaatit.append(osat[index])
                kaikki_koordinaatit.append(osat[index])

        laiva = Laiva(numero, osat[0], koordinaatit)
        laivat.append(laiva)
        numero+=1

    return laivat


def main():
    sarakkeet = ["A", "B", "C", "D", "E", "F", "G", "H", "I", "J"]
    rivit = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]

    tiedosto=input("Enter file name: ")

    laivat=read_file(tiedosto)

    #jos read_file-funktiossa oli ongelmaa ohjelma katkeaa tähän
    if not laivat:
        return

    laivojen_maara=len(laivat)
    lauta=Lauta()
    ammutut=[]

    print()

    while True:
        lauta.print_out_lauta()

        print()

        ammus=input("Enter place to shoot (q to quit): ")
        ammus=ammus.upper()


        if ammus=="q" or ammus=="Q":
            print("Aborting game!")
            break

        #tarkistetaan onko ruutuun jo ammuttu
        elif ammus in ammutut:
            print("Location has already been shot at!")


        #tarkistetaan, että koordinaatti on hyväksyttävä
        else:
            if str(ammus[0]) in sarakkeet and int(ammus[1]) in rivit:

                #luodaan tyhjä merkit lista
                merkit=[]

                #käydään kaikki laivat läpi silmukassa
                #ja katsotaan osuiko ammus johonkin laivaan
                for index in range(0, laivojen_maara-1):

                    merkki = laivat[index].ammuttu(ammus)
                    #lisätään merkki merkit listaan
                    merkit.append(merkki)

                    # nyt jos merkki-listaan on tallentunut X on ammus osunut laivaan
                    if "X" in merkit:
                        lauta.muuta_merkki("X", ammus)

                    # jos merkki-listassa on pelkkiä * merkkejä, oli ammus huti
                    else:
                        lauta.muuta_merkki("*", ammus)

                    #katsotaan laivan jäljellä olevat koordinaatit
                    #ja tarkistetaan onko se kokonaan uponnut
                    koordinaatit = laivat[index].get_koordinaatit()
                    #jos laiva on kokonaan uponnut kutsutaan sank-metodia
                    if koordinaatit == []:
                        uponnut_merkki, uponneet_koordinaatit = laivat[index].sank()
                        merkit.append(uponnut_merkki)
                        laivan_tyyppi=laivat[index].get_tyyppi()
                        laivat.remove(laivat[index])
                        print(f"You sank a {laivan_tyyppi}!")

                        for index in range(0, len(uponneet_koordinaatit)):
                            lauta.muuta_merkki(uponnut_merkki, uponneet_koordinaatit[index])


                #lopuksi lisätään ammus ammutut-listaa, jotta voidaan vertailla
                #onko kohtaan ammuttu jo aikaisemmin
                ammutut.append(ammus)

            else:
                print("Invalid command!")

        if laivat==[]:
            print("Congratulations! You sank all enemy ships.")
            break



main()