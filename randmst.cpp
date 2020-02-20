#include <iostream>
using namespace std;
 
int main(int argc, char **argv) 
{
 
   if(argc != 5)
   {
   	cout << "Invalid Argument Number" << endl; 
   }
   else
   {
     int version = atoi(argv[1]); 
     int numpoints = atoi(argv[2]); 
     int numtrials = atoi(argv[3]); 
     int dimension = atoi(argv[4]);
     cout << version << numpoints << numtrials << dimension << endl; 
   }
   return 0;
}