#include "data_handler.h"
#include <new>

void DataHandler::process_data() {

  std::cout << "processing data\n";

  std::cout << "stringifying shapes\n";
  stringfy_shapes();
  std::cout << "got stringifyed shapes\n";

  cout << "here3" << endl;
  if (this->file_entities.trips == nullptr)
    cout << "null";
  else
    cout << "not null";
  list<FileTrips> asdf = *this->file_entities.trips;

  list<RouteTrips> route_and_trips = process_trips();
  std::cout << "processed trips\n";
  // stopTimes_map(*this->file_entities.stop_times;
  std::cout << "processing creating stop times map\n";
  to_api_routes();
  std::cout << "got api routes\n";
  to_api_stopInfo();
  std::cout << "got api stop info\n";

  // delete file entities to free memory
  // delete this->file_entities.routes;
  // delete this->file_entities.stopInfo;
  // delete this->file_entities.trips;

  vector<pair<string, list<StopTime>>> stop_times_map;

  stop_times_map = stopTimes_map();

  std::cout << "got stop time map\n";
  process_routes(route_and_trips, stop_times_map);
  std::cout << "processed routes\n";
}
string DataHandler::get_interval(const string &str1, const string &str2) {
  std::stringstream s1(str1);
  std::stringstream s2(str2);
  std::string asdf, res_str = "";
  // short int sec1, sec2, min1, min2, hour1, hour2, res_sec, res_min, res_hour;
  unsigned char sec1, sec2, min1, min2, hour1, hour2, res_sec, res_min,
      res_hour;

  getline(s1, asdf, ':');
  hour1 = stoi(asdf);

  getline(s1, asdf, ':');
  min1 = stoi(asdf);

  getline(s1, asdf, ':');
  sec1 = stoi(asdf);

  getline(s2, asdf, ':');
  hour2 = stoi(asdf);

  getline(s2, asdf, ':');
  min2 = stoi(asdf);

  getline(s2, asdf, ':');
  sec2 = stoi(asdf);

  if (sec1 > sec2) {
    sec2 += 60;
    min2 -= 1;
    if (min2 == -1) {
      min2 = 59;
      hour2 -= 1;
      if (hour2 == -1)
        hour2 = 23;
    }
  }
  res_sec = sec2 - sec1;

  if (min1 > min2) {
    min2 += 60;
    hour2 -= 1;
    if (hour2 == -1)
      hour2 = 23;
  }

  res_min = min2 - min1;
  res_hour = hour2 - hour1;

  if (res_hour < 10)
    res_str = "0" + to_string(res_hour);
  else
    res_str = to_string(res_hour);
  if (res_min < 10)
    res_str += ":0" + to_string(res_min);
  else
    res_str += ":" + to_string(res_min);
  if (res_sec < 10)
    res_str += ":0" + to_string(res_sec);
  else
    res_str += ":" + to_string(res_sec);
  return res_str;
}

void DataHandler::to_api_routes() {
  for (auto route : *file_entities.routes) {
    Routes api_single_route = {route.RouteId, route.RouteShortName,
                               route.RouteLongName};
    api_entities.routes->push_back(api_single_route);
  }
}

void DataHandler::to_api_stopInfo() {
  list<StopInfo> api_stops;
  for (auto stop : *file_entities.stopInfo) {
    StopInfo api_single_stop = {stop.StopId, stop.StopName, stop.StopLat,
                                stop.StopLon};
    api_entities.stops->push_back(api_single_stop);
  }
}

vector<pair<string, list<StopTime>>> DataHandler::stopTimes_map() {
  std::string trip_id = file_entities.stopTime->front().TripId;
  std::string last_time, current_time, interval;
  // map<string, list<StopTime>> trip_stops;//stopInfo id, intervals
  vector<pair<string, list<StopTime>>> trip_stops; // stopInfo id, intervals
  list<StopTime> *stop_times = new list<StopTime>;
  int stopId;

  int flag = 0;
  cout << "looping on stop times\n";

  for (auto stop : *file_entities.stopTime) {
    if (trip_stops.size() > trip_stops.max_size() - 100) {
      throw std::string("trip_stops size exceeded max size");
    }
    counter++;
    stopId = stop.StopId;
    if (stop.StopSequence == 1) {
      // interval = "00:00:00";
      interval = stop.DepartureTime;

      if (interval != "") {
        // trip_stops[trip_id] = stop_times;
        try {
          trip_stops.push_back({trip_id, *stop_times});
        } catch (std::bad_alloc &e) {
          cout << "bad alloc: " << e.what() << endl;
          cout << "trip_stops push_back exception\n";
          throw e;
        } catch (std::exception &e) {
          cout << "exception: " << e.what() << endl;
          cout << "trip_stops push_back exception\n";
          throw e;
        } catch (std::string &e) {
          cout << "trip_stops push_back exception\n";
          throw e;
        } catch (...) {
          throw std::string("trip_stops push_back exception\n");
        }
        try {
          stop_times = new list<StopTime>;
        } catch (std::exception &e) {
          cout << "new list stop times exception: " << e.what() << endl;
          throw e;
        } catch (...) {
          throw std::string("stop_times allocation exception\n");
        }
      }

      trip_id = stop.TripId;
    } else {
      // interval = get_interval(last_time,stop.DepartureTime);
      interval = stop.DepartureTime;
    }

    string sequence_and_interval =
        to_string(stop.StopSequence) + ";" + interval;

    // stop_times[stopId] = sequence_and_interval;
    stop_times->push_back({stopId, sequence_and_interval});

    last_time = stop.DepartureTime;
  }
  cout << "done with stop times map\n";
  return trip_stops;
}

