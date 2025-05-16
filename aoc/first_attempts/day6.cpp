#include <string>
#include <fstream>
#include <algorithm>

bool path_looping(std::string map_ [130], int64_t new_obs_x, int64_t new_obs_y, std::vector<std::pair<int64_t, int64_t>> obstacles, int64_t guard_x, int64_t guard_y, uint64_t siz) {
    uint64_t direction {0};
    uint64_t checker {0};
    int64_t obstacle_x {-1};
    int64_t obstacle_y {-1};
    map_[new_obs_x][new_obs_y] = '#';
    obstacles.push_back(std::pair(new_obs_x, new_obs_y));
    while (!((guard_x == 0 && direction==1) || (guard_x == siz-1&& direction==3) || (guard_y == 0 && direction==0) || (guard_y == siz-1 && direction==2))) {
        if (direction%4==0) {
            obstacle_x = -1;
            obstacle_y = -1;
            for (auto it {obstacles.begin()}; it < obstacles.end(); ++it) {
                if((*it).first>obstacle_x && (*it).second==guard_y && (*it).first < guard_x) {
                    obstacle_x = (*it).first;
                    obstacle_y = (*it).second;
                }
            }

            if(obstacle_x != -1) {
                guard_x = obstacle_x+1;
            } else {
                guard_x = 0;
                printf("exiting up, %llu \n", checker);
                return false;
            }
        }
        else if (direction%4==1) {
            obstacle_x = siz+1;
            obstacle_y = siz+1;
            for (auto it {obstacles.begin()}; it < obstacles.end(); ++it) {
                if((*it).first==guard_x && (*it).second<obstacle_y && (*it).second > guard_y) {
                    obstacle_x = (*it).first;
                    obstacle_y = (*it).second;
                }
            }
            if(obstacle_x != (siz+1)) {
                guard_y = obstacle_y-1;
            } else {
                guard_y = siz-1;
                printf("exiting right \n");
                return false;
            }
        }
        else if (direction%4==2) {
            obstacle_x = siz+1;
            obstacle_y = siz+1;
            for (auto it {obstacles.begin()}; it < obstacles.end(); ++it) {
                if((*it).first<obstacle_x && (*it).second==guard_y && (*it).first > guard_x) {
                    obstacle_x = (*it).first;
                    obstacle_y = (*it).second;
                }
            }
            if(obstacle_x != -1) {
                guard_x = obstacle_x-1;
            } else {
                guard_x = siz-1;
                printf("exiting down \n");
                return false;
            }
        }
        else if (direction%4==3) {
            obstacle_x = -1;
            obstacle_y = -1;
            for (auto it {obstacles.begin()}; it < obstacles.end(); ++it) {
                if((*it).first==guard_x && (*it).second>obstacle_y && (*it).second < guard_y) {
                    obstacle_x = (*it).first;
                    obstacle_y = (*it).second;
                }
            }
            if(obstacle_y != -1) {
                guard_y = obstacle_y+1;
            } else {
                guard_y = 0;
                printf("exiting left \n");
                return false;
            }
        }
        ++direction;
        if (direction == 4) direction = 0;

        ++checker;

        if(checker ==100000) {
            printf("Exiting a LOOP\n");
            return true;
        }
    }
    return false;
}

