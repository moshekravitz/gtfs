#include "data_handler.h"

void DataHandler::process_data(){
    list<RouteTrips> route_and_trips = process_trips(*this->file_entities.trips);
    // stopTimes_map(*this->file_entities.stop_times;
    map<string, list<StopTime>> stopTimes_map = DataHandler::stopTimes_map(*this->file_entities.stopTime);
    this->api_entities.Routes = to_api_routes(*this->file_entities.routes);
    this->api_entities.Stops = to_api_stopInfo(*this->file_entities.stopInfo);
    this->api_entities.ExtendedRoutes = process_routes(route_and_trips, *this->file_entities.routes, *this->file_entities.trips, stopTimes_map, this->api_entities.Shapes);
    
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

list<Routes> DataHandler::to_api_routes(list<FileRoutes> fileRoutes)
{
    list<Routes> api_routes;
    for(auto route : fileRoutes)
    {
        Routes api_single_route = {route.RouteId,route.RouteShortName, route.RouteLongName};
        api_routes.push_back(api_single_route);
    }
    return api_routes;
}

list<StopInfo> DataHandler::to_api_stopInfo(list<FileStopInfo> fileStops)
{
    list<StopInfo> api_stops;
    for(auto stop : fileStops)
    {
        StopInfo api_single_stop = {stop.StopId, stop.StopName, stop.StopLat, stop.StopLon};
        api_stops.push_back(api_single_stop);
    }
    return api_stops;
}

map<string, list<StopTime>> DataHandler::stopTimes_map(list<FileStopTime> fileStops)
{
    std::string trip_id, last_time, current_time, interval;
    map<string, list<StopTime>> trip_stops;//stopInfo id, intervals
    list<StopTime> stop_times;
    int stopId;

    int flag = 0;
    for(auto stop : fileStops)
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
            /*
            if(flag < 15)
            {
                std::cout << "last: "<< last_time << " last: "<< stop.DepartureTime << endl;
                flag++;
            }
             */
            interval = get_interval(last_time,stop.DepartureTime);
        }

      string sequence_and_interval = to_string(stop.StopSequence) + ";" + interval;

      //stop_times[stopId] = sequence_and_interval;
      stop_times.push_back({stopId, sequence_and_interval});

      last_time = stop.DepartureTime;
    }
    return trip_stops;
}

std::map<int, std::string> DataHandler::convertListToMap(const std::list<Shape>& list) {
    std::map<int, std::string> resultMap;
    
    for (const auto& item : list) {
        resultMap[item.ShapeId] = item.shape;
    }
    
    return resultMap;
}

std::list<ExtendedRoutes> DataHandler::process_routes(std::list<RouteTrips> route_trips, std::list<FileRoutes> file_routes, std::list<FileTrips> file_trips, std::map<std::string, std::list<StopTime>> stop_times, std::list<Shape> shapes)  
{
    //std::map<int, std::string> shapes_map = convertListToMap(shapes);
    std::list<ExtendedRoutes> extended_routes;
    ExtendedRoutes temp_route;
    RouteTrips tempRouteTrip;

    for(auto route = file_routes.begin(); route != file_routes.end(); route++)
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
        for(auto file_trip = file_trips.begin(); file_trip != file_trips.end(); file_trip++)
        {
            for(auto trip = tempRouteTrip.trips.begin(); trip != tempRouteTrip.trips.end(); trip++)
            {
                if(*trip == file_trip->TripId)
                {
                    temp_trip = *file_trip;
                    file_trip = file_trips.end();
                    file_trip--;
                }
            }
        }

        temp_route.routeHeadSign = temp_trip.TripHeadsign;

        //if(temp_trip.ShapeId == shapes_map.find(temp_trip.ShapeId)->first)
                //temp_route.ShapeStr = shapes_map[temp_trip.ShapeId];
        //else
         //   throw std::runtime_error("ShapeId not found in process routes");
        for(auto shapesIt = shapes.begin(); shapesIt != shapes.end(); shapesIt++)
        {
            if(shapesIt->ShapeId == temp_trip.ShapeId)
            {
                temp_route.ShapeStr = shapesIt->shape;
                shapesIt = shapes.end();
                shapesIt--;
            }
        }

        for(auto stop_time = stop_times.begin(); stop_time != stop_times.end(); stop_time++)
        {
            if(stop_time->first == temp_trip.TripId)
            {
                //temp_route.TimeIntervals = stop_time->second;
                temp_route.StopInfo = stop_time->second;
                stop_time = stop_times.end();
                stop_time--;
            }
        }
        extended_routes.push_back(temp_route);
    }

    return extended_routes;
}
