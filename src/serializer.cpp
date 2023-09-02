#include "data_handler.h"


void DataHandler::serialize_data()
{
    json_strs.Routes = to_json(api_entities.routes);
    //json_strs.Shapes = to_json(api_entities.shapes);
    json_strs.ExtendedRoutes = to_json(api_entities.extendedRoutes);
    json_strs.Stops = to_json(api_entities.stops);
}

string DataHandler::to_json(const list<StopTime>& stop_times)
{
    if(stop_times.empty())
    {
        return "null";
    }
    string str = "[";
    //str += it->toJson();
    for (auto it = stop_times.begin(); it != stop_times.end(); ++it)
    {
        str += "{\"stopId\":\"";
        str += to_string(it->stopId);
        str += "\",\"stopInterval\":\"";
        str += it->stopInterval;
        str += "\"},";
    }
    str[str.size() - 1] = ']';
    return str;
}

string DataHandler::to_json(const list<ExtendedRoutes>& routes)
{
    string str = "[";
	//str += it->toJson();
	for (auto it = routes.begin(); it != routes.end(); ++it)
	{
        str += "{\"routeId\":\"";
        str += to_string(it->RouteId);
        str += "\",\"route head sign\":\"";
        str += it->routeHeadSign;
        str += "\",\"shapeStr\":\"";
        str += it->ShapeStr;
        str += "\",\"stopTimes\":";
        str += to_json(it->stopTime);
        str += "},";
	}
    str[str.size() - 1] = ']';
	return str;
}

string DataHandler::to_json(const list<StopInfo>& stops)
{
    string str = "[";
    //str += it->toJson();
    for (auto it = stops.begin(); it != stops.end(); ++it)
    {
        str += "{\"stopId\":\"";
        str += to_string(it->stopId);
        str += "\",\"headSign\":\"";
        str += it->headSign;
        str += "\",\"lan\":\"";
        str += to_string(it->lan);
        str += "\",\"lon\":\"";
        str += to_string(it->lon);
        str += "\"},";
    }
    str[str.size() - 1] = ']';
    return str;
}

string DataHandler::to_json(const list<Routes>& routes)
{
    string str = "[";
    //str += it->toJson();
    for (auto it = routes.begin(); it != routes.end(); ++it)
    {
        str += "{\"routeId\":\"";
        str += to_string(it->RouteId);
        str += "\",\"routeShortName\":\"";
        str += it->RouteShortName;
        str += "\",\"routeLongName\":\"";
        str += it->RouteLongName;
        str += "\"},";
    }
    str[str.size() - 1] = ']';
    return str;
}

