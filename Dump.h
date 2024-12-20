#ifndef DUMP
#define DUMP

void TreeDump         (struct node_t* tree);

void PrintGraphHead   (FILE* graph);
void PrintDefaultList (FILE* graph, struct node_t* tree);

void MySystem         (const char* str, int number_dump);
void PrintInorder     (struct node_t* node);

#endif
