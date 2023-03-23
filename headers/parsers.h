#pragma once
#include "FileEntities.h"
#include "checks.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <list>

std::list<FileTrips> get_file_trips_list(const std::string& txt_path);
