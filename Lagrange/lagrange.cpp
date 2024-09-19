#include"lagrange.h"

float func(float x){

	return sin(5.0 * x);

}

// создает массив из N случайных вещественных чисел от a до b
// 1-е и N-е всегда a и b
// требует отчистки памяти
float* get_random_massive(float &a, float &b, size_t &N){

	float* x = new float[N];
	float r;
    bool flag = 0; // хранит информацию о совпадении нового случайного числа с уже сгенерированными
    x[0] = a;
    for(size_t i=1; i<N-1; ++i){
    	while(true){
    		r = a + (b-a) * rand() / RAND_MAX;
    		if( abs(r-a) < EPS*(b-a) ){
    				flag = 1;
    			}
    		for(size_t j=0; j<i; ++j){
    			if( abs(r-x[j]) < EPS*(b-a) ){
    				flag = 1;
    			}
    		}
    		if( abs(r-b) < EPS*(b-a) ){
    				flag = 1;
    			}
    		if(flag == 0){
    			x[i] = r;
    			break;
    		}
    		else{
    			flag = 0;
    		}
    	}
    }
    x[N-1] = b;
    return x;

}

// создает массив повторяющихся в многочлене Лагранжа знаменателей
// требует отчисти памяти
float* get_denominator(float* x, size_t &N){

	float* denominator = new float[N];
    for(size_t i=0; i<N; ++i){
   		float product = 1.0;
    	for(size_t j=0; j<N; ++j){
    		if(i==j){
    			continue;
    		}
    		product *= x[i] - x[j];
    	}
    	denominator[i] = product;
    }
    return denominator;

}

// возвращает значение аппрокcимации в точке _x
// (x, y) - точки, по которым идет аппрокcимация
float lagrange(float _x, float* x, float* y, size_t &N, float* denominator){

	float result = 0, product;
	for(size_t i=0; i<N; ++i){
		product = 1.0;
		for(size_t j=0; j<N; ++j){
			if(i==j){
    			continue;
    		}
    		product *= (_x-x[j]);
		}
		result += y[i] * product / denominator[i];;
	}
	return result;

}
