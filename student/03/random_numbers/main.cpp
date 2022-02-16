#include <iostream>
#include <random>
#include <string>

using namespace std;

void produce_random_numbers(unsigned int lower, unsigned int upper, unsigned seed);

int main()
{
    unsigned int lower_bound, upper_bound, seed_value;
    cout << "Enter a lower bound: ";
    cin >> lower_bound;
    cout << "Enter an upper bound: ";
    cin >> upper_bound;

    if(lower_bound >= upper_bound)
    {
        cout << "The upper bound must be strictly greater than the lower bound"
             << endl;
        return EXIT_FAILURE;
    }
    else {
        cout << "Enter a seed value: ";
        cin >> seed_value;
        cout << endl;
    }

    produce_random_numbers(lower_bound, upper_bound, seed_value);

    return EXIT_SUCCESS;
}

void produce_random_numbers(unsigned int lower, unsigned int upper, unsigned seed)
{
    default_random_engine gen(seed);

    char merkki;

    do {
        uniform_int_distribution<int> distr(lower, upper);
        std::cout << "Your drawn random number is " << distr(gen) << std::endl;

        cout << "Press q to quit or any other key to continue: ";
        cin >> merkki;
        cout << endl;
    } while (merkki != 'q');
}
