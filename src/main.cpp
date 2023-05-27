#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include "../headers/checks.h"
#include "../headers/parsers.h"
#include "../headers/BEntities.h"
#include "../headers/BL.h"

int main()
{
    //-------------------------------stop times-------------------------------
    std::string stop_times_file_path = "/home/moshekravitz/asdf/stop_times.txt";

    std::list<FileStopTime> stopTims_test;
    std::map<std::string, std::map<int,std::string>> final_stopTimes;
    try {
        stopTims_test = get_file_stop_time_list(stop_times_file_path);
        final_stopTimes = stopTimes_map(stopTims_test);
    }
    catch(const char* error) {
        std::cout << error << std::endl;
    }
    //------------------------------------------------------------------------

    //---------------------------------trips----------------------------------
    std::string trips_file_path = "/home/moshekravitz/israel-public-transportation/trips.txt";
    std::list<RouteTrips>  final_RouteTrips;
    std::list<FileTrips > trips_test;
    try {
        trips_test = get_file_trips_list(trips_file_path);
        std::cout << "got file trips\n";
        final_RouteTrips = process_trips(trips_test);
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

    //---------------------------stop times fixes-----------------------------

    std::set<std::string> asdf =  get_problematic_stops_times(final_stopTimes);
    std::cout << "stops size: " << final_stopTimes.size() << std::endl;
    std::cout << "problematic stops size: " << asdf.size() << std::endl;

    //------------------------------------------------------------------------

    return 0;
}
