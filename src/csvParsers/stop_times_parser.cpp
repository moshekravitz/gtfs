#include "../../headers/FileEntities.h"
#include "../../headers/checks.h"
#include <fstream>
#include <sstream>
#include <list>
#include <map>
using namespace std;

map<string, string> get_file_stop_time_list(const std::string& txt_path)
{
    std::ifstream stop_times_file;
    stop_times_file.open(txt_path);

    FileStopTime stopTime;
    std::list<FileStopTime> trip_stop_time;

    std::string word, line_of_info, shape_str,tripId, last_trip_id = "";
    int  last_stop_sequence = 0;

    map<string, string> stopsTimes_list;

    //checking first line for csv structure
    string structure[8] = {"trip_id","arrival_time","departure_time","stop_id","stop_sequence","pickup_type","drop_off_type","shape_dist_traveled"};
    getline(stop_times_file, line_of_info);

    bool good_structure = check_csv_structure(structure, 8, line_of_info);
    if(!good_structure)
        throw "bad structure in routes";
    //end of check

    while (!stop_times_file.eof())
    {

        getline(stop_times_file, line_of_info);
        stringstream s(line_of_info);

        //Trip Id
        getline(s, word, ',');
        tripId = word;

        //Arrival Time
        getline(s, word, ',');
        stopTime.ArrivalTime = word;

        //Departure Time
        getline(s, word, ',');
        stopTime.DepartureTime = word;

        //Stop Id
        getline(s, word, ',');
        stopTime.StopId = stoi(word);

        //Stop Sequence
        getline(s, word, ',');
        stopTime.StopSequence = stoi(word);

        //Pickup Type
        getline(s, word, ',');
        stopTime.PickupType = stoi(word);

        //Drop Off Type
        getline(s, word, ',');
        stopTime.DropOffType = stoi(word);

        //Shape Id
        getline(s, word, ',');
        stopTime.ShapeDistTraveled = stoi(word);

        if(last_trip_id != tripId)
        {
            if(stopTime.StopSequence != 1)
                throw "shape error";
            if(last_trip_id != "")
            {
                stopsTimes_list[tripId] = shape_str;
            }
            last_trip_id = tripId;
            last_stop_sequence = 1;
        }
        else
        {
            last_stop_sequence++;
            if(last_stop_sequence != stopTime.StopSequence)
                throw "shape error";
        }
        trip_stop_time.emplace_back(stopTime);
    }
    return stopsTimes_list;
}
