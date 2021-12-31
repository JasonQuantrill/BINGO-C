#ifndef NodeTypeSeen
#define NodeTypeSeen
typedef struct node NodeType;
struct node {
        int num;
        NodeType *next;
   };
#endif
void Add(NodeType **call_list, int i);
int Search(NodeType *call_list, int i);
void PrintCallList(NodeType *call_list);
