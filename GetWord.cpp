#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Tree.h"

node_t* CreateSubtree(struct node_t* parent, const char* word)
{
    node_t* subtree = (node_t*) calloc(1, sizeof(node_t));

    assert(subtree);

    subtree->word  = word;
    subtree->left  = NULL;
    subtree->right = NULL;

    // if (parent != NULL)
    // {
    //     GetWord(parent, subtree);
    // }

    return subtree;
}

// int GetWord(struct node_t* parent, struct node_t* subtree)
// {
//     assert(parent);
//     assert(subtree);
//
//     // printf("%s\n", parent->word);
//     // scanf("%s", &subtree->word);
//
//     if (strcmp(subtree->word, "no") == 0)
//     {
//         if (parent->right == NULL)
//         {
//             parent->right = subtree;
//             return 0;
//         }
//         else
//         {
//             parent = parent->right;
//             GetWord(parent, subtree);
//         }
//     }
//
//     else if (strcmp(subtree->word, "yes") == 0)
//     {
//         if (parent->left == NULL)
//         {
//             parent->left = subtree;
//             return 0;
//         }
//         else
//         {
//             parent = parent->left;
//             GetWord(parent, subtree);
//         }
//     }
//
//     else if (strcmp(subtree->word, parent->word) == 0)
//     {
//         printf("This word was in the tree yet\n");
//     }
//
//     return 0;
// }
