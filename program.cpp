#include<iostream>
#include<fstream>
#include<cassert>

class Matrix
{
private:
	int* arr;
	unsigned int row;
	unsigned int col;
	int number;

public:
	Matrix(unsigned const int M, unsigned const int N): row(M),col(N) 
	{
		arr = new int[M*N];
	}

	int NumberOfRows() const
	{
		return row;
	}

	int NumberOfColumns() const
	{
		return col;
	}
	void setNumber(int n)
	{
		number = n;
	}
	int NumberOfMatrix() const
	{
		return number;
	}
	int& operator()(const unsigned int m, const unsigned int n) const
	{
		return arr[m*NumberOfColumns()+n];
	}

	~Matrix()
	{
		delete [] arr;
		arr = NULL;
	}

};


class ReadFile
{
private:
char c;
const char* file_name;
std::ifstream f;

public:
unsigned int row = 0;
unsigned int col = 0;

ReadFile(const char* fn): file_name(fn)
{
	f.open(file_name, std::ios::in);
	assert(f.is_open() && "File oppening..");
	if(!(f>>row && f>>c && f>>col))
		{
			std::cout<<"Cant read.."<<std::endl;
		}
}

bool read_char(char& data)
{
	assert(f);
	//assert(data);
	if(f>>data) {
		return true;
	} else {
		return false;
	}
}

bool read(int& data)
{
	assert(f);
	//assert(data);
	if(f>>data) {
		return true;
	} else {
		return false;
	}
}

int getRow()
{
	return row;
}

int getCol()
{
	return col;
}
~ReadFile()
{
	f.close();
}

};

class WriteFile
{
private:
const char* file_name;
std::ofstream f;

public:
WriteFile(const char* fn): file_name(fn)
{
	f.open(file_name,std::ios::out);
	assert(f.is_open() && "File oppening..");
}
void write(const int& i) 
{
	f<<i<<' ';
}
 void writechar(const char* c) 
{
	f<<c;
}
~WriteFile()
{
	f.close();
}

};

bool ReadMatrix(Matrix& m, ReadFile& r)
{
	char c;
	int i;
	int n;
	if(r.read_char(c) && r.read(n)) 
	{	
	m.setNumber(n);
	for(int i=0; i<m.NumberOfRows(); i++) {	
		for(int j=0; j<m.NumberOfColumns(); j++) {		
				int x = 0;
				if(r.read(x)) {
				m(i,j) = x; 
			} else {
				std::cout<<"Can't Read .."<<std::endl;
				return false;
			}
		}
	}
	} else {
		return false;
	}
	return true;
}

void AddMatrix(const Matrix& a, const Matrix& b, Matrix& c)
{
	assert(a.NumberOfRows()==b.NumberOfRows());
	assert(a.NumberOfColumns()==b.NumberOfColumns());
	assert(a.NumberOfRows() == c.NumberOfRows());
	assert(a.NumberOfColumns() == c.NumberOfColumns());
	for(int i=0; i<a.NumberOfRows(); i++)
	{
		for(int j=0; j<a.NumberOfColumns(); j++)
		{
			c(i,j) = a(i,j) + b(i,j);
		}
	}
}


void MultMatrix(const Matrix& a, const Matrix& b, Matrix& c)
{
	assert(a.NumberOfColumns() == b.NumberOfRows());
	assert(a.NumberOfRows() == c.NumberOfRows());
	assert(b.NumberOfColumns() == c.NumberOfColumns());
	for(int i=0; i<a.NumberOfRows(); i++)
	{
		for(int j=0; j<b.NumberOfColumns(); j++)
		{
			int s = 0;
			for(int k=0; k<a.NumberOfColumns();k++)
			{
				s += a(i,k)*b(k,j);
			}
			c(i,j) = s;
		}
	}
}
void WriteMatrix(const Matrix& m,  Matrix& a,  const Matrix& b, WriteFile& f)
{
	if(a.NumberOfMatrix() == 1)
	{
		f.write(a.NumberOfRows());
		f.writechar("x");
		f.write(b.NumberOfColumns());
		f.writechar("\n");
		f.writechar("\n");
		f.writechar("#");
		f.write(1);
		f.writechar("\n");
	} else {	
		f.writechar("#");
		f.write(a.NumberOfMatrix());
		f.writechar("\n");	
	}
	
	 for(int i=0; i<m.NumberOfRows(); i++)
	{
		for(int j=0; j<m.NumberOfColumns(); j++)
		{
			f.write(m(i,j));
		}
		f.writechar("\n"); 
	}
		f.writechar("\n"); 
}

void ReadMatrixSize(unsigned int& m, unsigned int& n, unsigned int& k, 
						ReadFile& ra, ReadFile& rc)
{
	m = ra.getRow();
	n = ra.getCol();
	k = rc.getCol();
}
int main()
{
	unsigned int M=0, N=0, K=0;
	ReadFile ra("./a.txt"), rb("./b.txt"), rc("./c.txt"), rd("./d.txt");
	ReadMatrixSize(M,N,K,ra,rc);
	Matrix a(M,N), b(M,N), c(N,K), d(N,K), sum_ab(M,N), sum_cd(N,K), mult(M,K);
	WriteFile file("./file.txt");
	while(ReadMatrix(a, ra) && ReadMatrix(b, rb) 
			&& ReadMatrix(c, rc) && ReadMatrix(d, rd))
	{
		AddMatrix(a,b,sum_ab);
		AddMatrix(c,d,sum_cd);
		MultMatrix(sum_ab, sum_cd, mult);
		WriteMatrix(mult,a,b,file);
	}
	return 0;
}
