#pragma once
#include<stdio.h>
#include<list>
#include<string>
using namespace std;

string to_roman_transfer(long long num, bool *ok=nullptr);
void verify(std::list<long long> splited_num);
std::list<long long> num_split(long long num, int& digit);
