#include <string>
#include <fstream>
#include <sstream>
#include <map>

bool is_possible(std::string curr_towel, std::vector<std::string>& blocks) {
    printf("Looking into %s.\n", curr_towel.c_str());
    if (curr_towel == "") {
        printf("Empty so good\n");
        return true;
    } else {
        bool answer {false};
        auto towel_size {curr_towel.size()};
        for (auto block{blocks.begin()}; block < blocks.end(); ++block) {
            auto blk_size {(*block).size()};
            if(towel_size >= blk_size && curr_towel.substr(0, blk_size) == (*block)) {
                answer = answer || is_possible(curr_towel.substr(blk_size, towel_size - blk_size), blocks);
            }
            if(answer)
                break;
        }
        return answer;
    }
}

void count_possible(std::string curr_towel, std::vector<std::string>& blocks, std::vector<uint64_t>& sol_count) {
    //printf("Looking into %s.\n", curr_towel.c_str());
    auto towel_size {curr_towel.size()};
    for (auto i {0}; i < towel_size; ++i) {
        for (auto block{blocks.begin()}; block < blocks.end(); ++block) {
            auto blk_size {(*block).size()};
            if(i+1 >= blk_size && curr_towel.substr(i+1-blk_size, blk_size) == (*block)) {
                if (i+1 > blk_size) {
                    sol_count.at(i) += sol_count.at(i-blk_size);
                } else {
                    ++sol_count.at(i);
                }
            }
        }
    }
}

int main() {
    std::vector<std::string> blocks;
    std::vector<std::string> towels;

    std::ifstream file("input19.txt");
    std::string temp_line;

    getline(file, temp_line);
    std::reverse(temp_line.begin(), temp_line.end());

    auto comma_loc {std::find(temp_line.begin(), temp_line.end(), ' ')};
    auto dist {std::distance(temp_line.begin(), comma_loc)};
    while(comma_loc != temp_line.end() ) {
        blocks.push_back(temp_line.substr(0, dist));
        temp_line = temp_line.substr(dist+2, std::distance(comma_loc+2, temp_line.end()));
        comma_loc = std::find(temp_line.begin(), temp_line.end(), ' ');
        dist = std::distance(temp_line.begin(), comma_loc);
        //printf("%s, ", blocks.back().c_str());
    }

    blocks.push_back(temp_line);
    //printf("%s\n", blocks.back().c_str());

    getline(file, temp_line); //empty one
    //printf("\n");

    while (getline(file, temp_line)) {
        std::reverse(temp_line.begin(), temp_line.end());
        towels.push_back(temp_line);
        //printf("%s\n", towels.back().c_str());
    }

    uint16_t first_answer {0};
    uint64_t second_answer {0};
    std::vector<uint64_t> sol_count;
    for (auto towel {towels.begin()}; towel < towels.end(); ++towel) {
        if (is_possible((*towel), blocks)) {
            sol_count.clear();
            sol_count = std::vector<uint64_t>((*towel).size(), 0);
            first_answer += 1;
            count_possible((*towel), blocks, sol_count);
            second_answer += sol_count.back();
        }
    }


    printf("First: %u. Second: %llu.\n", first_answer, second_answer);

    return 0;
}