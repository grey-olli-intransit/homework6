//* Написать программу, которая проверяет присутствует ли указанное пользователем при запуске программы слово в указанном пользователем файле (для простоты работаем только с латиницей).
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

#define NUM_STRINGS 3

void array_shift_left_by_one(char * array, int array_size) {
    if (array_size<3) {
        printf("Incorrect use of function by programmer!");
	exit(1);
    }
    int max_index = array_size - 1;
    int i=0;
    while(i <= max_index - 1) { 
        *(array + i)=*(array + i + 1);
        i++;
    }
    *(array + max_index)='\0';

} // array_shift

void print_int_array(int* arr, size_t size) {
   for(size_t i=0;i<size;i++)
       std::cout << arr[i] << " ";
   std::cout << std::endl;
}
   
int main(int argc, char ** argv) {
    if (argc != 3) {
        printf("\nUsage: thisexecutable <search_string> <file_path>\n");
        exit(1);
    }
    else {
        printf("Looking for chars '%s' in file %s ..\n",argv[1],argv[2]);
    }
    FILE *fh;
    if ( (fh=fopen(argv[2],"r")) == NULL){
        cout << "Cannot open file " << argv[2] << " for reading." << endl;
        exit(1);
    }
    size_t search_size=strlen(argv[1]);
    if (search_size > 254) {
        printf("Search string too long.");
	exit(1);
    }
    char buffer[255]={0};
    int char_from_file;
    size_t offset=0;
    bool found=false;
    while((char_from_file=fgetc(fh)) != EOF) {
      if(offset<search_size) {
	      buffer[offset]=(char)char_from_file;
          offset++;
	  continue;
      }
      else {
	      if (strcmp(buffer,argv[1])==0) {
	      found=true;
	      break;
	      }
	      else {
            buffer[search_size]=(char)char_from_file;
	        array_shift_left_by_one(buffer,255);
	        offset=search_size+1;
            if (strcmp(buffer,argv[1])==0) {
	            found=true;
	            break;
	        }
	        continue;
	      }
      }
    
    }
    fclose(fh);
    if (found)
        printf("Search string '%s' found.\n",argv[1]);
    else
        printf("Search string '%s' not found.\n",argv[1]);
}
