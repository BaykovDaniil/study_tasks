a:CSet.o factory.o main.o 
	g++ -fno-elide-constructors -std=c++11 CSet.o factory.o main.o
	
main.o:main.cpp CSet.h factory.h  
	g++ -fno-elide-constructors -std=c++11  main.cpp -c

CSet.o:CSet.cpp CSet.h factory.h
	g++ -fno-elide-constructors -std=c++11  CSet.cpp -c

factory.o:factory.cpp factory.h CSet.h
	g++ -fno-elide-constructors -std=c++11  factory.cpp -c