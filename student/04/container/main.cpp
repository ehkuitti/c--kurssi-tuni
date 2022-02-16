#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void read_integers(std::vector<int>& integers, int how_many) {
    int new_integer = 0;
    for(int i = 0; i < how_many; ++i) {
        std::cin >> new_integer;
        integers.push_back(1);
        integers[i] = new_integer;
    }
}

bool same_values(vector<int>& integers) {
    if (adjacent_find(integers.begin(), integers.end(), not_equal_to<>()) == integers.end()){
        return true;
    }
    else {
        return false;
    }
}

bool is_ordered_non_strict_ascending (vector<int>& integers) {

    bool onkoJarjestetty;

    onkoJarjestetty = is_sorted(integers.begin(), integers.end());

    if (onkoJarjestetty == true) {
        return true;
    }
    else {
        return false;
    }

}

bool is_arithmetic_series (vector<int>& integers) {

    unsigned long vertailuarvo = integers[1]-integers[0];
    unsigned long erotus = 0;
    bool olikoVaiEi = true;

//    for (unsigned long i = 0; i < integers.size(); ++i) {
//        unsigned long erotus = integers[i+1] - integers[i];
//        cout << "Erotus on " << erotus << " ja vertailuarvo on " << vertailuarvo;
//        if (i == integers.size() && erotus == vertailuarvo) {
//            return true;
//        }
//    }
//    return false;

    unsigned long i = 0;
    do {
        erotus = integers[i+1] - integers[i];
        ++i;
        if (erotus == vertailuarvo) {
            olikoVaiEi = true;
        }
        else {
            olikoVaiEi = false;
        }

    } while(olikoVaiEi == true && i < integers.size()-1);

    if (olikoVaiEi == true)
        return true;
    else {
        return false;
    }


}

bool is_geometric_series (vector<int>& integers) {
//    std::vector<int>::iterator it;
//    it = std::unique (integers.begin(), integers.end());

//    bool onkoTotta = true;
//    unsigned long x = 0;

    unsigned long vertailuarvo = 0;
    unsigned long suhdeluku = 0;
    bool olikoVaiEi = true;
    vector<int>::iterator ip;

    if (std::adjacent_find(integers.begin(), integers.end(), std::not_equal_to<>() ) == integers.end() ){
        for (unsigned long i = 0; i < integers.size(); ++i) {
            if (integers[i] == 0) {
                ip = unique(integers.begin(), integers.end());
                if (integers[0] == 0) {
                    return false;
                    }
                }
            else if (i == integers.size()) {
                    break;
            }
        }
    }
    unsigned long i = 0;
    do {
        vertailuarvo = integers[1]/integers[0];
        suhdeluku = integers[i+1] / integers[i];
        ++i;
        if (suhdeluku == vertailuarvo) {
            olikoVaiEi = true;
        }
        else {
            olikoVaiEi = false;
        }

    } while(olikoVaiEi == true && i < integers.size()-1);

    if (olikoVaiEi == true)
        return true;
    else {
        return false;
    }
}


int main()
{
    std::cout << "How many integers are there? ";
    int how_many = 0;
    std::cin >> how_many;

    std::cout << "Enter the integers: ";
    std::vector<int> integers;
    read_integers(integers, how_many);

   if(same_values(integers))
        std::cout << "All the integers are the same" << std::endl;
    else
        std::cout << "All the integers are not the same" << std::endl;

    if(is_ordered_non_strict_ascending(integers))
        std::cout << "The integers are in a non-strict ascending order" << std::endl;
    else
        std::cout << "The integers are not in a non-strict ascending order" << std::endl;

    if(is_arithmetic_series(integers))
        std::cout << "The integers form an arithmetic series" << std::endl;
    else
        std::cout << "The integers do not form an arithmetic series" << std::endl;

    if(is_geometric_series(integers))
        std::cout << "The integers form a geometric series" << std::endl;
    else
        std::cout << "The integers do not form a geometric series" << std::endl;

  return EXIT_SUCCESS;
}

