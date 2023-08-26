#include "../../headers/FileEntities.h"
#include "../../headers/checks.h"
#include <fstream>
#include <sstream>
#include <list>
using namespace std;

list<FileStopInfo> get_file_stop_info_list(const std::string& txt_path)
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
        throw std::runtime_error("bad structure in routes");
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
    return stop_info_list;
}