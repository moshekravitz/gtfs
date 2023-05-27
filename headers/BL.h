#pragma once

#include "../headers/FileEntities.h"
#include "../headers/BEntities.h"
#include <set>
#include <list>

std::list<RouteTrips> process_trips(std::list<FileTrips> csv_trips);
std::set<std::string> get_problematic_stops_times(std::map<std::string, std::map<int,std::string>> stop_times);
