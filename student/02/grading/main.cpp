#include <iostream>

using namespace std;

// Before passing automated tests, do not touch the values of the following
// constants, even if they differ from those you see in Plussa.
// At the end of the course, if you use this program to count your final grade,
// you should update the constants to make them identical with those in Plussa.
unsigned int MAX_N_POINTS = 780;
unsigned int MAX_G_POINTS = 100;

unsigned int score_from_weekly_exercises(unsigned int n, unsigned int g) //laskee viikkotehtävien pisteet prosentteina
{
    float n_only_percentage = (n * 100) / MAX_N_POINTS; //n-tehtävät prosenteiksi maksimipisteistä
    float n_and_g_percentage = ((n + g) * 100.0)/(MAX_N_POINTS + MAX_G_POINTS); //n ja g prosenteiksi vastaavista maksimeista
    float better_percentage = std::max(n_only_percentage, n_and_g_percentage);//tuleeko prosentuaalisesti parempi arvosana pelkillä n-tehtävillä vaiko yhteenlaskettuna
    if(better_percentage < 50.0) return 0; //arvotaulukko, annettu prosentti palauttaa vastaavan arvosanan
    if(better_percentage < 60.0) return 1;
    if(better_percentage < 70.0) return 2;
    if(better_percentage < 80.0) return 3;
    if(better_percentage < 90.0) return 4;
    return 5; //"else" arvosana 5
}

unsigned int score_from_gui_exercises(unsigned int g) //gui-tehtävien pisteet prosentteina
{
    float score_g = (g * 100.0) / MAX_G_POINTS; //muunnetaan prosenteiksi maksimista
    if(score_g < 30.0) return 2; //palautetaan pisteitä taulukon mukaisesti
    if(score_g < 40.0) return 3;
    if(score_g < 50.0) return 4;
    return 5; //"else" paras arvosana (5)
}

unsigned int score_from_projects(unsigned int p) //projektipisteet (tarkat luvut, ei prosentteja)
{
    if(p < 51) return 0; //palautetaan taulukkoa vastaavat arvosanat
    if(p < 75) return 1;
    if(p < 125) return 2;
    if(p < 150) return 3;
    if(p < 175) return 4;
    return 5; //"else" palautetaan paras arvosana (5)
}

unsigned int round(float fp) //liukulukujen pyöristäminen positiivisiksi kokonaisluvuksi
{
    unsigned int rounded_value = static_cast<unsigned int>(fp); //pakotetaan positiiviseksi kokonaisluvuksi
    if(fp - rounded_value > 0.5) //tarkistetaan pienenikö luku yli 0.5:llä, kun olisi pitänyt pyöristää ylöspäin
    {
        return rounded_value + 1; //pyöristetään ylöspäin eli lisätään 1, jolloin intin kanssa tulee seuraava tasaluku
    }
    return rounded_value; //palautetaan pyöristetty arvo joka tapauksessa
}

unsigned int count_final_grade(float mean, unsigned int g) //lasketaan lopullinen arvosana (ottaa vastaan keskiarvon ja g-pisteet)
{
    unsigned int rounded_mean = round(mean);
    if(rounded_mean < 3)
    {
        return rounded_mean;
    }
    if(rounded_mean < 4 and g >= 3)
    {
        return rounded_mean;
    }
    if(rounded_mean < 5 and g >= 4)
    {
        return rounded_mean;
    }
    if (rounded_mean == 5 and g == 5)
    {
        return rounded_mean;
    }
    return g;
}

int main()
{

    unsigned int n = 0;
    unsigned int g = 0;
    unsigned int p = 0;
    unsigned int e = 0;
    cout << "Enter N points, G points, P points: ";
    cin >> n;
    cin >> g;
    cin >> p;
    cout << "Enter exam grade (if no exam, enter zero): ";
    cin >> e;

    float mean = 0.0;
    int score_w = score_from_weekly_exercises(n, g);
    int score_p = score_from_projects(p);

    if(score_w == 0 or score_p == 0)
    {
        cout << "The final grade is 0" << endl;
        return 0;
    }
    if(e == 0)
    {
        mean = ((score_w + score_p) / 2.0) - 2.0;
    }
    else
    {
        mean = (score_w + score_p + e) / 3.0;
    }

    cout << "The final grade is "
         << count_final_grade(mean, score_from_gui_exercises(g))
         << endl;

    return 0;
}
