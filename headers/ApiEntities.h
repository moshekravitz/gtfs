#pragma once
#include <string>
#include <map>
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

struct ExtendedRoutes
{
    int RouteId;
    string routeHeadSign;
    string ShapeStr;
    pair<int, string> TimeIntervals;
};

struct StopInfo
{
    int stopId;
    string headSign;
    double lan;
    double lon;
};
