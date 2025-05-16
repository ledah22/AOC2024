#include <string>
#include <fstream>

void map_min_distances_from_E(std::vector<std::vector<uint32_t>>& cheapest_path, std::vector<std::vector<bool>>& walls, uint16_t dim, uint16_t x, uint16_t y, uint32_t steps_made) {
    if (cheapest_path.at(x).at(y) == std::numeric_limits<uint32_t>::max()) {
        cheapest_path.at(x).at(y) = steps_made;
    }
    //for(int i {0}; i< dim; ++i) {
    //    for(int j {0}; j< dim; ++j) {
    //        printf("%s ", (cheapest_path.at(i).at(j)== std::numeric_limits<uint32_t>::max()) ? "X" : std::to_string(cheapest_path.at(i).at(j)).c_str());
    //    }
    //    printf("\n");
    //}

    //for(int i {0}; i< dim; ++i) {
    //    for(int j {0}; j< dim; ++j) {
    //        printf("%s ", (walls.at(i).at(j)) ? "X" : ".");
    //    }
    //    printf("\n");
    //}
    //printf("\n\n");
    ++steps_made;

    if (x>0 && (cheapest_path.at(x-1).at(y) == std::numeric_limits<uint32_t>::max() && !(walls.at(x-1).at(y)))) {
        map_min_distances_from_E(cheapest_path, walls, dim, x-1, y, steps_made);
    }
    if (y>0 && (cheapest_path.at(x).at(y-1) == std::numeric_limits<uint32_t>::max() && !(walls.at(x).at(y-1)))) {
        map_min_distances_from_E(cheapest_path, walls, dim, x, y-1, steps_made);
    }
    if (y<dim-1 && (cheapest_path.at(x).at(y+1) == std::numeric_limits<uint32_t>::max() && !(walls.at(x).at(y+1)))) {
        map_min_distances_from_E(cheapest_path, walls, dim, x, y+1, steps_made);
    }
    if (x<dim-1 && (cheapest_path.at(x+1).at(y) == std::numeric_limits<uint32_t>::max() && !(walls.at(x+1).at(y)))) {
        map_min_distances_from_E(cheapest_path, walls, dim, x+1, y, steps_made);
    }
}

uint32_t beats_score(std::vector<std::vector<uint32_t>>& cheapest_path, std::vector<std::vector<bool>>& walls, uint16_t dim, uint16_t x, uint16_t y, uint16_t dir) {
    if (dir == 0) {
        if (x!=0 && x!=dim-1) {
            if(!walls.at(x-1).at(y) && !walls.at(x+1).at(y)) {
                if (cheapest_path.at(x-1).at(y) + 2 < cheapest_path.at(x+1).at(y)) {
                    //printf("Saving of %u\n", (cheapest_path.at(x+1).at(y) - (cheapest_path.at(x-1).at(y) + 2)));
                    return (cheapest_path.at(x+1).at(y) - (cheapest_path.at(x-1).at(y) + 2));
                }
            }
        }
    } else if (dir == 2) {
        if (x!=0 && x!=dim-1) {
            if(!walls.at(x-1).at(y) && !walls.at(x+1).at(y)) {
                if (cheapest_path.at(x+1).at(y) + 2 < cheapest_path.at(x-1).at(y)) {
                    //printf("Saving of %u\n", (cheapest_path.at(x-1).at(y) - (cheapest_path.at(x+1).at(y) + 2)));
                    return (cheapest_path.at(x-1).at(y) - (cheapest_path.at(x+1).at(y) + 2));
                }
            }
        }
    } else if (dir == 1) {
        if (y!=0 && y!=dim-1) {
            if(!walls.at(x).at(y-1) && !walls.at(x).at(y+1)) {
                if (cheapest_path.at(x).at(y-1) + 2 < cheapest_path.at(x).at(y+1)) {
                    //printf("Saving of %u\n",(cheapest_path.at(x).at(y+1) - (cheapest_path.at(x).at(y-1) + 2)));
                    return (cheapest_path.at(x).at(y+1) - (cheapest_path.at(x).at(y-1) + 2));
                }
            }
        }
    } else if (dir == 3) {
        if (y!=0 && y!=dim-1) {
            if(!walls.at(x).at(y-1) && !walls.at(x).at(y+1)) {
                if (cheapest_path.at(x).at(y+1) + 2 < cheapest_path.at(x).at(y-1)) {
                    //printf("Saving of %u\n", (cheapest_path.at(x).at(y-1) - (cheapest_path.at(x).at(y+1) + 2)));
                    return (cheapest_path.at(x).at(y-1) - (cheapest_path.at(x).at(y+1) + 2));
                }
            }
        }
    }

    return 0;

}

