#include "sha256.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
using namespace std;
template <typename Temp>
class Blockchain {
  private:
    template <typename typ>
    class Block 
    {
      public:
        typ* mesg_data;
        string mesg_prevHash;
        string mesg_hash;
        Block *mesg_next;

        Block(string prevHash, typ* data, Block *next) 
        {
          mesg_prevHash = prevHash;
          mesg_data = data;
          mesg_next = next;
          stringstream s;
          s << mesg_prevHash << mesg_data;
          mesg_hash = sha256(s.str());
        }
        
        Block() //generic block
        {
          mesg_prevHash = sha256("genesis block");
          mesg_next = 0;
          mesg_data = new typ();
          calcHash(mesg_prevHash);
        }

        ~Block() 
        {
          delete mesg_data;
          mesg_data = 0;
        }

        void calcHash(string prevHash) 
        {
          stringstream s;
          mesg_prevHash = prevHash;
          s << mesg_prevHash << mesg_data;
          mesg_hash = sha256(s.str());
        }

        typ getData() const 
        {
          return *mesg_data;
        }

        friend ostream& operator<<(ostream& os, const Block& b) 
        {
          os << "Data: " << b.getData() << endl << "Hash: " << b.mesg_hash << endl << "Previous Hash: " << b.mesg_prevHash;
          return os;
        }
    };

    Block<Typ> *mesg_head;
    Block<Typ> *mesg_tail;
    int mesg_size;

  public:
    Blockchain() 
    {
      mesg_head = new Block<Typ>();
      mesg_tail = mesg_head;
      string lastHash = getLastHash();
      ofstream outfile("lastHash.dat", ios::binary);
      outfile.write(lastHash.c_str(),lastHash.size());
      outfile.close();
      mesg_size=0; 
    }
    
    int getSize() 
    {
      return mesg_size;
    }

    string getLastHash() 
    {
      Block<Typ> *current = mesg_head;
      string currentHash = current->mesg_hash;
      while (current->mesg_next != 0) {
        current->mesg_next->calcHash(currentHash);
        current = current->mesg_next;
      }

      return current->mesg_hash;
    }
    
    bool verify()   //compares file's last hash to the chain's last hash
    {
      //read from file
      string lastHash = getLastHash();
      ifstream infile("lastHash.dat", ios::binary);
      string hash;
      hash.resize(lastHash.size());
      infile.read(&hash[0], lastHash.size());
      infile.close();
      return hash == lastHash;
    }
    
    void addBlock(Temp* data) throw (string) 
    {
      if(!verify()) 
      {
        throw "Blockchain was compromised.\n";
      }
      mesg_tail->mesg_next = new Block<Temp>(mesg_tail->mesg_hash, data, 0);
      mesg_tail = mesg_tail->mesg_next;
      string lastHash = getLastHash();
      ofstream outfile("lastHash.dat", ios::binary);
      outfile.write(lastHash.c_str(),lastHash.size());
      outfile.close();
      mesg_size++;
    }

    Typ* toArray() {
      Temp* arr=new Temp[mesg_size];
      if(mesg_head->mesg_next != 0) 
      {
        Block<Typ> *current = mesg_head->mesg_next;
        for(int i=0;i<mesg_size;i++) 
        {
          arr[i] = *(current->mesg_data);
          current = current->mesg_next;
        }
      }
      return arr;      
    }

    friend ostream& operator<<(ostream& os, const Blockchain<Temp>& b)
    {
      Block<Temp> *current = (b.mesg_head)->mesg_next;
      while(current!= 0)
      {
        os << *(current) << "\n";
        current = current->mesg_next;
      }
      return os;
    }
};
