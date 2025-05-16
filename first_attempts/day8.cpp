#include <string>
#include <fstream>
#include <ranges>

int main() {
    std::string temp_line;
    std::ifstream file ("input8.txt");
    uint64_t siz {50};
    std::vector<std::string> og_map;
    std::vector<std::string> antinodes;
    uint64_t ascii_values [62];
    for (int i {65}; i<=90; ++i)
        ascii_values[i-65] = i;
    for (int i {97}; i<=122; ++i)
        ascii_values[i-97+26] = i;
    for (int i {48}; i<=57; ++i)
        ascii_values[i+52-48] = i;
    
    while(getline(file, temp_line)) {
        og_map.push_back(temp_line);
        antinodes.push_back(std::string(siz, '.'));
    }

    bool part2 {true};
    for(uint64_t ascii_value : ascii_values) {
        for (int i {0}; i< siz; ++i) {
            for (int j {0}; j < siz; ++j) {
                if(og_map[i][j] == static_cast<char>(ascii_value)) {
                    printf("Found base %c at i=%u and j=%u \n", og_map[i][j], i, j);
                    for (int i_ {i}; i_ < siz; ++i_) {
                        for (int j_ {i==i_? j+1: 0}; j_<siz; ++j_) {
                            if (og_map[i_][j_] == static_cast<char>(ascii_value)) {
                                    antinodes[i][j] = '#';
                                    antinodes[i_][j_] = '#';
                                uint64_t reps {0};
                                while (part2 && reps<1000) {
                                    printf("Found a pair %c at i_=%u and j_=%u \n", og_map[i_][j_], i_, j_);
                                    if ((j_ >= j ? j+(2+reps)*(j_-j)<siz : j-(2+reps)*(j-j_)>=0) && i+(2+reps)*(i_-i) < siz) {
                                        if (j_>=j || j-(2+reps)*(j-j_) < 1000)
                                            antinodes[i+(2+reps)*(i_-i)][(j_ >= j)?(j+(2+reps)*(j_-j)):(j-(2+reps)*(j-j_))] = '#';
                                        printf("Set an antinode at i=%llu and j=%llu \n", (i+(2+reps)*(i_-i)), j+(2+reps)*(j_-j));
                                        for (int i {0}; i< siz; ++i) {
                                            for (int j {0}; j<siz; ++j) {
                                                printf("%c", antinodes.at(i).at(j));
                                            }
                                            printf("\n");
                                        }
                                    } else {
                                        printf("Coord don't pass first i=%llu and j=%llu \n", (i+(2+reps)*(i_-i)), j+(2+reps)*(j_-j));
                                    }

                                    if ((j_ >= j ? j>=(1+reps)*(j_-j) : j+(1+reps)*(j-j_)<siz) && i>= (1+reps)*(i_-i)) {
                                        antinodes[i-(1+reps)*(i_-i)][(j_ >= j)?(j-(1+reps)*(j_-j)):(j+(1+reps)*(j-j_))] = '#';
                                        printf("Set an antinode at i=%llu and j=%llu \n", (i-(1+reps)*(i_-i)), j+(1+reps)*(j-j_));
                                        for (int i {0}; i< siz; ++i) {
                                            for (int j {0}; j<siz; ++j) {
                                                printf("%c", antinodes.at(i).at(j));
                                            }
                                            printf("\n");
                                        }
                                    } else {
                                        printf("Coord don't pass second i=%llu and j=%llu \n", (i-(1+reps)*(i_-i)), j-(1+reps)*(j_-j));
                                    }

                                    ++reps;
                                }
                            }
                        }
                    }
                }
            }
        }
    }


    uint64_t answer1 {0};
    uint64_t answer2 {0};
    for (int i {0}; i< siz; ++i) {
        for (int j {0}; j<siz; ++j) {
            printf("%c", antinodes.at(i).at(j));
            if (antinodes.at(i).at(j) == '#') {
                ++(part2?answer2:answer1);
            }
        }
        printf("\n");
    }

    printf("First part: %llu. Second part: %llu \n", answer1, answer2);

    return 0;
}