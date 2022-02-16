#include <iostream>
#include <fstream>  //Tiedostojen lukemiseen
#include <string>

using namespace std;

int main() {
    string input_tiedoston_nimi = "";
    cout << "Input file: ";
    getline(cin, input_tiedoston_nimi);

    string output_tiedoston_nimi = "";
    cout << "Output file: ";
    getline (cin, output_tiedoston_nimi);

    ifstream input_tiedosto_olio(input_tiedoston_nimi);
    if ( not input_tiedosto_olio ) {
        cout << "Error! The file " << input_tiedoston_nimi << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }

    string syote = "";
    int i = 0;
    ofstream output_tiedosto_olio(output_tiedoston_nimi);

    while (getline(input_tiedosto_olio, syote)) {

        ++i;
        output_tiedosto_olio << i << " " << syote << "\n";

    }

   input_tiedosto_olio.close();
   output_tiedosto_olio.close();
   return EXIT_SUCCESS;
}
