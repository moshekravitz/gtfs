#pragma once

#include "../headers/FileEntities.h"
#include "../headers/BEntities.h"
#include <list>

std::list<RouteTrips> process_trips(std::list<FileTrips> csv_trips);
