#include "../include/hash_table.h"
#include <iostream>
#include <string.h>

Hash_table::Hash_table()
{
   numLines = 3;
   ptable = nullptr;
}

bool Hash_table::isHere(char* new_address)
{
   return isHere(ptable, new_address, numLines);
}

bool Hash_table::isHere(Node** ptable ,char* new_address, int size)
{  
   for (int i = 0; i < size; i++)
   {
      if (ptable[i]->address)
      {
         if (!strcmp(ptable[i]->address, new_address))
            return true;
      }
   }
   return false;
}

Node** Hash_table::create(int size)
{
   Node** temp = new Node*[size];
   for (int i = 0; i < size; i++)
   {
      temp[i] = new Node;
      temp[i]->address = nullptr;
      temp[i]->company = nullptr;
   }
   return temp;
}

int lenStr(char* str)
{
   int pos = 0;
   while (str[pos] != '\0')
      pos++;
   return ++(++pos);
}

char* createStr(char* str)
{
   char* newStr = new char[lenStr(str)];
   int i = 0;                                                              
   while (str[i] != '\0')                                                  
   {                                                                       
      newStr[i] = str[i];                                               
      i++;                                                                 
   }                                                                       
   newStr[i] = '\0';
   return newStr;
}

hash_table_info Hash_table::add(hash_table_info info, char* new_address,char* new_company)
{  
   //Создаём в куче строки, к которым мы будем ссылаться внутли хэш-таблицы
   char* strKey = createStr(new_address);
   char* strValue = createStr(new_company);
   //Если в хэш-таблице нет элементов, то добавляем туда первый элемент
   if (!info.ptable)
   {
      info.ptable = create(info.numLines);
      int index = hashCode(new_address, info.numLines);
      info.ptable[index]->address = strKey;
      info.ptable[index]->company = strValue;
      return info;
   }
   //Если в хэш-таблице есть уже хотя бы один элемент
   else
   {
      //Проверяем есть ли этот элемент уже в хэш-таблице
      if (isHere(info.ptable, new_address, info.numLines))
      {
         std::cout << "The address is already in list" << std::endl;
         return info;
      }
      //Элемента нет в таблице, значит добавляем его
      else
      {
         //С помощью хэш-функции получаем номер строки в хэш-таблице
         int index = hashCode(new_address, info.numLines);
         //Если эта строка свободна, то записываем туда ключ-значение
         if (!(info.ptable[index]->address))
         {
            info.ptable[index]->address = strKey;
            info.ptable[index]->company = strValue;
            return info;
         }
         //Если эта строка уже занята, то применяем метод
         //квадратичного опробования
         else
         {
            int i = 1;
            int tempIndex = index;
            //Ищем нужную ячейку, пока не выйдем за границы таблицы
            //либо пока ячейки, в которые мы попадаем, не будут заняты
            while (tempIndex < info.numLines && info.ptable[tempIndex]->address)
            {
               //Метод квадратичного опробования
               tempIndex = index + i*i;
               i++;
            }
            index = tempIndex;
            //В случае, если размеры массива меньше, чем полученный индекс
            //Тогда ре-хэшируем таблицу
            if (index >= info.numLines)
            {
               hash_table_info info1;
               info1.ptable = nullptr;
               info1.numLines = info.numLines+2;
               int count = countEl(info);
               line_info** lineInfo = new line_info*[++count];
               for (int i = 0, j = 0; i < count; i++, j++)
               {
                  if (i == count - 1)
                  {
                     lineInfo[i] = new line_info;
                     lineInfo[i]->address = strKey;
                     lineInfo[i]->company = strValue;
                  }
                  else if (info.ptable[j]->address)
                  {
                     lineInfo[i] = new line_info;
                     lineInfo[i]->address = info.ptable[j]->address;
                     lineInfo[i]->company = info.ptable[j]->company;
                  }
                  else --i;
               }
               return reHash(info1, lineInfo, new_address, new_company, count);
            }
            //В случае, если мы смогли найти пустую ячейку
            else if (!info.ptable[index]->address)
            {
               info.ptable[index]->address = strKey;
               info.ptable[index]->company = strValue;
               return info;
            }
            else return info;
         }
      }
   }
}      

int Hash_table::countEl(hash_table_info info)
{
   int count = 0;
   for (int i = 0; i < info.numLines; i++)
   {
      if (info.ptable[i]->address)
         count++;
   }
   return count;
}

void Hash_table::add(char* new_address, char* new_company)
{
   hash_table_info info;
   info.ptable = ptable;
   info.numLines = numLines;
   info = add(info, new_address, new_company);
   ptable = info.ptable;
   numLines = info.numLines; 
}

int intHash(int index, int size)
{
   index = index * index;
   index >>= 11;
   index = index % 1024 % size;
   if (index < 0)
      index = (-1) * index;
   return index;
}

int hashCode(char* new_address, int size)
{  
   //Перевод строки в число
   int index = 0;
   int base = 127;
   for (int ch = *new_address, i = 0; ch != '\0'; ch=*(new_address + ++i))
      index = (base*index + ch);
   //Функция "середины квадрата"
   return intHash(index, size);
}

int Hash_table::retNumLines()
{
   return numLines;
}

Hash_table::~Hash_table()
{
   if (ptable)
   {
      for (int i = 0; i < numLines; i++)
      {
         if (ptable[i]->address)
         {
            delete ptable[i]->address;
            delete ptable[i]->company;
            delete ptable[i];
         }      
      }
      delete ptable;
   }
}

hash_table_info Hash_table::reHash(hash_table_info info, line_info** lineInfo, char* new_address, char* new_company, int num)
{
   Node** tempTable = nullptr;
   for (int i = 0; i < num; i++)
   {
      info = add(info, lineInfo[i]->address, lineInfo[i]->company);
      //display(info.ptable, info.numLines);
   }
   return info; 
}  

void Hash_table::display()
{
   display(ptable, numLines);
}

void Hash_table::display(Node**& ptable, int size)
{
   std::cout << "________________DISPLAY__________________\n" << std::endl;
   if (ptable)
   {
      for (int i = 0; i < size; i++)
      {
         std::cout << i << '.';
         if (ptable[i] -> address)
         {
            std::cout<< ' '<<ptable[i]->address<<' '<<ptable[i]->company;
         }
         std::cout << std::endl;
      }
   }
   else std::cout << "PTABLE IS EMPTY!" << std::endl;
}

void Hash_table::remove(char* address)
{
   if (isHere(address))
   {
      for (int i = 0; i < numLines; i++)
      {
         if (ptable[i]->address && !strcmp(ptable[i]->address, address))
         {
            std::cout << ptable[i]->address << std::endl;
            ptable[i]->address = nullptr;
            ptable[i]->company = nullptr;
            return;
         }
      }
   }
   std::cout << "This name isn't in hash_table" << std::endl;
}
