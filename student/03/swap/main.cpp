#include <cstdlib>
#include <iostream>
#include <deque>

void swap(int& x, int& y) { //"&" lähettää parametreina VIIITTAUKSET i:hin ja j:hin. jos ilman, lähettää kopiot arvoista
                            // jolloin ei muuta arvoja halutusti
    int temp;
    temp = x;
    x = y;
    y = temp;

    // C++ antaa palauttaa VAIN YHDEN ARVON, joten käytettävä viitteitä(&) useamman arvon kanssa.
}

#ifndef UNIT_TESTING
int main()
{
    std::cout << "Enter an integer: ";
    int i = 0;
    std::cin >> i;

    std::cout << "Enter another integer: ";
    int j = 0;
    std::cin >> j;

    swap(i, j);
    std::cout << "The integers are " << i << " and " << j << std::endl;

    return EXIT_SUCCESS;
}
#endif
