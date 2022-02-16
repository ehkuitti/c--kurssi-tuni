//--------------------------------------------------
//  COMP.CS.110 Ohjelmointi 2: Rakenteet -pohjakoodi
//  Copyright © 2021
//--------------------------------------------------
/* Kurssikeskus
 *
 * Kuvaus:
 *
 * Ohjelman tarkoitus on esittää CSV-tyylillä formatoidusta tiedostosta erilai-
 * silla tavoilla järjestettynä. Ohjelman vaatii toimiakseen input-tiedoston,
 * joka voi olla .csv tai myös esim. txt, kunhan formatointi on CSV-mäinen
 * eli noudattaa asia1,asia2,asia3,asia4 tyylistä formatointia. Erotinmerkkinä
 * ei kuitenkaan tämän ohjelman tapauksessa käytetä commaa eli pilkkua, vaan
 * semi-colonia eli puolipistettä. Kun ohjelman ajaa Qt Creatorissa, on input-
 * tiedoston löydyttävä ko. projektin build-kansiosta QT:n oletusasetuksilla.
 *
 * Käyttäjän antaman syötetiedoston tulee täyttää tietyt ehdot, jotta se kelpaa
 * ohjelmalle. Ensinnäkään syötetiedostossa ei saa olla yhteensä yli neljää
 * kenttää. Yksittäinen kenttä ei myöskään saa olla tyhjä ja viimeisessä
 * kentässä ei saa olla kuin kokonaisluku tai teksti "full". Viimeinen kenttä
 * ei myöskään saa loppua puolipisteeseen.
 *
 * Käyttäjän antaessa ohjelma käy sen läpi ja tallentaa sen sisältämän datan
 * mappiin vaatimusten mukaisesti. Mappi sisältää parina stringin sekä vektorin
 * strukteineen (valmiiksi annettu struct). Mikäli kaikki etenee odotetusti, au-
 * keaa käyttäjälle komentorivi-ikkuna, johon voi syöttää ennaltapäätettyjä
 * komentoja. Käyttäjän antaessa komentoja tiedostosta tullut data järjestellään
 * yhä uudelleen erilaisiin rakenteisiin, jotta ne voidaan tulostaa käyttäjälle
 * halutulla tavalla. Lopulta ohjelman suoritus loppuu joko virhetilanteeseen,
 * quit-komentoon tai rastin klikkaamisen ohjelmaikkunan yläkulmasta.
 *
 * Ohjelman kirjoittaja
 * Nimi: Eetu Kuittinen
 * Opiskelijanumero: 150541820
 * Käyttäjätunnus: fkeeku
 * E-Mail: eetu.kuittinen@tuni.fi
 *
 * Huomioita ohjelmasta ja sen toteutuksesta:
 * Lähtökohtaisesti parametrit tuodaan viitteinä, jotta datan duplikointia ei
 * tapahtuisi.
 * */

#include <algorithm>
#include <set>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <sstream>

//Vakio kertoo täyden kurssin osallistujamäärän.
const int COURSE_FULL = 50;
//Vakio toimii erotinmerkkinä syötetiedoston lukemisessa.
const char CSV_FIELD_DELIMITER = ';';

struct Course
{
    std::string name;
    std::string location;
    int enrollments;
};

using namespace std;

// Jakaa annetun merkkijonon str annetun merkin delimiter erottelemiin osiin
// ja palauttaa osat vektorissa.
// Jos erotinmerkki on lainausmerkkien sisällä, erotinmerkistä ei välitetä,
// eli osaa olla erottelematta lainausmerkkien sisällä olevan tekstin.
//
// Splits the given string str into parts separated by the given delimiter
// and returns the parts in a vector.
// If the delimiter appears inside quatation, ignores delimiter,
// i.e. does not split quoted text.
std::vector<std::string> split_ignoring_quoted_delim(const std::string& str,
                                                     char delimiter)
{
    std::vector<std::string> result = {""}; //Tyhjän vektorin, joka ottaa stringejä
    bool inside_quotation = false;
    for(char current_char : str)
    {
        if(current_char == '"')
        {
            inside_quotation = not inside_quotation;
        }
        else if(current_char == delimiter and not inside_quotation)
        {
            result.push_back("");
        }
        else
        {
            result.back().push_back(current_char);
        }
    }
    if(result.back() == "")
    {
        result.erase(--result.end());
    }
    return result;
}


