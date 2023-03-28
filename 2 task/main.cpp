#include"CSet.h"
#include"factory.h"
#include <stdio.h>
#include <stdlib.h>


int main(){
    CData0 a(0,63); // пустое
    vector<Factory*> f = {new FactoryCData0, new FactoryCData1}; 
    vector<CSet*> arr;
    size_t n=0,c=0;
    ifstream in("input.txt");
    string str;

    try{
        while(getline(in, str))
        {
    	    if(str.size()==0){
    		++c;
    		continue;
    	    }
            CSet* tmp = CSet::create_by_Factory(str,f);
            ++c;
            ++n;
            arr.push_back(tmp);
        }

        for(size_t i=0;i<n;++i)
        {
            arr[i]->output();
            cout<<*arr[i];
        }

        CData0 d=*arr[0];
        for(size_t i=0;i<n-1;++i)
            *arr[i]=*arr[i+1];
        *arr[n-1]=d;

        for(size_t i=0;i<n;++i){
            --(*arr[i]);
            ++(*arr[i]);
            cout<<*arr[i]<<endl;
        }


        for(size_t i=0;i<n;++i){
            a = *arr[i] + a;
        }
        cout<<a<<"--------"<<endl;

        for(size_t i=0;i<n;i++){
            a = *arr[i] - a;
        }
        cout<<a<<"--------"<<endl;;

        CData1 b(*arr[0]);
        cout<<b;

    }
    catch(int i){
        if(i==-1)
        {
            cout<<"Uncorrect type(string "<<c+1<<")"<<endl;
        }
        if(i==-2)
        {
            cout<<"Uncorrect bounds(string "<<c+1<<")"<<endl;
        }
        if(i==-3)
        {
            cout<<"Uncorrect data(string "<<c+1<<")"<<endl;
        }
    }
    for(size_t i=0;i<n;++i){
        delete arr[i];
    }

    for(size_t i=0;i<2;++i)
        delete f[i];    

    in.close();

    return 0;
}