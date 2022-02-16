//--------------------------------------------------
//  COMP.CS.110 Ohjelmointi 2: Rakenteet -pohjakoodi
//  Copyright © 2021
//--------------------------------------------------
/* Miinaharava
 *
 * Kuvaus:
 *
 * Ohjelman on tarkoitus olla kopio alkuperäisestä miinaharavapelistä. Se toimii
 * seuraavasti:
 *
 * Aluksi valitaan siemenluku, joka on arvo, jonka avulla peli arvotaan.
 * Tämän jälkeen valitaan ruudukolle koko vetämällä liukusäädintä (slider).
 * Kun tämä on tehty, painetaan aloita peli.
 * Peli alkaa ja luo ruudukon oikean kokoiseksi.

 * Pelissä on ideana olla osumatta miinaan.
 * Ruutuja avataan klikkaamalla ja jos kohdalla ei ole miinaa,
 * se joko näyttää kuinka monessa viereisessä ruudussa on miina tai sitten jos
 * viereisissä ei ole miinaa, peli näyttää viereiset joiden vieressä ei ole
 * miinaa. Pelin voittaa käymällä koko laudan läpi niin, että pelin lopuksi
 * vain kaikki miinattomat ruudut on avattu ja miinalliset liputettu.
 *
 *
 * Ohjelman kirjoittaja
 * Nimi: Eetu Kuittinen
 * Opiskelijanumero: 150541820
 * Käyttäjätunnus: fkeeku
 * E-Mail: eetu.kuittinen@tuni.fi
 *
 * */


#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
