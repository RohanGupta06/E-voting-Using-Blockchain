
#include <iostream>
#include <cstring>
#include <iomanip>
#include <algorithm>
#include "Blockchain.cpp"
#include "authfunctions.h"
using namespace std;
void printResults(string *arr, int size, string names[],int sizeNames);

int main(int argv, char* argc[])
{
Blockchain<string> b;
while(true) {
	bool value = false;
	bool exitprogram = false;
    	authdb:
    		cout << "Welcome to E-voting System\n"
         	<< "Sign In Portal\n"
         	<< "1) Login\n"
         	<< "Select one of the options above or enter 0 to exit.\n"; 
    		int swc;
    		cin >> swc;
    	switch(swc)
    	{
    		case 1:
    		{
        		string u, p;
        		cout << "Please enter your credentials.\n"
             		<< "Username: ";
        		cin >> u;
        		cout << "Password: ";
        		cin >> p;
        		if(auth(u, p))
        		{             
            			cout << "Authentication Success!\n";
				
				int userChoice = 0;
  				static int size;
  				string *arr;
  				string names[]={"Rohan Gupta", "Abhishek Gupta", "Abhay Goyal", "Akash Raj"};
				do {
					cout<<"Welcome to Evoting System" <<"\n\n";
					cout<<"Select the choice"<<"\n";
					if(value==false) { 
					cout <<"(1) Vote for Candidate"<<"\n"; }
					cout <<"(2) Tally up the votes"<<"\n";
					cout <<"(3) EXIT"<<"\n\n";
    					string vote;
    					string *temp;
					cin >> userChoice;
					switch (userChoice)
					{
      						case 1:
							if(value==false) {
        						cout<<"College Election\n";
        						cout<<"Enter the number corresponding to the candidate of your choice:\n";
        						cout<<"1. Rohan Gupta\n"<<"2. Abhishek Gupta\n"<<"3. Abhay Goyal\n"<<"4. Akash Raj\n";
        						cout<<">> ";
        						cin>>vote;
        						try{
          							b.addBlock(new string(vote));
	  							value=true;
        						}
        						catch(string s){
          						cout<<s<<endl;
          						break;
        						}
        						break;}
        					case 2:
         						arr=b.toArray();
          						printResults(arr, b.getSize(), names, 3);
							delete[]arr;
          						arr=0;
          						break;
        					case 3:
          						cout<<"Thank you for your vote!\n";
          						break;
        					default:
          						cout<<"Invalid choice.\n";
          						break;
					}
				} while (userChoice != 3 && userChoice != 2);
				cout << endl;
        		}
        		else
        		{
            			cout << "Authentication Failure!\n";
           		}
        break;
    }
    
 
    }
    
  }
}

void printResults(string *arr, int size, string names[],int sizeNames){
  sort(arr, arr+size);
  int max=0;
  int count=1;
  string current=arr[0], maxResult=arr[0];
  for(int i=1;i<size;i++){
    if(current==arr[i]){
      count++;
      //current=arr[i];
      if(count>max){
        max=count;
        maxResult=current;
      }
    }
    else{
      current=arr[i];
      count=1;
    }
  }
  cout<<"The winner is: "<<names[atoi(maxResult.c_str())-1]<<". Result is "<<setprecision(3)<<(max*100)/(size)<<"%.\n";
}
