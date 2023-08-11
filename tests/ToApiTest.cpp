#include <iostream>
#include <string>
#include <list>
#include "../headers/BL.h"

using namespace std;


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
        {2, "13", "bs-ta", 1, 5},
        {3, "14", "bs-as", 0, 6},
        {4, "15", "bs-md", 1, 7}
    };
    map<std::string, map<int, string>> stop_times = {
        {"12", {{1, "12:30:00"}, {2, "12:33:00"}, {3, "12:50:00"}}},
        {"13", {{1, "21:00:00"}, {2, "21:20:00"}, {3, "21:33:00"}}},
        {"14", {{1, "22:00:00"}, {2, "22:20:00"}, {3, "22:33:00"}}},
        {"15", {{1, "23:00:00"}, {2, "23:20:00"}, {3, "23:33:00"}}}
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
        for(auto it2 : it.TimeIntervals)
        {
            cout << "stop id = " << it2.first << endl;
            cout << "time = " << it2.second << endl;
            cout << endl;
        }
        cout << endl;
    }

    return 0;
}
