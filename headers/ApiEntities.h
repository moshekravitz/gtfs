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

struct stopTime
{
    int stopId;
    string stopInterval;
};

struct ExtendedRoutes
{
    int RouteId;
    string routeHeadSign;
    string ShapeStr;
    std::list<stopTime> TimeIntervals;
};

struct StopInfo
{
    int stopId;
    string headSign;
    double lan;
    double lon;
};
