#include <string>
#include <fstream>

uint64_t new_score(uint64_t curr_score, uint32_t orientation, uint32_t direction) {
    //printf("here4\n");
    if(orientation == direction) {
        return curr_score+1;
    }

    if (std::abs((int)orientation - (int)direction) == 1 || std::abs((int)orientation - (int)direction) == 3) {
        return curr_score + 1001;
    }

    return curr_score + 2001;
}

void find_min_path(uint64_t remaining_attempts, std::vector<std::vector<uint64_t>>& path_costs, std::vector<std::string>& map, uint32_t dim_X, uint32_t dim_Y, uint32_t x, uint32_t y, uint32_t x_e, uint32_t y_e, uint64_t curr_score, uint32_t orientation) {
    //orientation 0 - up, 1 - right, 2 - down, 3 - left
    //printf("here9\n");
    if (curr_score < path_costs.at(x).at(y)) {
        path_costs.at(x).at(y) = curr_score;
    } else {
        return;
    }
    //printf("Score map:\n");
    //for(int i {0}; i < dim_X; ++i) {
    //    for(int j {0}; j < dim_Y; ++j) {
    //        std::string temp {path_costs.at(i).at(j)==std::numeric_limits<uint64_t>::max() ? "X" : std::to_string(path_costs.at(i).at(j))};
    //        std::string spaces {""};
    //        std::fill_n(spaces.begin(), 7-(temp.size()), ' ');
    //        printf("%s%s", temp.c_str(), spaces.c_str());
    //    }
    //    printf("\n");
    //}
    if (!remaining_attempts) {
        return;
    }
    --remaining_attempts;
    bool can_up {orientation!=2 && x>0 && map.at(x-1).at(y) != '#'};
    bool can_down {orientation!=0 && x<dim_X-1 && map.at(x+1).at(y) != '#'};
    bool can_right {orientation!=3 && y<dim_Y-1 && map.at(x).at(y+1) != '#'};
    bool can_left {orientation!=1 && y>0 && map.at(x).at(y-1) != '#'};

    uint32_t new_or;

    if(can_up) {
        new_or = 0;
        find_min_path(remaining_attempts, path_costs, map, dim_X, dim_Y, x-1, y, x_e, y_e, new_score(curr_score, orientation, new_or), new_or);
    }
    if(can_right) {
        new_or = 1;
        find_min_path(remaining_attempts, path_costs, map, dim_X, dim_Y, x, y+1, x_e, y_e, new_score(curr_score, orientation, new_or), new_or);
    }
    if (can_left) {
        new_or = 3;
        find_min_path(remaining_attempts, path_costs, map, dim_X, dim_Y, x, y-1, x_e, y_e, new_score(curr_score, orientation, new_or), new_or);
    }
    if (can_down) {
        new_or = 2;
        find_min_path(remaining_attempts, path_costs, map, dim_X, dim_Y, x+1, y, x_e, y_e, new_score(curr_score, orientation, new_or), new_or);
    }

}

uint64_t new_credits(uint64_t curr_score, uint32_t orientation, uint32_t direction) {
    //printf("here4\n");

    if(orientation == direction) {
        return curr_score > 1 ? curr_score - 1 : 0;
    }

    if (std::abs((int)orientation - (int)direction) == 1 || std::abs((int)orientation - (int)direction) == 3) {
        return curr_score > 1001 ? curr_score - 1001 : 0;
    }

    return curr_score>2001 ? curr_score>2001 : 0;
}

