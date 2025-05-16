#include <string>
#include <fstream>

void do_a_move(std::vector<char>& moves_, std::vector<std::string>& map_, uint64_t robot_x_, uint64_t robot_y_, uint64_t map_x, uint64_t map_y) {
    if (moves_.empty()) {
        printf("here3\n");
        return;
    }

    char curr_move {moves_.front()};
    moves_.erase(moves_.begin());

    if (curr_move == '^') {
        printf("here^\n");
        if (robot_x_ != 1) {
            uint64_t temp_loc {robot_x_-1};
            while(temp_loc!= 0 && map_.at(temp_loc).at(robot_y_)=='O') {
                --temp_loc;
            }

            if(temp_loc!= 0 && map_.at(temp_loc).at(robot_y_)!='#') {
                map_.at(robot_x_).at(robot_y_) = '.';
                --robot_x_;
                map_.at(temp_loc).at(robot_y_) = 'O';
                map_.at(robot_x_).at(robot_y_) = '@';
            }
        }
    } else if (curr_move == 'v') {
        printf("herev\n");
        if (robot_x_ != map_x) {
            uint64_t temp_loc {robot_x_+1};
            while(temp_loc!= map_x+1 && map_.at(temp_loc).at(robot_y_)=='O') {
                ++temp_loc;
            }
            printf("ISIDORA %llu compared to %llu %c\n", temp_loc,map_x, map_.at(temp_loc).at(robot_y_));
            if(temp_loc!= map_x+1 && map_.at(temp_loc).at(robot_y_)!='#') {
                map_.at(robot_x_).at(robot_y_) = '.';
                ++robot_x_;
                map_.at(temp_loc).at(robot_y_) = 'O';
                map_.at(robot_x_).at(robot_y_) = '@';
            }
        }
    } else if (curr_move == '>') {
        printf("here>\n");
        if (robot_y_ != map_y) {
            uint64_t temp_loc {robot_y_+1};
            while(temp_loc!= map_y+1 && map_.at(robot_x_).at(temp_loc)=='O') {
                ++temp_loc;
            }

            if(temp_loc!= map_y+1 && map_.at(robot_x_).at(temp_loc)!='#') {
                map_.at(robot_x_).at(robot_y_) = '.';
                ++robot_y_;
                map_.at(robot_x_).at(temp_loc) = 'O';
                map_.at(robot_x_).at(robot_y_) = '@';
            }
        }
    } else if (curr_move == '<') {
        printf("here<\n");
        if (robot_y_ != 1) {
            uint64_t temp_loc {robot_y_-1};
            while(temp_loc!= 0 && map_.at(robot_x_).at(temp_loc)=='O') {
                --temp_loc;
            }

            if(temp_loc!= 0 && map_.at(robot_x_).at(temp_loc)!='#') {
                map_.at(robot_x_).at(robot_y_) = '.';
                --robot_y_;
                map_.at(robot_x_).at(temp_loc) = 'O';
                map_.at(robot_x_).at(robot_y_) = '@';
            }
        }
    }

    for(int x {0}; x < map_.size(); ++x) {
        printf("%s\n", map_.at(x).c_str());
    }
    do_a_move(moves_, map_, robot_x_, robot_y_, map_x, map_y);

}