std::map<int, std::string>
DataHandler::convertListToMap(const std::list<Shape> &list) {
  std::map<int, std::string> resultMap;

  for (const auto &item : list) {
    resultMap[item.ShapeId] = item.shape;
  }

  return resultMap;
}

// void DataHandler::process_routes(std::list<RouteTrips> route_trips,
// std::map<std::string, std::list<StopTime>> stop_times)
void DataHandler::process_routes(
    std::list<RouteTrips> route_trips,
    std::vector<pair<std::string, std::list<StopTime>>> stop_times) {
  // std::map<int, std::string> shapes_map = convertListToMap(shapes);
  // std::list<ExtendedRoutes> extended_routes;
  ExtendedRoutes temp_route;
  RouteTrips tempRouteTrip;

  for (auto route = file_entities.routes->begin();route != file_entities.routes->end(); route++) 
  {
    temp_route.RouteId = route->RouteId;
    for (auto route_trips_it = route_trips.begin();route_trips_it != route_trips.end(); route_trips_it++) {
      if (route_trips_it->routeId == route->RouteId) {
        tempRouteTrip = *route_trips_it;
        route_trips.erase(route_trips_it);
        break;
      }
    }
    // temp_route.RouteId = route->routeId;

    FileTrips temp_trip;
    bool broke = false;
    for (auto file_trip = file_entities.trips->begin();file_trip != file_entities.trips->end(); file_trip++) {
      for (auto trip = tempRouteTrip.trips.begin();trip != tempRouteTrip.trips.end(); trip++) {
        if (*trip == file_trip->TripId) {
          temp_trip = *file_trip;
          broke = true;
          break;
        }
      }
      if (broke) {
        file_entities.trips->erase(file_trip);
        break;
      }
    }

    temp_route.routeHeadSign = temp_trip.TripHeadsign;

    for (auto shapesIt = api_entities.shapes->begin();
         shapesIt != api_entities.shapes->end(); shapesIt++) {
      if (shapesIt->ShapeId == temp_trip.ShapeId) {
        temp_route.ShapeStr = shapesIt->shape;
        //remove shapesIt
        api_entities.shapes->erase(shapesIt);
        break;
      }
    }

    // find in map and return it instead of iteration
    for (auto stop_time = stop_times.begin(); stop_time != stop_times.end();
         stop_time++) {
      if (stop_time->first == temp_trip.TripId) {
        // temp_route.TimeIntervals = stop_time->second;
        temp_route.stopTime = stop_time->second;
        break;
      }
    }
    api_entities.extendedRoutes->push_back(temp_route);
  }
}

void DataHandler::encode_single_coord(const float coordinate,
                                      string &output_str) {
  const int factor = pow(10, 5);
  int32_t int_coord = (int32_t)(coordinate * factor);
  int_coord <<= (int32_t)1;

  if (int_coord < 0) {
    int_coord = ~int_coord;
  }

  int index = 0;
  for (index = 0; output_str[index]; index++) {
  }

  for (index; int_coord >= 0x20; index++) {
    output_str += static_cast<char>(
        static_cast<char>(0x20 | (int32_t)(int_coord & 0x1f)) + 63);
    int_coord >>= (int32_t)5;
  }
  output_str += static_cast<char>(int_coord + 63);
}

string DataHandler::encode_coordinates_list(
    const list<CoordinateEntity> &coordinates) {
  string output_char_arr = {};

  //////////////////string output_str = output_char_arr;

  list<CoordinateEntity>::const_iterator it = coordinates.begin();

  CoordinateEntity last_coordinate = *it;
  encode_single_coord(static_cast<float>(it->latitude), output_char_arr);
  encode_single_coord(static_cast<float>(it->longitude), output_char_arr);

  for (; it != coordinates.end(); ++it) {
    encode_single_coord(
        static_cast<float>(it->latitude - last_coordinate.latitude),
        output_char_arr);
    encode_single_coord(
        static_cast<float>(it->longitude - last_coordinate.longitude),
        output_char_arr);
    last_coordinate = *it;
  }
  return output_char_arr;
}
void DataHandler::stringfy_shapes() {
  // process the shapes from file entities to api entities with multiple
  // processes

  //pid_t pid = fork();
  int half_size = file_entities.shapes->size() / 2;
  for(list<BShapes>::iterator it1 = file_entities.shapes->begin(); it1 != file_entities.shapes->end();it1++)
  {
    string shape_str = encode_coordinates_list(it1->coords);
    api_entities.shapes->emplace_back(Shape{it1->ShapeId, shape_str});
  }
}
