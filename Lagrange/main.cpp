#include"lagrange.h"


int main(){
    srand(time(NULL));

    // концы отрезков
    float a = 1.0;
    float b = 3.0;

    // количество узлов и размер сетки для вывода
    size_t N = 5;
    size_t M = 100;

    // массивы точек аппроксимации и знаменателей
    float* x = get_random_massive(a, b, N);;
    float* y = new float[N];
    float* denominator = get_denominator(x, N);

    for(size_t i=0; i<N; ++i){
    	y[i] = func(x[i]);
    }

    ostringstream ss; // для запуска Python и передечи в него данных
    ss << "python3 File.py " << a << " " << b << " " << N << " ";
    for(size_t i=0; i<N; ++i){
    	ss << x[i] << " " << y[i] << " ";
    }
    for(size_t i=0; i<=M; ++i){
    	ss << a + (b-a) * i / M << " " << lagrange(a + (b-a) * i / M, x, y, N, denominator) << " " << func(a + (b-a) * i / M) << " ";
    }

    system(ss.str().c_str()); // вызов Python
    delete [] x;
    delete [] y;
    delete [] denominator;
    return 0;
}