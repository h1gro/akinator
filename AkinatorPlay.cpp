#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Akinator.h"
#include "Dump.h"

void PlayMode(struct node_t* node, struct node_t* root)
{
    assert(node);
    assert(root);

    printf("IF YOU WANT TO PLAY WITH AKINATOR WRITE \"1\", ELSE WRITE \"2\"\n");

    Game(root, root);

    TreeDump(root);

    printf("IF YOU WANT TO GET A DIFINITION \"5\", ELSE WRITE \"6\"\n");

    GetDifCommand(root);
}

void Game(struct node_t* node, struct node_t* root)
{
    assert(node);
    assert(root);

    int comand_for_play = 0;

    scanf("%d", &comand_for_play);

    ClearBuffer();

    if (comand_for_play == PLAY_AKINATOR)
    {
        printf("\nOKEY LETS PLAY!!!\n");
        GuessWord(node, root);
    }

    else if (comand_for_play == DONT_PLAY_AKINATOR)
    {
        printf("\nITS SAD :(\n");
    }

    else
    {
        printf("\nYOU WROTE WRONG COMMAND!!!\nrepeat!\n");
        Game(node, root);
    }
}

int GuessWord(struct node_t* node, struct node_t* root)
{
    assert(node);
    assert(root);

    printf("%s\n", node->word);

    char* answer = (char*) calloc(10, sizeof(char));

    scanf("%s", answer);

    ClearBuffer();

    if (strcmp(answer, "no") == 0)
    {
        if (node->right == NULL)
        {
            PrintfGameEnding(node, root, answer);
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

void GetDifCommand(struct node_t* root)
{
    struct addr_t array = {};

    int command_for_def = 0;

    scanf("%d", &command_for_def);

    ClearBuffer();

    switch(command_for_def)
    {
        case GET_DIF:      array.nods_addresses = (node_t**) calloc(50, sizeof(node_t*));

                           assert(array.nods_addresses);

                           GetUserWord(root, &array);

                           //GetDifinition(root, GetUserWord(root, &array));
                           free(array.nods_addresses);
                           break;


        case DONT_GET_DIF: return;

        default:           printf("\nYOU WROTE WRONG COMMAND!!!\nrepeat!\n");
                           GetDifCommand(root);
    }
}

find_word FindWord(struct node_t* node, struct addr_t* array, char* word)
{
    assert(node);
    assert(array);

    if (strcmp(node->word, word) == 0)
    {
        return WORD_WAS_FOUNDED;
    }

    if (node->left != NULL)
    {
        if (FindWord(node->left, array, word) == WORD_WAS_FOUNDED)
        {
            array->nods_addresses[array->index] = node->left;
            array->index++;
        }
    }

    if (node->right != NULL)
    {
        if (FindWord(node->right, array, word) == WORD_WAS_FOUNDED)
        {
            array->nods_addresses[array->index] = node->right;
            array->index++;
        }
    }

    for (int i = 0; i < array->index; i++)
    {
        printf("nods_addresses[%d] = %p\n", i, array->nods_addresses[i]);
    }

    return FIND_WORD_ERROR;
}

find_word GetUserWord(struct node_t* root, struct addr_t* array)
{
    assert(root);
    assert(array);

    printf("WRITE WORD\n");

    char* word = (char*) calloc(100, sizeof(char));

    scanf("%s", word);

    ClearBuffer();

    find_word node_pointer = FindWord(root, array, word);

    if (node_pointer == FIND_WORD_ERROR)
    {
        printf("\nYOUR WORD IS NOT IN DATABASE!!!\n\n");
        GetUserWord(root, array);
    }

    return node_pointer;
}

void PrintfGameEnding(struct node_t* node, struct node_t* root, char* answer)
{
    printf("\nTHAT WAS ALL THAT I KNOW\n\n"
           "IF YOU WANT TO ADD NEW ANSWER "
           "WRITE: \"3\", ELSE WRITE: \"4\"\n");

    IfAddAnswer(node, root);

    free(answer);
}
