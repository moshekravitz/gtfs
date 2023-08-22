#pragma once
#include <string>
#include <map>
#include <list>
using namespace std;

struct Routes
{
    int RouteId;
    string RouteShortName;
    string RouteLongName;
};

struct Coordinates
{
    double lan;
    double lon;
};

struct Shape
{
    int ShapeId;
    string shape;
};


struct StopTime
{
    int stopId;
    string stopInterval;
}; 

struct ExtendedRoutes
{
    int RouteId;
    string routeHeadSign;
    string ShapeStr;
    //std::map<int, std::string> TimeIntervals;
    std::list<StopTime> stopTime;
};

struct StopInfo
{
    int stopId;
    string headSign;
    double lan;
    double lon;
};

struct ApiEntities
{
    std::list<Routes> Routes;
    std::list<Shape> Shapes;
    std::list<StopInfo> Stops;
    std::list<ExtendedRoutes> ExtendedRoutes;
};

struct JsonStrs
{
    string Routes;
    string Shapes;
    string Stops;
    string ExtendedRoutes;
};
