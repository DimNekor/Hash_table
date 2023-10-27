#include "../include/hash_table.h"
#include "../include/vector.h"
#include <stdio.h>
#include <climits>

void menuKeyboard()
{
   std::cout << std::endl;
   std::cout << "____________ADDING_BY_KEYBOARD____________\n" << std::endl;
   std::cout << "If you want to enter new key-value, input 'n'" << std::endl;
   std::cout << "If you want to end additing, input 'e'" << std::endl;
}

void firstMenu()
{
   std::cout << std::endl;
   std::cout << "___________START_THE_PROGRAMM_________\n" << std::endl;
   std::cout << "If you want to fill hash-table, input 'a'" << std::endl;
   std::cout << "If you want to finish program, input 'f'" << std::endl;
}

void menuAddEl()
{
   std::cout << std::endl;
   std::cout << "________ADDING_AN_ELEMENT_________\n" << std::endl;
   std::cout << "How would you like to add key-value?" << std::endl;
   std::cout << "Input 'f' to fill table from file" << std::endl;
   std::cout << "Input 'k' to fill table by keyboard" << std::endl;
}


void menuMain()
{
   std::cout << std::endl;
   std::cout << "_______________MAIN_MENU_________________\n" << std::endl;
   std::cout << "If you want to add element, input 'a'" << std::endl;
   std::cout << "If you want to display table. input 'd'" << std::endl;
   std::cout << "If you want to remove element, input 'r'" << std::endl;
   std::cout << "If you want to search element, input 's'" << std::endl;
   std::cout << "If you want to finish programm, input 'f'" << std::endl;
}

FILE* openFile(char filename[])
{
   FILE* fp = fopen(filename, "r");
   while (!fp)
   {
      std::cout << "Enter the correct name of file" << std::endl;
      std::cin >> filename;
      fp = fopen(filename, "r"); 
   }
   return fp;
}

int countLines(FILE* fp)
{
   int count = 1;
   char ch;
   while ((ch = getc(fp)) != EOF)
   {
      if (ch == '\n') count++;
   }
   rewind(fp);
   return count;
}

void fillFromFile(FILE*& fp, Hash_table& table)
{
   Vector keys[countLines(fp)];
   Vector values[countLines(fp)];
   char ch;
   bool isKey = true;
   int currentLine = 0;
   while ((ch = getc(fp)) != EOF)
   {
      if (ch != '\"' && ch != '\r' && ch != '\n')
      {
         if (isKey)
            keys[currentLine].push(ch);
         else values[currentLine].push(ch);
      }
      else if (ch == '\"')
      {
         values[currentLine].push(ch);
         if (isKey) isKey = false;
         else isKey = true;
      }
      else if (ch == '\n')
      {
         keys[currentLine].push('\0');
         values[currentLine].push('\0');
         table.add(keys[currentLine].retPmas(), values[currentLine].retPmas());
         currentLine++;
      }
   }
}

void getline(char* buf, int sizebuf)
{
   int i = 0;
   char ch;
   if ((ch = getchar()) == '\n')
   {
      ch = getchar();
   }
   while (--sizebuf > 0 && ch != EOF && ch!='\n')
   {
      buf[i++] = ch;
      ch = getchar();
   }
   if (ch == '\n')
      buf[i] = '\0';
}
   
void fillByKeyboard(Hash_table& table)
{
   char choice;
   line_info line;
   while (true)
   {
      menuKeyboard();
      int sizebuf = 50;
      char key[sizebuf];
      char value[sizebuf];
      std::cin >> choice;
      if (choice == 'n')
      {
         std::cout << "Enter key" << std::endl;
         getline(key, sizebuf);
         std::cout << "Enter value" << std::endl;
         getline(value, sizebuf);
         table.add(key, value);
      }
      else if (choice == 'e')
      {
         std::cout << "Adding was stopped" << std::endl;
         break;
      }
   }     
}

int main()
{
   char choice;
   firstMenu();
   bool isFirst = true;
   std::cin >> choice;
   Hash_table hash_table;
   while (true)
   {
      if (choice == 'a' && isFirst)
      {
         menuAddEl();
         std::cin >> choice;
         if (choice == 'f')
         {
            std::cout << "Enter the name of file" << std::endl;
            char filename[30];
            std::cin >> filename;
            FILE* fp = openFile(filename);
            int count = countLines(fp); 
            rewind(fp);
            fillFromFile(fp, hash_table); 
            isFirst = false;
            choice = 'h';
         }
         else if (choice == 'k')
         {
            fillByKeyboard(hash_table);
            isFirst = false;
         }
         else 
         {
            std::cout << "Incorrect Input" << std::endl;
            choice = 'a';
         }
      }
      else if (choice == 'f')
      {
         std::cout << "Program is over" << std::endl;
         break;
      }
      else if (!isFirst)
      {
         menuMain();
         std::cin >> choice;
         if (choice == 'a')
            fillByKeyboard(hash_table);
         else if (choice == 'd')
            hash_table.display();
         else if (choice == 'r')
         {
            int sizebuf = 50;
            char key[sizebuf];
            std::cout << "\n________________REMOVING____________\n" << std::endl;
            std::cout << "Enter the key, that you want to remove" << std::endl;
            getline(key, sizebuf);
            hash_table.remove(key);
         }
         else if (choice == 's')
         {
            char key[50];
            std::cout << "\n_____________SEARCHING____________\n" << std::endl;
            std::cout << "Enter the key you want to check in table" << std::endl;
            getline(key, 50);
            if (hash_table.isHere(key))
               std::cout << "This element in table" << std::endl;
            else
               std::cout << "This element is absent" << std::endl;
         }
         else if (choice == 'f')
         {
            std::cout << "The program is finished" << std::endl;
            break;
         }
      }
      else
      {
         std::cout << "Incorrect input" << std::endl;
         std::cin >> choice;
      }
   }
   return 0;
}