void map_path(std::vector<std::vector<uint32_t>>& cheapest_path, uint16_t dim, uint16_t x, uint16_t y, std::vector<std::pair<uint16_t, uint16_t>>& path) {
    path.push_back(std::pair(x, y));
    printf("Mapping (%u, %u)\n", x, y);
    if (cheapest_path.at(x).at(y) == 0)
        return;
    else {
        if (x > 0 && cheapest_path.at(x).at(y) == cheapest_path.at(x-1).at(y)+1) {
            map_path(cheapest_path, dim, x-1, y, path);
        } else if (y > 0 && cheapest_path.at(x).at(y) == cheapest_path.at(x).at(y-1)+1) {
            map_path(cheapest_path, dim, x, y-1, path);
        } else if (x < dim-1 && cheapest_path.at(x).at(y) == cheapest_path.at(x+1).at(y)+1) {
            map_path(cheapest_path, dim, x+1, y, path);
        } else if (y < dim-1 && cheapest_path.at(x).at(y) == cheapest_path.at(x).at(y+1)+1) {
            map_path(cheapest_path, dim, x, y+1, path);
        }
    }
}

int main() {
    std::string temp_line;
    std::ifstream file("input20.txt");
    std::uint16_t dim {141}; //15 or 141

    std::vector<std::vector<uint32_t>> cheapest_path;
    std::vector<std::vector<bool>> walls;
    std::pair<uint16_t, uint16_t> S;
    std::pair<uint16_t, uint16_t> E;

    while(getline(file, temp_line)) {
        cheapest_path.push_back(std::vector<uint32_t>(dim, std::numeric_limits<uint32_t>::max()));
        walls.push_back(std::vector<bool>(dim, false));
        for (uint16_t pos {0}; pos < dim; ++pos) {
            if (temp_line.at(pos) == '#') {
                walls.back().at(pos) = true;
            } else if (temp_line.at(pos) == 'S') {
                S = std::pair<uint16_t, uint16_t> (walls.size()-1, pos);
            } else if (temp_line.at(pos) == 'E') {
                E = std::pair<uint16_t, uint16_t> (walls.size()-1, pos);
            }
        }
    }

    //for(int i {0}; i < dim; ++i) {
    //    for(int j {0}; j < dim; ++j) {
    //        printf("%s",(i == S.first && j == S.second) ? "S" : ((i == E.first && j == E.second) ? "E" : ((walls.at(i).at(j)) ? "#" : ".")));
    //    }
    //    printf("\n");
    //}


    map_min_distances_from_E(cheapest_path, walls, dim, E.first, E.second, 0);
    uint32_t no_cheat_dist {cheapest_path.at(S.first).at(S.second)};
    std::vector<std::pair<uint16_t, uint16_t>> path;
    map_path(cheapest_path, dim, S.first, S.second, path);

    uint32_t first_answer {0};
    uint32_t saving_by_cheating {99};

    for (uint16_t x {0}; x < dim; ++x) {
        for (uint16_t y {0}; y < dim; ++y){
            if (walls.at(x).at(y)) {
                if (beats_score(cheapest_path, walls, dim, x, y, 0) >= saving_by_cheating) {
                    ++first_answer;
                }
                if (beats_score(cheapest_path, walls, dim, x, y, 1) >= saving_by_cheating) {
                    ++first_answer;
                }
                if (beats_score(cheapest_path, walls, dim, x, y, 2) >= saving_by_cheating) {
                    ++first_answer;
                }
                if (beats_score(cheapest_path, walls, dim, x, y, 3) >= saving_by_cheating) {
                    ++first_answer;
                }
            }
        }
    }

    uint16_t max_cheat_len {20};
    uint64_t second_answer {0};
    //  111720 was too low
    // 9306045 too high
    // 2400852 idk
    // 2606348 idk
    // 2399552 idk
    for (auto pos {path.begin()}; pos < path.end(); ++pos) {
        uint16_t cheat_centre_x {(*pos).first};
        uint16_t cheat_centre_y {(*pos).second};
        for (uint16_t cheat_x {(cheat_centre_x > max_cheat_len) ? static_cast<uint16_t>(cheat_centre_x - max_cheat_len) : static_cast<uint16_t>(0)}; cheat_x <= ((cheat_centre_x + max_cheat_len) < static_cast<uint16_t>(dim-1) ? (cheat_centre_x + max_cheat_len) : static_cast<uint16_t>(dim-1)); ++cheat_x) {
            for (uint16_t cheat_y {(cheat_centre_y > max_cheat_len) ? static_cast<uint16_t>(cheat_centre_y - max_cheat_len) : static_cast<uint16_t>(0)}; cheat_y <= ((cheat_centre_y + max_cheat_len) < static_cast<uint16_t>(dim-1) ? (cheat_centre_y + max_cheat_len) : static_cast<uint16_t>(dim-1)); ++cheat_y) {
                if (cheat_centre_x ==1 && cheat_centre_y == 3 && cheat_x==21 && cheat_y==24)  {
                    printf("Problematic case:\n !walls.at(cheat_x).at(cheat_y)=%u,\ncheapest_path.at(cheat_x).at(cheat_y)=%u\n (cheat_x > cheat_centre_x ? static_cast<uint16_t>(cheat_x - cheat_centre_x) : static_cast<uint16_t>(cheat_centre_x - cheat_x))=%u,\nsaving_by_cheating=%u,\n cheapest_path.at(cheat_centre_x).at(cheat_centre_y)=%u\n", (walls.at(cheat_x).at(cheat_y)==false), cheapest_path.at(cheat_x).at(cheat_y), (cheat_x > cheat_centre_x ? static_cast<uint16_t>(cheat_x - cheat_centre_x) : static_cast<uint16_t>(cheat_centre_x - cheat_x)), saving_by_cheating, cheapest_path.at(cheat_centre_x).at(cheat_centre_y));
                }
                uint16_t x_dist {(cheat_x > cheat_centre_x ? static_cast<uint16_t>(cheat_x - cheat_centre_x) : static_cast<uint16_t>(cheat_centre_x - cheat_x))};
                uint16_t y_dist {(cheat_y > cheat_centre_y ? static_cast<uint16_t>(cheat_y - cheat_centre_y) : static_cast<uint16_t>(cheat_centre_y - cheat_y))};
                if ((!walls.at(cheat_x).at(cheat_y)) && (x_dist + y_dist <= max_cheat_len) && (cheapest_path.at(cheat_x).at(cheat_y) + x_dist + y_dist + saving_by_cheating <= cheapest_path.at(cheat_centre_x).at(cheat_centre_y))) {
                    printf("Counting (%u, %u) to (%u, %u)\n", cheat_centre_x, cheat_centre_y, cheat_x, cheat_y);
                    ++second_answer;
                }

            }
        }
    }

    printf("First: %u. Second answer: %llu.\n", first_answer, second_answer);
    return 0;
}