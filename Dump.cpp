#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "Tree.h"
#include "Dump.h"

void TreeDump(struct node_t* tree)
{
    assert(tree);

    FILE* dump = fopen(DUMP_DOT, "w");

    assert(dump);

    PrintGraphHead(dump);

    PrintDefaultList(dump, tree);

    fprintf(dump, "}\n");
    fclose(dump);

    static int number_dump = 0;
    MySystem("dot Dump.dot -Tpng -o Graphs/Dump%03d.png", number_dump);

    PrintInorder(tree);
    printf("\n");
}

void PrintGraphHead(FILE* graph)
{
    assert(graph);

    fprintf(graph, "digraph G\n{\n    rankdir = TB;\n    bgcolor = \"pink2\"\n"
                   "    node[color = \"#b503fc\", fontsize = 14];\n"
                   "    edge[color = black, fontsize = 12];\n\n");
}

void PrintDefaultList(FILE* graph, struct node_t* tree)
{
    assert(graph);
    assert(tree);

    fprintf(graph, "    %x [shape = Mrecord, label = \"{ data %4s | { <f0> left %4lu | <f1> right %4lu}}\"];\n",
                        tree, tree->word, tree->left, tree->right);

    if (tree->left != NULL)
    {
        fprintf(graph, "    %x : <f0> -> %x\n", tree, tree->left);
        PrintDefaultList(graph, tree->left);
    }

    if (tree->right != NULL)
    {
        fprintf(graph, "    %x : <f1> -> %x\n", tree, tree->right);
        PrintDefaultList(graph, tree->right);
    }
}

void MySystem(const char* str, int number_dump)
{
    char command_dot[52] = "";

    sprintf(command_dot, str, number_dump);

    system(command_dot);
}

void PrintInorder(struct node_t* node)
{
    if(!node) return;

    printf("(");

    if(node->left)
    {
        PrintInorder(node->left);
    }

    printf("%s", node->word);

    if(node->right)
    {
        PrintInorder(node->right);
    }

    printf(")");
}
