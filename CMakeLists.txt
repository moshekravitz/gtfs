cmake_minimum_required(VERSION 3.24)
project(gtfs)

set(CMAKE_CXX_STANDARD 17)

#add cpr vcpkg
find_package(cpr CONFIG REQUIRED)

add_executable(gtfs src/main.cpp headers/ApiEntities.h  headers/FileEntities.h src/checks.cpp headers/checks.h headers/BEntities.h headers/parsers.h headers/BL.h tests/ToApiTest.cpp src/data_loader.cpp src/data_processing.cpp src/serializer.cpp src/http.cpp)

target_link_libraries(gtfs PRIVATE cpr::cpr)
