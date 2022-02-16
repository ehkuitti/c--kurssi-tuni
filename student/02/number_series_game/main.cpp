#include <iostream>

int main()
{
    double maara = 0;

    std::cout << "How many numbers would you like to have? ";
    std::cin >> maara;

    for (int luku = 1; luku <= maara; luku++ ) {

        if ((luku % 7 == 0) & (luku % 3 == 0)) {
            std::cout << "zip boing" << std::endl;
        }
        else if (luku % 7 == 0) {
            std::cout << "boing" << std::endl;
        }
        else if (luku % 3 == 0) {
            std::cout << "zip" << std::endl;
        }
        else {
            std::cout << luku << std::endl;
        }

    }

}


/*int main()
{
    double temp = 0;

    cout << "Enter a temperature: ";
    cin >> temp;

    cout << temp << " degrees Celsius is " << temp*1.8+32 << " degrees Fahrenheit" << endl;
    cout << temp << " degrees Fahrenheit is " << (temp-32)/1.8 << " degrees Celsius" << endl;

    return 0;
}
*/
