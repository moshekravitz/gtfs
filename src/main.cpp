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

int main()
{
    std::cout << "   starting\n";
    DataHandler dataHandler;

    char const* asdf = "C:/Users/moshe kravitz/Downloads/Telegram Desktop/israel-public-transportation-few";
    std::cout << "starting\n";

    dataHandler.load_data(asdf);
    try
    {
        std::cout << "loading data...\n";
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
