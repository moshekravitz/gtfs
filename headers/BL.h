#pragma once

#include "../headers/FileEntities.h"
#include "../headers/ApiEntities.h"
#include "../headers/BEntities.h"
#include "../tests/ToApiTest.cpp"
#include <set>
#include <list>

std::list<RouteTrips> process_trips(std::list<FileTrips> csv_trips);
std::set<std::string> get_problematic_stops_times(std::map<std::string, std::map<int,std::string>> stop_times);

std::list<ExtendedRoutes> process_routes(std::list<RouteTrips> route_trips, std::list<FileRoutes> file_routes, std::list<FileTrips> file_trips, std::map<std::string, std::list<StopTime>> stop_times, std::list<Shape> shapes);
