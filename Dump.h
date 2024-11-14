#ifndef DUMP
#define DUMP

static const char* DUMP_DOT = "Dump.dot";

void TreeDump         (struct node_t* tree);

void PrintGraphHead   (FILE* graph);
void PrintDefaultList (FILE* graph, struct node_t* tree);
//void PrintArrow       (FILE* dump,  struct node_t* tree);

void MySystem         (const char* str, int number_dump);
void PrintInorder     (struct node_t* node);

#endif
