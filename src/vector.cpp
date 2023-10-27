#include "../include/vector.h"
#include <cstdlib>

Vector::Vector()
{
   len = 0;
   pmas = nullptr;
}

void Vector::push(char ch)
{
   if (!len) 
   {
      len++;
      pmas = new char[len];
      pmas[len-1] = ch;
   }
   else
   {
      len++;
      char* tempMas = new char[len];
      for (int i = 0; i < len - 1; i++)
      {
         tempMas[i] = pmas[i];
      }
      tempMas[len - 1] = ch;
      delete []pmas;
      pmas = tempMas;
   }
}

void Vector::display()
{
   for (int i = 0; i<len; i++)
   {
      std::cout << pmas[i];
   }
   std::cout << std::endl;
}

char* Vector::retPmas()
{
   return pmas;
}

Vector::~Vector()
{
   delete []pmas;
   len = 0;
}
