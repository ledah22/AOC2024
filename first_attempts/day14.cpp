#include <string>
#include <fstream>

int main() {
    const uint64_t width {101}; //101
    const uint64_t height {103}; //103
    int64_t coord[height][width] {0};
    std::string temp_line;
    std::ifstream file ("input14.txt");
    uint64_t robo_count {0};
    std::vector<std::pair<std::pair<int64_t, int64_t>, std::pair<int64_t, int64_t>>> robots;
    uint64_t ind_temp;
    uint64_t val_temp;
    bool pos_temp;

    while (getline(file, temp_line)) {
        ++robo_count;
        val_temp = 0;
        //printf("here6\n");
        robots.push_back(std::pair<std::pair<int64_t, int64_t>, std::pair<int64_t, int64_t>> ());
 
        ind_temp = 2;
        //printf("dbg %c\n", temp_line.at(ind_temp));
        while(temp_line.at(ind_temp)>='0' && temp_line.at(ind_temp)<='9') {
            //printf("here0\n");
            val_temp = val_temp*10 + (temp_line.at(ind_temp)-'0');
            ++ind_temp;
        }
        robots.back().first.first = val_temp;
        ind_temp+=1;
        val_temp = 0;
        while(temp_line.at(ind_temp)>='0' && temp_line.at(ind_temp)<='9') {
            //printf("here1\n");
            val_temp = val_temp*10 + (temp_line.at(ind_temp)-'0');
            ++ind_temp;
        }
        robots.back().first.second = val_temp;

        ind_temp+=3;
        val_temp = 0;
        pos_temp = true;
        if(temp_line.at(ind_temp) == '-') {
            pos_temp = false;
            ++ind_temp;
        }
        while(temp_line.at(ind_temp)>='0' && temp_line.at(ind_temp)<='9') {
            //printf("here1\n");
            val_temp = val_temp*10 + (temp_line.at(ind_temp)-'0');
            ++ind_temp;
        }
        robots.back().second.first = val_temp*((pos_temp)?1:(-1));

        ind_temp+=1;
        val_temp = 0;
        pos_temp = true;
        if(temp_line.at(ind_temp) == '-') {
            pos_temp = false;
            ++ind_temp;
        }
        while(ind_temp < temp_line.size() && temp_line.at(ind_temp)>='0' && temp_line.at(ind_temp)<='9') {
            //printf("here1\n");
            val_temp = val_temp*10 + (temp_line.at(ind_temp)-'0');
            ++ind_temp;
        }
        robots.back().second.second = val_temp*((pos_temp)?1:(-1));
        
        //printf("p_x: %lld, p_y: %lld, v_x=%lld, v_y=%lld\n", robots.back().first.first, robots.back().first.second, robots.back().second.first, robots.back().second.second);

    }

    for (auto robot {robots.begin()}; robot < robots.end(); ++robot) {
        ++coord[(*robot).first.second][(*robot).first.first];
    }

    for (auto i {0}; i < height; ++i) {
        for (auto j {0}; j < width; ++j) {
            printf("%llu ", coord[i][j]);
            coord[i][j] = 0;
        }

        printf("\n");
    }

    printf("Now the solution: \n");

    uint64_t steps {100};
    uint64_t steps_pt2 {0};
    while (steps) {
        for (auto robot {robots.begin()}; robot < robots.end(); ++robot) {
            //printf("Before p_x: %lld, p_y: %lld, v_x=%lld, v_y=%lld\n", (*robot).first.first, (*robot).first.second, (*robot).second.first, (*robot).second.second);
            (*robot).first.first = ((*robot).first.first+(*robot).second.first+ width)%width;
            (*robot).first.second = ((*robot).first.second+(*robot).second.second + height)%height;
            //printf("After: p_x: %lld, p_y: %lld, v_x=%lld, v_y=%lld\n", (*robot).first.first, (*robot).first.second, (*robot).second.first, (*robot).second.second);
        }
        --steps;
        ++steps_pt2;
    }
    
    for (auto robot {robots.begin()}; robot < robots.end(); ++robot) {
        ++coord[(*robot).first.second][(*robot).first.first];
    }

    for (auto i {0}; i < height; ++i) {
        for (auto j {0}; j < width; ++j) {
            printf("%llu ", coord[i][j]);
        }

        printf("\n");
    }

    uint64_t safety_0 {0};
    uint64_t safety_1 {0};
    uint64_t safety_2 {0};
    uint64_t safety_3 {0};

    uint64_t x_half {width/2};
    uint64_t y_half {height/2};
    //printf("Halves: %llu %llu \n", x_half, y_half);

    for (auto robot {robots.begin()}; robot < robots.end(); ++robot) {
        uint64_t pos_x = (*robot).first.first;
        uint64_t pos_y = (*robot).first.second;

        //printf("%llu %llu \n", pos_x, pos_y);

        if (pos_x < x_half) {
            if (pos_y < y_half) {
                ++safety_0;
                //printf("inc 0 \n");
            }

            if (pos_y > y_half) {
                ++safety_2;
                //printf("inc 2 \n");
            }
        }

        if (pos_x > x_half) {
            if (pos_y < y_half) {
                ++safety_1;
                //printf("inc 1 \n");
            }

            if (pos_y > y_half) {
                ++safety_3;
                //printf("inc 3 \n");
            }
        }
    }

    while (steps_pt2 < 1000000) {
        for (auto robot {robots.begin()}; robot < robots.end(); ++robot) {
            //printf("Before p_x: %lld, p_y: %lld, v_x=%lld, v_y=%lld\n", (*robot).first.first, (*robot).first.second, (*robot).second.first, (*robot).second.second);
            (*robot).first.first = ((*robot).first.first+(*robot).second.first+ width)%width;
            (*robot).first.second = ((*robot).first.second+(*robot).second.second + height)%height;
            //printf("After: p_x: %lld, p_y: %lld, v_x=%lld, v_y=%lld\n", (*robot).first.first, (*robot).first.second, (*robot).second.first, (*robot).second.second);
        }
        ++steps_pt2;

        for (auto i {0}; i < height; ++i) {
            for (auto j {0}; j < width; ++j) {
                coord[i][j] = 0;
            }
    
            printf("\n");
        }

        for (auto robot {robots.begin()}; robot < robots.end(); ++robot) {
            if (coord[(*robot).first.second][(*robot).first.first]!=0) {
                continue;
            } else {
                ++coord[(*robot).first.second][(*robot).first.first];
            }
        }

        for (auto i {0}; i < height; ++i) {
            for (auto j {0}; j < width; ++j) {
                printf("%c ", coord[i][j]==0?'.':'X');
            }

            printf("Solution could be is %llu \n", steps_pt2);
        }
        continue;
        
    }

    printf("First: %llu. Second: %llu\n", safety_0*safety_1*safety_2*safety_3, safety_0);
    return 0;
}