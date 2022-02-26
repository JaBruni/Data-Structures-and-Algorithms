/*********************************************************************************
* Jason Bruni, jabruni
* 2022 Winter CSE101 PA6
* Arithmetic.cpp
* Client for BigInteger AdT that performs a set of arithmetic operations
*********************************************************************************/
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include "BigInteger.h"
using namespace std;

#define MAX_LEN 300

int main(int argc, char * argv[]){
	ifstream in;
	ofstream out;
	// check command line for correct number of arguments
	if(argc != 3){
		cerr << "Usage: " << argv[0] << "<input file> <output file>" << endl;
		return(EXIT_FAILURE);
	}
	
	in.open(argv[1]);
	if(!in.is_open()){
		cerr << "Unable to open file " << argv[1] << " for reading" << endl;
		return(EXIT_FAILURE);
	}
	
	out.open(argv[2]);
	if(!out.is_open()){
		cerr << "Unable to open file " << argv[2] << " for writing" << endl;
		return(EXIT_FAILURE);
	}
	string line;
	
	
	getline(in, line);
	BigInteger A = BigInteger(line);
	getline(in, line);
	getline(in, line);
	BigInteger B = BigInteger(line);
	out << A << endl;
	out << endl;
	out << B << endl;
	out<< endl;
	BigInteger C, D, E, F, G, H, I, J, K, L, Z;
	
	// A+B
	C = A+B;
	out << C << endl;
	out << endl;
	
	// A-B
	D = A-B;
	out << D << endl;
	out<< endl;
	
	// A-A
	E = A-A;
	out << E << endl;
	out << endl;
	
	// 3A - 2B
	F = (A+A+A) - (B+B);
	out << F << endl;
	out << endl;
	
	// A * B
	G = A*B;
	out << G << endl;
	out << endl;
	
	// A^2
	H = (A*A);
	out << H << endl;
	out << endl;
	
	// B^2
	I = (B*B);
	out << I << endl;
	out << endl;
	
	// 9A^4 + 16B^5
	BigInteger M;
	K = BigInteger("000000009");
	L = BigInteger("000000016");
	M = (K*A*A*A*A);
	L = (L*B*B*B*B*B);
	Z = M + L;
	out << Z;
	out << endl;
	
	in.close();
	out.close();
	return(EXIT_SUCCESS);
}