std::vector<std::pair<uint64_t, uint64_t>> backtrace_path(std::vector<std::vector<uint64_t>>& min_cost, uint32_t steps, uint64_t credits, std::vector<std::pair<uint64_t, uint64_t>> loc, std::vector<std::string>& map, uint32_t dim_X, uint32_t dim_Y, uint32_t x, uint32_t y, uint32_t x_s, uint32_t y_s,uint32_t orientation) {
    //printf("Adding x=%u y=%u, remaining credit is %llu.\n", x, y, credits);
    loc.push_back(std::pair<uint64_t, uint64_t>(x, y));
    --steps;
    if (((credits==2000 && orientation == 3) || (credits==1000 && orientation == 2)) && x==x_s && y ==y_s) {
        //for (auto pr{loc.begin()}; pr < loc.end(); ++pr) {
        //    map.at((*pr).first).at((*pr).second) = 'O';
        //}
        //printf("Finished this tail of length %zu. \n", loc.size());
        return loc;
    }
    if ((credits < min_cost.at(x).at(y)) || ((x!=x_s && y!=y_s) && credits < 1000+(x_s-x) + (y-y_s)) || credits == 0 || (steps < (x_s-x) + (y-y_s))) {
        //printf("Failed this tail.\n");
        return (std::vector<std::pair<uint64_t, uint64_t>>());
    }

    bool can_up {orientation!=2 && x>0 && map.at(x-1).at(y) != '#' && !count(loc.begin(), loc.end(), std::pair<uint64_t, uint64_t> (x-1, y))};
    bool can_down {orientation!=0 && x<dim_X-1 && map.at(x+1).at(y) != '#' && !count(loc.begin(), loc.end(), std::pair<uint64_t, uint64_t> (x+1, y))};
    bool can_right {orientation!=3 && y<dim_Y-1 && map.at(x).at(y+1) != '#' && !count(loc.begin(), loc.end(), std::pair<uint64_t, uint64_t> (x, y+1))};
    bool can_left {orientation!=1 && y>0 && map.at(x).at(y-1) != '#' && !count(loc.begin(), loc.end(), std::pair<uint64_t, uint64_t> (x, y-1))};

    std::vector<std::pair<uint64_t, uint64_t>> res_up;
    std::vector<std::pair<uint64_t, uint64_t>> res_down;
    std::vector<std::pair<uint64_t, uint64_t>> res_right;
    std::vector<std::pair<uint64_t, uint64_t>> res_left;

    if(can_up)
        res_up = backtrace_path(min_cost, steps, new_credits(credits, orientation, 0), std::vector<std::pair<uint64_t, uint64_t>>(), map, dim_X, dim_Y, x-1, y, x_s, y_s, 0);
    if(can_right)
        res_down = backtrace_path(min_cost, steps, new_credits(credits, orientation, 1), std::vector<std::pair<uint64_t, uint64_t>>(), map, dim_X, dim_Y, x, y+1, x_s, y_s, 1);
    if (can_left)
        res_right = backtrace_path(min_cost, steps, new_credits(credits, orientation, 3), std::vector<std::pair<uint64_t, uint64_t>>(), map, dim_X, dim_Y, x, y-1, x_s, y_s, 3);
    if (can_down)
        res_left = backtrace_path(min_cost, steps, new_credits(credits, orientation, 2), std::vector<std::pair<uint64_t, uint64_t>>(), map, dim_X, dim_Y, x+1, y, x_s, y_s, 2);
    
    if(res_up.empty() && res_down.empty() && res_right.empty() && res_left.empty()) {
        //printf("Failed this tail.\n");
        return (std::vector<std::pair<uint64_t, uint64_t>>());
    }
    
    loc.insert(loc.end(), res_up.begin(), res_up.end());
    loc.insert(loc.end(), res_down.begin(), res_down.end());
    loc.insert(loc.end(), res_right.begin(), res_right.end());
    loc.insert(loc.end(), res_left.begin(), res_left.end());
    //for (auto pr{loc.begin()}; pr < loc.end(); ++pr) {
    //    printf("(%llu, %llu) ", (*pr).first, (*pr).second);
    //}
    //printf("\n Length %zu\n", loc.size());
    return loc;
}

