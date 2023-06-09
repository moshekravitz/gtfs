#include "../headers/ApiEntities.h"
#include "../headers/BEntities.h"
#include "../headers/FileEntities.h"
#include "../headers/checks.h"

string get_interval(const string& str1, const string& str2)
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

list<Routes> to_api_routes(list<FileRoutes> fileRoutes)
{
    list<Routes> api_routes;
    for(auto route : fileRoutes)
    {
        Routes api_single_route = {route.RouteId,route.RouteShortName, route.RouteLongName};
        api_routes.push_back(api_single_route);
    }
    return api_routes;
}

list<StopInfo> to_api_stopInfo(list<FileStopInfo> fileStops)
{
    list<StopInfo> api_stops;
    for(auto stop : fileStops)
    {
        StopInfo api_single_stop = {stop.StopId, stop.StopName, stop.StopLat, stop.StopLon};
        api_stops.push_back(api_single_stop);
    }
    return api_stops;
}

map<string, map<int, string>> stopTimes_map(list<FileStopTime> fileStops)
{
    std::string trip_id, last_time, current_time, interval;
    map<string, map<int, string>> trip_stops;//stopInfo id, intervals
    map<int, string> stop_times;
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

      stop_times[stopId] = sequence_and_interval;

      last_time = stop.DepartureTime;
    }
    return trip_stops;
}