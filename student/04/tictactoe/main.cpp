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
 * Nimi: Eemil Lehto, Eetu Kuittinen
 * Opiskelijanumero: 431051, 150541820
 * Käyttäjätunnus: , fkeeku
 * E-Mail: eemil.lehto@tuni.fi, eetu.kuittinen@tuni.fi
 *
 * Huomioita ohjelmasta ja sen toteutuksesta:
 *
 * */

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include <sstream>
#include <iomanip>

/*Mahdollistaa standardikirjastosta löytyvien komentojen käyttämisen ilman,
 * että niiden eteen tarvitsee kirjoittaa std::*/
using namespace std;

const char PISTE_VAKIO = '.';
const char RASTI_VAKIO = 'X';
const char NOLLA_VAKIO = '0';
const string LOPETUS = "q";
const string RASTI = "Cross";
const string NOLLA = "Nought";


/*Tulostetaan pelilauta funktio ei palauta arvoa,
 * ottaa vastaan viitteen pelilautaan, joka on vektori.*/
void tulostaPeli(const vector<vector<char>>& peliLauta){
    //Jättää pelilaudan vasempaan yläkulmaan tyhjän "ruudun".
    cout << "  ";
    unsigned long ruudukonNumerot = 1;

    /*Pelilaudan yläpuolelle tulevia numeroita kasvatetaan niin kauan, kun ne
     * ovat pienempiä kuin vektorin koko.*/
    for(unsigned long numeroIndeksi = 0;
        numeroIndeksi < peliLauta.size();
        numeroIndeksi++){
        /*Alustetaan pelilaudan numeromuuttuja, joka saadaan aina kymmenen jako-
        * jäännöksestä*/
        ruudukonNumerot %= 10;
        cout << ruudukonNumerot << " ";
        ruudukonNumerot++;
    }
    cout << endl;
    ruudukonNumerot = 1;
    //Vaihtaa laudan "riviä", kun alempi for-loop on käynyt sen loppuun.
    for(unsigned long indeksi = 0;
        indeksi < peliLauta.size(); indeksi++){
        ruudukonNumerot %= 10;
        cout << ruudukonNumerot << " ";
        ruudukonNumerot++;

        //Käy läpi yksittäisen rivin kaikki alkiot.
        for(unsigned long toinenIndeksi = 0;
            toinenIndeksi < peliLauta[indeksi].size();
            toinenIndeksi++){
            cout << peliLauta[indeksi][toinenIndeksi] << " ";
        }
        cout << endl;
    }
}

/*Tarkistetaan, sisältääkö annettu syöte kirjaimia,
* palauttaa totuusarvon, parametreinä merkkijonojen sisältöjen kopiot.*/
bool onkoInt(string& ekaStringKoordinaatti,
             string& tokaStringKoordinaatti, int& ekaIntKoordinaatti,
             int& tokaIntKoordinaatti){
    //For-loopit käyvät molemmat annetut koordinaatit läpi merkki kerrallaan.
    for (unsigned long i = 0; i < ekaStringKoordinaatti.size(); i++){
        for (unsigned long j = 0; j < tokaStringKoordinaatti.size(); j++){
            //Jos löytyy edes yksi kirjain, palautetaan false.
            if(!isdigit(ekaStringKoordinaatti.at(i)) ||
                    !isdigit(tokaStringKoordinaatti.at(j))) {
             //String sisälsi kirjaimia.
             return false;
            }
        }
        /*Jos syöte sisälsi kirjaimia,arvot muutetaan stringstreamilla
         * merkkijonoista kokonaisluvuiksi.*/
        stringstream luku1Kokonaisluvuksi;
        stringstream luku2Kokonaisluvuksi;
        luku1Kokonaisluvuksi << ekaStringKoordinaatti;
        luku2Kokonaisluvuksi << tokaStringKoordinaatti;
        luku1Kokonaisluvuksi >> ekaIntKoordinaatti;
        luku2Kokonaisluvuksi >> tokaIntKoordinaatti;
        return true; //Syöte sisälsi kirjaimia.
    }
    //Sisälsi pelkkiä numeroita.
    return true;
}

/*Funktio ottaa parametreina pelilaudan viitteen, pelaajan merkin viitteen,
* koordinaattien viitteet. Ei palauta arvoa.*/
void lisaaMerkki(vector<vector<char>>& peliLauta,const char& merkki,
                 const int& ekaKoordinaatti, const int& tokaKoordinaatti){
    //Pelaajan merkki syötteen koordinaateille
    peliLauta.at(tokaKoordinaatti).at(ekaKoordinaatti) = merkki;
}

