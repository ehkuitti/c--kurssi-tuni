#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstring>

const int MAKSIMIKOKO = 80;

bool calculator(int first_operand, int second_operand, int& tulos, char operaattori)
{
    switch (operaattori)
    {
        case '*':
            tulos = first_operand*second_operand;
            return true;
        case '/':
            if (second_operand == 0)
            {
                std::cerr << "Error: Division by zero" << std::endl;
                return false;
            }
            tulos = first_operand/second_operand;
            return true;
        case '+':
            tulos = first_operand+second_operand;
            return true;
        case '-':
            tulos = first_operand-second_operand;
            return true;
    }

    return false;
}

int main()
{
    //Kommentti
    std::string syote = "";
    std::cout << "Input an expression in reverse Polish notation (end with #):"
              << std::endl
              << "EXPR> ";
    getline(std::cin, syote);

    int syotteenPituus = syote.length(); //Syötteen pituus muuttujana
    int merkkiTaulukko[MAKSIMIKOKO]; //Merkkitaulukko, jonka koko 80
    int tulos = 0;
    int numerolukumaara = 0;
    //strcpy(merkkiTaulukko, syote.c_str());

    if (!isdigit(syote[0]))
    {
        std::cerr << "Error: Expression must start with a number" << std::endl;
        return EXIT_FAILURE;
    }

    for (char merkki : syote)
    {
        if (merkki == ' ')
        {
            continue;
        }

        else if (isdigit(merkki))
        {
            merkkiTaulukko[numerolukumaara] = merkki-'0';
            numerolukumaara += 1;
            continue;
        }

        else if (merkki == '#')
        {
            if (numerolukumaara > 1)
            {
                std::cerr << "Error: Too few operators" << std::endl;
                return EXIT_FAILURE;
            }
            if (numerolukumaara == 1)
            {
                std::cout << "Correct: " << merkkiTaulukko[0] << " is the result" << std::endl;
                return EXIT_SUCCESS;
            }
        }

        else
        {
            if(merkki != '*' and merkki != '+' and merkki!= '/' and merkki != '-' and merkki != '#')
            {
                std::cerr << "Error: Unknown character" << std::endl;
                return EXIT_FAILURE;
            }
            else if (merkki == '*' or merkki == '+' or merkki == '/' or merkki == '-' or merkki == '#')
            {
                if (numerolukumaara < 2)
                {
                    std::cerr << "Error: Too few operands" << std::endl;
                    return EXIT_FAILURE;
                }
                int first_operand = merkkiTaulukko[numerolukumaara-2];
                int second_operand = merkkiTaulukko[numerolukumaara-1];
                if(!calculator(first_operand, second_operand, tulos, merkki))
                {
                    return EXIT_FAILURE;
                }
                merkkiTaulukko[numerolukumaara-2] = tulos;
                numerolukumaara -= 1;
            }
            continue;
        }
    }

    if (syotteenPituus > MAKSIMIKOKO) //Jos syöte on yli 80 merkkiä pitkä
    {
        std::cerr << "Error: too many arguments" << std::endl; //Kielletty operaatio
        return EXIT_FAILURE; //Ohjelma kaatuu
    }

    for (unsigned long y = 0; y < sizeof(merkkiTaulukko); y++)
    {

    }

    /*//Suluissa -1, koska halutaan jättää laskuista pois #
    if ((operaattorilukumaara-1) >= numerolukumaara)
    {
        //Operand == numero
        std::cerr << "Error: Too few operands";
        return EXIT_FAILURE;
    }

    if ((operaattorilukumaara-1) < (numerolukumaara-1))
    {
        std::cerr << "Error: Too few operators";
        return EXIT_FAILURE;
    }



    for (unsigned long i = 0; i < sizeof(merkkiTaulukko); i++)
    {

        if (isdigit(merkkiTaulukko[i])) //Jos indeksistä nolla löytyi luku
        {
            j++;
            kokonaislukuTaulukko[j] = merkkiTaulukko[i];
            continue;
        }

        else if (merkkiTaulukko[i] == '+')
        {
            tulos = kokonaislukuTaulukko[i-2] + kokonaislukuTaulukko[i-1];
        }

        else if (merkkiTaulukko[i] == '-')
        {
            tulos = kokonaislukuTaulukko[0] - kokonaislukuTaulukko[1];
        }

    }
*/
    return EXIT_SUCCESS;


    //Jos input oli yli 80 merkkiä pitkä
/*
    if (parts.size() > TAULUKON_KOKO) {
        std::cout << "Error: too many arguments";
    }
*/
}
