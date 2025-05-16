#include <string>
#include <fstream>
#include <regex>
#include <iterator>
#include <utility>

uint64_t LR_count(uint64_t siz_, std::vector<std::vector<char>> input_) {
    uint64_t LR_count_sum {0};
    for (int i {0}; i < siz_; ++i) {
        for (int j {0}; j< siz_-3; ++j)
        if (input_.at(i).at(j)=='X') {
            if (input_.at(i).at(j+1)=='M' && input_.at(i).at(j+2)=='A' && input_.at(i).at(j+3)=='S') {
                ++LR_count_sum;
                j += 3;
            }
        }
    }

    return LR_count_sum;
}

uint64_t RL_count(uint64_t siz_, std::vector<std::vector<char>> input_) {
    uint64_t RL_count_sum {0};
    for (int i {0}; i < siz_; ++i) {
        for (int j {0}; j< siz_-3; ++j)
        if (input_.at(i).at(j)=='S') {
            if (input_.at(i).at(j+1)=='A' && input_.at(i).at(j+2)=='M' && input_.at(i).at(j+3)=='X') {
                ++RL_count_sum;
                j += 3;
            }
        }
    }

    return RL_count_sum;
}

uint64_t vertical_count(uint64_t siz_, std::vector<std::vector<char>> input_) {
    std::vector<std::vector<char>> input_swapped (siz_, std::vector<char>(siz_));
    for (int j {0}; j< siz_; ++j) {
        for (int k {0}; k < siz_; ++k) {
            input_swapped.at(k).at(j) = input_.at(j).at(k);
        }
    }
    return (RL_count(siz_, input_swapped) + LR_count(siz_, input_swapped));
}

std::pair<uint64_t, uint64_t> RL_diag_count(uint64_t siz_, std::vector<std::vector<char>> input_) {
    uint64_t L_count {0};
    uint64_t R_count {0};
    for (int i {0}; i < siz_-3; ++i) {
        for (int j {0}; j< siz_; ++j)
        if (input_.at(i).at(j)=='S') {
            if (j > 2 && input_.at(i+1).at(j-1)=='A' && input_.at(i+2).at(j-2)=='M' && input_.at(i+3).at(j-3)=='X') {
                ++L_count;
            }

            if (j < siz_-3 && input_.at(i+1).at(j+1)=='A' && input_.at(i+2).at(j+2)=='M' && input_.at(i+3).at(j+3)=='X') {
                ++R_count;
            }
        }
    }

    return std::pair(L_count, R_count);
}

std::pair<uint64_t, uint64_t> LR_diag_count(uint64_t siz_, std::vector<std::vector<char>> input_) {
    uint64_t L_count {0};
    uint64_t R_count {0};
    for (int i {0}; i < siz_-3; ++i) {
        for (int j {0}; j< siz_; ++j)
        if (input_.at(i).at(j)=='X') {
            if (j > 2 && input_.at(i+1).at(j-1)=='M' && input_.at(i+2).at(j-2)=='A' && input_.at(i+3).at(j-3)=='S') {
                ++L_count;
            }

            if (j < siz_-3 && input_.at(i+1).at(j+1)=='M' && input_.at(i+2).at(j+2)=='A' && input_.at(i+3).at(j+3)=='S') {
                ++R_count;
            }
        }
    }

    return std::pair(L_count, R_count);
}



int main() {
    std::string line_temp;
    uint64_t siz {140};
    std::vector<std::vector<char>> line_total;
    std::ifstream file ("input4.txt");

    for (int i {0}; i < siz; ++i) {
        getline(file, line_temp);
        line_total.push_back(std::vector<char> (line_temp.begin(), line_temp.end()));
    }

    uint64_t total_count {0};
    std::pair<uint64_t, uint64_t> temp_pair;
    total_count += LR_count(siz, line_total) + RL_count(siz, line_total);
    printf("LR_count: %llu RL_count: %llu \n", LR_count(siz, line_total), RL_count(siz, line_total));
    temp_pair = RL_diag_count(siz, line_total);
    total_count += temp_pair.first + temp_pair.second;
    printf("RL_diag_count first: %llu second: %llu \n", temp_pair.first, temp_pair.second);
    temp_pair = LR_diag_count(siz, line_total);
    total_count += temp_pair.first + temp_pair.second;
    printf("LR_diag_count first: %llu second: %llu \n", temp_pair.first, temp_pair.second);
    total_count += vertical_count(siz, line_total);
    printf("vertical_count: %llu \n", vertical_count(siz, line_total));
    printf("total: %llu \n", total_count);

    return 0;
}
