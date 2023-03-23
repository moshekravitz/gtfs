#pragma once

#include <string>
#include <map>
#include <list>

struct BTrips
{
    std::string TripId;
    int RouteId;
    std::string TripHeadsign;
    int ShapeId;
    std::string ArrivalTime;
    std::string DepartureTime;
    std::map<int, int> StopId;
};

struct RouteTrips
{
    int routeId;
    std::list<std::string> trips;
};


struct BCoordinateEntity
{
    double longitude;
    double latitude;
};
