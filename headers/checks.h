#pragma once
#include "FileEntities.h"
#include <string>
#include <sstream>
#include <iostream>
#include <map>
#include <fstream>
#include <list>

bool check_csv_structure(std::string* structure, int size, std::string line_of_info);
std::string get_interval(const std::string& str1, const std::string& str2);
std::list<FileStopTime> get_file_stop_time_list(const std::string& txt_path);
std::map<std::string, std::map<int, std::string>> stopTimes_map(std::list<FileStopTime> fileStops);
