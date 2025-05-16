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
    std::vector<uint64_t> X_shifted;
    std::vector<uint64_t> Y_shifted;

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
            X.push_back(val_temp);
            X_shifted.push_back(val_temp+shift_val);
            ind_temp+=4;
            val_temp = 0;
            while(ind_temp < temp_line.size() && temp_line.at(ind_temp)>='0' && temp_line.at(ind_temp)<='9') {
                //printf("here5\n");
                val_temp = val_temp*10 + (temp_line.at(ind_temp)-'0');
                ++ind_temp;
            }
            Y.push_back(val_temp);
            Y_shifted.push_back(val_temp+shift_val);
        } else {
            //printf("A: %llu %llu, B: %llu %llu, X=%llu, Y=%llu\n", x_a.back(), y_a.back(), x_b.back(), y_b.back(), X.back(), Y.back());
        }

    }
    //printf("A: %llu %llu, B: %llu %llu, X=%llu, Y=%llu\n", x_a.back(), y_a.back(), x_b.back(), y_b.back(), X.back(), Y.back());

    line_count/=4;
    double_t A_sol;
    double_t B_sol;
    double_t A_sol_shifted {0};
    double_t B_sol_shifted {0};

    uint64_t first_total {0};
    uint64_t second_total {0};

    for (uint16_t eq_ind {0}; eq_ind <= line_count; ++eq_ind) {

        //printf("here7\n");

        B_sol = ((double_t)(Y.at(eq_ind)*x_a.at(eq_ind)) - (double_t)(X.at(eq_ind)*y_a.at(eq_ind))) /\
                ((double_t)(y_b.at(eq_ind)*x_a.at(eq_ind)) - (double_t)(x_b.at(eq_ind)*y_a.at(eq_ind)));
        A_sol = ((double_t)(X.at(eq_ind)*y_b.at(eq_ind)) - (double_t)(Y.at(eq_ind)*x_b.at(eq_ind)))/ \
                ((double_t)(y_b.at(eq_ind)*x_a.at(eq_ind)) - (double_t)(x_b.at(eq_ind)*y_a.at(eq_ind)));
        
        if ((double_t)(y_b.at(eq_ind)*x_a.at(eq_ind)) != (double_t)(x_b.at(eq_ind)*y_a.at(eq_ind))) {
            B_sol_shifted = B_sol + shift_val/((double_t)(y_b.at(eq_ind))*(double_t)(x_a.at(eq_ind)) - (double_t)(x_b.at(eq_ind))*(double_t)(y_a.at(eq_ind)))*((double_t)x_a.at(eq_ind)-(double_t)y_a.at(eq_ind));
            A_sol_shifted = A_sol + shift_val/((double_t)(y_b.at(eq_ind))*(double_t)(x_a.at(eq_ind)) - (double_t)(x_b.at(eq_ind))*(double_t)(y_a.at(eq_ind)))*((double_t)y_b.at(eq_ind)-(double_t)x_b.at(eq_ind));
        }
        
        printf("A_sol=%f B_sol=%f\n", A_sol,B_sol);
        if (B_sol==(int)B_sol && A_sol==(int)A_sol && A_sol>0 && B_sol>0) {
            //printf("here8\n");
            if (A_sol < 101 && B_sol < 101) {
                first_total += A_sol*A_cost + B_sol*B_cost;
            }
        }
        printf("A_sol_shift=%f B_sol_shift=%f\n", A_sol_shifted,B_sol_shifted);
        printf("int values: A_sol_shift=%lld B_sol_shift=%lld\n", static_cast<int64_t>(A_sol_shifted),static_cast<int64_t>(B_sol_shifted));
        uint64_t resA {0};
        uint64_t resB {0};
        //78384752060011 too low, .00001 and.99999 - no
        //83197086729624 0.001 and 0.999 - no
        //83457477611527 0.01 and 0.99 - no
        //99859481114738 0.1 and 0.9 - no

        if (std::fabs(B_sol_shifted-static_cast<int64_t>(B_sol_shifted))< 0.001 && B_sol_shifted > 0) {
            resB = static_cast<int64_t>(B_sol_shifted);
            printf("success B ceil \n");
        } else if (std::fabs(B_sol_shifted-static_cast<int64_t>(B_sol_shifted))> 0.999 && std::fabs(B_sol_shifted-static_cast<int64_t>(B_sol_shifted)) < 1 &&  B_sol_shifted > 0) {
            resB = static_cast<int64_t>(B_sol_shifted) + 1;
            printf("success B floor \n");
        }

        if (std::fabs(A_sol_shifted-static_cast<int64_t>(A_sol_shifted))< 0.001 && A_sol_shifted > 0) {
            resA = static_cast<int64_t>(A_sol_shifted);
            printf("A ceil \n");
        } else if (std::fabs(A_sol_shifted-static_cast<int64_t>(A_sol_shifted))> 0.999 && std::fabs(A_sol_shifted-static_cast<int64_t>(A_sol_shifted)) < 1 && A_sol_shifted > 0) {
            resA = static_cast<int64_t>(A_sol_shifted) + 1;
            printf("A floor \n");
        }

        printf("secondA: %llu secondB: %llu\n", resA, resB);
        second_total += resA*A_cost + resB*B_cost;
    }

    printf("\nFirst answer: %llu. Second answer: %llu.\n", first_total, second_total);
    return 0;
}