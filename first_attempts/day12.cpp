#include <string>
#include <fstream>
static const uint64_t siz {140}; //10 or 140

void find_neighbours(char character, uint64_t replacement_val, uint64_t x, uint64_t y, uint64_t map[siz][siz], std::vector<std::string>& og_map) {
     //printf("here: %c %llu, x=%llu y=%llu\n", character, replacement_val, x, y);
    map[x][y] = replacement_val;
    if (x<siz-1 && og_map.at(x+1).at(y)==character && map[x+1][y]==0) find_neighbours(character, replacement_val, x+1, y, map, og_map);
    if (y<siz-1 && og_map.at(x).at(y+1)==character && map[x][y+1]==0) find_neighbours(character, replacement_val, x, y+1, map, og_map);
    if (x>0 && og_map.at(x-1).at(y)==character && map[x-1][y]==0) find_neighbours(character, replacement_val, x-1, y, map, og_map);
    if (y>0 && og_map.at(x).at(y-1)==character && map[x][y-1]==0) find_neighbours(character, replacement_val, x, y-1, map, og_map);
}

int main() {
    std::ifstream file ("input12.txt");
    std::string temp_line;
    std::vector<std::string> plot_input;
    while(getline(file, temp_line)) {
        plot_input.push_back(temp_line);
    }

    uint64_t plot[siz][siz] {};
    uint64_t value_index {1};
    for (uint64_t x {0}; x< siz; ++x) {
        for (uint64_t y{0}; y< siz; ++y) {
            if (plot[x][y]==0) {
                char comp_var {plot_input.at(x).at(y)};
                //find around
                find_neighbours(comp_var, value_index, x, y, plot, plot_input);
                ++value_index;
            }
        }
    }
    
    const uint64_t num_of_values {value_index-1};
    std::vector<uint64_t> areas;
    areas.insert(areas.end(), num_of_values, 0);
    for (uint64_t x {0}; x< siz; ++x) {
        for (uint64_t y{0}; y< siz; ++y) {
            ++areas.at(plot[x][y]-1);
        }
    }

    std::vector<uint64_t> perimeters;
    perimeters.insert(perimeters.end(), num_of_values, 0);
    for (uint64_t x {0}; x< siz; ++x) {
        for (uint64_t y{0}; y< siz; ++y) {
             //printf("Check: %llu %u %u %u %u\n", plot[x][y], (x<siz-1 && plot[x][y]!=plot[x+1][y]), (y<siz-1 && plot[x][y]!=plot[x][y+1]) ,(x>0 && plot[x][y]!=plot[x-1][y]), (y>0 && plot[x][y]!=plot[x][y-1]));
            perimeters.at(plot[x][y]-1)+= ((x<siz-1 && plot[x][y]!=plot[x+1][y]) ||x==siz-1) + ((y<siz-1 && plot[x][y]!=plot[x][y+1]) || y==siz-1) + ((x>0 && plot[x][y]!=plot[x-1][y]) || x==0)+((y>0 && plot[x][y]!=plot[x][y-1]) || y==0);
        }
    }

    //for (uint64_t x {0}; x< siz; ++x) {
    //    for (uint64_t y{0}; y< siz; ++y) {
    //        printf("%llu ", plot[x][y]);
    //    }
    //    printf("\n");
    //}
    std::vector<uint64_t> edges;
    edges.insert(edges.end(), num_of_values, 0);
    for (uint64_t x {0}; x< siz; ++x) {
        for (uint64_t y{0}; y< siz; ++y) {
            bool right {((x<siz-1 && plot[x][y]!=plot[x+1][y]) ||x==siz-1)};
            bool top {((y>0 && plot[x][y]!=plot[x][y-1]) || y==0)};
            bool left {((x>0 && plot[x][y]!=plot[x-1][y]) || x==0)};
            bool bottom {((y<siz-1 && plot[x][y]!=plot[x][y+1]) || y==siz-1)};

            bool diag_low_left {(y<siz-1 && x>0 && plot[x][y]!=plot[x-1][y+1]) && !left && !bottom};
            bool diag_low_right {y<siz-1 && x<siz-1 && plot[x][y]!=plot[x+1][y+1] && !right && !bottom};
            bool diag_top_right {y>0 && x<siz-1 && plot[x][y]!=plot[x+1][y-1] && !top && !right};
            bool diag_top_left {y>0 && x>0 && plot[x][y]!=plot[x-1][y-1] && !top && !left};
            //printf("Check: %llu %u %u %u %u %u %u %u %u\n", plot[x][y], right && top, top && left, left && bottom, bottom && right, diag_low_left, diag_low_right, diag_top_right, diag_top_left);
            edges.at(plot[x][y]-1)+= (right && top) + (top && left) + (left && bottom) + (bottom && right)\
                                    + diag_low_left + diag_low_right + diag_top_right + diag_top_left;
            //printf("Number of edges at %llu is %llu\n", plot[x][y], edges.at(plot[x][y]-1));
        }
    }

    uint64_t total1 {0};
    uint64_t total2 {0};
    for(uint64_t ind {0}; ind < num_of_values; ++ind) {
         //printf("Area: %llu ", areas[ind]);
         //printf("perimeter: %llu\n", perimeters[ind]);
        total1 += perimeters[ind]*areas[ind];
        total2 += edges[ind]*areas[ind];
    }

     printf("First: %llu. Second: %llu.\n", total1, total2);

    return 0;
}