/* Funktiossa otetaan parametrinä vastaan string-viite input-tiedostoon.
 * Tämä annetaan ifstreamille parametrinä. Jos tiedosto ei aukea, palautetaan
 * false, jolloin mainissa tulostuu error. Muussa tapauksessa pushbackataan
 * linejen edestä. Parametreinä tiedostopolku ja rivit (string-vektori)
 * viitteinä.
 * */
bool read_input_file(const std::string& filepath,
                     std::vector<std::string>& lines)
{

    std::ifstream input_file_in(filepath);

    //Jos tiedosto EI OLE auki
    if (!input_file_in.is_open())
    {
        return false;
    }

    std::string line = "";

    /* Muussa tapuauksessa vektoria laajennetaan niin kauan kun tiedostossa
     * riittää dataa*/
    while (std::getline(input_file_in, line))
    {
        lines.push_back(line);
    }

    //Tiedosto käsitelty onnistuneesti
    return true;

}
/* Funktio tarkistaa, onko kenttiä tarpeeksi. Palauttaa totuusarvon
 * ("kyllä" tai "ei"). Parametrinä kenttävektorin viite.
 * */
bool validate_field_count(const std::vector<std::string>& fields)
{
    //Kenttiä oltava neljä, jotta tiedostoa voidaan käsitellä tällä ohjelmalla
    if (fields.size() != 4)
    {
        return false;
    }

    return true;

}

/* Funktio tarkistaa, onko vektorin mikään kenttä tyhjä. Palauttaa totuusarvon,
 * jonka ollessa false käsittely epäonnistuu. Paramentrinä kenttien viite.
 * */
bool validate_no_empty_fields(const std::vector<std::string>& fields)
{

    /* Käydään looppaamalla läpi kaikki kentät. Mikäli löytyy kenttä, joka on
     * tyhjä, palautuu false, josta aiheutuu error*/
    for (const auto& field : fields)
    {
        if (field.empty())
        {
            return false;
        }
    }

    return true;
}

/* Funktiossa toteutetaan available-komento. Ottaa parametreinä kurssiteema-
 * mapin viitteen, looppaa arvot läpi sisäkkäisissä silmukoissa, sekä luo uuden
 * mapin setillä, joka täytetään tulostuksen aakkostamista varten.
 * Ei palauta arvoa.
 * */
void available_command (std::map<std::string,
                        std::vector<Course>>& courses_by_theme)
{
    /* Jokainen kenttä tallennetaan omaksi muuttujakseen helpompaa käsittelyä
     * varten*/
    std::string theme = "";
    std::string name = "";
    std::string location = "";

    std::map<std::string, std::map<std::string,
        std::set<std::string>>> map_of_contents;

    for (auto& pair : courses_by_theme)
    {
        theme = pair.first;
        for (Course& course : pair.second)
        {
            location = course.location;
            if (course.enrollments == COURSE_FULL)
            {
                continue;
            }

            if (map_of_contents.find(theme) == map_of_contents.end()) {
                map_of_contents.insert(
                {theme, std::map<std::string, std::set<std::string>>()});
            }

            if (map_of_contents.at(theme).find(location)
                == map_of_contents.at(theme).end()) {
                map_of_contents.at(theme).insert({location,
                                                  std::set<std::string>()});
            }
            map_of_contents.at(theme).at(location).insert(course.name);
        }
    }

    for (auto& pair1 : map_of_contents)
    {
        theme = pair1.first;
        for (auto& pair2 : pair1.second)
        {
            location = pair2.first;
            for (auto& name2 : pair2.second)
            {
                std::cout << theme
                          << " : "
                          << location
                          << " : "
                          << name2
                          << std::endl;
            }
        }
    }

}

/* Funtio vertaa kahta kurssia Course-structilla tehtävää kurssia (parametrit),
 * palauttaa totuusarvon sen mukaan, kumman lokaatio tulee aikaisemmin.
 * */
bool vector_checker (Course course1, Course course2)
{
    return course1.location < course2.location;
}

/* Funktio komentoa courses_in_location varten. Parametreina input_readerin
 * split_vektorin viite sekä mappi, jota käydään läpi looppaamalla. Ei
 * paluuarvoa. Mappi otetaan vastaan kopiona, jotta data voidaan järjes-
 * tellä uudelleen ilman vaikutusta alkuperäiseen dataan.
 * */
