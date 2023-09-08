#include "data_handler.h"

void DataHandler::send_data() {
    //write json_strs_routes to a file
    std::ofstream json_file;
    json_file.open("/home/moshekravitz/Documents/gtfs/routes.json");
    json_file << json_strs.Routes;
    json_file.close();

    //write json_s"trs_stops to a file
    std::ofstream json_file2;
    json_file2.open("/home/moshekravitz/Documents/gtfs/stops.json");
    json_file2 << json_strs.Stops;
    json_file2.close();
    std::cout << "sending stop infos\n";

    //write json_strs_Extendedroutes to a file
    std::ofstream json_file3;
    json_file3.open("/home/moshekravitz/Documents/gtfs/extendedRoutes.json");
    json_file3 << json_strs.ExtendedRoutes;
    json_file3.close();
    std::cout << "sending routes\n";
}




