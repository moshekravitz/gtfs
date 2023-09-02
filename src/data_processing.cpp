#include "data_handler.h"

void DataHandler::process_data(){
    std::cout << "processing data\n";
    if(this->file_entities.trips == nullptr)
       cout << "null";
    else
        cout << "not null";
    list<FileTrips> asdf = *this->file_entities.trips;

    list<RouteTrips> route_and_trips = process_trips();
    std::cout << "processed trips\n";
    // stopTimes_map(*this->file_entities.stop_times;
    std::cout << "processing creating stop times map\n";
    map<string, list<StopTime>> stop_times_map = stopTimes_map();
    std::cout << "got stop time map\n";
    to_api_routes();
    std::cout << "got api routes\n";
    to_api_stopInfo();
    std::cout << "got api stop info\n";
    process_routes(route_and_trips, stop_times_map);
    std::cout << "processed routes\n";

}
string DataHandler::get_interval(const string& str1, const string& str2)
{
    std::stringstream s1(str1);
    std::stringstream s2(str2);
    std::string asdf, res_str = "";
    //short int sec1, sec2, min1, min2, hour1, hour2, res_sec, res_min, res_hour;
    unsigned char sec1, sec2, min1, min2, hour1, hour2, res_sec, res_min, res_hour;



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

    if(sec1 > sec2)
    {
        sec2 += 60;
        min2 -= 1;
        if(min2 == -1)
        {
            min2 = 59;
            hour2 -= 1;
            if(hour2 == -1)
                hour2 = 23;
        }
    }
    res_sec = sec2 - sec1;

    if(min1 > min2)
    {
        min2 += 60;
        hour2 -= 1;
        if(hour2 == -1)
            hour2 = 23;
    }

    res_min = min2 - min1;
    res_hour = hour2 - hour1;


    if(res_hour < 10)
        res_str = "0" + to_string(res_hour);
    else
        res_str = to_string(res_hour);
    if(res_min < 10)
        res_str += ":0" + to_string(res_min);
    else
        res_str += ":" + to_string(res_min);
    if(res_sec  < 10)
        res_str += ":0" + to_string(res_sec);
    else
        res_str += ":" + to_string(res_sec);
    return res_str;

}

void DataHandler::to_api_routes()
{
    for(auto route : *file_entities.routes)
    {
        Routes api_single_route = {route.RouteId,route.RouteShortName, route.RouteLongName};
        api_entities.routes.push_back(api_single_route);
    }
}

void DataHandler::to_api_stopInfo()
{
    list<StopInfo> api_stops;
    for(auto stop : *file_entities.stopInfo)
    {
        StopInfo api_single_stop = {stop.StopId, stop.StopName, stop.StopLat, stop.StopLon};
        api_entities.stops.push_back(api_single_stop);
    }
}

map<string, list<StopTime>> DataHandler::stopTimes_map()
{
    std::string trip_id, last_time, current_time, interval;
    map<string, list<StopTime>> trip_stops;//stopInfo id, intervals
    list<StopTime> stop_times;
    int stopId;

    int flag = 0;
    cout << "looping on stop times\n";
    for(auto stop : *file_entities.stopTime)
    {
        stopId = stop.StopId;
        if(stop.StopSequence == 1)
        {
            interval = "00:00:00";

            if(interval != "")
            {
                trip_stops[trip_id] = stop_times;
            }

            trip_id = stop.TripId;
        }
        else
        {
            interval = get_interval(last_time,stop.DepartureTime);
        }

      string sequence_and_interval = to_string(stop.StopSequence) + ";" + interval;

      //stop_times[stopId] = sequence_and_interval;
      stop_times.push_back({stopId, sequence_and_interval});

      last_time = stop.DepartureTime;
    }
    cout << "done with stop times map\n";
    return trip_stops;
}

std::map<int, std::string> DataHandler::convertListToMap(const std::list<Shape>& list) {
    std::map<int, std::string> resultMap;
    
    for (const auto& item : list) {
        resultMap[item.ShapeId] = item.shape;
    }
    
    return resultMap;
}

void DataHandler::process_routes(std::list<RouteTrips> route_trips, std::map<std::string, std::list<StopTime>> stop_times)  
{
    //std::map<int, std::string> shapes_map = convertListToMap(shapes);
    //std::list<ExtendedRoutes> extended_routes;
    ExtendedRoutes temp_route;
    RouteTrips tempRouteTrip;

    for(auto route = file_entities.routes->begin(); route != file_entities.routes->end(); route++)
    {
        temp_route.RouteId = route->RouteId;
        for(auto route_trips_it = route_trips.begin(); route_trips_it != route_trips.end(); route_trips_it++)
        {
            if(route_trips_it->routeId == route->RouteId)
            {
                tempRouteTrip = *route_trips_it;
                route_trips_it = route_trips.end();
                route_trips_it--;
            }
        }
        //temp_route.RouteId = route->routeId;
        
        FileTrips temp_trip;
        for(auto file_trip = file_entities.trips->begin(); file_trip != file_entities.trips->end(); file_trip++)
        {
            for(auto trip = tempRouteTrip.trips.begin(); trip != tempRouteTrip.trips.end(); trip++)
            {
                if(*trip == file_trip->TripId)
                {
                    temp_trip = *file_trip;
                    file_trip = file_entities.trips->end();
                    file_trip--;
                }
            }
        }

        temp_route.routeHeadSign = temp_trip.TripHeadsign;

        //if(temp_trip.ShapeId == shapes_map.find(temp_trip.ShapeId)->first)
                //temp_route.ShapeStr = shapes_map[temp_trip.ShapeId];
        //else
         //   throw std::runtime_error("ShapeId not found in process routes");
        for(auto shapesIt = api_entities.shapes.begin(); shapesIt != api_entities.shapes.end(); shapesIt++)
        {
            if(shapesIt->ShapeId == temp_trip.ShapeId)
            {
                temp_route.ShapeStr = shapesIt->shape;
                shapesIt = api_entities.shapes.end();
                shapesIt--;
            }
        }

        for(auto stop_time = stop_times.begin(); stop_time != stop_times.end(); stop_time++)
        {
            if(stop_time->first == temp_trip.TripId)
            {
                //temp_route.TimeIntervals = stop_time->second;
                temp_route.stopTime = stop_time->second;
                stop_time = stop_times.end();
                stop_time--;
            }
        }
        api_entities.extendedRoutes.push_back(temp_route);
    }
}
