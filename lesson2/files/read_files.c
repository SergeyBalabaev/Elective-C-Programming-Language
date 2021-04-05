#include <stdio.h>

// Программа принимает на вход файл, состоящий из набора цифр
// На выходе программы создается новый файл, содержащий четные цифры входного набора

int main() {
  FILE *fp;
  FILE *fp2;
  char name1[] = "1";
  char name2[] = "2";
  int ch;
  if ((fp = fopen(name1, "r+")) == NULL)
  {
    printf("Err1\n");
    return 0;
  }
  if ((fp2 = fopen(name2, "w")) == NULL)
  {
    printf("Err2\n");
    return 0;
  }
  while((ch=fgetc(fp)) !=EOF) {
	printf("%c", ch);
  	if(ch%2==0){
  	  fputc(ch, fp2);
  	}
  
  }
  fclose(fp);
  fclose(fp2);
  return 0;
}
