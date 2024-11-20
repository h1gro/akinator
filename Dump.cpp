#include <assert.h>

#include "Akinator.h"
#include "Dump.h"

static const char* DUMP_DOT = "Dump.dot";

void TreeDump(struct node_t* tree)
{
    assert(tree);

    FILE* dump = fopen(DUMP_DOT, "w");

    assert(dump);

    //printf("%s\n", __func__);
    //PrintInorder(tree);

    PrintGraphHead(dump);

    PrintDefaultList(dump, tree);

    fprintf(dump, "}\n");
    fclose(dump);

    static int number_dump = 0;
    MySystem("dot Dump.dot -Tpng -o Graphs/Dump%03d.png", number_dump);
    number_dump++;

    //PrintInorder(tree);
    printf("\n");
}

void PrintGraphHead(FILE* graph)
{
    assert(graph);

    fprintf(graph, "digraph G\n{\n    rankdir = TB;\n    bgcolor = \"pink2\"\n"
                   "    node[color = \"#b503fc\", fontsize = 14];\n"
                   "    edge[color = black, fontsize = 12, splines = ortho];\n\n");

}

void PrintDefaultList(FILE* graph, struct node_t* tree)
{
    assert(graph);
    assert(tree);

    fprintf(graph, "    %4s [shape = Mrecord, label = \"{ %4s | { <f0> left %4p | <f1> right %4p}}\"];\n",
                        tree->word, tree->word, tree->left, tree->right);

    if (tree->left != NULL)
    {
        fprintf(graph, "    %4s : <f0> -> %4s [style = \"filled\"]\n", tree->word, tree->left->word);
        PrintDefaultList(graph, tree->left);
    }

    if (tree->right != NULL)
    {
        fprintf(graph, "    %4s : <f1> -> %4s [style = \"filled\"]\n", tree->word, tree->right->word);
        PrintDefaultList(graph, tree->right);
    }
}

void PrintInorder(struct node_t* node)
{
    if(!node) {return;}

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