void courses_in_location_command(std::vector<std::string>& split_vector,
                                 std::map<std::string,
                                 std::vector<Course>> courses_by_theme)
{
    std::set<std::string> course_name_set = {};
    std::string location = split_vector.at(1);

    for (auto& pair : courses_by_theme)
    {
        for (Course& new_course : pair.second)
        {
            if (new_course.location == location)
            {
                course_name_set.insert(new_course.name);
            }
        }
    }

    /* Jos setin pituus ei tässä vaiheessa ole yli nollan,
     * lokaatiota ei löydy, koska muuten setti olisi pidempi kuin nolla*/
    if (course_name_set.size() == 0)
    {
        std::cerr << "Error: unknown location" << std::endl;
        return;
    }

    for (auto& name : course_name_set)
    {
        std::cout << name << std::endl;
    }
}

/* Funktio komentoa courses_in_theme_commandia varten.
 * Parametreina input_readerin split_vektorin viite sekä mappi,
 * jota käydään läpi looppaamalla. Ei paluuarvoa.
 * */
void courses_in_theme_command(std::vector<std::string>& split_vector,
                              std::map<std::string,
                              std::vector<Course>> courses_by_theme)
{
    std::string theme = split_vector.at(1);

    if (courses_by_theme.find(theme) == courses_by_theme.end())
    {
        std::cerr << "Error: unknown theme" << std::endl;
        return;
    }

    else
    {
        std::vector<Course> new_vector = courses_by_theme.at(theme);
        std::sort(new_vector.begin(), new_vector.end(), vector_checker);
        for (auto& cell : new_vector)
        {
            std::cout << cell.location << " : " << cell.name << std::endl;
        }
    }

}

/* Funktio parsii tiedoston rivit ja kutsuu edellisiä funktioita tarkistaakseen,
 * palauttaako kumpikaan falsea (virhetilanne). Tämän lisäksi tallentaa fields-
 * vektorin eri arvot omiksi muuttujikseen sekä tarkistaa, että onko kurssi jo
 * täynnä. Pushbackkaa vektoria for-loopissa, tehden alkioille tilaa vektoriin.
 * Funktio on yksi pitkä for-looppi, josta löytyy myös sisäkkäinen for-loop.
 * */
bool parse_input_lines(std::vector<std::string>& lines,
                       std::map<std::string,
                       std::vector<Course>>& courses_by_theme)
{
    for (const std::string& line : lines)
    {
        std::vector<std::string> fields
            = split_ignoring_quoted_delim(line, CSV_FIELD_DELIMITER);

        /* Eri kentät määritellään omiksi muuttujikseen, jotta niitä voidaan
         * myöhemmin kutsua muuttujan nimellä.*/
        std::string& theme = fields.at(0);
        std::string& name = fields.at(1);
        std::string& location = fields.at(2);
        int enrollments = 0;

        /* Jos jompikumpi funktioista palauttaa falsen eli tulee virhetilanne,
         * palautuu myös tästä funtkiosta false. Tällöin kyseessä virhetilanne.
         */
        if (!validate_field_count(fields)
            || !validate_no_empty_fields(fields))
        {
            return false;
        }

        /* Jos indeksin 3 paikalla lukee input-tiedostossa full, enrollments
         * saa arvokseen 50 (täyden kurssin vakion arvo).*/
        if (fields.at(3) == "full")
        {
            enrollments = COURSE_FULL;
        }

        else
        {
            std::istringstream enrollments_in(fields.at(3));
            if (!(enrollments_in >> enrollments))
            {
                return false;
            }

        }

        /* Luodaan uusi kurssi-strukti tiedoston alussa määritetyn struct-pohjan
         * avulla.*/
        Course new_course{name, location, enrollments};

        //courses_by_theme.try_emplace({});

        std::vector<Course>& courses_under_theme = courses_by_theme[theme];

        //Iteraattori käy läpi courses_under_themen alusta lähtien
        auto it = courses_under_theme.begin();
        for ( ; it != courses_under_theme.end(); ++it)
        {
            if (it->name == new_course.name
                && it->location == new_course.location)
            {
                break;
            }
        }

        if (it != courses_under_theme.end()) {
            courses_under_theme.erase(it);
        }

        /* Pushbackataan vektoria, jotta sinne mahtuu yhteensä 4 eri tietoa.
         * Tulostetaan jokainen tieto erikseen ja tiedon jälkeen rivinvaihto,
         * paitsi enrollmentsin jälkeen lisäksi myös tyhjä rivi.
         * */
        courses_under_theme.push_back(new_course);
    }
    return true;
}

/* Funtkio teemakomentoa varten. Ei palauta arvona, parametrina kurssiteemamapin
 * viite. Käydään mappia läpi for-loopilla.
 * */
