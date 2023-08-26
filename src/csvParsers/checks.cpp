#include <algorithm>
#include "../../headers/checks.h"

bool check_csv_structure(std::string* structure, int size, std::string line_of_info)
{
    if(line_of_info.at(0) < 'A' || line_of_info.at(0) > 'z')
        line_of_info = line_of_info.substr(3);

    line_of_info.erase(std::remove_if(line_of_info.begin(), line_of_info.end(), [](char c) { return c >= 0 && c <= 31; }), line_of_info.end());
    std::string word;
    std::stringstream s(line_of_info);
    for(int i = 0; i < size; i++)
    {
        getline(s, word, ',');//route Id
        if(word != structure[i])
        {
            return false;
        }
    }
    return true;
}

/*
bool comp_strs(std::string s1, std::string s2)
{
    if(s1.length() != s2.length())
    {
        std::cout << s1.length() << " " << s2.length() << std::endl;
        return false;
    }

    std::cout << "same size\n";
    for(int i = 0; i < s1.length(); i++)
    {
        //std:: cout << s1[i] << " " << s2[i] << std::endl;
        if(s1[i] != s2[i])
            return false;
    }
    return true;
}*/