#include <string>
#include <fstream>
#include <sstream>

bool can_plus_mul_it(uint64_t res_, std::vector<uint64_t> members_, bool last_was_plus)  {
    if(members_.empty()) {
        if ((res_ == 1 && !last_was_plus) || (res_==0 && last_was_plus))
            return true;
        else
            return false;
    } else {
        uint64_t top_mem {members_.back()};
        members_.erase(members_.end()-1);
        return (top_mem <= res_ && can_plus_mul_it(res_-top_mem, members_, true)) || (res_%top_mem==0 && can_plus_mul_it(res_/top_mem, members_, false));
    }
}

bool can_plus_mul_append_it(uint64_t res_, std::vector<uint64_t> members_)  {
    //printf("New appended line: ");
    //for (int j {0}; j< members_.size(); ++j) {
    //    printf("%llu ", members_.at(j));
    //}
    //printf(" and goal is %llu \n", res_);

    if (members_.size()==1) {
        return members_.front() == res_;
    } else {
        std::vector<uint64_t> members_app;
        members_app = members_;
        std::stringstream ss("");
        ss<<members_app.front();
        ss<<members_app.at(1);
        members_app.erase(members_app.begin());
        members_app.erase(members_app.begin());
        uint64_t new_val;
        ss>>new_val;
        //printf("New val is: %llu \n", new_val);
        members_app.insert(members_app.begin(), new_val);


        uint64_t first_mem {members_.front()};
        uint64_t snd_mem {members_.at(1)};
        members_.erase(members_.begin());
        members_.erase(members_.begin());
        std::vector<uint64_t> members_mul = members_;
        std::vector<uint64_t> members_add = members_;
        members_mul.insert(members_mul.begin(), first_mem*snd_mem);
        members_add.insert(members_add.begin(), first_mem+snd_mem);

        return can_plus_mul_append_it(res_, members_mul) || can_plus_mul_append_it(res_, members_add) || can_plus_mul_append_it(res_, members_app);
    }
}

int main() {
    std::ifstream inp_file ("input7.txt");
    std::string temp_line;
    uint64_t result_temp;
    std::vector<uint64_t> members_total {};
    uint64_t temp_member;
    uint64_t ind {100};
    bool doable;
    bool doable_appended;

    uint64_t sum {0};
    uint64_t sum_appended {0};
    while(getline(inp_file, temp_line)) {
        ind = temp_line.find_first_of(':');
        for (int i {0}; i< ind; ++i) {
            result_temp = result_temp*10 + std::stoi(temp_line.substr(i, 1));
        }
        printf("%llu \n ", result_temp);
        std::stringstream ss (temp_line.substr(ind+1, temp_line.size()-(ind+1)));
        while(ss >> temp_member) {
            members_total.push_back(temp_member);
            //printf("%llu ", temp_member);
        }
        doable = can_plus_mul_it(result_temp, members_total, true);
        //printf("The line %s is: %u \n", temp_line.c_str(), doable);
        if (doable) {
            sum += result_temp;
        }

        doable_appended = can_plus_mul_append_it(result_temp, members_total);
        //printf("If appended, the line %s is: %u \n", temp_line.c_str(), doable_appended);
        if (doable_appended) {
            sum_appended += result_temp;
        }
        
        members_total.clear();
        result_temp = 0;
    }

    printf("First res is: %llu. Second is: %llu \n", sum, sum_appended);
    return 0;
}