void reduce_map(std::vector<std::string>& map, uint32_t dim_X, uint32_t dim_Y) {
    bool nothing_changed {true};
    int counter_of_changes {0};
    for (int rep {0}; rep < 100; ++rep){
        printf("here20\n");
        for (int i {1}; i< dim_X-1; ++i) {
            for (int j {1}; j < dim_Y-1; ++j) {
                if(map.at(i).at(j) == '.') {
                    int hash_cnt {0};
                    if(i == 14 && j == 15) {
                        printf("%c %c %c; %c %c %c; %c %c %c\n", map.at(i-1).at(j-1), map.at(i-1).at(j), map.at(i-1).at(j+1), map.at(i).at(j-1), map.at(i).at(j), map.at(i).at(j+1), map.at(i+1).at(j-1), map.at(i+1).at(j), map.at(i+1).at(j+1));
                    }
                    if (map.at(i-1).at(j-1) == '#') {
                        ++hash_cnt;
                    }
                    if (map.at(i-1).at(j) == '#') {
                        ++hash_cnt;
                    }
                    if (map.at(i-1).at(j+1) == '#') {
                        ++hash_cnt;
                    }
                    if (map.at(i).at(j-1) == '#') {
                        ++hash_cnt;
                    }

                    if (map.at(i).at(j+1) == '#') {
                        ++hash_cnt;
                    }

                    if (map.at(i+1).at(j-1) == '#') {
                        ++hash_cnt;
                    }

                    if (map.at(i+1).at(j) == '#') {
                        ++hash_cnt;
                    }

                    if (map.at(i+1).at(j+1) == '#') {
                        ++hash_cnt;
                    }

                    if (hash_cnt >= 7) {
                        map.at(i).at(j) = '#';
                        nothing_changed = false;
                        ++counter_of_changes;
                    }
                }

            }
        }

        if (nothing_changed) {
            printf("Using the nothing-changed\n");
            break;
        }
    }

    printf("Number of changes: %u\n", counter_of_changes);
}

int main() {
    std::string temp_line;
    std::ifstream file("input16.txt");
    std::vector<std::string> map;
    std::vector<std::vector<uint64_t>> cheapest_path;
    uint32_t x_s;
    uint32_t y_s;
    uint32_t x_e;
    uint32_t y_e;
    uint64_t first_answer {0};
    uint32_t dim_X {0};

    while(getline(file, temp_line)) {
        map.push_back(temp_line);
        cheapest_path.push_back(std::vector<uint64_t> ());
        cheapest_path.back().assign(temp_line.size(), std::numeric_limits<uint64_t>::max());
        //printf("here0\n");
        for (uint32_t letter {0}; letter < temp_line.size(); ++letter) {
            if(temp_line.at(letter) == 'E') {
                x_e = map.size()-1;
                y_e = letter;
                //printf("here1\n");
            } else if (temp_line.at(letter) == 'S') {
                x_s = map.size()-1;
                y_s = letter;
                //printf("here2\n");
            }
        }
        ++dim_X;
    }

    uint32_t dim_Y {static_cast<uint32_t>(map.back().size())};
    find_min_path(1000, cheapest_path, map, dim_X, dim_Y, x_s, y_s, x_e, y_e, 0, 1);
    first_answer = cheapest_path.at(x_e).at(y_e);
    printf("here10\n");

    printf("Score map:\n");
    for(int i {0}; i < dim_X; ++i) {
        for(int j {0}; j < dim_Y; ++j) {
            std::string temp {cheapest_path.at(i).at(j)==std::numeric_limits<uint64_t>::max() ? "X" : std::to_string(cheapest_path.at(i).at(j))};
            std::string spaces {""};
            spaces.insert(spaces.end(), 7-temp.size(), ' ');
            printf("%s%s", temp.c_str(), spaces.c_str());
        }
        printf("\n");
    }

    //reduce_map(map, dim_X, dim_Y);
    uint32_t second_answer {0};
    std::vector<std::pair<uint64_t, uint64_t>> snd_sol {backtrace_path(cheapest_path, 5000, first_answer, std::vector<std::pair<uint64_t, uint64_t>>(), map, dim_X, dim_Y, x_e, y_e, x_s, y_s, 2)};
    std::vector<std::pair<uint64_t, uint64_t>> snd_sol2 {backtrace_path(cheapest_path, 5000, first_answer, std::vector<std::pair<uint64_t, uint64_t>>(), map, dim_X, dim_Y, x_e, y_e, x_s, y_s, 3)};
    snd_sol.insert(snd_sol.end(), snd_sol2.begin(), snd_sol2.end());
    
    for (auto pr{snd_sol.begin()}; pr < snd_sol.end(); ++pr) {
        map.at((*pr).first).at((*pr).second) = 'O';
    }

    for (auto row{0}; row < dim_X; ++row) {
        printf("%s\n", map.at(row).c_str());
        for (auto clm {0}; clm < dim_Y; ++clm) {
            if (map.at(row).at(clm) == 'O')
                ++second_answer;
        }
    }
    printf("First answer is: %llu. Second is %u\n", first_answer, second_answer);

    return 0;
}