/*Selvitetään, onko voittoa verikaalisesti. Ottaa vastaan pelilaudan- sekä
* pelaajan merkin viitteen. Palauttaa totuusarvon.*/
bool onkoVoittoaVertikaalisesti(const vector<vector<char>>& peliLauta,
                                const char& merkki){
    //Alustetaan voittolaskuri.
    int voittoLaskuri = 0;
    //Muuttuja joka osoittaa tarvittavan määrän merkkejä voitton.
    int vertikaaliVoitto = peliLauta.size();
    //For-loop vaihtaa saraketta, kun sarake läpikäyty.
    for(unsigned long indeksi = 0;
        indeksi < peliLauta.size();
        indeksi++){
        //Käy läpi saraketta kunnes käyty läpi.
        for(unsigned long toinenIndeksi = 0;
            toinenIndeksi < peliLauta[indeksi].size();
            toinenIndeksi++){
            char vertikaaliVertailuMerkki
            = peliLauta.at(toinenIndeksi).at(indeksi);
            //Jos löytyy merkki, kasvatetaan yhdellä.
            if(vertikaaliVertailuMerkki == merkki){
                voittoLaskuri++;
            }
            //Ei voittoa vertikaalisesti
            else{
                voittoLaskuri = 0;
            }
            /*Jos voittolaskuri on pelilaudan koko ja kaikki vertikaalimerkit
             * ovat samoja.*/
            if(voittoLaskuri == vertikaaliVoitto){
                //Voitto vertikaalisesti
                return true;
            }
        }
        voittoLaskuri = 0;
    }

    //Ei vertikaalivoittoa
    return false;
}

/*Funktio tarkistaa onko horisontaalivoittoa. Ottaa parametreina pelilaudan
* viitten ja pelaajan merkin viitteen. Toimii samalla peliaatteella kuin verti-
* kaalivoitto, mutta käy arvot läpi "riveittäin"*/
bool onkoVoittoaHorisontaalisesti(const vector<vector<char>>& peliLauta,
                                  const char& merkki){
    int voittoLaskuri = 0;
    //Muuttuja joka osoittaa tarvittavan määrän merkkejä voitton.
    int horisontaaliVoitto = peliLauta.size();
    for(unsigned long indeksi = 0; indeksi < peliLauta.size(); indeksi++){
        for(unsigned long toinenIndeksi = 0;
            toinenIndeksi < peliLauta[indeksi].size();
            toinenIndeksi++){
            char horisontaaliVertailuMerkki
                 = peliLauta.at(indeksi).at(toinenIndeksi);
            if(horisontaaliVertailuMerkki == merkki){
                voittoLaskuri++;
            }
            else{
                voittoLaskuri = 0;
            }
            if(voittoLaskuri == horisontaaliVoitto){
                return true;
            }
        }
        voittoLaskuri = 0;
    }
    return false;
}

/*Funktio käy arvot läpi diagonaalisesti eli vinottain. Ensimmäinen for-loop
* aloittaa vasemmasta yläkulmasta ja kulkee diagonaalisesti ruudukkoa läpi.
* Sen jälkeen toinen for-loop käy arvoja diagonaalisesti oikeasta yläkulmasta
* aloittaen päinvastaista "reittiä". Palauttaa totuusarvon ("Onko diagonaali-
* voittoa?"), ottaa vastaan parametreina pelilaudan viitten sekä pelaajan merkin
* viitteen vakiona. Funktio huomioi myös ruudukon koon eli esim. 4x4 ruudukolla
* tarvitaan 4:n sarja diagonaalisesti eikä voi voittaa alkuperäisellä kolmella*/
bool onkoVoittoaDiagonaalisesti(const vector<vector<char>>& peliLauta,
                                const char& merkki){
    int voittoLaskuri = 0;
    //Muuttuja joka osoittaa tarvittavan määrän merkkejä voitton.
    int diagonaaliVoitto = peliLauta.size();
    /*käydään ruudukko ensin diagonaalisesti vasemmasta yläkulmasta
    * oikeaan alakulmaan*/
    for(unsigned long indeksi = 0; indeksi < peliLauta.size(); indeksi++){
        char diagonaaliVertailuMerkki = peliLauta.at(indeksi).at(indeksi);
        if(diagonaaliVertailuMerkki == merkki){
            voittoLaskuri++;
        }
        else{
            voittoLaskuri = 0;
        }
        if(voittoLaskuri == diagonaaliVoitto){

            //Peli voitettu diagonaalisesti.
            return true;
        }
    }
    /*Käydään sitten tarkistus diagonaalisesti oikeasta yläkulmasta vasempaan
     * alakulmaan*/
    int laskevaIndeksi = peliLauta.size() - 1;
    for(unsigned long toinenIndeksi = 1;
        toinenIndeksi < peliLauta.size();
        toinenIndeksi++){
        char vertailuMerkki = peliLauta.at(laskevaIndeksi).at(toinenIndeksi);
        if(vertailuMerkki == merkki){
            voittoLaskuri++;
        }
        else{
            voittoLaskuri = 0;
        }
        if(voittoLaskuri == diagonaaliVoitto){

            //Peli voitettu diagonaalisesti.
            return true;
        }
        laskevaIndeksi--;
    }
    //Ei diagonaalivoittoa toistaiseksi.
    return false;
}

