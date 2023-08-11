#pragma once
#include <iostream>
#include <math.h>
#include <math.h>
#include <fstream>
#include <sstream>
#include "../headers/FileEntities.h"
#include "../headers/BL.h"

class DataHandler
{
    public:
        DataHandler();
        ~DataHandler();

        //getting the data from the file
        void load_data(const std::string& txt_path);

        void process_data();

        //serializing the data to json
        void serialize_data();
        
        //sending the data to the server
        void send_data();

    private:
    FileEntities file_entities;
    ApiEntities api_entities;
    JsonStrs json_strs;

    //getting the data from the file
    void load_routes(const std::string& txt_path);
    void load_trips(const std::string& txt_path);
    void load_stop_times(const std::string& txt_path);
    void load_stop_info(const std::string& txt_path);
    void load_shapes(const std::string& txt_path);

    //helper functions for load_shapes
    void encode_single_coord(const float coordinate, std::string& output_str);
    std::string encode_coordinates_list(const std::list<CoordinateEntity>& coordinates);

    std::list<RouteTrips> process_trips(std::list<FileTrips> csv_trips);


    string get_interval(const string& str1, const string& str2);
    list<Routes> to_api_routes(list<FileRoutes> fileRoutes);
    list<StopInfo> to_api_stopInfo(list<FileStopInfo> fileStops);
    list<ExtendedRoutes> process_routes(list<RouteTrips> route_trips, list<FileRoutes> file_routes, list<FileTrips> file_trips, map<string, list<StopTime>> stop_times, list<Shape> shapes);
    map<string, list<StopTime>> stopTimes_map(list<FileStopTime> fileStops);
    map<int, string> convertListToMap(const list<Shape>& list);


    string to_json(const list<ExtendedRoutes>& routes);
    string to_json(const list<StopTime>& routes);
    string to_json(const list<StopInfo>& stops);
    string to_json(const list<Routes>& routes);
    string to_json(const list<Shape>& shapes);
};