int main() {
    std::string temp_line;
    std::ifstream map_file ("input6.txt");
    uint64_t siz {130};
    std::string paths[siz];
    std::string map[siz];

    int row_temp {0};
    while(getline(map_file, temp_line)) {
        paths[row_temp] = temp_line;
        map[row_temp++] = temp_line;
    }

    std::vector<std::pair<int64_t, int64_t>> obstacles {};
    int64_t guard_x;
    int64_t guard_y;

    uint64_t direction {0}; // up, right, down, left

    for(int i {0}; i< siz; ++i) {
        for (int j {0}; j<siz; ++j) {
            if (map[i][j] == '#') {
                obstacles.push_back(std::pair(i, j));
            } else if (map[i][j] == '^') {
                guard_x = i;
                guard_y = j;
            }
        }
    }

    int64_t guard_x_OG = guard_x;
    int64_t guard_y_OG = guard_y;

    uint64_t checker {0};
    int64_t obstacle_x {-1};
    int64_t obstacle_y {-1};
    while (!((guard_x == 0 && direction==1) || (guard_x == siz-1&& direction==3) || (guard_y == 0 && direction==0) || (guard_y == siz-1 && direction==2))) {
        if (direction%4==0) {
            obstacle_x = -1;
            obstacle_y = -1;
            for (auto it {obstacles.begin()}; it < obstacles.end(); ++it) {
                if((*it).first>obstacle_x && (*it).second==guard_y && (*it).first < guard_x) {
                    obstacle_x = (*it).first;
                    obstacle_y = (*it).second;
                    printf("found better up obstacle %llu %llu for position %llu %llu\n", obstacle_x, obstacle_y, guard_x, guard_y);
                }
            }

            if(obstacle_x != -1) {
                printf("found up %llu %llu \n", obstacle_x, obstacle_y);
                for (int64_t j {guard_x}; j>obstacle_x; --j) {
                    paths[j][guard_y] = 'X';
                }
                guard_x = obstacle_x+1;
                paths[guard_x][guard_y] = '^';
            } else {
                for (int64_t j {guard_x}; j>0; --j) {
                    paths[j][guard_y] = 'X';
                }
                paths[0][guard_y] = 'X';
                guard_x = 0;
                break;
            }
        }
        else if (direction%4==1) {
            obstacle_x = siz+1;
            obstacle_y = siz+1;
            for (auto it {obstacles.begin()}; it < obstacles.end(); ++it) {
                if((*it).first==guard_x && (*it).second<obstacle_y && (*it).second > guard_y) {
                    obstacle_x = (*it).first;
                    obstacle_y = (*it).second;
                    printf("found better up obstacle %llu %llu for position %llu %llu\n", obstacle_x, obstacle_y, guard_x, guard_y);
                }
            }
            if(obstacle_x != (siz+1)) {
                for (int64_t j {guard_y}; j<obstacle_y; ++j) {
                    paths[guard_x][j] = 'X';
                }
                guard_y = obstacle_y-1;
                paths[guard_x][guard_y] = '^';
            } else {
                for (int64_t j {guard_y}; j<siz; ++j) {
                    paths[guard_x][j] = 'X';
                }
                guard_y = siz-1;
                break;
            }
        }
        else if (direction%4==2) {
            obstacle_x = siz+1;
            obstacle_y = siz+1;
            for (auto it {obstacles.begin()}; it < obstacles.end(); ++it) {
                if((*it).first<obstacle_x && (*it).second==guard_y && (*it).first > guard_x) {
                    obstacle_x = (*it).first;
                    obstacle_y = (*it).second;
                    printf("found better up obstacle %llu %llu for position %llu %llu\n", obstacle_x, obstacle_y, guard_x, guard_y);
                }
            }
            if(obstacle_x != -1) {
                for (int64_t j {guard_x}; j<obstacle_x; ++j) {
                    paths[j][guard_y] = 'X';
                }
                guard_x = obstacle_x-1;
                paths[guard_x][guard_y] = '^';
            } else {
                for (int64_t j {guard_x}; j<siz; ++j) {
                    paths[j][guard_y] = 'X';
                }
                guard_x = siz-1;
                break;
            }
        }
        else if (direction%4==3) {
            obstacle_x = -1;
            obstacle_y = -1;
            for (auto it {obstacles.begin()}; it < obstacles.end(); ++it) {
                if((*it).first==guard_x && (*it).second>obstacle_y && (*it).second < guard_y) {
                    obstacle_x = (*it).first;
                    obstacle_y = (*it).second;
                    printf("found better up obstacle %llu %llu for position %llu %llu\n", obstacle_x, obstacle_y, guard_x, guard_y);
                }
            }
            if(obstacle_y != -1) {
                for (int64_t j {guard_y}; j>obstacle_y; --j) {
                    paths[guard_x][j] = 'X';
                }
                guard_y = obstacle_y+1;
                paths[guard_x][guard_y] = '^';
            } else {
                for (int64_t j {guard_y}; j>0; --j) {
                    paths[guard_x][j] = 'X';
                }
                guard_y = 0;
                paths[guard_x][guard_y] = 'X';
                break;
            }
        }
        ++direction;
        if (direction == 4) direction = 0;
    }

    for(int i {0}; i< siz; ++i) {
        printf("%s \n",paths[i].c_str());
    }
    printf("\n");
    uint64_t total_paths {0};
    for(int i {0}; i< siz; ++i) {
        for (int j {0}; j<siz; ++j) {
            if (paths[i][j] == 'X' || paths[i][j] == '^')
            ++total_paths;
        }
    }

    path_looping(paths, 70, 60, obstacles, guard_x_OG, guard_y_OG, siz);

    paths[guard_x_OG][guard_y_OG] = '^';
    uint64_t loop_count {0};
    for(int i {0}; i< siz; ++i) {
        for (int j {0}; j<siz; ++j) {
            if (paths[i][j] == 'X') {
                loop_count += path_looping(map, i, j, obstacles, guard_x_OG, guard_y_OG, siz) ? 1 : 0;
            }
        }
    }

    printf("First part is: %llu Second part is %llu.\n", total_paths, loop_count);
    return 0;
}