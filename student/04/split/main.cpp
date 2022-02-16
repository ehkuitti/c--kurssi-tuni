#include <iostream>
#include <string>
#include <vector>

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

      /*size_t separatorViimeisellaIndeksilla;
      separatorViimeisellaIndeksilla = line.find_last_of(separator);

      for (unsigned long i = 0; i < line.length(); ++i) {
          if ((line[i] == separator) && (line[i+1] == separator)){
              line.replace(line[i], line[i+1], "\n");
              break;
              return vektori;
          }
          if ((line[0] == separator) && (line[separatorViimeisellaIndeksilla] == separator)){
              line.replace(line[0], line[separatorViimeisellaIndeksilla], "\n");
              break;
              return vektori;
          }
        }
      return vektori;*/
}
int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector<std::string> parts = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
