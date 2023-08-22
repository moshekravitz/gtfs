#pragma once
#include <string>
#include <list>

struct FileRoutes
{
    int RouteId;
    std::string RouteShortName;
    std::string RouteLongName;
};

struct FileTrips
{
    int RouteId;
    std::string TripId;
    std::string TripHeadsign;
    int DirectionId;
    int ShapeId;
};

struct FileStopTime
{
    std::string TripId;
    std::string ArrivalTime;
    std::string DepartureTime;
    int StopId;
    int StopSequence;
    int PickupType;
    int DropOffType;
    int ShapeDistTraveled;
};

struct FileStopInfo
{
    int StopId;

    int StopCode;

    std::string StopName;

    std::string StopDesc;

    double StopLat;

    double StopLon;

    int LocationType;

    int ParentStation;

    int ZoneId;
};
struct CoordinateEntity
{
    double longitude;
    double latitude;
};
struct FileShapes
{
    int ShapeId;
    double lon;
    double lat;
    int sequence;
};

struct FileEntities
{
    std::list<FileRoutes>* routes;
    std::list<FileTrips>* trips;
    std::list<FileStopTime>* stopTime;
    std::list<FileStopInfo>* stopInfo;
    //std::list<FileShapes>* shapes;
};
