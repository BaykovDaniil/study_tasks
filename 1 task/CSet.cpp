#include"CSet.h"
#include"factory.h"


unsigned long int BinDec(char* bin, int size)
{
    unsigned long int n=0;
    for(int i = size-1; i>=0; --i){
    	if(bin[i]=='1')
        	n += pow(2,size-1-i);
    }
   	return n;
}


CSet *CSet::create_by_Factory(char* str, Factory **f)
{
	int type, pos, lower, upper, x;
	pos = get_int(str, type);
	if(pos<1)
		throw -1; // uncorrect type
	if(type!=0 && type!=1)
		throw -1; // uncorrect type
	str+=pos;
	char* filename = new char[256];
	pos = get_word(str, filename);
	str+=pos;
	pos = get_int(str, lower);
	if(pos<1)
		throw -2; // uncorrect bounds
	str+=pos;
	pos = get_int(str, upper);
	if(pos<1)
		throw -2; // uncorrect bounds
	if(lower>upper){
		delete[]filename;
		throw -2; // uncorrect bounds
	}
	str+=pos;
    unsigned long int k;
    int size = ceil((upper-lower)/sizeof(unsigned long int));
    unsigned long int* n = new unsigned long int[size];
    for(int i=0; i<size; ++i)
    	n[i]=0;
	while(pos=get_int(str,x),pos)
	{
		if(pos<1){
			delete[]filename;
			throw -3; // uncorrect data
		}
		if(x>upper || x<lower){
			delete[]filename;
			throw -3; // uncorrect data
		}
		k = 1;
		int index = floor((x - lower) / size);
		k = k << (sizeof(unsigned long int)*(index+1) - x);
		n[index] = n[index] | k;
        str+=pos;
    	}
	if(type==0)
		return f[0]->create(lower,upper,n,filename);
	if(type==1)
		return f[1]->create(lower,upper,n,filename);
	return nullptr;
}
/*
CData0 operator+(const CSet&f, const CSet&s)
{
	int new_lower = min(f.lower,s.lower), new_upper = max(f.upper, s.upper);
	CData0 result(new_lower, new_upper);
	for(int i=new_lower; i<=new_upper; ++i)
	{
		result.num = result.num << 1;
		if(f.is_belong(i) == 1 || s.is_belong(i) == 1)
		{
			result.num = result.num + 1;
		}
	}
	if(f.filename!=nullptr){
		result.filename=new char[256];
		strcpy(result.filename, f.filename);
	}
	return result;
}

CData0 operator-(const CSet&f, const CSet&s)
{
	int new_lower = max(f.lower,s.lower), new_upper = min(f.upper, s.upper);
	if(new_lower>new_upper){
		CData0 res(0,0);
		if(f.filename!=nullptr){
			res.filename=new char[256];
			strcpy(res.filename, f.filename);
		}
		return res;
	}

	CData0 result(new_lower, new_upper);
	for(int i=new_lower; i<=new_upper; ++i)
	{
		result.num = result.num << 1;
		if(f.is_belong(i) == 1 && s.is_belong(i) == 1)
		{
			result.num = result.num + 1;
		}
	}

	if(f.filename!=nullptr){
		result.filename=new char[256];
		strcpy(result.filename, f.filename);
	}
	return result;
}
*/
CData0 operator++(CSet &b, int)
{	
	CData0 tmp(b);
	++b;
	return tmp;
}

CData0 operator--(CSet &b, int)
{	
	CData0 tmp(b);
	--b;
	return tmp;
}

int CData0::output()
{
	ofstream File(filename);

	for(int i=lower;i<=upper;++i)
	{
		if(is_belong(i))
			File<<i<<" ";
	}
	File.close();
	return 0;
}

int CData1::output()
{
	ofstream File(filename);
	for(int i=lower;i<=upper;++i)
	{
		if(is_belong(i))
			File<<i<<endl;
	}
	File.close();
	return 0;
}

CSet::CSet(int l, int u, unsigned long int* n, char* file)
{
	lower = l;
	upper = u;
	size = ceil((u-l)/sizeof(unsigned long int));
	num = n;
	n = nullptr;
	filename = file;
	file=nullptr;
}
/*
CSet::CSet(int l, int u, char* str, char* file)
{
	lower = l;
	upper = u;
	num = BinDec(str, u - l + 1);
	filename = file;
	delete[]str;
	str=nullptr;
	file=nullptr;

}


CSet::CSet(int l, int u, char* str)
{
	lower = l;
	upper = u;
	num = BinDec(str, u - l + 1);
}
*/

CSet::CSet(int l, int u)
{
	lower = l;
	upper = u;
	size = ceil((u-l)/sizeof(unsigned long int));
	num = new unsigned long int[size];
	for(int i=0; i<size; ++i)
	{
		num[i]=0;
	}
}

CSet::CSet(const CSet &set)
{
	lower = set.lower;
	upper = set.upper;
	size = set.size;
	num = new unsigned long int[size];
	for(int i=0; i<size; ++i)
	{
		num[i]=set.num[i];
	}
	if(set.filename != nullptr){
		filename = new char[256];
		strcpy(filename, set.filename);
	}

}

CSet::CSet(CSet &&set){
	this->upper = set.upper;
	this->lower = set.lower;
	this->size = set.size;
	this->num = set.num;
	set.num = nullptr;
	this->filename = set.filename;
	set.filename = nullptr;

}




CSet& CSet::operator =(const CSet &set)
{
	lower = set.lower;
	upper = set.upper;
	delete[]num;
	num = new unsigned long int[size];
	for(int i=0; i<size; ++i)
	{
		num[i]=set.num[i];
	}
	delete[]filename;
	if(set.filename != nullptr){
		filename = new char[256];
		strcpy(filename, set.filename);
	}
	return *this;
}

CSet& CSet::operator =(CSet &&set)
{
	lower = set.lower;
	upper = set.upper;
	delete[]num;
	num = set.num;
	set.num = nullptr;
	delete[]filename;
	filename = set.filename;
	set.filename = nullptr;
	return *this;
}

CSet& CSet::operator ++()
{
	upper++;

	if((upper-lower)/sizeof(unsigned long int) == size)
	{
		unsigned long int* tmp = new unsigned long int[size+1];
		for(int i=0; i<size; ++i)
		{
			tmp[i]=num[i];
		}
		tmp[size] = 1;
		delete[]num;
		num = tmp;
		++size;
	}
	else
	{
		num[size-1] = num[size-1] << 1;
	}


	//++size;
	return *this;
}

CSet& CSet::operator --()
{
	if(upper-lower<=0){
		return *this;
	}
	this->upper--;
	this->num[size] = this->num[size] >> 1;
	//--size;
	if((upper-lower)/sizeof(unsigned long int) == size-1)
	{
		--size;
		unsigned long int* tmp = new unsigned long int[size];
		for(int i=0; i<size; ++i)
		{
			tmp[i]=num[i];
		}
		delete[]num;
		num = tmp;
	}

	return *this;
}

int CSet::is_belong(int n) const
{
	if(n < lower || n > upper)
		return 0;

	int pos = floor((n - lower) / size);

	unsigned long int s = num[pos] >> (lower + sizeof(unsigned long int)*(pos+1) - n);

	if((s&1) == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}


ostream& operator<<(ostream &stream, const CSet &set)
{
	stream<<"lower bound:"<<set.lower<<endl;
	stream<<"upper bound:"<<set.upper<<endl;
	stream<<"numbers:";
	for(int i=set.lower;i<=set.upper;++i)
	{
		if(set.is_belong(i)) stream<<i<<" ";
	}
	stream<<endl;
	return stream;
}