void theme_command (std::map<std::string,
                    std::vector<Course>>& courses_by_theme)
{
        for (auto& info_pair : courses_by_theme)
        {
            std::cout << info_pair.first << "\n";
        }
}

/* Funktio kurssikomennolle. Ottaa vastaan input_readerein sekä kurssiteemamapin
 * viiteet. Ei paluuarvoa, tarkistaa löytyykö teemaa ja jos löytyy, järjestää
 * sen uudelleen looppaamalla. Valittu set yhdesksi tietorakenteista, sillä
 * setissä alkiot järjestetään automaattisesti aakkosjärjestyksessä. Lopuksi
 * tulostetaan arvot.
 * */
void courses_command (std::vector<std::string>& split_vector,
                      std::map<std::string,
                      std::vector<Course>>& courses_by_theme)
{
      std::string theme = split_vector.at(2);
      std::string location = split_vector.at(1);
      std::set<std::string> location_set = {};
      bool locationChecker = false;
      std::stringstream int_to_string;
      std::string enrollments_string = "";

      if (courses_by_theme.find(theme) == courses_by_theme.end())
      {
          std::cerr << "Error: unknown theme" << std::endl;
      }

      else
      {
          std::vector<Course> theme_vector = courses_by_theme[theme];

          for (auto& course : theme_vector)
          {
              if (course.location == location)
              {
                  locationChecker = true;
                  std::string name_enrollments = course.name;
                  name_enrollments.append(" --- ");
                  if (course.enrollments == COURSE_FULL)
                  {
                      name_enrollments.append("full");
                  }

                  else
                  {
                      name_enrollments.append(std::to_string
                                              (course.enrollments));
                      name_enrollments.append(" enrollments");
                  }

                  location_set.insert(name_enrollments);
              }
          }

          //Jos sijaintia ei löydy, printataan error
          if (locationChecker == false)
          {
              std::cerr << "Error: unknown location" << std::endl;
              return;
          }
          /* Muussa tapauksessa loopataan setin läpi ja tulostetaan rivi joka
           * kierroksella*/
          for (auto& line : location_set)
          {
              std::cout << line << std::endl;
          }
      }

}

/* Peruutuskomentofuntkio. Ei palauta arvoa, param. viitteet split_vektoriin
 * ja kurssiteemamappiin. Funktiossa luodaan uusi tyhjä vektori, joka täytetään
 * arvoilla vailla peruttua kurssia. Lopulta tulostetaan viesti joko onnistu-
 * misesta tai epäonnistumisesta.
 * */
void cancel_command (std::vector<std::string>& split_vector,
                     std::map<std::string,
                     std::vector<Course>>& courses_by_theme)
{

    std::map<std::string, std::vector<Course>> copy = {};
    std::string name = split_vector.at(1);
    bool course_found = false;

    for (auto& pair : courses_by_theme)
    {
        copy.insert({pair.first, {}});
        for (Course& new_course : pair.second)
        {
            //Jos kurssia ei löydy split_vektorin indeksistä yksi
            if (new_course.name != name)
            {
                copy.at(pair.first).push_back(new_course);
            }

            else
            {
                course_found = true;
            }

        }
    }

    //Jos kurssia ei löydy
    if (course_found == false)
    {
        std::cerr << "Error: unknown course" << std::endl;
    }

    else
    {
        courses_by_theme = copy;
        std::cout << name << " cancelled in all locations" << std::endl;
    }
}

/* Ei palauta arvoa, parametrina kurssiteemamappi. Käytetään settiä datan
 * aakkostamiseen. Käydään läpi mappia ja täytetään settiä tilanteen mukaan.
 * */
void favorite_theme_command (std::map<std::string,
                       std::vector<Course>>& courses_by_theme)
{

    if (courses_by_theme.size() == 0)
    {
        std::cerr << "No enrollments" << std::endl;
        return;
    }

    std::set<std::string> favorite_set;
    int max_enrollments = 0;

    for (auto& pair : courses_by_theme)
    {
        int amount_of_participants = 0;
        for (Course& new_course : pair.second)
        {
            amount_of_participants += new_course.enrollments;
        }

        if (amount_of_participants > max_enrollments)
        {
            max_enrollments = amount_of_participants;
            favorite_set = {};
            favorite_set.insert(pair.first);
        }
        else if (amount_of_participants == max_enrollments)
        {
            favorite_set.insert(pair.first);
        }
    }

    std::cout << max_enrollments << " enrollments in themes" << std::endl;

    for (auto& theme : favorite_set)
    {
        std::cout << "--- " << theme << std::endl;
    }

}

