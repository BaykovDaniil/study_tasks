#include"CSet.h"
#include"factory.h"


CSet *CSet::create_by_Factory(string str, vector<Factory*> f)
{
	int type, lower, upper, x;
	stringstream stream(str);
	stream >> type;
	/*if(pos<1)
		throw -1; // uncorrect type
	if(type!=0 && type!=1)
		throw -1; // uncorrect type
	str+=pos;
	*/
	string filename;
	stream >> filename;
	stream >> lower;
	stream >> upper;
	//cout<<lower<<endl;
	
	/*
	if(pos<1){
		delete[]filename;
		throw -2; // uncorrect bounds
	}
	
	if(pos<1){
		delete[]filename;
		throw -2; // uncorrect bounds
	}
	if(lower>upper){
		delete[]filename;
		throw -2; // uncorrect bounds
	}
	*/
	//str+=pos;
    //int index;
    int size = ceil(float(upper-lower)/64);
    vector<bitset<64>> n(size);

	while(stream >> x)
	{
		/*if(pos<1){
			delete[]filename;
			throw -3; // uncorrect data
		}
		if(x>upper || x<lower){
			delete[]filename;
			throw -3; // uncorrect data
		}*/
		//index = (x - lower)/64;
		n[(x - lower)/64][(x-lower)%64] = 1;
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
	int pos = 0;
	for(int i=new_lower; i<=new_upper; ++i)
	{
		if(f.is_belong(i) == 1 || s.is_belong(i) == 1)
		{
			result.body[pos / 64][(i-new_lower) % 64] = 1;
		}
		++pos;
	}
	result.filename = f.filename;
	return result;
}

CData0 operator-(const CSet&f, const CSet&s)
{
	int new_lower = max(f.lower,s.lower), new_upper = min(f.upper, s.upper);
	if(new_lower>new_upper){
		CData0 res(0,0);
		res.filename = f.filename;
		return res;
	}
	CData0 result(new_lower, new_upper);
	int pos=0;
	for(int i=new_lower; i<=new_upper; ++i)
	{
		if(f.is_belong(i) == 1 && s.is_belong(i) == 1)
		{
			result.body[pos / 64][(i-new_lower)%64] = 1;
		}
		++pos;
	}
	result.filename = f.filename;
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

CSet::CSet(int l, int u, vector<bitset<64>> &b, string file)
{
	lower = l;
	upper = u;
	size = ceil(float(upper-lower)/64);
	body = b;
	filename = file;
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
	filename = set.filename;

}

CSet::CSet(CSet &&set){
	this->upper = set.upper;
	this->lower = set.lower;
	this->size = set.size;
	this->body = set.body;
	this->filename = set.filename;
}




CSet& CSet::operator =(const CSet &set)
{
	lower = set.lower;
	upper = set.upper;
	size = set.size;
	body = set.body;
	filename = set.filename;
	return *this;
}

CSet& CSet::operator =(CSet &&set)
{
	lower = set.lower;
	upper = set.upper;
	size = set.size;
	body = set.body;
	filename = set.filename;
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

CSet& CSet::operator --()
{
	if(upper-lower<=0){
		return *this;
	}
	this->upper--;

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
