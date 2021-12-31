#include <stdio.h>
#include <stdlib.h>
#include "list.h"


#ifndef NodeTypeSeen
#define NodeTypeSeen
typedef struct node NodeType;
struct node {
        int num;
        NodeType *next;
   };
#endif

void PrintCallList(NodeType *call_list)
{
  if (call_list == NULL)
    return;
  PrintCallList(call_list->next);

  if (call_list->num < 16)
    printf("L");
  else if (call_list->num < 31)
    printf("I");
  else if (call_list->num < 46)
    printf("N");
  else if (call_list->num < 61)
    printf("U");
  else
    printf("X");
  printf("%d ", call_list->num);
}

int Search(NodeType *call_list, int i)
{
  NodeType *p;
  for (p=call_list; p!= NULL; p = p->next)
    if (p->num == i)
      return 1;
  return 0;
}


void Add(NodeType **call_list, int i)
{
NodeType *new;
new=(NodeType *) malloc(sizeof(NodeType));
new->num=i;
new->next=*call_list;
*call_list=new;
}
