/* K&R - Exercise 6-5. Write a function undef that will remove a name and 
 * definition from the table maintained by lookup and install.  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nlist {  /* table entry */
    struct nlist *next;  /* next entry in chain */
    char *name;  /* defined name */
    char *defn; /* replacement text */
};

#define HASHSIZE 101

static struct nlist *hashtab[HASHSIZE];  /* pointer table */


/* hash: form hash value for string s */
unsigned hash(char *s)
{
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}
    
/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;  /* found */
    return NULL;  /* not found */
}

/* install: put (name, defn) in hashtab. 
 * Returns NULL if no room for new entry */
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {  /* not found */
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else  /* already there */
        free((void *) np->defn);  /* free previous defn */
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
}

/* free_name_defn: a helper function used to free the 
 * memory used by name & defn */
void free_name_defn(struct nlist *np)
{
    free((void *) np->name);  /* free name */
    free((void *) np->defn);  /* free defn */
}

/* undef: remove a name and defn from table. */
/* XXX Haven't tested removing node within a linked list. In order
 * to do so, would have to find words that create a hash collision... */
int undef(char *name)
{
    struct nlist *np1, *np2;

    if ((np1 = lookup(name)) == NULL)  /* not found */
        return 1;
    else  {
        np1 = np2 = hashtab[hash(name)];
        if ((np2 = np2->next) == NULL) {
            free_name_defn(np1);
            np1 = NULL;  /* set beginning node to NULL */
        } else {
            while (strcmp(np2->name, name) != 0) {
                np1 = np2;
                np2 = np2->next;
            }
            np1->next = np2->next;
            free_name_defn(np2);
            free((void *) np2);  /* free node */
        }
    }
    return 0;
}


int main(void)
{
    char name1[] = "IN";
    char defn1[] = "1";
    char defn2[] = "2";
    struct nlist *np1, *np2;

    np1 = install(name1, defn1);
    if (np1 != NULL) {
        printf("Success!\n");
        printf("NP1 has been installed: %s => %s\n", np1->name, np1->defn);
    }

    printf("\nLet's check lookup to see if it really was installed..\n");
    np2 = lookup(name1);
    if (np2 != NULL) {
        printf("Success!\n");
        printf("NP2 has name %s and definition %s\n", np2->name, np2->defn);
    }

    printf("\nLet's change the definition...\n");
    np1 = install(name1, defn2);
    if (np1 != NULL) {
        printf("Success!\n");
        printf("NP1 has been installed: %s => %s\n", np1->name, np1->defn);
    }

    printf("\nNow let's test out undef...\n");
    if (undef(name1) == 0) {
        if ((np2 = lookup(name1)) == NULL)
            printf("Success! np2 is NULL\n");
        else
            printf("Wrong. np2 is: %s => %s\n", np2->name, np2->defn);

    } else
        printf("Something's gone wrong...\n");
}
