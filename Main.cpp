#include <stdlib.h>
#include <assert.h>

#include "Akinator.h"
#include "Tree.h"
#include "Dump.h"

//TODO научиться давать определения по заданному слову(елементу дерева), если оно есть в дереве
//TODO уметь отличать два элемента дерева друг от друга и писать чем они отличаются и чем похожи

int main()
{
    struct file_t akin = {};

    node_t* root = NULL;

    akin.file_ptr = fopen(TREE_FILE, "r");

    assert(akin.file_ptr);

    root = AkinatorCtor(root);

    ReadTree(root, &akin);

    CheckFclose(akin.file_ptr);

    TreeDump(root);

    AkinatorDtor(root);

    return 0;
}
