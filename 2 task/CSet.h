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
	//unsigned long int *num = nullptr;
	vector<bitset<64>> body;
	//CSet(int l, int u, char* str);
	//CSet(int l, int u, char* str, string file);
	CSet(int l, int u, vector<bitset<64>> &n, string file);
	CSet(int l, int u);
	CSet(const CSet &);
	CSet(CSet &&);
	CSet& operator =(const CSet &);
	CSet& operator =(CSet &&);
	CSet& operator ++();
	CSet& operator --();
	friend ostream& operator<<(ostream &, const CSet &);
	int is_belong(int n) const;
	virtual int output()=0;
	virtual ~CSet(){
		//delete [] filename;
	}
	static CSet *create_by_Factory(string str, vector<Factory*> f);
};


struct CData0:public CSet{
	//CData0(int l, int u, char* str):CSet(l,u,str){}
	//CData0(int l, int u, char* str, char* file):CSet(l,u,str,file){}
	CData0(int l, int u, vector<bitset<64>> &n, string file):CSet(l,u,n,file){}
	CData0(int l, int u):CSet(l,u){}
	CData0(const CSet &b):CSet(b){}
	CData0(CSet &&b):CSet(b){}
	int output() override;
};


struct CData1:public CSet{
	//CData1(int l, int u, char* str):CSet(l,u,str){}
	//CData1(int l, int u, char* str, char* file):CSet(l,u,str,file){}
	CData1(int l, int u, vector<bitset<64>> &n, string file):CSet(l,u,n,file){}
	CData1(int l, int u):CSet(l,u){}
	CData1(const CSet &b):CSet(b){}
	CData1(CSet &&b):CSet(b){}
	int output() override;
};


char *mygets(char *&str, size_t &LMax, FILE *in);
int get_int(char *s,int &x);
int get_word(char *s,char *&str);

CData0 operator++(CSet &b, int);
CData0 operator--(CSet &b, int);
CData0 operator+(const CSet &f, const CSet &s);
CData0 operator-(const CSet &f, const CSet &s);
