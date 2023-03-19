#include "../../headers/checks.h"

bool check_csv_structure(std::string* structure, int size, std::string line_of_info)
{
    std::string word;
    std::stringstream s(line_of_info);
    for(int i = 0; i < size; i++)
    {
        getline(s, word, ',');//route Id
        if(word != structure[i])
            return false;
    }
}
