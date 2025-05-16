#include <string>
#include <fstream>
#include <sstream>

int main() {
    std::ifstream file ("input11.txt");
    std::string temp_line;
    getline(file, temp_line);
    std::stringstream ss (temp_line);
    temp_line = "";

    std::vector<std::string> stones;
    while (ss>>temp_line) {
        stones.push_back(temp_line);
        temp_line = "";
    }

    uint64_t blinks {75};
    while (blinks) {
        for (auto it {stones.begin()}; it < stones.end(); ++it) {
            //printf("here2: %s\n", (*it).c_str());
            if((*it) == "0") {
                (*it) = "1";
                //printf("0 to 1\n");
            } else if ((*it).size()%2==0) {
                std::string og_val = (*it);
                uint64_t half = og_val.size()/2;
                //printf("mod2 half=%llu", half);
                (*it) = og_val.substr(0, half);
                og_val = og_val.substr(half, half);
                //printf(" value1=%s value2=%s\n", (*it).c_str(), og_val.c_str());
                while (og_val.at(0) == '0' && og_val.size() > 1) {
                    og_val= og_val.substr(1, og_val.size()-1);
                }
                //printf(" without zeroes is %s \n", og_val.c_str());
                it = stones.insert(++it, og_val);
                //printf("new 2 values: %s %s\n", (*(it-1)).c_str(), (*it).c_str());
            } else {
                //printf("else\n");
                uint64_t value = std::stoull((*it));
                value *= 2024;
                (*it) = std::to_string(value);
                //printf("new value: %llu %s \n", value, (*it).c_str());
            }
        }

        //printf("Blink: ");
        for (auto it {stones.begin()}; it < stones.end(); ++it) {
            //printf("%s ", (*it).c_str());
        }
        printf("\n Size: %zu \n", stones.size());
        --blinks;
    }
    return 0;
}