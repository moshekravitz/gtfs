#include "../../headers/checks.h"

using namespace std;

list<FileStopTime> get_file_stop_time_list(const std::string& txt_path)
{
    std::ifstream stop_times_file;
    stop_times_file.open(txt_path);

    if (!stop_times_file.is_open()) {
        throw std::runtime_error("Failed to open file\n");
    }

    FileStopTime stopTime;
    //std::list<FileStopTime> trip_stop_time;

    std::string word, line_of_info, shape_str,tripId, last_trip_id = "";
    int  last_stop_sequence = 0;

    list<FileStopTime> stopsTimes_list;

    //checking first line for csv structure
    string structure[8] = {"trip_id","arrival_time","departure_time","stop_id","stop_sequence","pickup_type","drop_off_type","shape_dist_traveled"};
    getline(stop_times_file, line_of_info);

    std::cout << "line of info: " << line_of_info << endl;

    bool good_structure = check_csv_structure(structure, 8, line_of_info);
    if(!good_structure)
        throw std::runtime_error("bad structure in routes");
    //end of check

    stringstream s;
    getline(stop_times_file, line_of_info);
    s << line_of_info;

    while (!stop_times_file.eof())
    {
        //Trip Id
        getline(s, word, ',');
        stopTime.TripId = word ;

        //Arrival Time
        getline(s, word, ',');
        stopTime.ArrivalTime = word;

        //Departure Time
        getline(s, word, ',');
        stopTime.DepartureTime = word;

        //Stop Id
        getline(s, word, ',');
        stopTime.StopId = word.empty() ? 0 : stoi(word);

        //Stop Sequence
        getline(s, word, ',');
        stopTime.StopSequence = word.empty() ? 0 : stoi(word);

        //Pickup Type
        getline(s, word, ',');
        stopTime.PickupType = word.empty() ? 0 : stoi(word);

        //Drop Off Type
        getline(s, word, ',');
        stopTime.DropOffType = word.empty() ? 0 : stoi(word);

        //Shape Id
        getline(s, word, ',');
        stopTime.ShapeDistTraveled = word.empty() ? 0 : stoi(word);

        stopsTimes_list.push_back(stopTime);

        getline(stop_times_file, line_of_info);
        s.clear();
        s << line_of_info;

        /*
        if(last_trip_id != tripId)
        {
            std::cout << "last_trip_id: " << last_trip_id << " current: " << tripId << endl;
            if(stopTime.StopSequence != 1)
            {
                throw "shape error";
            }
            if(last_trip_id != "")
            {
                stopsTimes_list[last_trip_id] = stopTime;
            }
            last_trip_id = tripId;
            last_stop_sequence = 1;
        }
        else
        {
            last_stop_sequence++;
            std::cout << "last_stop_sequence: " << last_stop_sequence << " current: " << stopTime.StopSequence << endl;
            if(last_stop_sequence != stopTime.StopSequence)
                throw "shape error";
        }

        trip_stop_time.push_back(stopTime);
         */
    }

    stop_times_file.close();

    return stopsTimes_list;
}
