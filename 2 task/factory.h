#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<fstream>

using namespace std;


struct Factory
{
	virtual CSet *create(int l, int u, vector<bitset<64>> &str, string file)=0;
	virtual ~Factory(){}
};

struct FactoryCData0:public Factory{
	CSet* create(int l, int u, vector<bitset<64>> &str, string file);
};

struct FactoryCData1:public Factory{
	CSet* create(int l, int u, vector<bitset<64>> &str, string file);
};

