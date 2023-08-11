#include "data_handler.h"


void DataHandler::serialize_data()
{
    json_strs.Routes = to_json(api_entities.Routes);
    json_strs.Shapes = to_json(api_entities.Shapes);
    json_strs.ExtendedRoutes = to_json(api_entities.ExtendedRoutes);
    json_strs.Stops = to_json(api_entities.Stops);
}

string DataHandler::to_json(const list<StopTime>& routes)
{
    string str = "[";
    //str += it->toJson();
    for (auto it = routes.begin(); it != routes.end(); ++it)
    {
        str += "{\"stopId\":\"";
        str += to_string(it->stopId);
        str += "\",\"stopInterval\":\"";
        str += it->stopInterval;
        str += ",";
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
        str += "\",\"agencyId\":\"";
        str += it->routeHeadSign;
        str += ",\"shapeStr\":";
        str += it->ShapeStr;
        str += "{\"stopTimes\":\"";
        str += to_json(it->stopTime);
		str += ",";
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
        str += ",";
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
        str += ",";
    }
    str[str.size() - 1] = ']';
    return str;
}

