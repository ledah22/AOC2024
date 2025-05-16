#include <vector>
#include <map>
#include <string>
// +---+---+---+
// | 7 | 8 | 9 |
// +---+---+---+
// | 4 | 5 | 6 |
// +---+---+---+
// | 1 | 2 | 3 |
// +---+---+---+
//     | 0 | A |
//     +---+---+
void map_keys0(uint16_t x_s, uint16_t y_s, uint16_t x_e, uint16_t y_e, std::vector<char>& steps) {
    if (x_e == x_s && y_e==y_s)
        return;
    if (y_e < y_s && !(x_s == 3 && y_s == 1)) {
        --y_s;
        steps.push_back('<');
    } else if (x_e > x_s && !(x_s == 2 && y_s == 0)) {
        ++x_s;
        steps.push_back('v');
    } else if (y_e > y_s) {
        ++y_s;
        steps.push_back('>');
    } else if (x_e < x_s) {
        --x_s;
        steps.push_back('^');
    }

    map_keys0(x_s, y_s, x_e, y_e, steps);

}

void map_keys0_rec(uint16_t x_s, uint16_t y_s, uint16_t x_e, uint16_t y_e, std::vector<char> steps, std::vector<std::vector<char>>& collection) {
    if (x_e == x_s && y_e==y_s) {
        //printf("Adding this to collection for x_e=%u, y_e=%u: ", x_e, y_e);
        //for (auto step {steps.begin()}; step < steps.end(); ++step) {
        //    printf("%c", (*step));
        //}
        //printf("\n");
        collection.push_back(steps);
        return;
    }
    
    if (y_e < y_s && !(x_s == 3 && y_s == 1)) {
        //printf("Moving < from (%u, %u), aiming for (%u, %u)\n", x_s, y_s, x_e, y_e);
        std::vector<char> steps0 {steps};
        steps0.push_back('<');
        map_keys0_rec(x_s, y_s-1, x_e, y_e, steps0, collection);
    }

    if (x_e > x_s && !(x_s == 2 && y_s == 0)) {
        //printf("Moving V from (%u, %u), aiming for (%u, %u)\n", x_s, y_s, x_e, y_e);
        std::vector<char> steps1 {steps};
        steps1.push_back('v');
        map_keys0_rec(x_s+1, y_s, x_e, y_e, steps1, collection);
    }

    if (y_e > y_s) {
        //printf("Moving > from (%u, %u), aiming for (%u, %u)\n", x_s, y_s, x_e, y_e);
        std::vector<char> steps2 {steps};
        steps2.push_back('>');
        map_keys0_rec(x_s, y_s+1, x_e, y_e, steps2, collection);
    }

    if (x_e < x_s) {
        //printf("Moving ^ from (%u, %u), aiming for (%u, %u)\n", x_s, y_s, x_e, y_e);
        std::vector<char> steps3 {steps};
        steps3.push_back('^');
        map_keys0_rec(x_s-1, y_s, x_e, y_e, steps3, collection);
    }
}

//     +---+---+
//     | ^ | A |
// +---+---+---+
// | < | v | > |
// +---+---+---+

//     +---+---+
//     | ^ | A |
// +---+---+---+
// | < | v | > |
// +---+---+---+
void map_keys1(uint16_t x_s, uint16_t y_s, uint16_t x_e, uint16_t y_e, std::vector<char>& steps) {
    if (x_e == x_s && y_e==y_s)
        return;
    if (x_e > x_s) {
        ++x_s;
        steps.push_back('v');
    }  else if (y_e > y_s) {
        ++y_s;
        steps.push_back('>');
    } else if (y_e < y_s && !(x_s == 0 && y_s == 1)) {
        --y_s;
        steps.push_back('<');
    } else if (x_e < x_s && !(x_s == 1 && y_s == 0)) {
        --x_s;
        steps.push_back('^');
    }

    map_keys1(x_s, y_s, x_e, y_e, steps);
}

