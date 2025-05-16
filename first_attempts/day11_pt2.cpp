#include <string>
#include <fstream>
#include <sstream>
#include <map>
const uint64_t blinks_const {75};

uint64_t recursive_blinks(uint64_t val, uint64_t blinks_remaining, std::map<uint64_t, uint64_t[blinks_const+1]>& cached_values_) {
    printf("Called for val=%llu and blinks=%llu\n", val, blinks_remaining);
    if(cached_values_.contains(val) && cached_values_[val][blinks_remaining] != 0) return cached_values_[val][blinks_remaining];
    printf("here2\n");
    if (blinks_remaining == 0) {
        cached_values_[val][blinks_remaining] = 1;
        printf("here3\n");
    } else {
        printf("here4\n");
        if(val==0) {cached_values_[val][blinks_remaining] = recursive_blinks(1, blinks_remaining-1, cached_values_);
        } else {
            uint64_t num_digits = std::to_string(val).size();
            if (num_digits%2==1) {cached_values_[val][blinks_remaining] = recursive_blinks(val*2024, blinks_remaining-1, cached_values_);
            } else {
            num_digits = pow(10, (num_digits/2));
            printf("here5: will calculate %llu and %llu\n", val/num_digits, val%num_digits);
            cached_values_[val][blinks_remaining] =  recursive_blinks(val/num_digits, blinks_remaining-1, cached_values_) + recursive_blinks(val%num_digits, blinks_remaining-1, cached_values_);
            }
        }  
    }

    return cached_values_[val][blinks_remaining];
}

int main() {
    std::ifstream file ("input11.txt");
    std::string temp_line;
    getline(file, temp_line);
    std::stringstream ss (temp_line);
    std::vector<uint64_t> stones;
    uint64_t total {0};
    while (ss>>temp_line) {
        stones.push_back(std::stoull(temp_line));
        temp_line = "";
    }

    std::map<uint64_t, uint64_t[blinks_const+1]> cached_values;

    for (uint64_t blink_temp {0}; blink_temp<=blinks_const; ++blink_temp) {
        printf("here0\n");
        for(uint64_t val {0}; val < 100; ++val) {
            printf("here1\n");
            cached_values[val][blink_temp] = recursive_blinks(val, blink_temp, cached_values);
            printf("[%llu][%llu]=%llu ", val, blink_temp, cached_values[val][blink_temp]);
        }
        printf("\n");
    }

    printf("here6\n");
    for (auto it {stones.begin()}; it < stones.end(); ++it) {
        total += recursive_blinks(*it, blinks_const, cached_values);
    }

    printf("result is %llu\n", total);
    return 0;
}
