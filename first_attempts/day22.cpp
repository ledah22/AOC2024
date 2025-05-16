#include <vector>
#include <string>
#include <fstream>
#include <map>

int main() {
    std::vector<uint64_t> seeds;
    std::vector<std::vector<uint64_t>> seed_states;
    std::vector<std::vector<int16_t>> changes;
    std::string temp_line;
    std::ifstream file ("input22_dbg.txt");

    while(getline(file, temp_line)) {
        seeds.push_back(std::stoull(temp_line));
    }

    //seeds.clear();
    //seeds.push_back(123);
    uint64_t iteration_max {2000}; //2000

    for (uint16_t ind {0}; ind < iteration_max; ++ind) {
        for(uint16_t ind2 {0}; ind2 < seeds.size(); ++ind2) {
            auto seed = seeds.at(ind2);
            seed_states.at(ind2).push_back(seed%10);
            auto seed_og {seed};

            auto seed_val {seed};
            seed_val <<= 6;

            seed ^= seed_val;
            seed &= 0xffffff;
            seed_val = seed;

            seed_val >>= 5;

            seed ^= seed_val;
            seed &= 0xffffff;
            seed_val = seed;

            seed <<= 11;

            seed ^= seed_val;
            seed &= 0xffffff;

            changes.at(ind2).push_back(static_cast<int16_t>(seed%10) - static_cast<int16_t>(seed_og%10));

            //printf("%llu ", *seed);
        }
    }

    for(uint16_t ind2 {0}; ind2 < seeds.size(); ++ind2) {
        seed_states.at(ind2).push_back(seeds.at(ind2)%10);
    }

    std::map<std::tuple<int16_t, int16_t, int16_t, int16_t>, uint64_t> bananas;
    for(uint16_t ind {0}; ind < changes.size(); ++ind) {
        //NO because only the first occurence per ind should count!!!
        for(uint16_t ind1 {0}; ind1 < changes.front().size() - 3; ++ind1) {
            bananas[std::tuple(changes.at(ind).at(ind1), changes.at(ind).at(ind1+1), changes.at(ind).at(ind1+2), changes.at(ind).at(ind1+3))] += seed_states.at(ind).at(ind1+4);
        }
    }

    uint64_t max_bananas {0};

    for (const auto& ban_pair: bananas) {
        if (ban_pair.second > max_bananas) {
            max_bananas = ban_pair.second;
        }
    }



    //printf("\n");
    uint64_t first_answer {0};
    for (auto seed {seeds.begin()}; seed < seeds.end(); ++seed) {
        first_answer += *seed;
        //printf("%llu ", *seed);
    }
    printf("First: %llu. Second answer: %llu.\n", first_answer, max_bananas);
    return 0;
}