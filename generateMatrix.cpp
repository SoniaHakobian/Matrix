#include<cstdlib>
#include<ctime>
#include<iostream>
#include<string>
#include<fstream>

void InputData(int& M, int& N, int& count)
{
	std::cout<<"How many Matrix do you want to have in a file?"<<std::endl;
	std::cout<<"Count = ";
	std::cin>>count;
	std::cout<<"Enter the size of rows: M = ";
	std::cin>>M;
	std::cout<<"Enter the size of columns: N = ";
	std::cin>>N;
}


void Generatefile(std::string& name, const int M, const int N, int count)
{
	srand(time(0));
	int num = 1;
	std::cout<<"Enter the desired file name.."<<std::endl;
        std::cout<<"Name = ";
	std::cin>>name;

	std::ofstream f;
	f.open(name, std::ios::out);
	f<<M<<"x"<<N<<std::endl;
	f<<"\n";
	//f<<"\n";
	while(count>0) {
		f<<"#"<<num++<<std::endl;
		for(int i=0; i<M; i++) {
			for(int j=0; j<N; j++) {	
				f<<rand() % 100<<" "; //to generate numbers in range 0 to 99
			}
			f<<"\n";
		}
	//	f<<"\n";
		f<<"\n";
		count--;
	}
	f.close();
}

int main()
{
	std::string file_name = "default.txt";
	int M=0, N=0, count=0;

	InputData(M, N, count);
	Generatefile(file_name,M,N,count);	
	return 0;
}
