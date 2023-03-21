#include"CSet.h"
#include"factory.h"
#include <stdio.h>
#include <stdlib.h>

int foo();

void foo(vector<bitset<32>> &a){
    a[0][0]=1;
}

int main(){

    //vector<bitset<32>> a(5);
    //a[0][0]=1;
    //foo(a);
    //for(size_t i=0;i<5;++i){
    //    cout<<a[i];
    //    cout<<endl;
    //}



    CData0 a(1,5); // пустое

    Factory *f[]={new FactoryCData0,new FactoryCData1}; 
    CSet **arr=nullptr;size_t n=0;
    size_t LMax = 2;
    FILE *in = fopen("input.txt","r");
    char* str=nullptr;

    try{
        while(mygets(str,LMax,in))
        {
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
            cout<<*arr[i];
        }
 
        CData0 d=*arr[0];
        for(size_t i=0;i<n-1;++i)
            *arr[i]=*arr[i+1];
        *arr[n-1]=d;

        for(size_t i=0;i<n;++i){
            (*arr[i])--;
            (*arr[i])++;
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
            cout<<"Uncorrect type(string "<<n<<")"<<endl;
        }
        if(i==-2)
        {
            cout<<"Uncorrect bounds(string "<<n<<")"<<endl;
        }
        if(i==-3)
        {
            cout<<"Uncorrect data(string "<<n<<")"<<endl;
        }
        arr[n-1]=nullptr;
        delete[]str;
    }
    /*for(int i=0;i<arr[1]->size;++i){
        //for(int j=0;j<*arr[0].size;++j)
            cout<<arr[1]->body[i];
            cout<<endl<<"-----"<<endl;
    }*/

    for(size_t i=0;i<n;++i)
        delete arr[i];
    delete []arr;
    for(size_t i=0;i<2;++i)
        delete f[i];    

    fclose(in);


    return 0;
}