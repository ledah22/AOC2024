#include <string>
#include <fstream>
#include <map>
#include <algorithm>

void find_cheapest_way(std::vector<std::vector<uint64_t>>& map, std::map<uint16_t, std::vector<uint16_t>>& bytes, uint16_t x, uint16_t y, uint16_t dim, uint64_t steps, uint16_t direction, uint16_t remaining_steps) {
    if (map.at(y).at(x) > steps) {
        map.at(y).at(x) = steps;
    } else {return;}
    ++steps;
    --remaining_steps;
    //for (auto key:bytes) {
    //    printf("Key %u: ", key.first);
    //    for (int i {0}; i < key.second.size(); ++i) {
    //        printf ("%u ", key.second.at(i));
    //    }
    //    printf("\n");
    //}
    if (x < dim-1) {
        auto upomoc = bytes[y];
        //printf("(bytes.find(%u)==bytes.end())=%u\n",y, (bytes.find(y)==bytes.end()) );
        //printf("std::find(bytes[%u].begin(), bytes[%u].end(), %u+1) == bytes[%u].end() is %ld\n",y, y, x, y, std::find(upomoc.begin(), upomoc.end(), x+1) -upomoc.begin() );
    }

    if (y > 0 && direction!=2 && ((bytes.find(y-1)==bytes.end()) || std::find(bytes[y-1].begin(), bytes[y-1].end(), x) == bytes[y-1].end())) {
        //printf("! bytes.find(%u-1)==bytes.end()=%u\n", y, !(bytes.find(y-1)==bytes.end()));
        find_cheapest_way(map, bytes, x, y-1, dim, steps, 0, remaining_steps);
    }

    if (x > 0 && direction!=1 && ((bytes.find(y)==bytes.end()) || std::find(bytes[y].begin(), bytes[y].end(), x-1) == bytes[y].end())) {
        //printf("!(bytes.find(%u)==bytes.end())=%u\n",y, !(bytes.find(y)==bytes.end()) );
        find_cheapest_way(map, bytes, x-1, y, dim, steps, 3, remaining_steps);
    }

    if (x < dim-1 && direction!=3 && ((bytes.find(y)==bytes.end()) || std::find(bytes[y].begin(), bytes[y].end(), x+1) == bytes[y].end())) {
        //printf("!(bytes.find(%u)==bytes.end())=%u\n",y, !(bytes.find(y)==bytes.end()) );
        find_cheapest_way(map, bytes, x+1, y, dim, steps, 1, remaining_steps);
    }

    if (y < dim-1 && direction!=0 && ((bytes.find(y+1)==bytes.end()) || std::find(bytes[y+1].begin(), bytes[y+1].end(), x) == bytes[y+1].end())) {
        //printf("!(bytes.find(%u+1)==bytes.end())=%u\n",y, !(bytes.find(y+1)==bytes.end()) );
        find_cheapest_way(map, bytes, x, y+1, dim, steps, 2, remaining_steps);
    }

}

int main() {
    std::string temp_line;
    std::ifstream file ("input18.txt");
    uint16_t num_steps {2987}; //1024
    uint16_t dim {71}; //71
    std::vector<std::pair<uint16_t, uint16_t>> bytes;
    std::map<uint16_t, std::vector<uint16_t>> bytes_dict;
    uint16_t step_x_temp;
    uint16_t step_y_temp;
    uint16_t temp;
    uint16_t byte_count {0};

    std::vector<std::vector<uint64_t>> map;
    map.insert(map.end(), dim, std::vector<uint64_t> (dim, std::numeric_limits<uint64_t>::max()));

    while(getline(file, temp_line)) {
        temp = temp_line.find_first_of(',');
        step_x_temp = std::stoul(temp_line.substr(0, temp));
        step_y_temp = std::stoul(temp_line.substr(temp+1, temp_line.size() - temp-1));
        //printf("here %u\n", step_y_temp);

        bytes.push_back(std::pair(step_y_temp, step_x_temp));
        //printf("here0");
        if (num_steps > byte_count++) {
            if (bytes_dict.find(step_y_temp)!=bytes_dict.end()) {
                //printf("here1");
                bytes_dict[step_y_temp].push_back(step_x_temp);
                printf("here1: (%u, %u))\n", step_y_temp, step_x_temp);
            } else {
                bytes_dict[step_y_temp] = std::vector<uint16_t> (1, step_x_temp);
                printf("here2: (%u, %u)\n", step_y_temp, step_x_temp);
            }
        }
        //printf("here3");
    }

    //for (auto key:bytes_dict) {
    //    printf("Key %u: ", key.first);
    //    for (int i {0}; i < key.second.size(); ++i) {
    //        printf ("%u ", key.second.at(i));
    //    }
    //    printf("\n");
    //}
    temp = 16000; // increase for non-dbg
    find_cheapest_way(map, bytes_dict, 0, 0, dim, 0, 0, temp);

    //for (int i {0}; i < dim; ++i) {
    //    for (int j {0}; j < dim; ++j) {
    //        printf("%llu ", map.at(i).at(j));
    //    }
    //    printf("\n");
    //}

    uint64_t step_count {map.at(dim-1).at(dim-1)};

    printf("Cheapest way with a kilobyte: %llu.\n", step_count);

    return 0;
}