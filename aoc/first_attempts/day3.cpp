#include <string>
#include <fstream>
#include <regex>
#include <iterator>

bool check_change(std::string& inp_, uint64_t prev_, uint64_t start_ind_, bool do_) {
    std::regex found_do_pattern("do\\(\\)");
    std::regex found_dont_pattern("don't\\(\\)");
    int64_t last_do {-1};
    int64_t last_dont {-1};
    std::smatch matcher;
    std::string temp_str = inp_.substr(prev_, start_ind_ - prev_);

    while(std::regex_search(temp_str, matcher, found_do_pattern)) {
        last_do = static_cast<int64_t>(matcher.position());
        temp_str = temp_str.substr(last_do+1, start_ind_ - (last_do+1));
    }
    last_do += prev_;

    temp_str = inp_.substr(prev_, start_ind_ - prev_);
    while(std::regex_search(temp_str, matcher, found_dont_pattern)) {
        last_dont = static_cast<int64_t>(matcher.position());
        temp_str = temp_str.substr(last_dont+1, start_ind_ - (last_dont+1));
    }
    last_dont += prev_;

    printf("Dos and don'ts: %lld %lld. Start: %llu. End: %llu. \n", last_do, last_dont, prev_, start_ind_);
    return (last_dont > last_do && do_) || (last_dont < last_do && !do_);
}

void find_first_occur(std::string& inp_, uint64_t& start_ind_, uint64_t& counter_, bool& do_) {
    uint64_t end_padding {0};
    uint64_t prev {start_ind_};
    while (start_ind_ < inp_.size() - 7) {
        if(inp_.at(start_ind_) == 'm') {
            if(inp_.at(start_ind_+1) == 'u') {
                if(inp_.at(start_ind_+2) == 'l')  {
                    std::regex pattern("\\((\\d){1,3},(\\d){1,3}\\).*");
                    if (start_ind_ >= inp_.size() - 9) {
                        end_padding = (inp_.size() - 7) - start_ind_;
                    }
                    if (std::regex_match(inp_.substr(start_ind_+3, 9 - end_padding), pattern)) {
                        do_ = check_change(inp_, prev, start_ind_, do_) ? !do_ : do_;
                        uint64_t coma_ind {start_ind_+4};
                        while (inp_.at(coma_ind) != ',') {
                            ++coma_ind;
                        }
                        uint64_t bracket_ind {coma_ind+1};
                        while (inp_.at(bracket_ind) != ')') {
                            ++bracket_ind;
                        }
                        printf("%s ", inp_.substr(start_ind_+4, coma_ind - (start_ind_+4)).c_str());
                        printf("%s \n", inp_.substr(coma_ind+1, bracket_ind - coma_ind-1).c_str());
                        uint64_t mul1 {std::stoull(inp_.substr(start_ind_+4, coma_ind - (start_ind_+4)))};
                        uint64_t mul2 {std::stoull(inp_.substr(coma_ind+1, bracket_ind - coma_ind-1))};
                        counter_ += (do_) ? mul1*mul2 : 0;
                        start_ind_ += 7;
                        return;
                    }

                    end_padding = 0;
                }
            }
        }
        ++start_ind_;
    }
}

int main() {
    std::string line_temp;
    std::string line_total;
    std::ifstream file ("input3.txt");
    while(getline(file, line_temp)) {
        line_total += line_temp;
    }

    std::uint64_t curr_ind {0};
    std::uint64_t count_regulars {0};
    bool doo {true};
    while (curr_ind < line_total.size()-7) {
        find_first_occur(line_total, curr_ind, count_regulars, doo);
    }

    printf("The count is: %llu \n", count_regulars);
    return 0;
}