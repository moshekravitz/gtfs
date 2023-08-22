#include "../headers/FileEntities.h"
#include "../headers/parsers.h"
#include "../headers/checks.h"
#include "data_handler.h"
#include <fstream>
#include <sstream>
#include <list>

using namespace std;

void DataHandler::load_data(const std::string& txt_path)
{
    this->load_routes(txt_path + "/routes.txt");
    this->load_shapes(txt_path + "/shapes.txt");
    this->load_stop_times(txt_path + "/stop_times.txt");
    this->load_trips(txt_path + "/trips.txt");
}

void DataHandler::load_routes(const std::string& txt_path)
{

    //list<FileRoutes> get_file_routes_list(const std::string& txt_path)
    //{
    
    std::ifstream routes_file;
    routes_file.open(txt_path);

    FileRoutes route;
    list<FileRoutes> routes_list;

    string word, line_of_info;

    //checking first line for csv structure
    string structure[7] = {"route_id","agency_id","route_short_name","route_long_name","route_desc","route_type","route_color"};
    getline(routes_file, line_of_info);

    bool good_structure = check_csv_structure(structure, 7, line_of_info);
    if(!good_structure)
        throw "bad structure in routes";
    //end of check

    while (!routes_file.eof())
    {

        stringstream s(line_of_info);

        //route Id
        getline(s, word, ',');
        route.RouteId = !word.empty() ?stoi(word) : throw "missing route id";

        getline(s, word, ',');

        //route short name
        getline(s, word, ',');
        route.RouteShortName = word;

        //route long name
        getline(s, word, ',');
        route.RouteLongName = word;

        routes_list.emplace_back(route);

    }
    this->file_entities.routes = &routes_list;
}



void DataHandler::load_trips(const std::string& txt_path)
{
    std::ifstream trips_file;
    trips_file.open(txt_path);

    FileTrips trip;
    std::list<FileTrips> trips_list;

    std::string word, line_of_info;

    //checking first line for csv structure
    string structure[6] = {"route_id","service_id","trip_id","trip_headsign","direction_id","shape_id"};
    getline(trips_file, line_of_info);

    bool good_structure = check_csv_structure(structure, 6, line_of_info);
    if(!good_structure)
        throw "bad structure in routes";
    //end of check

    int asdf = 0;
    while (!trips_file.eof())
    {
        getline(trips_file, line_of_info);
        line_of_info.erase(std::remove_if(line_of_info.begin(), line_of_info.end(), [](char c) { return c >= 0 && c <= 31; }), line_of_info.end());
        stringstream s(line_of_info);

        //route Id
        getline(s, word, ',');
        trip.RouteId = word.empty() ? 0 : stoi(word);

        getline(s, word, ',');//Service Id

        //Trip Id
        getline(s, word, ',');
        trip.TripId = word;

        //TripHeadsign
        getline(s, word, ',');
        trip.TripHeadsign = word;

        //Direction Id
        getline(s, word, ',');
        trip.DirectionId = word.empty() ? 0 : stoi(word);

        //Shape Id
        getline(s, word, ',');
        trip.ShapeId = word.empty() ? 0 : stoi(word);

        trips_list.emplace_back(trip);
        asdf++;
    }

    this->file_entities.trips = &trips_list;
}

