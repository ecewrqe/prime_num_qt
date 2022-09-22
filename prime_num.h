/**
 * prime number list cpp
 *
 * @author			euewrqe
 * @version        v1.1
 *
 */

#pragma once
#include<stdio.h>
#include<list>
std::list<long long> get_primenum_list(long long, long long=7, bool happy=false, bool prime=true);
bool is_prime_func(long long n, long long & pi);
bool is_happy_func(long long n);
