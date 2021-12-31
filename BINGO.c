#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "list.h"

void ArrayifyCard(int card[5][5], char *cardfile);
void PrintCard(int card[5][5], NodeType *call_list);
int CheckCard(int card[5][5], NodeType *call_list);
int GetNextNum(NodeType *call_list);
int main( int argc, char *argv[] )
{
  if (argc != 3) { printf("Usage: %s seed cardFile\n",argv[0]); exit(1); }
  else if (isdigit(*argv[1]) == 0) { printf("Expected integer seed, but got %s\n", argv[1]); exit(2); }
  int card[5][5];
  srand(*argv[1]);
  char getnext;
  int winner = 0;
  NodeType *Node,
           *call_list,
           *ptr;
  int nextnum;

  call_list = NULL;

  ArrayifyCard(card, argv[2]);

  while ( 1 )
  {
    system("clear");
    printf("CallList: ");
    PrintCallList(call_list);
    printf("\n\n");
    PrintCard(card, call_list);
    printf("enter any non-enter key to Call (q to quit): ");
    if (CheckCard(card, call_list) == 1) {
      winner = 1;
      break;
    }
    getnext = getchar();
    if ( getnext == 'q')
      break;
    else if ( getnext == '\n' ) {
      putchar('\n');
      continue;
    }
    nextnum = GetNextNum(call_list);
    Add(&call_list, nextnum);
  }
  
  putchar('\n');
  system("clear");
  printf("CallList: ");
  PrintCallList(call_list);
  printf("\n\n");
  PrintCard(card, call_list);
  if (winner == 1)
    printf("WINNER\n\n");
  else
    printf("Thanks for playing!\n\n");
  exit(1);
}

/*****************/

int GetNextNum(NodeType *call_list)
{
  int num = (rand() % 75) +1;
  while (Search(call_list, num) == 1)
    num = (rand() % 75) +1;
  return num;
}

int CheckCard(int card[5][5], NodeType *call_list)
{
  for (int i = 0; i < 5; i++)
  {
    if (((Search(call_list,card[i][0])) == 1) &&
        ((Search(call_list,card[i][1])) == 1) &&
        ((Search(call_list,card[i][2])) == 1) &&
        ((Search(call_list,card[i][3])) == 1) &&
        ((Search(call_list,card[i][4])) == 1))
      return 1;
  }

  for (int j = 0; j < 5; j++)
  {
    if (((Search(call_list,card[0][j])) == 1) &&
        ((Search(call_list,card[1][j])) == 1) &&
        ((Search(call_list,card[2][j])) == 1) &&
        ((Search(call_list,card[3][j])) == 1) &&
        ((Search(call_list,card[4][j])) == 1))
      return 1;
  }

  if (((Search(call_list,card[2][0])) == 1) &&
      ((Search(call_list,card[2][1])) == 1) &&
      ((Search(call_list,card[2][3])) == 1) &&
      ((Search(call_list,card[2][4])) == 1))
    return 1;
      
  if (((Search(call_list,card[0][2])) == 1) &&
      ((Search(call_list,card[1][2])) == 1) &&
      ((Search(call_list,card[3][2])) == 1) &&
      ((Search(call_list,card[4][2])) == 1))
    return 1;

  if (((Search(call_list,card[0][0])) == 1) &&
      ((Search(call_list,card[0][4])) == 1) &&
      ((Search(call_list,card[4][0])) == 1) &&
      ((Search(call_list,card[4][4])) == 1))
    return 1;
}

void ArrayifyCard(int card[5][5], char *cardfile)
{
  FILE *fp, *fp2;
  char ch;

  if ((fp=fopen(cardfile, "r"))==NULL) {
    fprintf(stderr, "%s is nonexistent or unreadable\n", cardfile);
    exit(3);
  }

  fp2=fopen(cardfile, "r");
  int numlines = 0;
  while (ch != EOF) {
    ch = fgetc(fp2);
    if (ch == '\n')
      numlines++;
  }
  fgetc(fp2);
  if (numlines != 5) {
    fprintf(stderr, "%s has bad format\n",cardfile);
    exit(4);
  }
  
  int num = 0, digit;
  for (int i=0; i < 5; i++)
  {
    for (int j=0; j < 5; j++)
    {
      digit = fgetc(fp);
      if (isdigit(digit)) {
        num = (digit - '0');
        num = num * 10;
      }
      else {
        printf("%s has bad format\n", cardfile);
        exit(4);
      }
      digit = fgetc(fp);
      if (isdigit(digit)) {
        num = num + (digit - '0');
      }
      else {
        printf("%s has bad format\n", cardfile);
        exit(4);
      }
      card[i][j] = num;
      if ((i == 2) && (j == 2))
        { }//pass
      else if ((num < (1 + 15 * j)) || ((num > 15 + 15 * j))){
        printf("%s has bad format\n", cardfile);
        exit(4);
      }
      digit = fgetc(fp);
      if ((digit != ' ') && (digit != '\n')) {
        printf("%s has bad format\n", cardfile);
        exit(4);
      }
      if (j == 4) {
        continue;
      }
    }
  }
  if (card[2][2] != 0) {
    printf("%s has bad format\n", cardfile);
    exit(4);
  }
}

void PrintCard(int card[5][5], NodeType *call_list)
{
  printf("L   I   N   U   X\n");
  for (int i=0; i< 5; i++) {
    for (int j=0; j < 5; j++)  {
      if (card[i][j] < 10)
        printf("0%d", card[i][j]);
      else
        printf("%d", card[i][j]);
      if (((Search(call_list, card[i][j])) == 1) || (card[i][j] == 0))
        printf("m ");
      else
        printf("  ");
    }
    printf("\n");
  }
}
