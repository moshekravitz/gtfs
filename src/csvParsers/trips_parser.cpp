#include "../../headers/FileEntities.h"
#include "../../headers/checks.h"
#include <fstream>
#include <sstream>
#include <list>
using namespace std;

list<FileTrips> get_file_trips_list(const std::string& txt_path)
{
    std::ifstream trips_file;
    trips_file.open(txt_path);

    FileTrips trip;
    std::list<FileTrips> trips_list;

    std::string word, line_of_info;

    //checking first line for csv structure
    string structure[6] = {"route_id","service_id","trip_id","trip_headsign","direction_id","shape_id"};
    getline(trips_file, line_of_info);

    bool good_structure = check_csv_structure(structure, 6, line_of_info);
    if(!good_structure)
        throw "bad structure in routes";
    //end of check

    while (!trips_file.eof())
    {
        getline(trips_file, line_of_info);
        stringstream s(line_of_info);

        //route Id
        getline(s, word, ',');
        trip.RouteId = stoi(word);

        getline(s, word, ',');//Service Id

        //Trip Id
        getline(s, word, ',');
        trip.TripId = word;

        //TripHeadsign
        getline(s, word, ',');
        trip.TripHeadsign = word;

        //Direction Id
        getline(s, word, ',');
        trip.DirectionId = stoi(word);

        //Shape Id
        getline(s, word, ',');
        trip.ShapeId = stoi(word);

        trips_list.emplace_back(trip);
    }
    return trips_list;
}