void DataHandler::load_stop_info(const std::string& txt_path)
{
    std::ifstream stop_info_file;
    stop_info_file.open(txt_path);

    FileStopInfo StopInfo;
    std::list<FileStopInfo> stop_info_list;

    std::string word, line_of_info;

    //checking first line for csv structure
    //stop_id,stop_code,stop_name,stop_desc,stop_lat,stop_lon,location_type,parent_station,zone_id
    string structure[9] = {"stop_id","stop_code","stop_name","stop_desc","stop_lat","stop_lon","location_type","parent_station","zone_id"};
    getline(stop_info_file, line_of_info);

    bool good_structure = check_csv_structure(structure, 9, line_of_info);
    if(!good_structure)
        throw "bad structure in routes";
    //end of check

    while (!stop_info_file.eof())
    {

        stringstream s(line_of_info);

        //Stop Id
        getline(s, word, ',');
        StopInfo.StopId = word.empty() ? 0 : stoi(word);

        //Stop Code
        getline(s, word, ',');
        StopInfo.StopCode = word.empty() ? 0 : stoi(word);

        //Stop Name
        getline(s, word, ',');
        StopInfo.StopName = word.empty() ? 0 : word;

        //Stop Desc
        getline(s, word, ',');
        StopInfo.StopDesc = word.empty() ? 0 : stoi(word);

        //Stop Lat
        getline(s, word, ',');
        StopInfo.StopLat = word.empty() ? 0 : stoi(word);

        //Stop Lon
        getline(s, word, ',');
        StopInfo.StopLon = word.empty() ? 0 : stoi(word);

        //Location Type
        getline(s, word, ',');
        StopInfo.LocationType = word.empty() ? 0 : stoi(word);

        //Parent Station
        getline(s, word, ',');
        StopInfo.ParentStation = word.empty() ? 0 : stoi(word);

        //Zone Id
        getline(s, word, ',');
        StopInfo.ZoneId = word.empty() ? 0 : stoi(word);

        stop_info_list.emplace_back(StopInfo);
    }
    this->file_entities.stopInfo = &stop_info_list;
}

void DataHandler::load_stop_times(const std::string& txt_path)
{
    std::ifstream stop_times_file;
    stop_times_file.open(txt_path);

    if (!stop_times_file.is_open()) {
        throw "Failed to open file\n";
    }

    FileStopTime stopTime;
    //std::list<FileStopTime> trip_stop_time;

    std::string word, line_of_info, shape_str,tripId, last_trip_id = "";
    int  last_stop_sequence = 0;

    list<FileStopTime> stopsTimes_list;

    //checking first line for csv structure
    string structure[8] = {"trip_id","arrival_time","departure_time","stop_id","stop_sequence","pickup_type","drop_off_type","shape_dist_traveled"};
    getline(stop_times_file, line_of_info);

    std::cout << "line of info: " << line_of_info << endl;

    bool good_structure = check_csv_structure(structure, 8, line_of_info);
    if(!good_structure)
        throw "bad structure in routes";
    //end of check

    stringstream s;
    getline(stop_times_file, line_of_info);
    s << line_of_info;

    while (!stop_times_file.eof())
    {
        //Trip Id
        getline(s, word, ',');
        stopTime.TripId = word ;

        //Arrival Time
        getline(s, word, ',');
        stopTime.ArrivalTime = word;

        //Departure Time
        getline(s, word, ',');
        stopTime.DepartureTime = word;

        //Stop Id
        getline(s, word, ',');
        stopTime.StopId = word.empty() ? 0 : stoi(word);

        //Stop Sequence
        getline(s, word, ',');
        stopTime.StopSequence = word.empty() ? 0 : stoi(word);

        //Pickup Type
        getline(s, word, ',');
        stopTime.PickupType = word.empty() ? 0 : stoi(word);

        //Drop Off Type
        getline(s, word, ',');
        stopTime.DropOffType = word.empty() ? 0 : stoi(word);

        //Shape Id
        getline(s, word, ',');
        stopTime.ShapeDistTraveled = word.empty() ? 0 : stoi(word);

        stopsTimes_list.push_back(stopTime);

        getline(stop_times_file, line_of_info);
        s.clear();
        s << line_of_info;

        /*
        if(last_trip_id != tripId)
        {
            std::cout << "last_trip_id: " << last_trip_id << " current: " << tripId << endl;
            if(stopTime.StopSequence != 1)
            {
                throw "shape error";
            }
            if(last_trip_id != "")
            {
                stopsTimes_list[last_trip_id] = stopTime;
            }
            last_trip_id = tripId;
            last_stop_sequence = 1;
        }
        else
        {
            last_stop_sequence++;
            std::cout << "last_stop_sequence: " << last_stop_sequence << " current: " << stopTime.StopSequence << endl;
            if(last_stop_sequence != stopTime.StopSequence)
                throw "shape error";
        }

        trip_stop_time.push_back(stopTime);
         */
    }

    stop_times_file.close();

    this->file_entities.stopTime = &stopsTimes_list;
}

