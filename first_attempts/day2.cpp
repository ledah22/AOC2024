#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>

bool is_it_safe(std::vector<int64_t>& intensities_, int64_t size_temp_) {
    bool safe_temp_ {true};
    bool pos_dir_;

    if (size_temp_ >= 2) {
        pos_dir_ = (intensities_.at(1) > intensities_.at(0) && intensities_.at(1) != intensities_.at(0));
        for (int j {1}; j < size_temp_; ++j) {
            if ((intensities_.at(j) != intensities_.at(j-1)) && (pos_dir_ ? (intensities_.at(j) > intensities_.at(j-1)) : (intensities_.at(j) < intensities_.at(j-1))) && (abs(intensities_.at(j) - intensities_.at(j-1))>0) && (abs(intensities_.at(j) - intensities_.at(j-1))<4)) {
               // all good 
               //printf("safe \n");
            } else {
                //printf("unsafe \n");
                safe_temp_ = false;
            }
        }
    }

    return safe_temp_;
}
int main() {
    std::string temp_line;
    int64_t safe_count {0};
    int64_t moderately_safe_count {0};
    std::ifstream file ("input2.txt");
    std::stringstream ss;
    std::vector<int64_t> intensities;
    std::vector<int64_t> intensities_temp;
    int64_t value {0};
    bool safe_temp;
    bool moderately_safe_temp {true};
    int64_t size_temp {0};
    bool temp_mod_safety;

    while (getline(file, temp_line)) {
        ss = std::stringstream (temp_line);
        while (ss >> value) {
            intensities.emplace_back(value);
        }

        size_temp = intensities.size();

        safe_temp = is_it_safe(intensities, size_temp);
        moderately_safe_temp = safe_temp;

        if (!safe_temp) {
            temp_mod_safety = false;
            int64_t ind_ {0};
            while (!temp_mod_safety && ind_ < size_temp) {
                intensities_temp = intensities;
                auto it {intensities_temp.begin()};
                std::advance(it, ind_);
                intensities_temp.erase(it);
                temp_mod_safety = is_it_safe(intensities_temp, size_temp-1);
                ++ind_;
            }
            moderately_safe_temp = temp_mod_safety;
        }

        moderately_safe_count+= moderately_safe_temp;
        safe_count += safe_temp;
        printf("New moderate count %llu \n", moderately_safe_count);
        safe_temp = true;
        intensities.clear();
    }

    printf("%llu and if loosened %llu \n", safe_count, moderately_safe_count);
    return 0;
}