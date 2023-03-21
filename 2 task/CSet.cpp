#include"CSet.h"
#include"factory.h"


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
	if(pos<1){
		delete[]filename;
		throw -2; // uncorrect bounds
	}
	str+=pos;
	pos = get_int(str, upper);
	if(pos<1){
		delete[]filename;
		throw -2; // uncorrect bounds
	}
	if(lower>upper){
		delete[]filename;
		throw -2; // uncorrect bounds
	}
	str+=pos;
    //unsigned long int k;
    //int size = ceil(float(upper-lower)/64);
    int index;
    int size = ceil(float(upper-lower)/64);
    vector<bitset<64>> n(size);
    //unsigned long int* n = new unsigned long int[size];
    //for(int i=0; i<size; ++i)
    //	n[i]=0;
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
		index = (x - lower)/64;
		n[index][(x-lower)%64] = 1;
		//k = 1;
		//int index = floor(float(x - lower) / (8*sizeof(unsigned long int)));
		//k = k << (lower + 8*sizeof(unsigned long int)*(index+1) - x - 1);
		//n[index] = n[index] | k;
        str+=pos;
    }
	if(type==0)
		return f[0]->create(lower,upper,n,filename);
	if(type==1)
		return f[1]->create(lower,upper,n,filename);
	return nullptr;
}

CData0 operator+(const CSet&f, const CSet&s)
{
	int new_lower = min(f.lower,s.lower), new_upper = max(f.upper, s.upper);
	CData0 result(new_lower, new_upper);
	//unsigned long int k;

	int pos = 0;
	for(int i=new_lower; i<=new_upper; ++i)
	{
		//k = 1;
		if(f.is_belong(i) == 1 || s.is_belong(i) == 1)
		{
			result.body[pos / 64][(i-new_lower) % 64] = 1;

			//int index = floor(float(i - new_lower) / (8*sizeof(unsigned long int)));
			//k = k << (new_lower + 8*sizeof(unsigned long int)*(index+1) - i - 1);
			//result.num[index] = result.num[index] | k;
		}
		++pos;
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
	//unsigned long int k;
	CData0 result(new_lower, new_upper);
	int pos;
	for(int i=new_lower; i<=new_upper; ++i)
	{
		//k = 1;
		if(f.is_belong(i) == 1 && s.is_belong(i) == 1)
		{
			result.body[pos / 64][(i-new_lower)%64] = 1;
			//nt index = floor(float(i - new_lower) / (8*sizeof(unsigned long int)));
			//k = k << (new_lower + 8*sizeof(unsigned long int)*(index+1) - i - 1);
			//result.num[index] = result.num[index] | k;
		}
		++pos;
	}

	if(f.filename!=nullptr){
		result.filename=new char[256];
		strcpy(result.filename, f.filename);
	}
	return result;
}

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

CSet::CSet(int l, int u, vector<bitset<64>> &b, char* file)
{
	lower = l;
	upper = u;
	size = ceil(float(upper-lower)/64);
	body = b;
	filename = file;
	file=nullptr;
}


CSet::CSet(int l, int u)
{
	lower = l;
	upper = u;
	size = ceil(float(upper-lower)/64);
	body.resize(size);
}

CSet::CSet(const CSet &set)
{
	lower = set.lower;
	upper = set.upper;
	size = set.size;
	body = set.body;

	if(set.filename != nullptr){
		filename = new char[256];
		strcpy(filename, set.filename);
	}

}

CSet::CSet(CSet &&set){
	this->upper = set.upper;
	this->lower = set.lower;
	this->size = set.size;
	this->body = set.body;
	this->filename = set.filename;
	set.filename = nullptr;

}




CSet& CSet::operator =(const CSet &set)
{
	lower = set.lower;
	upper = set.upper;
	size = set.size;
	body = set.body;
	
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
	size = set.size;
	body = set.body;
	delete[]filename;
	filename = set.filename;
	set.filename = nullptr;
	return *this;
}

CSet& CSet::operator ++()
{
	upper++;

	if(abs(float(upper-lower)/64 - size) < 0.001)
	{
		body.push_back(bitset<64>());
		++size;
	}
	return *this;
}

CSet& CSet::operator --() // TODO
{
	if(upper-lower<=0){
		return *this;
	}
	this->upper--;
//cout<<body[size-1][(upper-lower+1)%64]<<endl;
//cout<<body[size-1]<<size<<endl;
	body[size-1][(upper-lower+1)%64] = 0;

	if(abs(float(upper-lower)/64 - (size-1)) < 0.001 && size>1)
	{
		--size;
		body.pop_back();
	}
	
	return *this;
}

int CSet::is_belong(int n) const
{
	if(n < lower || n > upper)
		return 0;
	int pos = floor((n - lower) / 64);
	if(body[pos][(n - lower) % 64] == 0)
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