void DataHandler::encode_single_coord(const float coordinate, string& output_str) {
    const int factor = pow(10, 5);
    int32_t int_coord = (int32_t)(coordinate * factor);
    int_coord <<= (int32_t)1;

    if (int_coord < 0) {
        int_coord = ~int_coord;
    }

    int index = 0;
    for (index = 0;output_str[index]; index++) {}

    for (index; int_coord >= 0x20; index++) {
        output_str +=  static_cast<char> (static_cast<char> (0x20 | (int32_t)(int_coord & 0x1f)) + 63);
        int_coord >>= (int32_t)5;
    }
    output_str += static_cast<char> (int_coord + 63);
}

string DataHandler::encode_coordinates_list(const list<CoordinateEntity>& coordinates)
{
    string output_char_arr = {};

    //////////////////string output_str = output_char_arr;

    list<CoordinateEntity>::const_iterator it = coordinates.begin();

    CoordinateEntity last_coordinate = *it;
    encode_single_coord(static_cast<float>(it->latitude), output_char_arr);
    encode_single_coord(static_cast<float>(it->longitude), output_char_arr);

    for(;it != coordinates.end(); ++it)
    {
        encode_single_coord(static_cast<float>(it->latitude - last_coordinate.latitude), output_char_arr);
        encode_single_coord(static_cast<float>(it->longitude - last_coordinate.longitude), output_char_arr);
        last_coordinate = *it;
    }
    return output_char_arr;
}

//map<int, string> get_file_shapes_list(const std::string& txt_path)
void DataHandler::load_shapes(const std::string& txt_path)
{
    std::ifstream shapes_file;
    shapes_file.open(txt_path);

    FileShapes shape;
    list<Shape> shapes_list;
    //map<int, string> shapes_list;

    string word, line_of_info, shape_str;
    int lastShapeId = 0, last_sequence = 0;
    list<CoordinateEntity> coordinates;

    //checking first line for csv structure
    //shape_id,shape_pt_lat,shape_pt_lon,shape_pt_sequence
    string structure[4] = {"shape_id","shape_pt_lat","shape_pt_lon","shape_pt_sequence"};
    getline(shapes_file, line_of_info);

    bool good_structure = check_csv_structure(structure, 4, line_of_info);
    if(!good_structure)
        throw "bad structure in shapes";
    //end of check

    while (!shapes_file.eof())
    {

        stringstream s(line_of_info);

        //shape id
        getline(s, word, ',');
        shape.ShapeId = word.empty() ? 0 : stoi(word);

        //latitude
        getline(s, word, ',');
        shape.lat = word.empty() ? 0 : stod(word);

        //longitude
        getline(s, word, ',');
        shape.lon = word.empty() ? 0 : stod(word);

        getline(s, word, ',');
        shape.sequence = word.empty() ? 0 : stoi(word);

        if(lastShapeId != shape.ShapeId)
        {
            if(shape.sequence != 1)
                throw "shape error";
            if(lastShapeId != 0)
            {
                shape_str = encode_coordinates_list(coordinates);
                //shapes_list[lastShapeId] = shape_str;
                shapes_list.emplace_back(Shape{lastShapeId, shape_str});
            }
            lastShapeId = shape.ShapeId;
            CoordinateEntity tempCoord = {shape.lon,shape.lat};
            coordinates.emplace_back(tempCoord);
        }
        else
        {
            last_sequence++;
            if(last_sequence != shape.sequence)
                throw "shape error";
            CoordinateEntity tempCoord = {shape.lon,shape.lat};
            coordinates.emplace_back(tempCoord);
        }
    }
}

std::list<RouteTrips> DataHandler::process_trips(std::list<FileTrips> csv_trips)
{
    std::list<RouteTrips> route_and_Trips;

    bool flag = false;
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
