#include <iostream>

using namespace std;

int main()
{
    long pallojen_maara = 0;
    long nostettavien_pallojen_maara = 0;
    long kertoma = 1;
    long kertoma2 = 1;
    long kertoma3 = 1;
    cout << "Enter the total number of lottery balls: ";
    cin >> pallojen_maara;

    cout << "Enter the number of drawn balls: ";
    cin >> nostettavien_pallojen_maara;

    if (pallojen_maara < 0) {
        cout << "The number of balls must be a positive number." << endl;
        return EXIT_SUCCESS;
    }

    else if (nostettavien_pallojen_maara > pallojen_maara) {
        cout << "The maximum number of drawn balls is the total amount of balls." << endl;
        return EXIT_SUCCESS;
    }

    else if (pallojen_maara <= 1) {
        cout << pallojen_maara << "! = " << kertoma;
        return EXIT_SUCCESS;
    }

    else {
        for (long laskija = pallojen_maara; laskija >= 2; laskija--) {
            kertoma = kertoma * laskija;
        }
    }

    int uusi_maara = pallojen_maara - nostettavien_pallojen_maara;

    for (long laskija2 = uusi_maara; laskija2 >= 2; laskija2--) {
        kertoma2 = kertoma2 * laskija2;
    }

    for (long laskija3 = nostettavien_pallojen_maara; laskija3 >= 2; laskija3--) {
        kertoma3 = kertoma3 * laskija3;
    }

    long lopullinen_vastaus = kertoma / (kertoma2 * kertoma3);

    cout << "The probability of guessing all " << nostettavien_pallojen_maara << " balls correctly is 1/" << lopullinen_vastaus << endl;

    return EXIT_SUCCESS;
}