void do_a_new_move(char curr_move, std::vector<std::string>& map_, uint64_t& robot_x_, uint64_t& robot_y_, uint64_t map_x, uint64_t map_y) {

    if (curr_move == '^') {
        printf("here^\n");
        if (robot_x_ != 1) {
            uint64_t temp_loc_x;
            uint64_t temp_loc_y;
            std::vector<std::pair<uint64_t, uint64_t>> move_up;
            std::vector<std::pair<uint64_t, uint64_t>> last_row;
            std::vector<std::pair<uint64_t, uint64_t>> curr_row;
            last_row.push_back(std::pair(robot_x_, robot_y_));
            bool move_possible {true};
            bool first_move {true};
            while(!last_row.empty() && move_possible){
                move_up.insert(move_up.end(), curr_row.begin(), curr_row.end());
                curr_row.clear();

                for (auto box {last_row.begin()}; box < last_row.end(); ++box) {
                    temp_loc_x = (*box).first-1;
                    temp_loc_y = (*box).second-1;
                    if ((map_.at(temp_loc_x).at(temp_loc_y+1) == '#' || (!first_move && map_.at(temp_loc_x).at(temp_loc_y+2) == '#'))) {
                        move_possible = false;
                        break;
                    }
                    for (auto i {0}; i <= (first_move? 1:2); ++i) {
                        if(temp_loc_x > 0 && temp_loc_y+i > 0 && temp_loc_y+i+1 < map_y && map_.at(temp_loc_x).at(temp_loc_y+i) == '[' && map_.at(temp_loc_x).at(temp_loc_y+i+1) == ']') {
                            curr_row.push_back(std::pair(temp_loc_x, temp_loc_y+i));
                            printf("Just added (%llu,%llu)\n", temp_loc_x,temp_loc_y+i);
                        }
                    } 
                }

                last_row = curr_row;

                first_move = false;
            }

            printf("Current memebers of move_up:\n");
                for (auto box {move_up.begin()}; box < move_up.end(); ++box) {
                    printf("(%llu,%llu) ", (*box).first, (*box).second);
                }
                printf("\n");
            printf("Move is %s\n", move_possible?"possible":"not possible");
            if (!move_possible) {
                move_up.clear();
            }

            for (auto box {move_up.begin()}; box < move_up.end(); ++box) {
                printf("Old box value: %llu %llu\n", (*box).first, (*box).second);
                map_.at((*box).first).at((*box).second) = '.';
                map_.at((*box).first).at((*box).second+1) = '.';
            }

            if (move_possible) {
                map_.at(robot_x_).at(robot_y_) = '.';
                --robot_x_;
                map_.at(robot_x_).at(robot_y_) = '@';
            }
            for (auto box {move_up.begin()}; box < move_up.end(); ++box) {
                printf("New box value: %llu %llu\n", (*box).first, (*box).second);
                map_.at((*box).first-1).at((*box).second) = '[';
                map_.at((*box).first-1).at((*box).second+1) = ']';
            }

        }
    } else if (curr_move == 'v') {
        printf("herev\n");
        if (robot_x_ != map_x) {
            uint64_t temp_loc_x;
            uint64_t temp_loc_y;
            std::vector<std::pair<uint64_t, uint64_t>> move_down;
            std::vector<std::pair<uint64_t, uint64_t>> last_row;
            std::vector<std::pair<uint64_t, uint64_t>> curr_row;
            last_row.push_back(std::pair(robot_x_, robot_y_));
            bool move_possible {true};
            bool first_move {true};
            while(!last_row.empty() && move_possible){
                move_down.insert(move_down.end(), curr_row.begin(), curr_row.end());
                curr_row.clear();

                for (auto box {last_row.begin()}; box < last_row.end(); ++box) {
                    temp_loc_x = (*box).first+1;
                    temp_loc_y = (*box).second-1;
                    if ( (map_.at(temp_loc_x).at(temp_loc_y+1) == '#' || (!first_move && map_.at(temp_loc_x).at(temp_loc_y+2) == '#'))) {
                        move_possible = false;
                        break;
                    }
                    for (auto i {0}; i <=(first_move? 1:2); ++i) {
                        if(temp_loc_x > 0 && temp_loc_y+i > 0 && temp_loc_y+i+1 < map_y && map_.at(temp_loc_x).at(temp_loc_y+i) == '[' && map_.at(temp_loc_x).at(temp_loc_y+i+1) == ']') {
                            curr_row.push_back(std::pair(temp_loc_x, temp_loc_y+i));
                        }
                    }
                }
                last_row = curr_row;
                first_move = false;
            }
            printf("Move is %s\n", move_possible?"possible":"not possible");

            if (!move_possible) {
                move_down.clear();
            }

            for (auto box {move_down.begin()}; box < move_down.end(); ++box) {
                map_.at((*box).first).at((*box).second) = '.';
                map_.at((*box).first).at((*box).second+1) = '.';
            }

            if (move_possible) {
                map_.at(robot_x_).at(robot_y_) = '.';
                ++robot_x_;
                map_.at(robot_x_).at(robot_y_) = '@';
            }
            for (auto box {move_down.begin()}; box < move_down.end(); ++box) {
                map_.at((*box).first+1).at((*box).second) = '[';
                map_.at((*box).first+1).at((*box).second+1) = ']';
            }

        }
    } else if (curr_move == '>') {
        printf("here>\n");
        if (robot_y_ != map_y) {
            uint64_t temp_loc {robot_y_+1};
            while(temp_loc!= map_y+1 && (map_.at(robot_x_).at(temp_loc)=='[' || map_.at(robot_x_).at(temp_loc)==']')) {
                ++temp_loc;
            }

            if(temp_loc!= map_y+1 && map_.at(robot_x_).at(temp_loc)!='#') {
                map_.at(robot_x_).at(robot_y_) = '.';
                ++robot_y_;
                map_.at(robot_x_).at(robot_y_) = '@';
                bool last_was_open {false};
                for (auto i {robot_y_+1}; i <= temp_loc; ++i) {
                    map_.at(robot_x_).at(i)= last_was_open ? ']':'[';
                    last_was_open = !last_was_open;
                }
            }
        }
    } else if (curr_move == '<') {
        printf("here<\n");
        if (robot_y_ > 2) {
            uint64_t temp_loc {robot_y_-1};
            while(temp_loc!= 0 && (map_.at(robot_x_).at(temp_loc)=='[' || map_.at(robot_x_).at(temp_loc)==']')) {
                --temp_loc;
            }

            if(temp_loc!= 0 && map_.at(robot_x_).at(temp_loc)!='#') {
                map_.at(robot_x_).at(robot_y_) = '.';
                --robot_y_;
                map_.at(robot_x_).at(robot_y_) = '@';
                bool last_was_open {true};
                for (auto i {robot_y_-1}; i >= temp_loc; --i) {
                    map_.at(robot_x_).at(i)= last_was_open ? ']':'[';
                    last_was_open = !last_was_open;
                }
            }
        }
    }

    for(int x {0}; x < map_.size(); ++x) {
        printf("%s\n", map_.at(x).c_str());
    }
}

