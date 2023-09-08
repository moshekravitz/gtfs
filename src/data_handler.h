#pragma once
#include "../headers/ApiEntities.h"
#include "../headers/BL.h"
#include "../headers/FileEntities.h"
#include <fstream>
#include <iostream>
#include <math.h>
#include <sstream>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
using namespace std;

class DataHandler {
public:
  DataHandler() {
    // initialize data
    file_entities = FileEntities();
    file_entities.trips = new std::list<FileTrips>;
    file_entities.routes = new std::list<FileRoutes>;
    file_entities.shapes = new std::list<BShapes>;
    file_entities.stopInfo = new std::list<FileStopInfo>;
    file_entities.stopTime = new std::list<FileStopTime>;
    api_entities = ApiEntities();
    api_entities.extendedRoutes = new std::list<ExtendedRoutes>;
    api_entities.routes = new std::list<Routes>;
    api_entities.shapes = new std::list<Shape>;
    api_entities.stops = new std::list<StopInfo>;
    json_strs = JsonStrs();
    api_url = "http://localhost:5000/";
  }
  ~DataHandler() {}

  // getting the data from the file
  void load_data(const std::string &txt_path);

  void process_data();

  // serializing the data to json
  void serialize_data();

  // sending the data to the server
  void send_data();

  void send_only_stops() {
    file_entities = FileEntities();
    file_entities.stopInfo = new std::list<FileStopInfo>;
    this->load_stop_info(
        "/home/moshekravitz/Downloads/israel-public-transportation/stops.txt");

    api_entities = ApiEntities();
    api_entities.stops = new std::list<StopInfo>;

    this->to_api_stopInfo();

    string json_str = stop_info_to_json();

    std::ofstream json_file2;
    json_file2.open("/home/moshekravitz/Documents/gtfs/stops.json");
    json_file2 << json_str;
    json_file2.close();
    std::cout << "sending stop infos\n";
  }

private:
  FileEntities file_entities;
  ApiEntities api_entities;
  JsonStrs json_strs;
  string api_url;
  // TODO - delete this
  int counter;

  // getting the data from the file
  void load_routes(const std::string &txt_path);
  void load_trips(const std::string &txt_path);
  void load_stop_times(const std::string &txt_path);
  void load_stop_info(const std::string &txt_path);
  void load_shapes(const std::string &txt_path);

  // helper functions for load_shapes
  void encode_single_coord(const float coordinate, std::string &output_str);
  std::string
  encode_coordinates_list(const std::list<CoordinateEntity> &coordinates);

  // std::list<RouteTrips> process_trips(std::list<FileTrips> csv_trips);
  std::list<RouteTrips> process_trips();

  string get_interval(const string &str1, const string &str2);
  void to_api_routes();
  void to_api_stopInfo();
  void process_routes(list<RouteTrips> route_trips,
                      vector<pair<string, list<StopTime>>> stop_times);
  // void process_routes(list<RouteTrips> route_trips,
  // map<string,list<StopTime>> stop_times); map<string, list<StopTime>>
  // stopTimes_map();
  vector<pair<string, list<StopTime>>> stopTimes_map();
  map<int, string> convertListToMap(const list<Shape> &list);
  void stringfy_shapes();

  string extendedRoutes_to_json();
  string to_json(const list<StopTime> stop_times);
  string to_json(const list<BShapes> shapes);
  string to_json(const list<CoordinateEntity> coords);
  string stop_info_to_json();
  string routes_to_json();
  string shapes_to_json();
};
