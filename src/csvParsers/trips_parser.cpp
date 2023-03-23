#include "../../headers/parsers.h"
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

    int asdf = 0;
    while (!trips_file.eof())
    {
        getline(trips_file, line_of_info);
        line_of_info.erase(std::remove_if(line_of_info.begin(), line_of_info.end(), [](char c) { return c >= 0 && c <= 31; }), line_of_info.end());
        stringstream s(line_of_info);

        //route Id
        getline(s, word, ',');
        trip.RouteId = word.empty() ? 0 : stoi(word);

        getline(s, word, ',');//Service Id

        //Trip Id
        getline(s, word, ',');
        trip.TripId = word;

        //TripHeadsign
        getline(s, word, ',');
        trip.TripHeadsign = word;

        //Direction Id
        getline(s, word, ',');
        trip.DirectionId = word.empty() ? 0 : stoi(word);

        //Shape Id
        getline(s, word, ',');
        trip.ShapeId = word.empty() ? 0 : stoi(word);

        trips_list.emplace_back(trip);
        asdf++;
    }


    std::cout << "\n--------------------\n";
    std::cout << "trips" << asdf << "\n";
    std::cout << "--------------------\n";
    return trips_list;
}

