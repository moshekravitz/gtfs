cmake_minimum_required(VERSION 3.24)
project(gtfs)

set(CMAKE_CXX_STANDARD 17)

add_executable(gtfs src/main.cpp headers/ApiEntities.h src/csvParsers/routes_parser.cpp headers/FileEntities.h src/csvParsers/trips_parser.cpp src/csvParsers/stop_times_parser.cpp src/csvParsers/checks.cpp headers/checks.h src/csvParsers/stop_info_parser.cpp src/csvParsers/shapes_parser.cpp headers/BEntities.h src/trip_processing.cpp src/ToApiEntities.cpp headers/parsers.h headers/BL.h tests/ToApiTest.cpp)