#include <string>
#include <fstream>
#include <sstream>

int main() {
    std::string temp_line;
    std::ifstream rule_file("input5_rules.txt");
    std::ifstream file("input5.txt");
    std::stringstream ss;

    std::vector<std::pair<uint64_t, uint64_t>> rules;
    uint64_t temp1;
    uint64_t temp2;

    std::vector<uint64_t> values;

    while(getline(rule_file, temp_line)) {
        ss = std::stringstream(temp_line);
        ss >> temp1;
        ss = std::stringstream(temp_line.substr(3, temp_line.size()-3));
        ss >> temp2;
        rules.push_back(std::pair(temp1, temp2));
    }

    uint64_t correct_sum {0};
    uint64_t middle_term;
    bool modif;
    while(getline(file, temp_line)) {
        modif = false;
        ss = std::stringstream(temp_line);
        while (temp_line.size()!=2) {
            ss>>temp1;
            values.push_back(temp1);
            temp_line = temp_line.substr(3, temp_line.size()-3);
            ss = std::stringstream(temp_line);
        }
        ss>>temp1;
        values.push_back(temp1);
        for (auto j {values.begin()}; j < values.end(); ++j) {
            for (auto i {rules.begin()}; i< rules.end(); ++i) {
                if (*j==(*i).second) {
                    for (auto k {j+1}; k < values.end(); ++k) {
                        if (*k == (*i).first) {
                            uint64_t swapping_temp {(*k)};
                            *k = *j;
                            *j = swapping_temp;
                            i= rules.end();
                            --j;
                            modif = true;
                            break;
                        }
                    }
                }
            }
        }

        middle_term = modif ? values.at(values.size()/2) : 0;
        correct_sum += middle_term;
        values.clear();
    }

    printf("Second part's answer is: %llu \n", correct_sum);
    return 0;
}
