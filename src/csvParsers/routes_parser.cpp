#include "../../headers/FileEntities.h"
#include "../../headers/checks.h"
#include <fstream>
#include <sstream>
#include <list>
using namespace std;

list<FileRoutes> get_file_routes_list(const std::string& txt_path)
{
    std::ifstream routes_file;
    routes_file.open(txt_path);

    FileRoutes route;
    list<FileRoutes> routes_list;

    string word, line_of_info;

    //checking first line for csv structure
    string structure[7] = {"route_id","agency_id","route_short_name","route_long_name","route_desc","route_type","route_color"};
    getline(routes_file, line_of_info);

    bool good_structure = check_csv_structure(structure, 7, line_of_info);
    if(!good_structure)
        throw "bad structure in routes";
    //end of check

    while (!routes_file.eof())
    {

        stringstream s(line_of_info);

        //route Id
        getline(s, word, ',');
        route.RouteId = !word.empty() ?stoi(word) : throw "missing route id";

        getline(s, word, ',');

        //route short name
        getline(s, word, ',');
        route.RouteShortName = word;

        //route long name
        getline(s, word, ',');
        route.RouteLongName = word;

        routes_list.emplace_back(route);

    }
    return routes_list;
}
