#include<iostream>
#include<list>
#include<map>
#include<string>
using namespace std;
#define LEVELMAX 7

list<long long> num_split(long long num, int& digit) {
    list<long long> splited_num;
    while (num / 10 != 0) {
        splited_num.push_back(num % 10);
        num = num / 10;
        digit++;
    }
    splited_num.push_back(num % 10);
    digit++;
    return splited_num;
}
string to_roman(int figure, int digit) {  // digit: 1-4, 5-7, 8-10
    char level_name[LEVELMAX] = { 'I', 'V', 'X', 'L', 'C', 'D', 'M' };
    char main_figure, figure_upper_five,figure_is_nine;
    bool is_beyond = false;
    string num_romanic;
    int count = 0;
    if (digit <= 4) {
        int current_level = (digit - 1) * 2 + 1 - 1;
        main_figure = level_name[current_level];
        if (current_level + 1 > 6) { // M
            figure_upper_five = level_name[1];
            figure_is_nine = level_name[2];
            is_beyond = true;
        }
        else {
            figure_upper_five = level_name[current_level + 1];
            figure_is_nine = level_name[current_level + 2];
        }
        
        if (figure <= 3 && figure > 0) {
            while (count < figure) { // I, X, C, M
                num_romanic += main_figure;
                count++;
            }
            
        }
        else if (figure == 4) { // I, X, C, M|V, L, C, (V)
            num_romanic += main_figure;
            if (is_beyond) {
                num_romanic += '(';
                num_romanic += figure_upper_five;
                num_romanic += ')';
            }
            else {
                num_romanic += figure_upper_five;
            }
            
        }
        else if (figure >= 5 && figure < 9) { // V, L, C, (V)|I, X, C, M
            if (is_beyond) {
                num_romanic += '(';
                num_romanic += figure_upper_five;
                num_romanic += ')';
            }
            else {
                num_romanic += figure_upper_five;
            }
            while (count <= figure - 6) {
                num_romanic += main_figure;
                count++; 
            }
        }
        else if (figure == 9) { // I, X, C, M|X, C, M, (X)
            num_romanic += main_figure;
            if (is_beyond) {
                num_romanic += '(';
                num_romanic += figure_is_nine;
                num_romanic += ')';
            }
            else {
                num_romanic += figure_is_nine;
            }
            
        }

        
    }else if (digit > 4 && digit <= 7) { // digit: 5-7
        num_romanic += '(';
        digit = digit - 4;
        int current_level = (digit - 1) * 2 + 1 - 1 + 2;
        main_figure = level_name[current_level];
        if (current_level + 1 > 6) { // M
            figure_upper_five = level_name[1];
            figure_is_nine = level_name[2];
            is_beyond = true;
        }
        else {
            figure_upper_five = level_name[current_level + 1];
            figure_is_nine = level_name[current_level + 2];
        }

        if (figure <= 3 && figure > 0) {
            while (count < figure) { // I, X, C, M
                num_romanic += main_figure;
                count++;
            }

        }
        else if (figure == 4) { // I, X, C, M|V, L, C, (V)
            num_romanic += main_figure;
            if (is_beyond) {
                num_romanic += '[';
                num_romanic += figure_upper_five;
                num_romanic += ']';
            }
            else {
                num_romanic += figure_upper_five;
            }

        }
        else if (figure >= 5 && figure < 9) { // V, L, C, (V)|I, X, C, M
            if (is_beyond) {
                num_romanic += '[';
                num_romanic += figure_upper_five;
                num_romanic += ']';
            }
            else {
                num_romanic += figure_upper_five;
            }
            while (count <= figure - 6) {
                num_romanic += main_figure;
                count++;
            }
        }
        else if (figure == 9) { // I, X, C, M|X, C, M, (X)
            num_romanic += main_figure;
            if (is_beyond) {
                num_romanic += '[';
                num_romanic += figure_is_nine;
                num_romanic += ']';
            }
            else {
                num_romanic += figure_is_nine;
            }

        }
        num_romanic += ')';
    }
    else if (digit > 7 && digit <= 10) {
    num_romanic += '[';
    digit = digit - 7;
    int current_level = (digit - 1) * 2 + 1 - 1 + 2;
    main_figure = level_name[current_level];
    if (current_level + 1 > 6) { // M
        figure_upper_five = level_name[1];
        figure_is_nine = level_name[2];
        is_beyond = true;
    }
    else {
        figure_upper_five = level_name[current_level + 1];
        figure_is_nine = level_name[current_level + 2];
    }

    if (figure <= 3 && figure > 0) {
        while (count < figure) { // I, X, C, M
            num_romanic += main_figure;
            count++;
        }

    }
    else if (figure == 4) { // I, X, C, M|V, L, C, (V)
        num_romanic += main_figure;
        if (is_beyond) {
            num_romanic += '{';
            num_romanic += figure_upper_five;
            num_romanic += '}';
        }
        else {
            num_romanic += figure_upper_five;
        }

    }
    else if (figure >= 5 && figure < 9) { // V, L, C, (V)|I, X, C, M
        if (is_beyond) {
            num_romanic += '{';
            num_romanic += figure_upper_five;
            num_romanic += '}';
        }
        else {
            num_romanic += figure_upper_five;
        }
        while (count <= figure - 6) {
            num_romanic += main_figure;
            count++;
        }
    }
    else if (figure == 9) { // I, X, C, M|X, C, M, (X)
        num_romanic += main_figure;
        if (is_beyond) {
            num_romanic += '{';
            num_romanic += figure_is_nine;
            num_romanic += '}';
        }
        else {
            num_romanic += figure_is_nine;
        }

    }
    num_romanic += ']';
    }
    
    
    return num_romanic;
}
string to_roman_transfer(long long num, bool *ok=nullptr) {
    /**
    アラビア数字を入力し、ローマ数字へ転換する関数
    1-I, 5-V, 10-X, 50-L, 100-C, 500-D, 1000-M, 5000-(V), 
    9000-M(X), 10,000-(X), 20,000-(XX), 50,000-(L), 50,300-(L)CCC, 51,345-(L)MCCCXLV
    100,000-(C), 500,000-(D), 1,000,000-(M), 5,000,000-((V))
    --------------------------------
    long long max = 5000;

    long long scale_assert = arabic_num / max;
    int I_lev = 1; int V_lev = 5; int X_lev = 10; int L_lev = 50; int C_lev = 100; int D_lev = 500; int M_lev = 1000;

    */
    int digit = 0;
    *ok = true;

    list<long long> splited_units = num_split(num, digit);
    if(digit > 10){
        *ok = false;
        return "xxxx";

    }
    string romanic_number;
    /*cout << digit << endl;
    cout << (LEVELMAX - 1) / 2 + 1 << endl;
    cout << digit / ((LEVELMAX - 1) / 2 + 1) << endl;*/
    cout << num << " for transfer" << endl;
    int top_num;
    while (splited_units.size() != 0) {
        top_num = splited_units.back();
        splited_units.pop_back();
        romanic_number += to_roman(top_num, digit);
        digit = splited_units.size();
    }
    
    return romanic_number;
}

void verify(list<long long> splited_num) {
    std::list<long long>::iterator it = splited_num.begin();
    int digit = 0;
    cout << "the num's digit_count is: " << splited_num.size() << endl;
    while (it != splited_num.end()) {
        cout << *it << endl;
        it++;
        digit++;
    }

    /*while (splited_num.size() != 0) {
        cout << splited_num.back() << ", the list's capacity is:" << splited_num.size() << endl;
        splited_num.pop_back();
        
    }*/

}
