#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;

int main(){

   string s1 = "111112222233333";
   string s2 = "-111112222233333";
  
   BigInteger A = BigInteger(s1);
   BigInteger B = BigInteger(s2);
   BigInteger C, D, E, F, G, H;
   
   cout << "A = " << A << endl;
   cout << "B = " << B << endl;
   
    cout << endl;
   
   C = A + B;
   cout << "C = " << C << endl;
    cout << endl;
   
   D = A + A;
   cout << "D = " << D << endl;
    cout << endl;
   
   E = A - B;
   cout << "E = " << E << endl;
    cout << endl;
   
   F = A - A;
   cout << "F = " << F << endl;
    cout << endl;
	
	H = B - A;
	cout << "H = " << H << endl;
	cout << endl;
   
   G = A * B;
   cout << "G = " << G << endl;
    cout << endl;
   
   A.makeZero();
   cout << "A = " << A << endl;
    cout << endl;
   
   B.negate();
   cout << "B = " << B << endl;
    cout << endl;
   
   return(EXIT_SUCCESS);
}