#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct Trie {
    int count; //Counts number of words total
    struct Trie *children[26];
};

//I was always taught to prototype my functions after structures
//It's fine if you don't but it never hurts (especially if they are)
//out of order and they call each other
void insert(struct Trie **ppTrie, char *word);
int numberOfOccurances(struct Trie *pTrie, char *word);
struct Trie *deallocateTrie(struct Trie *pTrie);

void insert(struct Trie **ppTrie, char *word) {
    struct Trie *pTrie = *ppTrie; //De references the double pointer
    if (!pTrie) //Checks are always important :)
    {
        pTrie = (struct Trie*) malloc(sizeof(struct Trie)); //Adds memory if statement occurs above
        pTrie->count = 0;
        for (int i = 0; i < 26; i++)
            pTrie->children[i] = NULL;
        *ppTrie = pTrie;
    }
    int len = strlen(word); //Gets length
    for (int i = 0; i < len; i++) //Runs for each letter
    {
        int index = word[i] - 'a'; //Gets current index char is turned into number automatically by GCC
        if (!pTrie->children[index]) 
        { //If there is no child node it creates one but it always checks first
        //I was getting logical errors from not checking.
            pTrie->children[index] = (struct Trie*) malloc(sizeof(struct Trie)); //Mallocs for each letter
        }
        pTrie = pTrie->children[index]; //Moves newly created node to location detected above.
    }
    //Adds one to count
    pTrie->count++;
}

int numberOfOccurances(struct Trie *pTrie, char *word) 
{
    if (!pTrie) //Always check :)
    {
        return 0;
    }
        
    int len = strlen(word);
    for (int i = 0; i < len; i++) 
    {
        int index = word[i] - 'a';
        if (!pTrie->children[index]) //If this occurs the child is not a match
        {
            return 0;
        }
            
        pTrie = pTrie->children[index];
    }
    return pTrie->count; //If it makes it thorugh all of the conditions above
                    //And makes it here then the word is a match and is returned as one
}

struct Trie *deallocateTrie(struct Trie *pTrie) 
{//Frees the memory and returns NULL
    if (!pTrie)
    {
        return NULL;
    }
        
    for (int i = 0; i < 26; i++)
    {
        pTrie->children[i] = deallocateTrie(pTrie->children[i]);
    }
    free(pTrie);
    return NULL;
}

int main(void) 
{
    //TAKES USER INPUT AND FOR NUMBER OF ELEMENTS TO INSERT
    //THEN INPUTS THE NUMBER OF ELEMENTS INTO THE TRIE DATA STRUCTURE
    int numWords;
    printf("Enter the number words: ");
    scanf("%d", &numWords);
    struct Trie *trie = NULL;
    char word[100];
    for (int i = 0; i < numWords; i++) 
    {
        printf("Word to insert: ");
        scanf("%s", word);
        insert(&trie, word);
    }
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) 
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(trie, pWords[i]));
    }
    trie = deallocateTrie(trie);
    if (trie != NULL)
        printf("There is an error in this program\n");
    return 0;
}
