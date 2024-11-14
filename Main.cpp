#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Tree.h"
#include "Dump.h"

//TODO научиться давать определения по заданному слову(елементу дерева), если оно есть в дереве
//TODO уметь отличать два элемента дерева друг от друга и писать чем они отличаются и чем похожи

int main()
{
    node_t* root = NULL;

    root = TreeCtor(root);

    CreateSubtree(root, "maxim");

    TreeDump(root);

    TreeDtor(root);
    return 0;
}
