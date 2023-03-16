#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<fstream>

using namespace std;


struct Factory
{
	virtual CSet *create(int l, int u, unsigned long int str, char* file)=0;
	virtual ~Factory(){}
};

struct FactoryCData0:public Factory{
	CSet* create(int l, int u, unsigned long int str, char* file);
};

struct FactoryCData1:public Factory{
	CSet* create(int l, int u, unsigned long int str, char* file);
};

