#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<ctime>
#include<string>
#include<sstream>
#define EPS 0.001 // погрешность сравнения вещественных чисел

using namespace std;


float func(float x);
float* get_random_massive(float &a, float &b, size_t &N);
float* get_denominator(float* x, size_t &N);
float lagrange(float _x, float* x, float* y, size_t &N, float* denominator);