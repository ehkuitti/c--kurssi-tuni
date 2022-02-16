#include <iostream>
#include <stdio.h>
#include <math.h>
#include <climits>


//Koodi
using namespace std;

int main()
{
    int luku = 0;

    cout << "Enter a number: ";
    cin >> luku;

    int kuutio = luku * luku * luku;

    if (kuutio > INT_MAX || kuutio < INT_MIN) {
        cout << "Luku on suurempi kuin suurin sallittu arvo" << endl;
    }
    else {
        cout << "The cube of " << luku << " is " << kuutio << "." << endl;
    }
}







/*
  #include <iostream>
#include <string.h>

using namespace std;

int main()
{
    double temp = 0;

    cout << "Enter a temperature: ";
    cin >> temp;

    cout << temp << " degrees Celsius is " << temp*1.8+32 << " degrees Fahrenheit" << endl;
    cout << temp << " degrees Fahrenheit is " << (temp-32)/1.8 << " degrees Celsius" << endl;

    return 0;
}


 */
