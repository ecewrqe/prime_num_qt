/**
 * prime number cplus main window
 *
 * @author			euewrqe
 * @version        v1.1
 *
 */

#include<stdio.h>
#include <cmath>
#include<iostream>
#include<string>
#include<set>
#include<list>
#include "prime_num.h"
using namespace std;
/// <summary>
/// pow(10, 2)
/// </summary>
/// <param name="n"></param>
/// <param name="m"></param>
/// <returns></returns>
int numSquareSum(long long n);

bool is_prime_func(long long n, long long &pi) {
	if (n == 1) {
		return true;
	}
    for (int i = 2; i < pow(n, 0.5) + 1; i++) {
		if (n % i == 0) {
			pi = i;
			return false;
		}
	}
	return true;
}

bool is_happy_func(long long n) {
    set<int> st;
	while (1) {
		n = numSquareSum(n);
		if (n == 1) return true;
		/*cout << "find:" << st.find(n) << " end:" << st.end() << endl;*/
		if (st.find(n) != st.end()) return false;
		st.insert(n);
	}
}

int numSquareSum(long long n) {
	int squareSum = 0;
	while (n) {
		squareSum += (n % 10) * (n % 10);
		n /= 10;
	}
	return squareSum;
}


list<long long> get_primenum_list(long long max_num, long long min_num, bool happy, bool prime) {
	
    list<long long> prime_list;
	if (min_num < 7) {
		min_num = 7;
	}
    long long num = min_num;

	if (min_num > max_num) {
		return prime_list;
	}

	if (prime) {
		while (num <= max_num) {

            long long remainder;
            long long is_prime = is_prime_func(num, remainder);
			if (is_prime) {
				if (happy && is_happy_func(num)) {
					prime_list.push_back(num);
				}
				else if (!happy) {
					prime_list.push_back(num);
				}
			}
			num += 1;
		}
	}
	else {
		while (num <= max_num) {
			if (happy && is_happy_func(num)) {
				prime_list.push_back(num);
			}
			num += 1;
		}
	}
	return prime_list;



}
