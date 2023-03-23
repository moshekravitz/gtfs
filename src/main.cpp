#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "../headers/checks.h"
#include "../headers/parsers.h"
#include "../headers/BEntities.h"
#include "../headers/BL.h"

int main()
{
    //-------------------------------stop times-------------------------------
    std::string stop_times_file_path = "/home/moshekravitz/asdf/stop_times.txt";

    std::list<FileStopTime> stopTims_test;
    try {
        stopTims_test = get_file_stop_time_list(stop_times_file_path);
        std::map<std::string, std::map<int,std::string>> final_stopTimes = stopTimes_map(stopTims_test);
    }
    catch(const char* error) {
        std::cout << error << std::endl;
    }
    //------------------------------------------------------------------------

    //---------------------------------trips----------------------------------
    std::string trips_file_path = "/home/moshekravitz/israel-public-transportation/trips.txt";
    std::list<RouteTrips>  final_stopTimes;
    std::list<FileTrips > trips_test;
    try {
        trips_test = get_file_trips_list(trips_file_path);
        std::cout << "got file trips\n";
        final_stopTimes = process_trips(trips_test);
        std::cout << "got processed trips\n";
    }
    catch(const char* error) {
        std::cout << error << std::endl;
    }
    /*
    for(auto it : final_stopTimes)
    {
        std::cout << it.routeId << std::endl;
        for(auto it2 : it.trips)
        {
            std::cout << "    " << it2 << std::endl;
        }
    }
     */
    //------------------------------------------------------------------------

    return 0;
}