void map_keys1_rec(uint16_t x_s, uint16_t y_s, uint16_t x_e, uint16_t y_e, std::vector<char> steps, std::vector<std::vector<char>>& collection) {
    if (x_e == x_s && y_e==y_s) {
        //printf("Adding this to collection for x_e=%u, y_e=%u: ", x_e, y_e);
        //for (auto step {steps.begin()}; step < steps.end(); ++step) {
        //    printf("%c", (*step));
        //}
        //printf("\n");
        collection.push_back(steps);
        return;
    }
    if (x_e > x_s) {
        std::vector<char> steps0 {steps};
        steps0.push_back('v');
        map_keys1_rec(x_s+1, y_s, x_e, y_e, steps0, collection);
    }
    if (y_e > y_s) {
        std::vector<char> steps1 {steps};
        steps1.push_back('>');
        map_keys1_rec(x_s, y_s+1, x_e, y_e, steps1, collection);
    }
    if (y_e < y_s && !(x_s == 0 && y_s == 1)) {
        std::vector<char> steps2 {steps};
        steps2.push_back('<');
        map_keys1_rec(x_s, y_s-1, x_e, y_e, steps2, collection);
    }
    if (x_e < x_s && !(x_s == 1 && y_s == 0)) {
        std::vector<char> steps3 {steps};
        steps3.push_back('^');
        map_keys1_rec(x_s-1, y_s, x_e, y_e, steps3, collection);
    }
}

void one_stage(std::vector<std::vector<char>>& collection0, std::vector<std::vector<char>>& collection3, size_t& min_sized_temp, std::map<char, std::pair<uint16_t, uint16_t>>& keys1) {
    std::vector<std::vector<char>> collection1;
    std::vector<char> steps1;
    std::vector<std::vector<char>> collection_temp;
    std::vector<char> collection_temp1;
    std::vector<std::vector<char>> collection_temp2;
    //size_t new_min_size {std::numeric_limits<size_t>::max()};
    for (auto coll {collection0.begin()}; coll < collection0.end(); ++coll) { 
        //printf("here0\n");
        if ((*coll).size() <= min_sized_temp) {
            //printf("here1\n");
            collection1.clear();
            for (uint16_t ind {0}; ind < (*coll).size()-1; ++ind) {
                //printf("here2\n");
                steps1.clear();
                steps1.push_back('A');
                collection_temp = collection1;
                collection_temp2.clear();
                map_keys1_rec(keys1[(*coll).at(ind)].first, keys1[(*coll).at(ind)].second, keys1[(*coll).at(ind+1)].first, keys1[(*coll).at(ind+1)].second, steps1, collection_temp2);
                collection1.clear();
                if(collection_temp.empty()) {
                    //printf("here3\n");
                    for (int newby {0}; newby < collection_temp2.size(); ++newby) {
                        collection1.push_back(collection_temp2.at(newby));
                        //if (collection_temp2.at(newby).size() <= new_min_size) {
                        //    collection1.push_back(collection_temp2.at(newby));
                        //    new_min_size = collection_temp2.at(newby).size();
                        //}
                    }
                } else {
                    //printf("here4\n");
                    for (int og {0}; og < collection_temp.size(); ++og) {
                        for (int newby {0}; newby < collection_temp2.size(); ++newby) {
                            collection_temp1.clear();
                            collection_temp1.insert(collection_temp1.end(), collection_temp.at(og).begin(), collection_temp.at(og).end());
                            collection_temp1.insert(collection_temp1.end(), collection_temp2.at(newby).begin(), collection_temp2.at(newby).end());
                            collection1.push_back(collection_temp1);
                        }
                    }
                }
                //new_min_size = std::numeric_limits<size_t>::max();
            }
            for (auto ind {collection1.begin()}; ind < collection1.end(); ++ind) {
                //printf("here5\n");
                if(/*(*ind).size() <= new_min_size && */std::find(collection3.begin(), collection3.end(), *ind) == collection3.end()) {
                    collection3.push_back(*ind);
                    //new_min_size = (*ind).size();
                }
            }
        }
    }
    for (auto ind2 {collection3.begin()}; ind2 < collection3.end(); ++ind2) {
        //printf("here6\n");
        (*ind2).push_back('A');
    }
    //min_sized_temp = ++new_min_size;
    min_sized_temp = std::numeric_limits<size_t>::max();

    for (auto ind2 {collection3.begin()}; ind2 < collection3.end(); ++ind2) {
        if (min_sized_temp > (*ind2).size()) {
            min_sized_temp = (*ind2).size();
        }
        //printf("Size is %zu\n", (*ind2).size());
    }

    //printf("Min is %zu\n", min_sized_temp);
}

