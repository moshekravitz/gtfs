#include "data_handler.h"


void DataHandler::send_data()
{
    //write json_strs_routes to a file
    std::ofstream json_file;
    json_file.open("json_file.json");
    json_file << json_strs.Routes;
    json_file.close();
    //write json_strs_stops to a file
    std::ofstream json_file2;
    json_file2.open("json_file2.json");
    json_file2 << json_strs.Stops;
    json_file2.close();
    //write json_strs_Extendedroutes to a file
    std::ofstream json_file3;
    json_file3.open("json_file3.json");
    json_file3 << json_strs.ExtendedRoutes;
    json_file3.close();
    //write json_strs_Shapes to a file
    std::ofstream json_file4;
    json_file4.open("json_file4.json");
    json_file4 << json_strs.Shapes;
    json_file4.close();
    cout << "done writing to file" << endl;
}