/*Funktio palauttaa totuusarvon. Funktiossa tarkistetaan, onko ruudukossa tilaa
* vertaamalla yksittäisen paikan merkkiä pisteeseen pistevakioon. Jos yhtään
* pistettä ei löydy eli löytyy vain nollia tai ykkösiä, ruudukko on täynnä.
* Parametrinä pelilaudan viite.*/
bool onkoRuudukossaTilaa(const vector<vector<char>>& peliLauta){
    for(unsigned long indeksi = 0; indeksi < peliLauta.size(); indeksi++){
        for(unsigned long toinenIndeksi = 0;
            toinenIndeksi < peliLauta[indeksi].size();
            toinenIndeksi++){
            char taynnaVertailuMerkki = peliLauta.at(indeksi).at(toinenIndeksi);
            if(taynnaVertailuMerkki == PISTE_VAKIO){
                //Ruudukko täysi.
                return false;
            }
        }
    }
    //Ruudukossa on tilaa.
    return true;
}

/*Funktion ideana tarkistaa, voiko paikalle kirjoittaa, eli toisin sanoen
 * löytyykö paikalta jo jommankumman pelaajan merkkiä (X tai 0). Ottaa
 * parametreinä pelilaudan viitteen sekä koordinaattien viitteet.
 * Palauttaa totuusarvon, palametrinä pelilaudan viite sekä viitteet koordinaat-
 * tien vakioihin*/
bool voikoPaikalleKirjoittaa(const vector<vector<char>>& peliLauta,
                             const int& ensimmainenKoordinaatti,
                             const int& toinenKoordinaatti){
    char paikanTarkistusMerkki = ' ';
    paikanTarkistusMerkki = peliLauta.at(toinenKoordinaatti)
                                     .at(ensimmainenKoordinaatti);

    if(paikanTarkistusMerkki == RASTI_VAKIO
    || paikanTarkistusMerkki == NOLLA_VAKIO){
        return false;
    }
    else{
        return true;
    }
}

/*Funktio ei palauta mitään. Ruudukon laajentaminen toteutetaan joko lisäämällä tyh-
 *jiä "ruutuja" sen mukaisesti, minne halutaan laajentaa tai toiseen suuntaan
 *rakentamalla ensin laajennettu kopio ruudukosta ja lisäämällä vanhat merkit
 *myöhemmin kopioituun ruudukkoon uusille paikoilleen.
 *Parametreina ruudukkovektori, ensimmäinen ja toinen koordinaatti,
 *sekä pelaajan merkki viitteinä.*/
