#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Akinator.h"
#include "Dump.h"

static const char* TREE_FILE = "Tree.txt";

node_t* CreateNode(struct node_t* parent, const char* word)
{
    printf("\nCREATE SUBTREE\n");

    node_t* new_node = (node_t*) calloc(1, sizeof(node_t));

    assert(new_node);

    strcpy(new_node->word, word);

    new_node->left  = NULL;
    new_node->right = NULL;

    //akin->node_number += 1;

    new_node->parent = parent;

    return new_node;
}

int GuessWord(struct node_t* node, struct node_t* root)
{
    assert(node);

    printf("%s\n", node->word);

    char* answer = (char*) calloc(10, sizeof(char));

    scanf("%s", answer);

    if (strcmp(answer, "no") == 0)
    {
        if (node->right == NULL)
        {
            printf("\nTHAT WAS ALL THAT I KNOW\n\n"
                   "IF YOU WANT TO ADD NEW ANSWER WRITE: 1, ELSE WRITE: 2\n");

            IfAddAnswer(node, root);
            free(answer);
            return 0;
        }
        else
        {
            GuessWord(node->right, root);
        }
    }

    else if (strcmp(answer, "yes") == 0)
    {
        if (node->left == NULL)
        {
            printf("IT WAS OBVIOSLY!\n");
            free(answer);
            return 0;
        }
        else
        {
            GuessWord(node->left, root);
        }
    }

    else
    {
        printf("NOT ANSWER, WRITE YES OR NO!\n");
        GuessWord(node, root);
    }

    free(answer);
    return 0;
}

void CreateNewAnswer(struct node_t* node, struct node_t* root)
{
    FILE* file_ptr = fopen(TREE_FILE, "w+");

    assert(file_ptr);

    char* user_question  = (char*) calloc(50, sizeof(char));
    char* user_answer_no = (char*) calloc(50, sizeof(char));

    printf("WRITE YOUR QUESTION IF ANSWER YES - %s\n"
           "AND YOUR ANSWER IF QUESTION ANSWER - NO:\n", node->word);

    scanf("%s%s", user_question, user_answer_no);

    node->left  = CreateNode(node->left, node->word);
    node->right = CreateNode(node->right, user_answer_no);

    strcpy(node->word, user_question);

    RewriteTree(root, file_ptr);

    fprintf(file_ptr, ";");

    free(user_question);
    free(user_answer_no);

    CheckFclose(file_ptr);
}

void RewriteTree(struct node_t* node, FILE* file_ptr)
{
    fprintf(file_ptr, "{\"%s\"", node->word);

    if (node->left != NULL)
    {
        RewriteTree(node->left, file_ptr);
    }

    if (node->right != NULL)
    {
        RewriteTree(node->right, file_ptr);
    }

    fprintf(file_ptr, "}");
}

void IfAddAnswer(struct node_t* node, struct node_t* root)
{
    int command = 0;

    scanf("%d", &command);

    if (command == ADD_ANSWER) {CreateNewAnswer(node, root);}

    else if(command == DONT_ADD_ANSWER) {return;}

    else
    {
        printf("WRONG COMMAND!!!\nREWRITE!\n\n");
        IfAddAnswer(node, root);
    }
}