int main() {
    std::string temp_line;
    std::string doubled_temp_line {""};
    std::ifstream file("input15.txt");

    std::vector<char> moves;
    std::vector<std::string> map;
    std::vector<std::string> doubled_map;
    uint64_t robot_x;
    uint64_t robot_y;
    uint64_t doubled_robot_x;
    uint64_t doubled_robot_y;
    uint64_t line_count;

    getline(file, temp_line);

    do {
        printf("here0\n");
        ++line_count;
        map.push_back(temp_line);
        for (int ind {0}; ind < temp_line.size(); ++ind) {
            if (temp_line.at(ind) == '#') {
                doubled_temp_line += "##";
            } else if (temp_line.at(ind) == '.') {
                doubled_temp_line += "..";
            } else if (temp_line.at(ind) == '@') {
                robot_y = ind;
                robot_x = line_count-1;
                printf("here1\n");

                doubled_temp_line += "@.";
                doubled_robot_x = line_count-1;
                doubled_robot_y = doubled_temp_line.size()-2;
            } else if (temp_line.at(ind) == 'O') {
                doubled_temp_line += "[]";
            }
        }
        doubled_map.push_back(doubled_temp_line);
        doubled_temp_line = "";
        getline(file, temp_line);
    } while(temp_line != "##################################################"); //while(temp_line != "##########");//

    map.push_back(temp_line);
    doubled_map.push_back(temp_line+temp_line);
    getline(file, temp_line);

    printf("New map:\n");
    for (auto i {doubled_map.begin()}; i < doubled_map.end(); ++i) {
        printf("%s\n", (*i).c_str());
    }

    while(getline(file, temp_line)) {
        printf("here2: %s\n", temp_line.c_str());
        for (int ind {0}; ind < temp_line.size(); ++ind) {
            moves.push_back(temp_line.at(ind));
        }
    }

    // *do_a_move(moves, map, robot_x, robot_y, line_count-1, map.front().size()-1);*/
    for (auto move {moves.begin()}; move < moves.end(); ++move) {
        do_a_new_move(*move, doubled_map, doubled_robot_x, doubled_robot_y, line_count-1, doubled_map.front().size()-2);
    }

    
    uint64_t first_answer {0};
    uint64_t second_answer {0};
    for(int line_ind {0}; line_ind < line_count; ++line_ind) {
        temp_line = map.at(line_ind);
        printf("here8: %s\n", temp_line.c_str());
        for (int inside_line_ind {0}; inside_line_ind < temp_line.size(); ++inside_line_ind) {
            if(temp_line.at(inside_line_ind) == 'O') {
                first_answer += (line_ind)*100 + inside_line_ind;
            } 
        }
        temp_line = doubled_map.at(line_ind);
        for (int inside_line_ind {0}; inside_line_ind < temp_line.size()-1; ++inside_line_ind) {
            if(temp_line.at(inside_line_ind) == '[' && temp_line.at(inside_line_ind+1) == ']') {
                second_answer += (line_ind)*100 + inside_line_ind;
            } 
        }

    }

    printf("First: %llu. Second: %llu.\n", first_answer, second_answer);

    return 0;
}