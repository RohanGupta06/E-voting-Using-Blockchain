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
        typ* m_data;
        string m_prevHash;
        string m_hash;
        Block *m_next;

        Block(string prevHash, typ* data, Block *next) 
        {
          m_prevHash = prevHash;
          m_data = data;
          m_next = next;
          stringstream s;
          s << m_prevHash << m_data;
          m_hash = sha256(s.str());
        }
        
        Block() //generic block
        {
          m_prevHash = sha256("genesis block");
          m_next = 0;
          m_data = new typ();
          calcHash(m_prevHash);
        }

        ~Block() {
          delete m_data;
          m_data = 0;
        }

        void calcHash(string prevHash) {
          stringstream s;
          m_prevHash = prevHash;
          s << m_prevHash << m_data;
          m_hash = sha256(s.str());
        }

        typ getData() const {
          return *m_data;
        }

        friend ostream& operator<<(ostream& os, const Block& b) {
          os << "Data: " << b.getData() << endl << "Hash: " << b.m_hash << endl << "Previous Hash: " << b.m_prevHash;
          return os;
        }
    };

    Block<Typ> *m_head;
    Block<Typ> *m_tail;
    int m_size;

  public:
    Blockchain() {
      m_head = new Block<Typ>();
      m_tail = m_head;
      string lastHash = getLastHash();
      //create binary file with last hash
      ofstream outfile("lastHash.dat", ios::binary);
      outfile.write(lastHash.c_str(),lastHash.size());
      outfile.close();
      m_size=0;
      /*TESTING BINARY FILE (Reading)
      ifstream infile("lastHash.dat", ios::binary);
      string hash;
      hash.resize(m_lastHash.size());
      infile.read(&hash[0], m_lastHash.size());
      infile.close();
      cout<<"\nFile data: "<<hash<<endl;*/
    }
    
    int getSize() {
      return m_size;
    }

    string getLastHash() {
      Block<Typ> *current = m_head;
      string currentHash = current->m_hash;
      while (current->m_next != 0) {
        current->m_next->calcHash(currentHash);
        current = current->m_next;
      }

      return current->m_hash;
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
    
    void addBlock(T* data) throw (string) 
    {
      if(!verify()) {
        throw "Blockchain was compromised.\n";
      }
      m_tail->m_next = new Block<Temp>(m_tail->m_hash, data, 0);
      m_tail = m_tail->m_next;
      string lastHash = getLastHash();
      ofstream outfile("lastHash.dat", ios::binary);
      outfile.write(lastHash.c_str(),lastHash.size());
      outfile.close();
      m_size++;
    }

    Typ* toArray() {
      Temp* arr=new Temp[m_size];
      if(m_head->m_next != 0) {
        Block<Typ> *current = m_head->m_next;
        for(int i=0;i<m_size;i++) {
          arr[i] = *(current->m_data);
          current = current->m_next;
        }
      }
      return arr;      
    }

    friend ostream& operator<<(ostream& os, const Blockchain<Temp>& b){
      Block<Temp> *current = (b.m_head)->m_next;
      while(current!= 0){
        os << *(current) << "\n";
        current = current->m_next;
      }
      return os;
    }
};
