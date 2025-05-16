#include <fstream>
#include <sstream>
#include <string>
#include <tuple>

int main() {
    std::ifstream file ("input9.txt");
    std::string temp_line;
    std::vector<uint64_t> inp;
    if(getline(file, temp_line)) {
        for(auto it {temp_line.begin()}; it < temp_line.end(); ++it) {
            inp.push_back(static_cast<uint64_t>(*it));
            //printf("%c ", *it);
        }
        //printf("\n\n");
    }
    std::vector<uint64_t> translated_inp;
    std::vector<std::tuple<uint64_t, uint64_t, uint64_t>> mem_blocks;
    std::vector<std::pair<uint64_t, uint64_t>> free_blocks;
    uint64_t ind_counter {0};
    uint64_t temp_counter {0};
    uint64_t empty_sym {300000};

    for(uint64_t i {0}; i< inp.size(); ++i) {
        uint64_t repeater {empty_sym};
        //printf("Index i=%d ", i);
        if (i%2==0) {
            repeater = ind_counter++;
            //printf("Adding mem block (%llu, %llu, %llu) \n", temp_counter,  inp.at(i)-'0', repeater);
            mem_blocks.push_back(std::make_tuple(temp_counter,  inp.at(i)-'0', repeater));
        } else {
            free_blocks.push_back(std::pair(temp_counter,  inp.at(i)-'0'));
            //printf("Adding free mem (%llu, %llu) \n", temp_counter,  inp.at(i)-'0');
        }

        for (uint64_t j {0}; j < inp.at(i)-'0'; ++j) {
            translated_inp.push_back(repeater);
            //printf(" is added %llu beacuse j=%d and inp.at(i) = %llu \n", repeater, j, inp.at(i)-'0');
            //if (temp_counter > 50320 && temp_counter < 50370)
                //printf("Index %llu: %llu \n", temp_counter,repeater);
            temp_counter++;
        }
        
    }
    //printf("\n");

    uint64_t translated_inp_size {translated_inp.size()};
    uint64_t end_ind {translated_inp_size-1};
    uint64_t start_ind {0};
    uint64_t checksum {0};

    while (end_ind>=start_ind) {
        while (translated_inp.at(start_ind)!=empty_sym && end_ind>=start_ind) {
            checksum += translated_inp.at(start_ind)*start_ind;
            if (start_ind > 50320) {
                    //printf("Added start_ind=%llu element %llu\n", start_ind, translated_inp.at(start_ind));
                    //printf("Current checksum=%llu\n", checksum);
                }
            ++start_ind;
        }

        while (translated_inp.at(start_ind)==empty_sym && end_ind>=start_ind) {
            if (translated_inp.at(end_ind)!=empty_sym) {
                checksum += translated_inp.at(end_ind)*start_ind;
                if (start_ind > 50320) {
                    //printf("Added end_ind=%llu at start_ind=%llu element %llu\n", end_ind, start_ind, translated_inp.at(end_ind));
                    //printf("Current checksum=%llu\n", checksum);
                }
                ++start_ind;
            }

            --end_ind;
        }
    }

    while (translated_inp.at(start_ind)!=empty_sym) {
            checksum += translated_inp.at(start_ind)*start_ind;
            if (start_ind > 50320) {
                    printf("Added start_ind=%llu element %llu\n", start_ind, translated_inp.at(start_ind));
                    printf("Current checksum=%llu\n", checksum);
                }
            ++start_ind;
        }

    uint64_t checksum2 {0};
    bool temp_done {false};
    for (auto free_it {free_blocks.begin()}; free_it < free_blocks.end(); ++free_it) {
        temp_done = false;
        for (auto mem_it{mem_blocks.end()-1}; mem_it >= mem_blocks.begin(); --mem_it) {
            //printf("Comparing free %llu %llu and Mem %llu %llu \n",(*free_it).first, (*free_it).second, std::get<1>(*mem_it), std::get<0>(*mem_it));
            if ((*free_it).second > std::get<1>(*mem_it) && (*free_it).first < std::get<0>(*mem_it)) {
                std::get<0>(*mem_it) = (*free_it).first;
                (*free_it).first += std::get<1>(*mem_it);
                (*free_it).second -= std::get<1>(*mem_it);
                free_it = free_blocks.begin();
                //printf("Moved mem %llu to %llu %llu and free to %llu %llu\n", std::get<2>(*mem_it), std::get<0>(*mem_it), std::get<1>(*mem_it), (*free_it).first, (*free_it).second);
                temp_done = true;
                break;
            } else if ((*free_it).second == std::get<1>(*mem_it) && (*free_it).first < std::get<0>(*mem_it)) {
                std::get<0>(*mem_it) = (*free_it).first;
                free_blocks.erase(free_it);
                //printf("Moved mem %llu to %llu %llu\n", std::get<2>(*mem_it), std::get<0>(*mem_it), std::get<1>(*mem_it));
                free_it = free_blocks.begin();
                temp_done = true;
                break;
            }
        }
        if (temp_done) {
            free_it = free_blocks.begin()-1;
            std::sort(mem_blocks.begin(), mem_blocks.end(), [](auto it1, auto it2) {return std::get<0>(it1) < std::get<0>(it2);});
        }
    }

    for (auto mem_it{mem_blocks.end()-1}; mem_it >= mem_blocks.begin(); --mem_it) {
        for (uint64_t i {std::get<0>(*mem_it)}; i< std::get<0>(*mem_it)+std::get<1>(*mem_it); ++i)
            checksum2 += std::get<2>(*mem_it) * i;
    }

    printf("First part: %llu. Second part: %llu \n", checksum, checksum2);

    return 0;
}