void ruudukonLaajentaminen(vector<vector<char>>& ruudukko,
                           int& ekaKoordinaatti,
                           int& tokaKoordinaatti, const char& merkki,
                           int& ruudukonKoko){
    /*Suoritetaan ruudukon laajentaminen lisäämällä tyhjiä ruutuja vektoreiden
     * perään ja alariville luodaan kokonaan tyhjä vektori. Merkin lisäämine
     * hoituu myöhemmin lisääMerkki funktion kutsulla pääohjelmassa*/
    if(ekaKoordinaatti == ruudukonKoko || tokaKoordinaatti == ruudukonKoko){
        for(int indeksi = 0; indeksi < ruudukonKoko; indeksi++){
            ruudukko.at(indeksi).push_back(PISTE_VAKIO);
        }

        //Luodaan uusi vektori, joka tuodaan pelilaudan alareunaan
        vector<char> laajennusVektori;

        for(int indeksi = 0; indeksi <= ruudukonKoko; indeksi++){
            laajennusVektori.push_back(PISTE_VAKIO);
        }
        ruudukko.push_back(laajennusVektori);
        /*jos koordinaatit ovat mennet negatiivisiksi aikaisemmin suoritetusta
         * vähentämisoperaatioista, lisätään niitä yhdellä*/
        if(ekaKoordinaatti == -1){
            ekaKoordinaatti++;
        }
        if(tokaKoordinaatti == -1){
            tokaKoordinaatti++;
        }
        ruudukko.at(tokaKoordinaatti).at(ekaKoordinaatti) = merkki;

    }
    /*Mikäli laajentuminen halutaan toiseen suuntaan, kopioidaan yhtä suurempaan
     * taulukkoon vanha peli ja lisätään pelaajan merkki uuteen taulukkoon.
     * lopuksi kopioidaan laajennettu taulukko alkuperäiseen muuttujaan*/
    else{
        int uudenRuudukonKoko = ruudukonKoko + 1;
        vector<char> sarakeKopio(uudenRuudukonKoko, PISTE_VAKIO);
        vector<vector<char>> ruudukkoKopio(uudenRuudukonKoko, sarakeKopio);

        for(unsigned long indeksi = 0; indeksi < ruudukko.size(); indeksi++){
            for(unsigned long toinenIndeksi = 0;
                toinenIndeksi < ruudukko[indeksi].size();
                toinenIndeksi++){

                char kopiointiMerkki = ruudukko.at(indeksi).at(toinenIndeksi);
                ruudukkoKopio.at(indeksi + 1).at(toinenIndeksi + 1)
                = kopiointiMerkki;
            }
        }
        ruudukkoKopio.at(tokaKoordinaatti + 1).at(ekaKoordinaatti + 1) = merkki;
        ruudukko = ruudukkoKopio;
    }
}


/*Funktion tehtävänä tarkistaa, yritetäänkö laajentaa kahteen suuntaan. Tämä
operaatio ei ole sallittu. Palauttaa totuusarvon, parametreina koordinaattien
sekä pelin koon sisältöjen viitteet.*/
bool onkoKaksiLaajennusta(int& ekaKoordinaatti,
                          int& tokaKoordinaatti,
                          const int& pelinKoko){

    if(ekaKoordinaatti == 0 && tokaKoordinaatti > pelinKoko){
        return false;
    }
    else if(tokaKoordinaatti == 0 && ekaKoordinaatti > pelinKoko){
        return false;
    }

    /*Pienennetään koordinaattien arvoja, jolloin ne sopivat myöhempiin
     * indekseihin automaattisesti.*/
    ekaKoordinaatti--;
    tokaKoordinaatti--;
    return true;
}

