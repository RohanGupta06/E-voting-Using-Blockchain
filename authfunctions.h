#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <fstream>
using namespace std;
int register_user()
{
    system("cls");
    string uzr, paz;
    cout << "Authentication Database Program 1.0\n"
         << "~~~~~~~~~~~~Registration~~~~~~~~~~~~\n"
         << "                                    \n"
         << "~Desired Username: ";
    cin >> uzr;
    cout << "~Desired Password: "; 
    cin >> paz;
    //SEARCH TO SEE IF THE USER EXISTS
    //IF NOT IN DB, THEN ADD USER TO DB, IF IN DB, CLOSE.
    fstream authfile;
    authfile.open("user.db");
    if(authfile.is_open())
    {
        vector<string> filelines;
        string procstring;
        while(getline(authfile,procstring))
        {
            filelines.push_back(procstring);
        }
        stringstream uss(filelines[0]);//Users stream
        stringstream pss(filelines[1]);//Paswords stream
        istream_iterator<string> ubegin(uss), uend;//Users iterators
        istream_iterator<string> pbegin(pss), pend;//Passwords iterators
        vector<string> users(ubegin, uend); //Where we store every user
        vector<string> passwords(pbegin, pend); //Where we store every password.
        bool alreadyexists = false;
        for(int i=0; i<users.size();i++)//Do this while we haven't parsed the entire database
        {
            if(uzr == users[i])
            {
                alreadyexists = true;
                break;
            }
        }
        if(alreadyexists == true)
        {
            cout << "This username already exists.\n";
            system("pause");
            system("cls");
            authfile.close(); //Never leave a file open when you stop using it.
        }
        else
        {
            authfile.close(); //Closing the read stream
            authfile.open("user.db"); //Opening the write stream
            users.push_back(uzr);
            passwords.push_back(paz);
            string userline, passwordline;
            for(int i = 0; i<users.size(); i++)
            {
                userline = userline + users[i] + " ";
            }
            for(int i = 0; i<passwords.size(); i++)
            {
                passwordline = passwordline + passwords[i] + " ";
            }
            authfile << userline << "\n" << passwordline;
            authfile.close();
            system("pause");
            system("cls");
        }
        
    }
    else
    {
        cout << "Fatal Error: Can't connect to database!\n";
        system("pause");
    }
}
int auth(string u, string p)
{
    bool authstate = false;
    fstream authfile;
    authfile.open("user.db");
    if(authfile.is_open())
    {   
        vector<string> filelines;
        string procstring;
        while(getline(authfile,procstring))
        {
            filelines.push_back(procstring);
        }
        stringstream uss(filelines[0]);//Users stream
        stringstream pss(filelines[1]);//Paswords stream
        istream_iterator<string> ubegin(uss), uend;//Users iterators
        istream_iterator<string> pbegin(pss), pend;//Passwords iterators
        vector<string> users(ubegin, uend); //Where we store every user
        vector<string> passwords(pbegin, pend); //Where we store every password.
        for(int i=0; i<users.size() || i<passwords.size();i++)//Do this while we haven't parsed the entire database
        {
            if(u == users[i] && p == passwords[i])
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
int list()
{
    bool exit = false;
    list:
    system("cls");
    cout << "Welcome to our informational databse!\n1. Contacts\n2. Passwords\n3. Notes\n";
    cout << "Choose an option from the list above (ex: 1) or 0 to exit!\nYour choice: \n";
    int option;
    cin >> option;
    switch(option) 
    {
        case 0:
            {
                system("cls");
                cout << "Bye!\n";
                exit = true;
                break;
            }
        case 1:    
            {      
                system("cls");
                cout << "~Contact List~\n"
                     << "Name    Phone\nAmy     40003231\nJoe     40003231\n"
                     << "John    40003231" << endl;
                     break; 
            }               
        case 2:
            {
                system("cls");
                cout << "      ~My Password list~\n"
                     << "_______________________________\n"
                     << "|Website           | Password |" << endl
                     << "|==================|==========|" << endl
                     << "|www.gmail.com     | fluffy01 |\n"
                     << "|------------------|----------|\n"
                     << "|www.facebook.com  | 01234567 |\n"
                     << "|------------------|----------|\n"
                     << "|www.steemit.com   | hawh2h8a |\n"
                     << "|__________________|__________|\n";
                     break; 
            }
        case 3:
            {
                system("cls");
                cout << "~My notes - Read them~\n"
                     << "Note 1: Remember to feed your pets\n"
                     << "Note 2: Remember to add a ; to every line that finishes an instruction\n"
                     << "Note 3: Remember to follow me if you like my tutorials\n"
                     << "Note 4: Don't forget to add a break after each case in switches!\n"
                     << "Note 5: Don't forget to add a \\n after each comment so the text displays properly\n"
                     << "Note 6: Notice that one \\ in front of a newline inside a comment escapes the newline\n"
                     << "Note 7: If my tutorial is helping you please like, follow and even resteem it so you can help me aswell!\n";
                     break;
                
            }
        default:   
            {      
                cout << "There is no such option!\n";
                system("pause");
                break;
            }
    }
    system("pause");
    if(exit == false)
    {
            goto list;
    }
}
