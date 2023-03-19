#include "../../headers/FileEntities.h"
#include "../../headers/checks.h"
#include <fstream>
#include <sstream>
#include <list>
#include <map>
#include <cmath>

using namespace std;

void encode_single_coord(const float coordinate, string& output_str) {
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

string encode_coordinates_list(const list<CoordinateEntity>& coordinates)
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

map<int, string> get_file_shapes_list(const std::string& txt_path)
{
    std::ifstream shapes_file;
    shapes_file.open(txt_path);

    FileShapes shape;
    //list<FileShapes> shapes_list;
    map<int, string> shapes_list;

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
        shape.ShapeId = stoi(word);

        //latitude
        getline(s, word, ',');
        shape.lat = stod(word);

        //longitude
        getline(s, word, ',');
        shape.lon = stod(word);

        getline(s, word, ',');
        shape.sequence = stoi(word);

        if(lastShapeId != shape.ShapeId)
        {
            if(shape.sequence != 1)
                throw "shape error";
            if(lastShapeId != 0)
            {
                shape_str = encode_coordinates_list(coordinates);
                shapes_list[lastShapeId] = shape_str;
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
    return shapes_list;
}