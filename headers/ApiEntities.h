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
    std::list<Routes> routes;
    std::list<Shape> shapes;
    std::list<StopInfo> stops;
    std::list<ExtendedRoutes> extendedRoutes;
};

struct JsonStrs
{
    string Routes;
    string Shapes;
    string Stops;
    string ExtendedRoutes;
};
