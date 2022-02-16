#include <iostream>
#include <string>

using namespace std;

int main()
{
    std::string encryption_key;
    std::cout << "Enter the encryption key: ";
    std::cin >> encryption_key;

    if (encryption_key.length() != 26)
    {
        std::cout << "Error! The encryption key must contain 26 characters.\n";
        return 1;
    }

    for (size_t i = 0; i < encryption_key.length(); i += 1)
    {
        char char_to_check = encryption_key.at(i);
        if (char_to_check < 'a' || char_to_check > 'z')
        {
            std::cout << "Error! The encryption key must contain only lower case characters.";
            return 1;
        }
    }

    for (char char_to_find = 'a'; char_to_find <= 'z'; char_to_find += 1)
    {
        size_t pos = encryption_key.find(char_to_find);
        if (pos == std::string::npos)
        {
            std::cout << "Error! The encryption key must contain all alphabets a-z.\n";
            return EXIT_FAILURE;
        }
    }


    std::string text_to_encrypt;
    std::cout << "Enter the text to be encrypted: ";
    std::cin >> text_to_encrypt;

    for (size_t i = 0; i < text_to_encrypt.length(); i += 1)
    {
        char char_to_check = text_to_encrypt.at(i);
        if (char_to_check < 'a' || char_to_check > 'z')
        {
            std::cout << "Error! The text to be encrypted must contain only lower case characters.";
            return 1;
        }
    }

    std::string encrypted_text;

    for (size_t i = 0; i < text_to_encrypt.length(); i += 1)
    {
        char unencrypted_char = text_to_encrypt.at(i);
        size_t j = unencrypted_char - 'a';
        char encrypted_char = encryption_key.at(j);
        encrypted_text += encrypted_char;
    }

    std::cout << "Encrypted text: " << encrypted_text << "\n";
    return EXIT_SUCCESS;
}
