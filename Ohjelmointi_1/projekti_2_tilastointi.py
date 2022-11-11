"""COMP.CS.100 projekti 2
tekijä:Vilma Lehto
opiskelijanumero:050044139"""
def read_message():
    """Funktio lukee käyttäjän syöttämän rivi/arvon,
    liittää sen edelliseen riviin muodstaen listan,
    lopuksi muodostettu lista muutetaan float-luvuiksi"""
    arvo=str(input())
    arvot=[arvo]
    while arvo != "":
        arvo=str(input())
        if arvo != "":
            arvot.append(arvo)

    for index in range(len(arvot)):
        arvot[index]=float(arvot[index])


    return arvot

def count_mean(arvot):
    """Funktio ottaa parametrina käyttäjän syöttämät arvot
    laskee näiden arvojen summan, lukumäärän ja sitten keskiarvon,
    palauttaen main-funktiolle keskiarvon"""
    summa=sum(arvot)
    lkm=len(arvot)

    keskiarvo=summa/lkm

    return keskiarvo


def count_standard_deviation(arvot):
    """Funktio ottaa parametrina käyttäjän syöttämät arvot
    laskee varianssin ja siitä keskihajonnan, palauttaen
    main-funtkiolle keskihajonnan"""

    varianssi = 0
    keskiarvo = count_mean(arvot)

    for index in range(len(arvot)):
        alkio=(1 / (len(arvot)-1))*((arvot[index]-keskiarvo)**2)
        varianssi+=alkio

    keskihajonta=varianssi**(1/2)

    return keskihajonta

def count_limits_for_histogram(arvot):
    """Funktio laskee rajat histogrammille,
    ottamalla parametsiksi käyttäjän määrittelemät arvot
    ja palauttamalla rajat,
    tiedän en tehny sitä for-silmukkaa meni yli ymmärryksen"""

    keskihajonta=count_standard_deviation(arvot)

    nollaraja=0
    eka=0.5*keskihajonta
    toka=keskihajonta
    kolmas=1.5*keskihajonta
    neljas=2*keskihajonta
    viides=2.5*keskihajonta
    kuudes=3*keskihajonta

    return nollaraja, eka, toka, kolmas, neljas, viides, kuudes

def length_of_the_star_row(arvot, alaraja, ylaraja):
    """Käy arvot läpi ja vertaa niitä ala- ja ylärajoihin
    palauttaa tiedon montako arvoa kysytyllä välillä oli"""
    keskiarvo=count_mean(arvot)
    pituus=0

    for index in range (len(arvot)):
        vertailuarvo=abs(arvot[index]-keskiarvo)
        if alaraja<=vertailuarvo and ylaraja>vertailuarvo:
            pituus+=1

    return pituus

def main():
    print("Enter the data, one value per line.")
    print("End by entering empty line.")

    arvot=read_message()

    #määritetään ohjelman loppuminen jos arvoja saadaan alle kaksi
    if len(arvot)<2:
         print("Error: needs two or more values.")

    #jos arvoja on kaksi tai useampi
    #ohjelma jatkaa eteenpäin
    else:
        keskiarvo=count_mean(arvot)
        print(f"The mean of given data was: {keskiarvo:.2f}")

        keskihajonta=count_standard_deviation(arvot)
        print(f"The standard deviation of given data was: {keskihajonta:.2f}")


        #jos keskihajonta on 0 ohjelma loppuu
        if keskihajonta==0:
            print("Deviation is zero.")

        #muuten ohjelma jatkaa eteenpäin tulostamalla histogrammin
        else:

            #välienrajat
            nollaraja, eka, toka, kolmas, neljas, viides, kuudes\
                =count_limits_for_histogram(arvot)

            #kuinka monta arvoa on halutulla välillä
            pituus1=int(length_of_the_star_row(arvot, nollaraja, eka))
            pituus2=int(length_of_the_star_row(arvot, eka, toka))
            pituus3=int(length_of_the_star_row(arvot, toka, kolmas))
            pituus4=int(length_of_the_star_row(arvot, kolmas, neljas))
            pituus5=int(length_of_the_star_row(arvot, neljas, viides))
            pituus6=int(length_of_the_star_row(arvot, viides, kuudes))
            merkki="*"


            #tulostetaan histogrammi
            print(f"Values between std. dev. {nollaraja:.2f}-{eka:.2f}:"
                  f" {merkki*pituus1}")
            print(f"Values between std. dev. {eka:.2f}-{toka:.2f}: "
                  f"{merkki * pituus2}")
            print(f"Values between std. dev. {toka:.2f}-{kolmas:.2f}: "
                  f"{merkki * pituus3}")
            print(f"Values between std. dev. {kolmas:.2f}-{neljas:.2f}: "
                  f"{merkki * pituus4}")
            print(f"Values between std. dev. {neljas:.2f}-{viides:.2f}: "
                  f"{merkki * pituus5}")
            print(f"Values between std. dev. {viides:.2f}-{kuudes:.2f}: "
                  f"{merkki * pituus6}")



main()