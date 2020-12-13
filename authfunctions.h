#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <fstream>
using namespace std;

int auth(string u, string p)
{

    bool authstate = false;
    fstream authfile;
    authfile.open("user.txt");
    if(authfile.is_open())
    {   
        vector<string> filelines;
        string procstring;
        while(getline(authfile,procstring))
        {
            filelines.push_back(procstring);
        }
        stringstream uss(filelines[0]);
        stringstream pss(filelines[1]);
	stringstream lss(filelines[2]);
        istream_iterator<string> ubegin(uss), uend;
        istream_iterator<string> pbegin(pss), pend;
	istream_iterator<int> lbegin(lss), lend;
        vector<string> users(ubegin, uend); 
        vector<string> passwords(pbegin, pend); 
	vector<int> locks(lbegin, lend);
	
        for(int i=0; i<users.size() || i<passwords.size() || i<locks.size();i++)//Do this while we haven't parsed the entire database
        {
            if(u == users[i] && p == passwords[i] && locks[i]==1)
            {
                authfile.close();
                authstate = true;
		
		
                break;
            } 
        }
    }
    else
    {
        cout << "MAJOR ERROR Could not connect to database!\n";
    }
    return authstate;
}
