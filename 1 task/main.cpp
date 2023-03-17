#include"CSet.h"
#include"factory.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    CData0 a(1,5); // пустое

    Factory *f[]={new FactoryCData0,new FactoryCData1}; 
    CSet **arr=nullptr;size_t n=0;
    size_t LMax = 2;
    FILE *in = fopen("input.txt","r");
    char* str=nullptr;

    try{
        while(mygets(str,LMax,in)){
            CSet **tmp=new CSet *[n+1];
            if(arr){
                memmove(tmp,arr,sizeof(void *)*n);
                delete[]arr;
            }
            arr=tmp;
            tmp=nullptr;
            ++n;
            arr[n-1]=CSet::create_by_Factory(str,f);
        }
        for(size_t i=0;i<n;++i)
        {
            arr[i]->output();
        }
        
        CData0 d=*arr[0];
        for(size_t i=0;i<n-1;++i)
            *arr[i]=*arr[i+1];
        *arr[n-1]=d;

        for(size_t i=0;i<n;++i){
            (*arr[i])--;
            (*arr[i])++;
        }
/*
        for(size_t i=0;i<n;++i){
            a = *arr[i] + a;
        }
        cout<<a<<"--------"<<endl;

        for(size_t i=0;i<n;i++){
            a = *arr[i] - a;
        }
        cout<<a<<"--------"<<endl;;
*/    
        CData1 b(a);
        cout<<b;
    }
    catch(int i){
        if(i==-1)
        {
            cout<<"Uncorrect type(string "<<n<<")";
        }
        if(i==-2)
        {
            cout<<"Uncorrect bounds(string "<<n<<")";
        }
        if(i==-3)
        {
            cout<<"Uncorrect data(string "<<n<<")";
        }
        arr[n-1]=nullptr;
        delete[]str;
    }

    for(size_t i=0;i<n;++i)
        delete arr[i];
    delete []arr;
    for(size_t i=0;i<2;++i)
        delete f[i];    

    fclose(in);
    
    return 0;
}