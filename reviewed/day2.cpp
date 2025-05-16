#include <fstream>
#include <string>
#include <sstream>
#include <list>

bool calc_and_check_diff(bool incr_, uint32_t m_, uint32_t l_) {
    auto diff {incr_ ? (m_ - l_) : (l_ - m_)};
    return (diff > 3 || diff < 1) ;
}

void check_it_ind(auto& it, uint32_t& curr, uint32_t forbidden_val) {
    if (curr != 0) {
        ++it;
    }
    if (curr++ == forbidden_val) {
        ++it;
    }
}

bool is_report_moderately_safe(std::list<uint32_t> in_) {
    uint32_t skip_ind {0};
    bool moderately_safe {false};
    while(skip_ind < in_.size() && !moderately_safe) {
        uint32_t skip_check {0};
        auto it {in_.begin()};
        check_it_ind(it, skip_check, skip_ind);
        uint32_t last_val {*it};
        //printf("\n New: %u ", last_val);
        check_it_ind(it, skip_check, skip_ind);
        uint32_t measurement {*it};
        //printf("%u ", measurement);
        bool incr {measurement > last_val};
        bool temp_safe {true};
        while (it != in_.end()) {
            if (incr != measurement > last_val) {
                //printf("Incr error \n");
                temp_safe = false;
                break;
            }
            if (calc_and_check_diff(incr, measurement, last_val)) {
                //printf("Diff error \n");
                temp_safe = false;
                break;
            }
            last_val = measurement;
            check_it_ind(it, skip_check, skip_ind);
            measurement = *(it);
            //printf("%u ", measurement);
        }
        moderately_safe = temp_safe;
        ++skip_ind;
    }

    return moderately_safe;
}

bool is_report_strictly_safe(std::list<uint32_t> in_) {
    auto it {in_.begin()};
    uint32_t last_val {*it++};
    uint32_t measurement {*it};
    bool incr {measurement > last_val};
    while (it != in_.end()) {
        if (incr != measurement > last_val) {
            return false;
        }
        if (calc_and_check_diff(incr, measurement, last_val)) {
            return false;
        }
        last_val = measurement;
        measurement = *(++it);
    }

    return true;
    
}
int main() {
    bool incr {false};
    std::fstream file {"../first_attempts/input2.txt"};
    std::string line;
    uint32_t temp;
    uint32_t diff;
    uint32_t ans1 {0};
    std::list<uint32_t> report;
    uint32_t ans2 {0};

    while(getline(file, line)) {
        //printf("%s \n", line.c_str());
        report.clear();
        std::stringstream ss {line};
        while (ss >> temp) {
            report.emplace_back(temp);
        }
        bool strictly_safe {is_report_strictly_safe(report)};
        ans1 += strictly_safe;

        //printf("pt 2 check, strictly it is %u\n", strictly_safe);
        ans2 += strictly_safe ? 1 : is_report_moderately_safe(report);
    }

    printf("First answer is %u, second is %u\n", ans1, ans2);
    return 0;
}