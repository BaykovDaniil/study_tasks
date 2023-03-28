#include"CSet.h"
#include"factory.h"


CSet* FactoryCData0::create(int l, int u, vector<bitset<64>> &str, string file){
        return new CData0(l,u,str,file);
}

CSet* FactoryCData1::create(int l, int u, vector<bitset<64>> &str, string file){
        return new CData1(l,u,str,file);
}
