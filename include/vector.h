#pragma once
#include <iostream>

class Vector
{
private:
   int len;
   char* pmas;
public:
   Vector();
   char* retPmas();
   void push(char);
   void display();
   ~Vector();
};