/* Funktio tarkistaa, että vektori on oikean kokoinen. Mikäli näin on, palaute-
 * taan true eli "ongelma löytyi". Muussa tapauksessa palautuu false. Paramet-
 * rina splitattu vektori sekä input_readerissä määritelty command.
 * */
bool command_error_checker (std::string& command,
                            std::vector<std::string>& split_vector)
{

    int sz = split_vector.size();

    //Jos käyttäjä ei syöttänyt kolmea arvoa
    if (sz != 3)
    {
        std::cerr << "Error: error in command " << command << std::endl;
        return true;
    }

    //Ei ongelmaa
    else
    {
        return false;
    }

}

/* Funktion tehtävänä on toimia syötteenlukijana. Funktion alussa kysytään
 * syötettä, jonka jälkeen ohjelman suoritus tapahtuu muissa funtkioissa, jotka
 * vastaavat erilaisista komentojen ajamisista. Ei palauta arvoa, ottaa vastaan
 * kurssivektorin parametrina sekä stringejä sisältävän input_file_lines vekto-
 * rin. Funktiossa luodaan splitvektori, johon tallennetaan komento sekä halutut
 * kyselyt. Ei palauta arvoa, parametrina viite kurssiteemavektoriin.
 */
void input_reader (std::map<std::string,
                   std::vector<Course>>& courses_by_theme)
{

    while (true)
    {
        std::string input = "";
        std::cout << "> ";
        std::getline(std::cin, input);

        //Ohjelman suoritus loppuu mainissa quit-komennolla
        if (input == "quit")
        {
            return;
        }

        std::vector<std::string> split_vector
        = split_ignoring_quoted_delim(input, ' ');

        //Jos ei ole annettu komentoa, tehdään uusi kierros while-loopissa
        if (split_vector.size() == 0)
        {
            continue;
        }

        //Syötteen ensimmäinen alkio on syötetty komento
        std::string command = split_vector.at(0);

        //Tarkistetaan, onko komento themes
        if (command == "themes")
        {
            theme_command(courses_by_theme);
            continue;

        }


        //Tarkistetaan, onko komento courses
        else if (command == "courses")
        {
            //Jos arvoja oli alle 3, tulee error ja uusi kierros whilea
            if (command_error_checker(command, split_vector))
            {
                //Hypätään muiden ehtojen yli seuraavalle while-kierrokselle
                continue;
            }
            else
            {
                courses_command(split_vector, courses_by_theme);
                continue;
            }
        }

        //Tarkistetaan, onko komento available
        else if (command == "available")
        {
            available_command(courses_by_theme);
            continue;
        }

        else if (command == "courses_in_theme")
        {
            courses_in_theme_command(split_vector, courses_by_theme);
            continue;
        }

        else if (command == "courses_in_location")
        {
            courses_in_location_command(split_vector, courses_by_theme);
            continue;
        }

        else if (command == "favorite_theme")
        {
            favorite_theme_command( courses_by_theme);
            continue;
        }

        else if (command == "cancel")
        {
            cancel_command(split_vector, courses_by_theme);
            continue;
        }

        /* Mikäli komento ei ole mikään edellämainituista, printataan error
         * merkkinä tuntemattomasta komennosta.
         * */
        else
        {
            std::cerr << "Error: Unknown command: " << command << std::endl;
        }

    }
}

/* Main-funtio. Mainissa toteutetaan vain ne toiminnot, joista ei erikseen tar-
 * vita funktioita.
 * */
int main()
{

    std::string input_filepath = "";
    std::cout << "Input file: ";
    std::getline(std::cin, input_filepath);

    std::vector<std::string> input_file_lines = {};

    //Jos tiedoston lukeminen epäonnistuu
    if (!read_input_file(input_filepath, input_file_lines))
    {
        std::cerr << "Error: the input file cannot be opened\n";
        return EXIT_FAILURE;
    }

    /* Käytettävä päätietorakenne map, johon tulee string sekä vektori
     * täytettynä valmiiksi annetulla structilla*/
    std::map<std::string, std::vector<Course>> courses_by_theme;
    //Jos löytyy
    if (!parse_input_lines(input_file_lines, courses_by_theme))
    {
        std::cerr << "Error: empty field";
        return EXIT_FAILURE;
    }

    /* Syötteen lukeminen tiedoston onnistuneen avaamisen jälkeen tapahtuu
     * input_reader -fukntiossa*/
    input_reader(courses_by_theme);

    return EXIT_SUCCESS;
}
