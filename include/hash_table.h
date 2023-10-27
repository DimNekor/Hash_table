#include <iostream>

struct Node
{
   char* address;
   char* company;
};

struct hash_table_info
{
   Node** ptable;
   int numLines;
};

struct line_info
{
   char* address;
   char* company;
};

class Hash_table
{
private:
   Node** ptable;
   int numLines;
   hash_table_info add(hash_table_info, char*, char*);
   int countEl(hash_table_info);
   Node** create(int);
   void display(Node**&, int);
   bool isHere(Node**, char*, int);
   hash_table_info reHash(hash_table_info, line_info**, char*, char*, int);
   

public:
   Hash_table();
   bool isHere(char*);
   void add(char*, char*);
   void remove(char*);
   int retNumLines();
   void display();
   ~Hash_table();
};


int hashCode(char*, int);
int intHash(int, int);  
