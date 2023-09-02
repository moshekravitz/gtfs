#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include "../headers/checks.h"
#include "../headers/parsers.h"
#include "../headers/BEntities.h"
#include "../headers/BL.h"
#include "data_handler.h"

void fix_files(std::list<std::string> txt_paths);

int main()
{
    std::cout << "   starting\n";
    DataHandler dataHandler;


    std::string asdf = "/home/moshekravitz/Downloads/israel-public-transportation-few";
    std::cout << "starting\n";
    fix_files({asdf + "/routes.txt",asdf + "/trips.txt",asdf + "/shapes.txt",asdf + "/stop_times.txt",asdf + "/stops.txt"});//asdf + "/stop_info.txt",

    try
    {
        std::cout << "loading data...\n";
        dataHandler.load_data(asdf);
        std::cout << "data loaded\n";
    }
    catch(...)
    {
        std::cout << "load data failed " << std::endl;
    }
    try
    {
        std::cout << "processing data...\n";
        dataHandler.process_data();
    }
    catch(...)
    {
        std::cout << "process data failed " << std::endl;
    }
    try
    {
        std::cout << "serialize data...\n";
        dataHandler.serialize_data();
    }
    catch(...)
    {
        std::cout << "serialize data failed " << std::endl;
    }
    try
    {
        std::cout << "sending data...\n";
        dataHandler.send_data();
    }
    catch(...)
    {
        std::cout << "send data failed " << std::endl;
    }
    return 0;
}


void fix_file(const std::string& txt_path)
{
}

void fix_files(std::list<std::string> txt_paths)
{
    std::list<std::string>::iterator it;
    for(it = txt_paths.begin(); it != txt_paths.end(); it++)
    {
        //check for wired characters and removed from the file
        std::string txt_path = *it;
        cout << "fixing: " << txt_path << endl;
        std::ifstream file(txt_path);
        char ch;
        std::string new_file = txt_path + "_new";
        std::ofstream new_file_stream(new_file);
        while(file.get(ch))
        {
            if(ch == '\r') {}
            else if(ch >= 0 && ch <= 31 && ch != 10)
            {
                std::cout << "found wired character " << ch << std::endl;
                new_file_stream << ch;
            }
            else
            {
                new_file_stream << ch;
            }
        }
        file.close();
        new_file_stream.close();
        remove(txt_path.c_str());
        rename(new_file.c_str(), txt_path.c_str());
    }
}

