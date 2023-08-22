#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include "../headers/checks.h"
#include "../headers/parsers.h"
#include "../headers/BEntities.h"
#include "../headers/BL.h"

int test_process_routes()
{
    list<RouteTrips> route_trips = {
            {1, {"12","13","14"}},
            {2, {"22","23","24"}},
            {3, {"32","33","34"}},
            {4, {"42","43","44"}}
    };
    list<FileRoutes> file_routes = {
            {1, "600", "jeru"},
            {2, "412", "tel aviv"},
            {3, "464", "ashdod"},
            {4, "885", "mod"}
    };

    list<FileTrips> file_trips = {
            {1, "12", "bs-jr", 0, 4},
            {1, "13", "bs-jr", 0, 4},
            {1, "14", "bs-jr", 0, 4},
            {2, "23", "bs-ta", 1, 5},
            {2, "22", "bs-ta", 1, 5},
            {2, "24", "bs-ta", 1, 5},
            {3, "33", "bs-as", 0, 6},
            {3, "32", "bs-as", 0, 6},
            {4, "43", "bs-md", 1, 7}
    };

    //map<std::string, map<int, string>> stop_times = {
    map<std::string, std::list<StopTime>> stop_times = {
            {"12", {{1, "12:30:00"}, {2, "12:33:00"}, {3, "12:50:00"}}},
            {"13", {{1, "12:30:00"}, {2, "12:33:00"}, {3, "12:50:00"}}},
            {"14", {{1, "12:30:00"}, {2, "12:33:00"}, {3, "12:50:00"}}},
            {"23", {{1, "21:00:00"}, {2, "21:20:00"}, {3, "21:33:00"}}},
            {"22", {{1, "21:00:00"}, {2, "21:20:00"}, {3, "21:33:00"}}},
            {"24", {{1, "21:00:00"}, {2, "21:20:00"}, {3, "21:33:00"}}},
            {"33", {{1, "22:00:00"}, {2, "22:20:00"}, {3, "22:33:00"}}},
            {"32", {{1, "22:00:00"}, {2, "22:20:00"}, {3, "22:33:00"}}},
            {"43", {{1, "23:00:00"}, {2, "23:20:00"}, {3, "23:33:00"}}}
    };

    list<Shape> shapes = {
            {5, "12;13;14;15;16;17;18;19;20"},
            {4, "22;23;24;25;26;27;28;29;30"},
            {7, "32;33;34;35;36;37;38;39;40"},
            {6, "42;43;44;45;46;47;48;49;50"}
    };

    std::list<ExtendedRoutes> asdf = process_routes(route_trips, file_routes, file_trips, stop_times, shapes);

    for(auto it : asdf)
    {
        cout << "id = " << it.RouteId << endl;
        cout << "shape = " << it.ShapeStr << endl;
        cout << "trip headsign = " << it.routeHeadSign << endl;
        for(auto it2 : it.StopInfo)
        {
            cout << "   stop id = " << it2.stopId << endl;
            cout << "   time = " << it2.stopInterval << endl;
            //cout << endl;
        }
        cout << endl;
    }

    return 0;
}

int main()
{
/*

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

   /*
    //---------------------------stop times fixes-----------------------------

    std::set<std::string> asdf =  get_problematic_stops_times(final_stopTimes);
    std::cout << "stops size: " << final_stopTimes.size() << std::endl;
    std::cout << "problematic stops size: " << asdf.size() << std::endl;

    //------------------------------------------------------------------------
    
    */


    std::list<FileTrips> file_trips;
    std::map<std::string, std::list<StopTime>> stop_times;
    std::list<Shape> shapes;

    std::list<ExtendedRoutes> extendedRoutesList = process_routes(route_trips, file_routes, file_trips, stop_times, shapes);

    return 0;
}
