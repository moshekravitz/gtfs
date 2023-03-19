#pragma once

#include <string>

struct BTrips
{
    int RouteId;
    std::string TripId;
    std::string TripHeadsign;
    int DirectionId;
    int ShapeId;
    std::string ArrivalTime;
    std::string DepartureTime;
    int StopId;
    int StopSequence;
    int PickupType;
    int DropOffType;
    int ShapeDistTraveled;
};

struct BCoordinateEntity
{
    double longitude;
    double latitude;
};
