//Написать программу, которая создаст два текстовых файла, примерно по 50-100 символов в каждом (особого значения не имеет);
//Написать функцию, «склеивающую» эти файлы, предварительно буферизуя их содержимое в динамически выделенный сегмент памяти 
//нужного размера.
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

#define NUM_STRINGS 3

int main(int argc, char ** argv) {
    FILE *fh1, *fh2, *fh3;
    const char * file1 = "./output1.txt";
    const char * file2 = "./output2.txt";
    const char * file3 = "./output-merged.txt";
    size_t i=0;
    if ( (fh1=fopen(file1,"w+")) == NULL){
        cout << "Cannot open/create file " << file1 << endl;
        exit(1);	
    }
    if ( (fh2=fopen(file2,"w+")) == NULL){
        cout << "Cannot open/create file " << file2 << endl;
        exit(1);	
    }
    if ( (fh3=fopen(file3,"w+")) == NULL){
        cout << "Cannot open/create file " << file3 << endl;
        exit(1);	
    }
    // заполняем файлы
    const char * samplestring1 = "Проверочная_строка_в_первом_файле.\n";
    const char * samplestring2 = "Проверочная строка во втором файле.\n";
    for (i=0; i<3; i++)
	    fputs(samplestring1,fh1);
    for (i=0; i<3; i++)
	    fputs(samplestring2,fh2);

    // перемотка в начало на обоих файлах
    rewind(fh1);
    rewind(fh2);
    char buff[256]={};
    char ** mem_to_free=(char **) calloc(NUM_STRINGS*2*sizeof(char**),sizeof(char **));
    if(mem_to_free == NULL) {
        printf("Cannot allocate memory!");
        exit(1);
     }
    // читаем первый файл построчно
    for(i=0;i<NUM_STRINGS;i++) {
     if (fgets(buff,255,fh1)==NULL) { // остановится на каждом \n
       printf("EOF on fh1 reached.\n");
       break;
     }
     size_t len = strlen(buff);
     mem_to_free[i] = (char *) calloc(len+1,sizeof(char));
     if(mem_to_free[i] == NULL) {
        printf("Cannot allocate memory!");
        exit(2);
     }
     strncpy(mem_to_free[i],buff,len+1);
    }
    // читаем второй файл построчно
    for(i=NUM_STRINGS;i<NUM_STRINGS*2;i++) {
     if (fgets(buff,255,fh2)==NULL) { // остановится на каждом \n
       printf("EOF on fh2 reached.\n");
       break;
     }
     size_t len = strlen(buff);
     mem_to_free[i] = (char *) calloc(len+1,sizeof(char));
     strncpy(mem_to_free[i],buff,len+1);
    }

    // вывод на экран и запись в файл смерженного результата.
    for(i=0;i<NUM_STRINGS*2;i++) {
      printf("%s",mem_to_free[i]);
      fprintf(fh3,"%s",mem_to_free[i]);
    }
    // освобождение памяти, закрытие файлов
    for(i=0;i<NUM_STRINGS*2;i++)
	    free(mem_to_free[i]);
    free(mem_to_free);
    if(ferror(fh1)||ferror(fh2)||ferror(fh3)) {
        printf("Warning: i/o errors encountered!");
    }
    fclose(fh1);
    fclose(fh2);
    fclose(fh3);
}
