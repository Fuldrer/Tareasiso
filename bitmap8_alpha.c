/******************* Sistemas Operativos II ***************************/
/* 
96 Bloques
Enteros de 8Bits
 **************************/ 
/**********************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

char *commandList[] = {"print", "write", "read", "get_next", "set_busy", "set_free", "exit"};
const char* FILE_BITMAP = "bitmap8.bin";
const char* help = "Comandos validos:\nprint: Imprime el mapa de bits\nwrite: Escribe el mapa de bits a un archivo\nread: Lee el mapa de bits de un archivo\nget_next: Devuelve el siguiente bloque libre\nset_busy <bloque>: Marca como ocupado el <bloque> especificado\nset_free <bloque>: Marca como libre el <bloque> especificado\nexit: Salir delexit programa";

#define BITMAP_SIZE 12 
const int BLOCK_SIZE = 4096; 
const int BITS_PER_WORD = 8;  
/******************************/


uint8_t BITMAP[BITMAP_SIZE]=  {0,20,30,40,50,60,70,80,90,100,11,12};

void printBITMAP();
char *int2bin(uint8_t t_value);
int getFreeBlock();
void setBlockBusy(int t_block);
void setBlockFree(int t_block);

//Funciones adicionales
void parseCommand(char *cmd);
void writeBITMAP();
void readBITMAP();

int main(int argc, char *argv[])
{
  char cmd[200];
  int i = 0;
  readBITMAP();
 
  printf(help);
  while (1)
  {
    
    printf("\r\nCommand>");
    fgets(cmd, 200, stdin);
    if (!strcmp(cmd, "exit\n"))
      break;
    parseCommand(cmd);
  }
}

void parseCommand(char *cmd)
{
  int b = 0;
  char m_command[200];
  char m_param1[200];
  char *ptr;

  ptr = strtok(cmd, " \n");

  if (ptr != NULL)
    strcpy(m_command, ptr);

  ptr = strtok(NULL, " \n");
  if (ptr != NULL)
    strcpy(m_param1, ptr);

  int i = 7;
  while (i--)
  {
    if (!strcmp(m_command, commandList[i]))
    {
      int arg;
      if (!strcmp("get_next", m_command))
	    getFreeBlock();

      if (!strcmp("print", m_command))
        printBITMAP();

      if (!strcmp("set_busy", m_command))
        setBlockBusy(atoi(m_param1));

      if (!strcmp("set_free", m_command))
        setBlockFree(atoi(m_param1));

      if (!strcmp("write", m_command))
        writeBITMAP();

      if (!strcmp("read", m_command))
        readBITMAP();
    }
  }
}


void printBITMAP()
{
  int m_count = BITMAP_SIZE;
  int i = 0;
  int m_res;
  char *m_item;

  printf("%d", BITMAP[0]);
  for (i = 1; i < m_count; i++)
    printf(",%d", BITMAP[i]);
  printf("\n");  

  for (i = 0; i < m_count; i++)
  {
    m_item = int2bin(BITMAP[i]);
    printf("%s\r\n", m_item);    
  }
  printf("\r\n");
}


char *int2bin(uint8_t t_value)
{
  char *s = malloc(BITS_PER_WORD + 1);
  s[BITS_PER_WORD] = '\0';
  int i;
  uint8_t mask = 1 << (BITS_PER_WORD - 1); 
  for (i = 0; i < BITS_PER_WORD; i++, mask >>= 1)
    s[i] = ((t_value & mask) == 0) ? '0' : '1';
  return s;
}


int getFreeBlock()
{
  char *m_item;
  int firstbit;
  char *temp;
  int m_count = BITMAP_SIZE;
  int i = 0;
  int j = 0;
  for(i = 0; i < m_count; i++)
  {
    m_item = int2bin(BITMAP[i]);
    //printf("%s\r\n",m_item);
    for(j = 0; j < m_count; j++)
    {
      temp = m_item[j];
      printf( temp);
      if(temp == 1)
      {
        printf("Llega aqui");
        firstbit = j+(8*i);
        break;
      }
    }
  }
  printf("%d", firstbit);
  int freeblock = BITS_PER_WORD * 1 + firstbit ;
  printf(" TODO");
  return freeblock;
  
}

void setBlockBusy(int t_block)
{

   printf("TODO");
   return;
}

void setBlockFree(int t_block)
{
   printf("TODO");
   return;
}

//funcion que almacena el bitmap en un archivo, es necesario ejecutar el comando write
void writeBITMAP()
{
  FILE *fptr;
  if ((fptr = fopen(FILE_BITMAP, "wb")) == NULL)
  {
    printf("Error abriendo el archivo %s", FILE_BITMAP);
    return;
  }

  fwrite(&BITMAP, sizeof(BITMAP), 1, fptr);
  fclose(fptr);
  printf("BITMAP escrito satisfactoriamente ...\n");
}

//funcion que almacena el bitmap en un archivo, es necesario ejecutar el comando write
void readBITMAP()
{
  FILE *fptr;
  if ((fptr = fopen(FILE_BITMAP, "rb")) == NULL)
  {
    printf("Error abriendo el archivo %s", FILE_BITMAP);
    return;
  }

  fread(&BITMAP, sizeof(BITMAP), 1, fptr);
  fclose(fptr);
  printf("BITMAP leido satisfactoriamente ...\n");
}

