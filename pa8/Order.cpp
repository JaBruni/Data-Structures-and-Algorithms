/*********************************************************************************
* Jason Bruni, jabruni
* 2022 Winter CSE101 PA8
* Order.cpp
* Client module for Dictionary ADT that prints out key:value pairs
* and the order they were obtained in
*********************************************************************************/
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include "Dictionary.h"
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
	
	Dictionary A;
	int line_count;
	string line;
	while(getline(in, line)){
		line_count++;
		A.setValue(line, line_count);
	}
	out << A << endl;
	out << A.pre_string() << endl;
	
	in.close();
	out.close();
}