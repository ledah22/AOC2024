#include <string>
#include <fstream>

uint64_t find_paths(uint64_t x, uint64_t y, std::vector<std::vector<uint64_t>> trails, uint64_t siz) {
    uint64_t ret_val {0};
    uint64_t curr_val {trails.at(x).at(y)};
    if(curr_val == 9) {
        ret_val = 1;
        printf("Finsished a path\n");
    } else {
        printf("About to recurse: up=%llu, left=%llu, down=%llu, right=%llu \n", (x>0 ? trails.at(x-1).at(y) : 30), (y>0 ? trails.at(x).at(y-1) : 30), (x<siz-1 ? trails.at(x+1).at(y) : 30), (y<siz-1 ? trails.at(x).at(y+1) : 30));
        ret_val += ((x>0 && trails.at(x-1).at(y) == curr_val+1) ? find_paths(x-1, y, trails, siz):0) + ((y>0 && trails.at(x).at(y-1) == curr_val+1) ? find_paths(x, y-1, trails, siz):0) + ((x<siz-1 && trails.at(x+1).at(y) == curr_val+1) ? find_paths(x+1, y, trails, siz):0)+ ((y<siz-1 && trails.at(x).at(y+1) == curr_val+1) ? find_paths(x, y+1, trails, siz):0);
    }
    return ret_val;
}

bool reachable_paths(uint64_t x, uint64_t y, uint64_t goal_x, uint64_t goal_y, std::vector<std::vector<uint64_t>> trails, uint64_t siz) {
    uint64_t curr_val {trails.at(x).at(y)};
    if(x == goal_x && y == goal_y) {
        return true;
    } else {
        //printf("About to recurse: up=%llu, left=%llu, down=%llu, right=%llu \n", (x>0 ? trails.at(x-1).at(y) : 30), (y>0 ? trails.at(x).at(y-1) : 30), (x<siz-1 ? trails.at(x+1).at(y) : 30), (y<siz-1 ? trails.at(x).at(y+1) : 30));
        return false || ((x>0 && trails.at(x-1).at(y) == curr_val+1) ? reachable_paths(x-1, y, goal_x, goal_y, trails, siz):false) || ((y>0 && trails.at(x).at(y-1) == curr_val+1) ? reachable_paths(x, y-1, goal_x, goal_y, trails, siz):0) || ((x<siz-1 && trails.at(x+1).at(y) == curr_val+1) ? reachable_paths(x+1, y, goal_x, goal_y, trails, siz):0) || ((y<siz-1 && trails.at(x).at(y+1) == curr_val+1) ? reachable_paths(x, y+1, goal_x, goal_y, trails, siz):false);
    }
}

int main() {
    std::string temp_line;
    std::ifstream file ("input10.txt");
    uint64_t siz {45}; // 8 or 45
    std::vector<std::vector<uint64_t>> trails; 
    uint64_t temp {0};
    std::vector<std::pair<uint64_t, uint64_t>> zero_loc;
    std::vector<std::pair<uint64_t, uint64_t>> nine_loc;

    while (getline(file, temp_line)) {
        uint64_t temp2 {0};
        trails.push_back(std::vector<uint64_t>{});
        for (auto it {0}; it < temp_line.size(); ++it) {
            trails.at(temp).push_back(temp_line.at(it)-'0');
            if (trails.at(temp).back() == 0) {
                zero_loc.push_back(std::pair(temp, temp2));
                //printf("found a zero at x=%llu y=%llu \n", temp, temp2);
            }
            if (trails.at(temp).back() == 9) {
                nine_loc.push_back(std::pair(temp, temp2));
                //printf("found a nine at x=%llu y=%llu \n", temp, temp2);
            }
            ++temp2;
        }
        ++temp;
    }

    uint64_t first_sum {0};
    uint64_t second_sum {0};
    for (auto it {zero_loc.begin()}; it < zero_loc.end(); ++it) {
        for (auto it2 {nine_loc.begin()}; it2 < nine_loc.end(); ++it2) {
            //first_sum += reachable_paths((*it).first, (*it).second, (*it2).first, (*it2).second, trails, siz);
        }
        
        second_sum += find_paths((*it).first, (*it).second, trails, siz);
    }

    printf("First answer: %llu. Second answer: %llu\n", first_sum, second_sum);

    return 0;
}