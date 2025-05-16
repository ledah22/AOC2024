#include <string>
#include <fstream>
#include <cmath>

int main() {

    std::string temp_line;
    std::ifstream file ("input13.txt");
    uint64_t line_count {0};
    std::vector<uint64_t> x_a;
    std::vector<uint64_t> y_a;
    std::vector<uint64_t> x_b;
    std::vector<uint64_t> y_b;
    std::vector<uint64_t> X;
    std::vector<uint64_t> Y;

    const uint64_t A_cost {3};
    const uint64_t B_cost {1};
    const double_t shift_val {10000000000000};
    uint64_t ind_temp;
    uint64_t val_temp;

    while (getline(file, temp_line)) {
        ++line_count;
        val_temp = 0;
        //printf("here6\n");
        if (line_count%4==1) {
            ind_temp = 12;
            while(temp_line.at(ind_temp)>='0' && temp_line.at(ind_temp)<='9') {
                //printf("here0\n");
                val_temp = val_temp*10 + (temp_line.at(ind_temp)-'0');
                ++ind_temp;
            }
            x_a.push_back(val_temp);
            ind_temp+=4;
            val_temp = 0;
            while(ind_temp < temp_line.size() && temp_line.at(ind_temp)>='0' && temp_line.at(ind_temp)<='9') {
                //printf("here1\n");
                val_temp = val_temp*10 + (temp_line.at(ind_temp)-'0');
                ++ind_temp;
            }
            y_a.push_back(val_temp);
        } else if (line_count%4==2) {
            ind_temp = 12;
            while(temp_line.at(ind_temp)>='0' && temp_line.at(ind_temp)<='9') {
                //printf("here2\n");
                val_temp = val_temp*10 + (temp_line.at(ind_temp)-'0');
                ++ind_temp;
            }
            x_b.push_back(val_temp);
            ind_temp+=4;
            val_temp = 0;
            while(ind_temp < temp_line.size() && temp_line.at(ind_temp)>='0' && temp_line.at(ind_temp)<='9') {
                //printf("here3\n");
                val_temp = val_temp*10 + (temp_line.at(ind_temp)-'0');
                ++ind_temp;
            }
            y_b.push_back(val_temp);
        } else if (line_count%4==3) {
            ind_temp = 9;
            while(temp_line.at(ind_temp)>='0' && temp_line.at(ind_temp)<='9') {
                //printf("here4\n");
                val_temp = val_temp*10 + (temp_line.at(ind_temp)-'0');
                ++ind_temp;
            }
            X.push_back(val_temp+shift_val);
            ind_temp+=4;
            val_temp = 0;
            while(ind_temp < temp_line.size() && temp_line.at(ind_temp)>='0' && temp_line.at(ind_temp)<='9') {
                //printf("here5\n");
                val_temp = val_temp*10 + (temp_line.at(ind_temp)-'0');
                ++ind_temp;
            }
            Y.push_back(val_temp+shift_val);
        } else {
            //printf("A: %llu %llu, B: %llu %llu, X=%llu, Y=%llu\n", x_a.back(), y_a.back(), x_b.back(), y_b.back(), X.back(), Y.back());
        }

    }
    //printf("A: %llu %llu, B: %llu %llu, X=%llu, Y=%llu\n", x_a.back(), y_a.back(), x_b.back(), y_b.back(), X.back(), Y.back());

    line_count/=4;
    uint64_t A_sol;
    uint64_t B_sol;

    uint64_t first_total {0};
    uint64_t second_total {0};

    for (uint16_t eq_ind {0}; eq_ind <= line_count; ++eq_ind) {

        //printf("here7\n");

        B_sol = ((Y.at(eq_ind)*x_a.at(eq_ind)) - (X.at(eq_ind)*y_a.at(eq_ind))) /\
                ((y_b.at(eq_ind)*x_a.at(eq_ind)) - (x_b.at(eq_ind)*y_a.at(eq_ind)));
        A_sol = ((X.at(eq_ind)*y_b.at(eq_ind)) - (Y.at(eq_ind)*x_b.at(eq_ind)))/ \
                ((y_b.at(eq_ind)*x_a.at(eq_ind)) - (x_b.at(eq_ind)*y_a.at(eq_ind)));
        
        printf("A_sol=%llu B_sol=%llu\n", A_sol,B_sol);
        if ((B_sol*x_b.at(eq_ind)+A_sol*x_a.at(eq_ind) == X.at(eq_ind)) && (B_sol*y_b.at(eq_ind)+A_sol*y_a.at(eq_ind) == Y.at(eq_ind)) && A_sol>0 && B_sol>0) {
            printf("here8\n");
            second_total += A_sol*A_cost + B_sol*B_cost;
        }

        B_sol = ((X.at(eq_ind)*y_a.at(eq_ind)) - (Y.at(eq_ind)*x_a.at(eq_ind))) /\
                ((x_b.at(eq_ind)*y_a.at(eq_ind)) - (y_b.at(eq_ind)*x_a.at(eq_ind)));
        A_sol = ((Y.at(eq_ind)*x_b.at(eq_ind)) - (X.at(eq_ind)*y_b.at(eq_ind)))/ \
                ((x_b.at(eq_ind)*y_a.at(eq_ind)) - (y_b.at(eq_ind)*x_a.at(eq_ind)));

        printf("A_sol=%llu B_sol=%llu\n", A_sol,B_sol);
        if ((B_sol*x_b.at(eq_ind)+A_sol*x_a.at(eq_ind) == X.at(eq_ind)) && (B_sol*y_b.at(eq_ind)+A_sol*y_a.at(eq_ind) == Y.at(eq_ind)) && A_sol>0 && B_sol>0) {
            printf("here9\n");
            second_total += A_sol*A_cost + B_sol*B_cost;
        }
    }

    printf("\nFirst answer: %llu. Second answer: %llu.\n", first_total, second_total);
    return 0;
}