#include <iostream>
#include <fstream>  //Tiedostojen lukemiseen
#include <string>
#include <map>
#include <vector>

using namespace std;

std::vector<std::string> split(
        const std::string& text,
        char delimiter,
        bool ignore_empty = false
)
{
      std::vector<std::string> parts;

      std::string::size_type left = 0;
      std::string::size_type right = 0;
      while (left <= text.size())
      {
          std::string part = "";

          right = text.find(delimiter, left);
          if (right == std::string::npos)
          {
              right = text.size();
          }

          part = text.substr(left, right - left);

          if (part != "" || !ignore_empty)
          {
              parts.push_back(part);
          }

          left = right + 1;

      }
      return parts;
}

int main()
{
    string input_tiedoston_nimi = "";
    cout << "Input file: ";
    getline(cin, input_tiedoston_nimi);

    ifstream input_tiedosto_olio(input_tiedoston_nimi);
    if ( not input_tiedosto_olio ) {
        cout << "Error! The file " << input_tiedoston_nimi << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }

    map <string, int> pistetaulukko;
    string syote = "";
    int luku = 0;
    char delimiter = ':';
    vector<string> splitVektori;

    while (getline(input_tiedosto_olio, syote)) {

        ++luku;
        splitVektori = split(syote, delimiter);
        string nimi = splitVektori.at(0);
        int pistemaara = stoi(splitVektori.at(1));
        if ( pistetaulukko.find(nimi) != pistetaulukko.end() ) {
            // nimi löytyi mapista.
            pistetaulukko.at(nimi) += pistemaara;
        }

        else {
                pistetaulukko.insert( {nimi, pistemaara} );
        }

    }


    cout << "Final scores: " << endl;
    for (auto& syote : pistetaulukko) {
        cout << syote.first << ": " << syote.second << endl;

    }

    input_tiedosto_olio.close();
    return EXIT_SUCCESS;


}
