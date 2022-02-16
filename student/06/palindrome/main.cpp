#include <iostream>
#include <string>
#ifndef RECURSIVE_FUNC
#define RECURSIVE_FUNC
#endif

bool palindrome_recursive(std::string s)
{
  RECURSIVE_FUNC
  // Do not remove RECURSIVE_FUNC declaration, it's necessary for automatic testing to work
  // ------------
    unsigned ekaMerkki = 0;
    unsigned vikaMerkki = s.length()-1;
    std::string::size_type pituus = 0;
    pituus = s.length();

    if (pituus <= 1) {
        return true;
    }

    else if (s.at(ekaMerkki) == s.at(vikaMerkki)) //On mahdollista, että on palindromi, sillä ensimmäinen ja viimeinen merkki ovat samoja
    {
        s = s.erase(vikaMerkki, 1);
        s = s.erase(ekaMerkki, 1);

        return palindrome_recursive(s);
    }

    return false; //("else") False jo nyt, koska ensimmäisen ja viimeisen oltava samoja ollakseen palindromi
}

// Do not modify rest of the code, or the automated testing won't work.
#ifndef UNIT_TESTING
int main()
{
    std::cout << "Enter a word: ";
    std::string word;
    std::cin >> word;

    if(palindrome_recursive(word)){
        std::cout << word << " is a palindrome" << std::endl;
    } else {
        std::cout << word << " is not a palindrome" << std::endl;
    }
}
#endif

//    unsigned long i = 0;

//    if (s.length() < 2) {
//        return false;
//    }
