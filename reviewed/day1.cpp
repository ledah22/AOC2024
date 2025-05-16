#include <fstream>
#include <string>
#include <cstdlib>
#include <map>

int main () {
    std::string temp_line;
    std::ifstream file ("input1.txt");
    int32_t temp;
    uint16_t const len {1000};

    std::vector<int32_t> map1;
    map1.reserve(len);
    std::vector<int32_t> map2;
    map2.reserve(len);

    while(file >> temp) {
        //printf("%u ", temp);
        map1.push_back(temp);
        file >> temp;
        //printf("%u\n", temp);
        map2.push_back(temp);
    }

    std::sort(map1.begin(), map1.end());
    std::sort(map2.begin(), map2.end());

    uint64_t ans1 {0};
    for (auto i {0}; i < len; ++i) {
        //printf("|%d - %d| = %d", map1.at(i), map2.at(i), std::abs(map1.at(i) - map2.at(i)));
        ans1 += std::abs(map1.at(i) - map2.at(i));
    }

    std::map<int32_t, int32_t> counts;
    for (auto itx {map2.begin()}; itx != map2.end(); ++itx) {
        ++counts[*itx];
    }

    uint64_t ans2 {0};
    for (auto itx {map1.begin()}; itx != map1.end(); ++itx) {
        ans2 += counts[*itx]*(*itx);
    }
    printf("First answer is %llu, second is %llu\n", ans1, ans2);
    return 0;
}