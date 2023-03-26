#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<fstream>
#include<cmath>
#include<vector>
#include<bitset>

#include <string>

#include <sstream>

#include <iostream>

using namespace std;


struct Factory;

struct CSet{
	string filename = "";
	int lower=0, upper=0, size;
	vector<bitset<64>> body;
	CSet(int l, int u, vector<bitset<64>> &n, string file);
	CSet(int l, int u);
	CSet(const CSet &) = default;
	CSet(CSet &&) = default;
	CSet& operator =(const CSet &) = default;
	CSet& operator =(CSet &&) = default;
	CSet& operator ++();
	CSet& operator --();
	friend ostream& operator<<(ostream &, const CSet &);
	int is_belong(int n) const;
	virtual int output()=0;
	virtual ~CSet(){
	}
	static CSet *create_by_Factory(string str, vector<Factory*> f);
};


struct CData0:public CSet{
	CData0(int l, int u, vector<bitset<64>> &n, string file):CSet(l,u,n,file){}
	CData0(int l, int u):CSet(l,u){}
	CData0(const CSet &b):CSet(b){}
	CData0(CSet &&b):CSet(b){}
	int output() override;
};


struct CData1:public CSet{
	CData1(int l, int u, vector<bitset<64>> &n, string file):CSet(l,u,n,file){}
	CData1(int l, int u):CSet(l,u){}
	CData1(const CSet &b):CSet(b){}
	CData1(CSet &&b):CSet(b){}
	int output() override;
};


CData0 operator++(CSet &b, int);
CData0 operator--(CSet &b, int);
CData0 operator+(const CSet &f, const CSet &s);
CData0 operator-(const CSet &f, const CSet &s);

bool isNumeric(string const &str);