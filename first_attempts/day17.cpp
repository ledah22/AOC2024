#include <string>
#include <math.h>
static uint64_t A {0};
static uint64_t B {0};
static uint64_t C {0};

static std::string output {""};

void adv(uint16_t operand) {
    A = A/(1<<operand);
}

void bxl(uint16_t operand) {
    B = B^operand;
}

void bst(uint16_t operand) {
    B = operand%8;
}

void jnz(uint16_t operand, uint32_t& pc) {
    pc = (A==0) ? pc : (operand);
}

void bxc() {
    B = B^C;
}

void out(uint16_t operand) {
    //printf("%u,", operand%8);
    output += std::to_string(operand%8) + ",";
}

void bdv(uint16_t operand) {
    B = A/(1<<operand);
}

void cdv(uint16_t operand) {
    C = A/(1<<operand);
}

uint16_t get_op_from_combo(uint16_t combo) {
    if (combo >=0 && combo <=3) {
        return combo;
    }
    if (combo == 4 ) {

        return A;
    }
    if (combo == 5 ) {

        return B;
    }
    if (combo == 6 ) {

        return C;
    }
    
    return 10;
}

void inst(uint16_t opc, uint16_t literal, uint32_t& pc) {
    uint16_t combo = get_op_from_combo(literal);
    if (opc > 7) {
        printf("inst is broken!\n");
        return;
    }
    pc +=2;

    if(opc==0) {
        adv(combo);
    } else if (opc==1) {
        bxl(literal);
    } else if (opc==2) {
        bst(combo);
    } else if (opc==3) {
        jnz(literal, pc); //has pc increased on receipt
    } else if (opc==4) {
        bxc();
    } else if (opc==5) {
        out(combo);
    } else if (opc==6) {
        bdv(combo);
    } else { //op=7
        cdv(combo);
    } 

}

int main() {
    std::string program {"2,4,1,3,7,5,4,2,0,3,1,5,5,5,3,0"};
    //std::string program {"0,3,5,4,3,0"};
    std::string out_target {program+","};
    uint32_t it {0};
    uint32_t pc;
    //12328674937
    uint64_t A_value {236549618794496};
    const uint64_t top_val {236558208729088};

    while (A_value < top_val) {
        A = A_value;
        //printf("Checking for A = %llu\n", A);
        it = 0;
        output = "";
        B = 0;
        C= 0;
        while (it < program.size()) {
            uint16_t out_size {static_cast<uint16_t>(output.size())};
            if (out_size>0 && (out_size > out_target.size() ||  output != out_target.substr(0, output.size())))
                break;
            pc = it/2;
            inst(program.at(it)-'0', program.at(it+2)-'0', pc);
            it = pc*2;
        }

        if(out_target == output) {
            printf("Desired A is: %llu\n", A_value);
            break;
        }

        ++A_value;
    }

    printf("A is: %llu\n", A_value);
    return 0;
}