#include "../headers/BL.h"
#include <iostream>

std::list<RouteTrips> process_trips(std::list<FileTrips> csv_trips)
{
    std::list<RouteTrips> route_and_Trips;

    bool flag = false;
    std::cout << "hello world" << std::endl;
    for(std::list<FileTrips>::const_iterator it = csv_trips.begin(); it != csv_trips.end(); it++)
    {
        for(auto route = route_and_Trips.begin(); route != route_and_Trips.end(); route++)
        {
            if(route->routeId == it->RouteId)
            {
                route->trips.push_back(it->TripId);
                flag = true;
            }
        }
        if(!flag)//if route not yet in the list
        {
            RouteTrips temp_route = {it->RouteId,{it->TripId}};
            route_and_Trips.push_back(temp_route);
        }
        flag = false;
    }

    return route_and_Trips;
}

bool comp_list_stoptimes(std::map<int,std::string> m1, std::map<int,std::string> m2)
{
    if(m1.size() != m2.size())
        return false;

    for(const auto & [key, value] : m1)
    {
        const auto & it = m2.find(key);
        if(it == m2.end() || it->second != value)
            return false;
    }

    for(const auto & [key, value] : m2)
    {
        const auto & it = m1.find(key);
        if(it == m2.end() || it->second != value)
            return false;
    }
    return true;
}

std::set<std::string> get_problematic_stops_times(std::map<std::string, std::map<int,std::string>> stop_times)
{
    //std::list<std::string> duplicates_list;
    std::set<std::string> duplicates_list;

    for(auto it = stop_times.begin(); it != stop_times.end(); it++)
    {
        for(auto it2 = it; it2 != stop_times.end(); it2++)
        {
            if(comp_list_stoptimes(it->second, it2->second))
            {
                //TODO: is insert correct?
                //duplicates_list.insert(it->first);
                duplicates_list.insert(it2->first);
            }
        }
    }
    std::cout << "\n----------------------\n";
    std::cout << duplicates_list.size();
    std::cout << "\n----------------------\n";
    return duplicates_list;
}