int main(){

    //Ensimmäinen tulostus.
    cout << "Start game: " << endl;
    //Tuottaa 3x3 kokoisen pisteruudukon.
    vector<vector<char>> peliRuudukko{ {PISTE_VAKIO, PISTE_VAKIO, PISTE_VAKIO},
                                       {PISTE_VAKIO, PISTE_VAKIO, PISTE_VAKIO},
                                       {PISTE_VAKIO, PISTE_VAKIO, PISTE_VAKIO}};
    tulostaPeli(peliRuudukko);
    cout << endl;
    string ensimmainenStringKoordinaatti = "j";
    string toinenStringKoordinaatti = "j";
    int ensimmainenKoordinaatti = 0;
    int toinenKoordinaatti = 0;

    //Tämä ehto pitää pelin käynnissä.
    bool koordinaattienTarkistus = false;
    //Pelaajan vuoro määritellään jakojäännöksellä.
    int vuoronMaarittaja = 0;

    //Rasti aloittaa.
    char pelaajanMerkki = RASTI_VAKIO;
    string pelaajanNimi = RASTI;

    while(koordinaattienTarkistus == false){
        vuoronMaarittaja %= 2;
        int ruudukonKoko = peliRuudukko.size();
        if(vuoronMaarittaja == 0){
            pelaajanMerkki = RASTI_VAKIO;
            pelaajanNimi = RASTI;
        }
        else{
            pelaajanMerkki = NOLLA_VAKIO;
            pelaajanNimi = NOLLA;
        }
        cout << "For " << pelaajanMerkki << ", enter coordinates: x y> ";
        cin >> ensimmainenStringKoordinaatti;
        if(ensimmainenStringKoordinaatti == LOPETUS){
            cout << "Why on earth you are giving up the game?" << endl;
            return EXIT_SUCCESS;
        }
        cin >> toinenStringKoordinaatti;

        /*Koordinaatit tallennetaan stringeiksi, jotta voidaan
         * selvittää sisältääkö syöte kirjaimia. Jos syöte
         * sisältää kirjaimia, funktio palauttaa falsen ja tulostaa virhe-
         * ilmoituksen, muuten jatketaan ohjelman suorittamista.*/
        if(onkoInt(ensimmainenStringKoordinaatti,
                      toinenStringKoordinaatti, ensimmainenKoordinaatti,
                      toinenKoordinaatti)){
            /*Tarkistetaan että koordinaatit ovat numeroina sallittuja
             * muuten tulostetaan virheilmoitus*/
            if(ensimmainenKoordinaatti >= 0 && toinenKoordinaatti >= 0 &&
                    ensimmainenKoordinaatti <= ruudukonKoko + 1 &&
                    toinenKoordinaatti <= ruudukonKoko + 1){
                /*Tarkistetaan ettei käyttäjän syöttämät koordinaatit
                 * yritä laajentaa pelilautaa kahteen suuntaan
                 * muuten tulostetaan virheilmoitus*/
                if(onkoKaksiLaajennusta(ensimmainenKoordinaatti,
                                        toinenKoordinaatti,
                                        ruudukonKoko)){
                   /*Mikäli käyttäjän antamat syötteet ovat oikeelliset
                    * tarkistetaan vielä haluaako käyttäjä laajentaa
                    * pelilautaa. Mikäli näin on, kutsutaan laajentamis-
                    * funktiota.*/
                   if(ensimmainenKoordinaatti < 0
                      || toinenKoordinaatti < 0
                      || ensimmainenKoordinaatti == ruudukonKoko
                      || toinenKoordinaatti == ruudukonKoko ){

                       ruudukonLaajentaminen(peliRuudukko,
                                             ensimmainenKoordinaatti,
                                             toinenKoordinaatti,
                                             pelaajanMerkki,
                                             ruudukonKoko);
                       tulostaPeli(peliRuudukko);
                       cout << endl;

                   }
                   /*Mikäli käyttäjä ei halua laajentaa pelilautaa
                    * suoritetaan normaali prosessi merkin kirjoittami-
                    * seksi peliruudukkoon. Tässä prosessissa tarkas
                    * tetaan voiko paikalle kirjoittaa, eli että halutulla
                    * ei ole jo merkkiä*/
                   else{
                       if(voikoPaikalleKirjoittaa(peliRuudukko,
                                               ensimmainenKoordinaatti,
                                               toinenKoordinaatti)){
                           lisaaMerkki(peliRuudukko,
                                       pelaajanMerkki,
                                       ensimmainenKoordinaatti,
                                       toinenKoordinaatti);
                           tulostaPeli(peliRuudukko);
                           cout << endl;
                       }
                       else{
                           cout << "The given place is already occupied"
                                << endl;
                           vuoronMaarittaja++;
                       }
                   }
                }
                else{
                    cout << "Coordinate outside the board" << endl;
                    vuoronMaarittaja++;
                }
            }
            else{
                cout << "Coordinate outside the board" << endl;
                vuoronMaarittaja++;
            }

        }
        else{
            cout << "Coordinate outside the board" << endl;
            vuoronMaarittaja++;
        }
        /*Tarkistetaan onko jompi kumpi pelaajista voittanut jo peliä
         * käymällä peliruudukko läpi horisontaalisesti, vertikaalisesti
         * ja diagonaalisesti*/
        if(onkoVoittoaHorisontaalisesti(
           peliRuudukko, pelaajanMerkki)){
            cout << pelaajanNimi
                 << " won horizontally" << endl;
            cout << "Game over!" << endl;
            return EXIT_SUCCESS;
        }
        else if(onkoVoittoaVertikaalisesti(
                peliRuudukko, pelaajanMerkki)){
            cout << pelaajanNimi
                 << " won vertically" << endl;
            cout << "Game over!" << endl;
            return EXIT_SUCCESS;
        }
        else if(onkoVoittoaDiagonaalisesti(
                peliRuudukko,
                pelaajanMerkki)){
            cout << pelaajanNimi << " won diagonally"
                 << endl;
            cout << "Game over!" << endl;
            return EXIT_SUCCESS;
        }
        /*Tarkistetaan aina lopuksi onko peliruudukko täyttynyt jo
         * merkeistä. Mikäli näin on, tulostetaan ilmoitus pelin
         * päättymisestä*/
        koordinaattienTarkistus = false;
        if(onkoRuudukossaTilaa(peliRuudukko)){
            cout << "No empty places" << endl;
            cout << "Game over!" << endl;
            return EXIT_SUCCESS;
        }
        vuoronMaarittaja++;
    }
}