int main() {
    std::vector<std::string> codes = {"A279A", "A286A", "A508A", "A463A", "A246A"};
    std::vector<uint32_t> values = {279, 286, 508, 463, 246};
    //std::vector<std::string> codes = {"A029A", "A980A", "A179A", "A456A", "A379A"};
    //std::vector<uint32_t> values = {29, 980, 179, 456, 379};
    std::map<char, std::pair<uint16_t, uint16_t>> keys0;
    keys0['7'] = std::pair(0, 0);
    keys0['8'] = std::pair(0, 1);
    keys0['9'] = std::pair(0, 2);
    keys0['4'] = std::pair(1, 0);
    keys0['5'] = std::pair(1, 1);
    keys0['6'] = std::pair(1, 2);
    keys0['1'] = std::pair(2, 0);
    keys0['2'] = std::pair(2, 1);
    keys0['3'] = std::pair(2, 2);
    keys0['0'] = std::pair(3, 1);
    keys0['A'] = std::pair(3, 2);

    std::map<char, std::pair<uint16_t, uint16_t>> keys1;
    keys1['^'] = std::pair(0, 1);
    keys1['A'] = std::pair(0, 2);
    keys1['<'] = std::pair(1, 0);
    keys1['v'] = std::pair(1, 1);
    keys1['>'] = std::pair(1, 2);

    std::vector<char> steps0;
    std::vector<char> steps1;
    std::vector<char> steps2;

    std::vector<std::vector<char>> collection0;
    std::vector<std::vector<char>> collection1;
    std::vector<std::vector<char>> collection2;
    std::vector<std::vector<char>> collection3;
    std::vector<std::vector<char>> collection4;
    //std::vector<char> steps_temp;
    //map_keys0(1, 0, 3, 2, steps);
    //for (auto step {steps.begin()}; step < steps.end(); ++step) {
    //    printf("(%u, %u) ", (*step).first, (*step).second);
    //}
    //printf("\n");

    //279A: A -> 2 -> 7 -> 9 -> A
    //286A: A -> 2 -> 8 -> 6 -> A
    //508A: A -> 5 -> 0 -> 8 -> A
    //463A: A -> 4 -> 6 -> 3 -> A
    //246A: A -> 2 -> 4 -> 6 -> A

    uint64_t first_answer {0};
    uint16_t counter {0};
    for (auto code {codes.begin()}; code < codes.end(); ++code) {
        collection0.clear();
        collection1.clear();
        collection2.clear();
        collection3.clear();
        collection4.clear();
        std::vector<std::vector<char>> collection_temp;
        std::vector<char> collection_temp1;
        std::vector<std::vector<char>> collection_temp2;

        printf("Solving %s\n", (*code).c_str());
        for (uint16_t ind {0}; ind < (*code).size()-1; ++ind) {
            steps0.clear();
            steps0.push_back('A');
            collection_temp = collection0;
            collection_temp2.clear();
            map_keys0_rec(keys0[(*code).at(ind)].first, keys0[(*code).at(ind)].second, keys0[(*code).at(ind+1)].first, keys0[(*code).at(ind+1)].second, steps0, collection_temp2);
            
            collection0.clear();
            if(collection_temp.empty()) {
                for (int newby {0}; newby < collection_temp2.size(); ++newby) {
                    collection0.insert(collection0.end(), collection_temp2.begin(), collection_temp2.end());
                }
            } else {
                for (int og {0}; og < collection_temp.size(); ++og) {
                    for (int newby {0}; newby < collection_temp2.size(); ++newby) {
                        collection_temp1.clear();
                        collection_temp1.insert(collection_temp1.end(), collection_temp.at(og).begin(), collection_temp.at(og).end());
                        collection_temp1.insert(collection_temp1.end(), collection_temp2.at(newby).begin(), collection_temp2.at(newby).end());
                        collection0.push_back(collection_temp1);
                    }
                }
            }
        
        }

        auto min_sized_temp {collection0.front().size()};

        for (auto ind2 {collection0.begin()}; ind2 < collection0.end(); ++ind2) {
            if((*ind2).size() < min_sized_temp) {
                min_sized_temp = (*ind2).size();
            }
            (*ind2).push_back('A');
        }
        ++min_sized_temp;

        uint16_t repetitions {25}; // 2 for first, 25 for second pt
        for (uint16_t i {0}; i < repetitions; ++i) {
            one_stage(collection0, collection3, min_sized_temp, keys1);
            collection0 = collection3;
            collection3.clear();
        }
        //one_stage(collection3, collection4, min_sized_temp, keys1);
 
        //uint64_t smallest_solution {collection4.front().size()};
        //for (auto ind2 {collection4.begin()+1}; ind2 < collection4.end(); ++ind2) {
        //    if ((*ind2).size() < smallest_solution) {
        //        smallest_solution = (*ind2).size();
        //    }
        //}
        first_answer += (min_sized_temp-1) * values.at(counter++);
    }

    printf("First: %llu. Second: 0.\n", first_answer);

    return 0;
}