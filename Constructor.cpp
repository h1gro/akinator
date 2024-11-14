#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Tree.h"

node_t* TreeCtor(struct node_t* root)
{
    root = (node_t*) calloc(1, sizeof(node_t));
    printf("root ctor1 = %p\n", root);

    assert(root);

    root->word  = "human?";
    root->left  = NULL;
    root->right = NULL;

    return root;
}

int TreeDtor(struct node_t* node)
{
    if(!node)
    {
        return 0;
    }

    TreeDtor(node->left);
    TreeDtor(node->right);

    free(node);

    node = NULL;

    return 0;

}


