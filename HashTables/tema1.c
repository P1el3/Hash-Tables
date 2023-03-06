#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *f1;
FILE *f2;

typedef struct node
{
    void *el;
    struct node *urm;
    struct node *pre;
}Node;

typedef struct list
{
    Node* first;
    int dim;
    void(*Free)(void*);
    void(*print)(void*);
    int(*cmp)(void*, void*);
}List;

List initList(void(*Free)(void*) , void(*print)(void*), int(*cmp)(void*, void*))
{
    List l;
    l.first=NULL;
    l.dim = 0;
    l.Free = Free;
    l.print = print;
    l.cmp = cmp;
    return l;
}
//functie de adaugare elemnt
void addItem(List *l, void* el)
{
    Node *new_N = (Node*)malloc(sizeof(Node));
        if (new_N == NULL)
            return;
    new_N -> el = el;
    if(l -> first == NULL)
    {
        l -> first = new_N;
        new_N -> urm = new_N -> pre = l -> first;
        l -> dim++;
        return;
    }
    if(l -> cmp(el, l -> first -> el) < 0)
    {
        new_N -> urm = l -> first;
        new_N -> pre = l -> first -> pre;
        l -> first -> pre -> urm = new_N;
        l -> first -> pre = new_N;
        l -> first = new_N;
        l -> dim++;
        return;
    }

    if( l->cmp(l->first->el, el) == 0 )
        return;

    Node *aux = l -> first -> urm;
        while(l -> cmp (aux -> el, el) < 0 && aux != l -> first)
        {
            aux = aux -> urm;
        }
        if (l -> cmp(aux -> el, el) == 0)
        {
            free(new_N);
            return;
        }

        new_N -> pre = aux -> pre;
        new_N -> urm = aux;
        aux -> pre -> urm = new_N;
        aux -> pre = new_N;
        l -> dim++;
}

void removeItem(List *l, void *el)
{
    if(l -> first == NULL)
        return;
    if(l -> cmp(el, l -> first -> el) == 0)
        {
            int only = 0;
            if(l -> first == l -> first -> urm)
                only = 1;

            Node *aux = l -> first;
            l -> first -> pre -> urm = l -> first -> urm;
            l -> first -> urm -> pre = l -> first -> pre;
            l -> first = l -> first -> urm;
            l -> Free(aux -> el);
            free(aux);

            if(only)
                l -> first = NULL;
            return;
        }
    Node *aux = l -> first -> urm;
    while(l -> cmp(el, aux -> el) != 0 && aux != l -> first)
        aux = aux -> urm;
    if(aux == l -> first)
        return;
    aux -> pre -> urm = aux -> urm;
    aux -> urm -> pre = aux -> pre;
    l -> Free(aux -> el);
    free(aux);
}

void printList(List *l)
{
    if(l -> first == NULL)
        return;

    Node *aux = l -> first;
    l -> print(aux -> el);
    aux = aux -> urm;
    while(aux != l -> first)
    {
        l -> print(aux -> el);
        aux = aux -> urm;
    }
}

void freeList(List *l)
{
    if(l -> first == NULL)
        return;

    Node *aux = l -> first -> urm;
    while(aux != l -> first)
    {
        Node *x = aux -> urm;
        l -> Free(aux -> el);
        free(aux -> el);
        free(aux);
        aux = x;
    }

    l -> Free(l -> first -> el);
    free(l -> first -> el);
    free(l -> first);
}

void* getItem(List *l, void *el)
{
    if(l -> first == NULL)
        return NULL;
    if(l -> cmp(l -> first -> el, el) == 0)
        return l -> first -> el;

    Node *aux = l -> first -> urm;
    while (aux != l -> first)
    {

        if(l -> cmp(aux -> el, el) == 0)
            return aux -> el;
        aux = aux -> urm;
    }
    return NULL;
}
typedef struct
{
    size_t M;
    int (*hash)(void*);
    List *v;
} TH;

TH initTable(size_t M, int (*hash)(void*), void(*Free)(void*) , void(*print)(void*), int(*cmp)(void*, void*))
{
    TH t;
    t.M = M;
    t.hash = hash;
    t.v = malloc(sizeof(List) * M);
    int i;
    for(i = 0; i < M; i++)
        t.v[i] = initList(Free, print, cmp);

    return t;
}

void freeTable(TH* t)
{
    int i;
    for(i = 0; i < t -> M; i++)
        freeList(&t -> v[i]);
    free(t -> v);
}

void addElement(TH* t, void* el)
{
    int findList = t -> hash(el);
    addItem(&t -> v[findList], el);
}

void removeElement(TH* t, void* el)
{
    int findList = t -> hash(el);
    removeItem(&t -> v[findList], el);
}
void* getElement(TH* t, void* el)
{
    int findList = t -> hash(el);
    return getItem(&t -> v[findList], el);
}

typedef struct site
{
    char *key;
    char *value;
}Site;

void freeSite(void *el)
{
    Site *p = (Site*)el;
    free(p -> key);
    free(p -> value);
}
void printElement(void* el)
{
    Site* aux = (Site*)el;
    fprintf(f2, "%s ", aux -> value);
}
int cmpElemente(void *el1, void *el2)
{
    Site *e1 = (Site*)el1;
    Site *e2 = (Site*)el2;
    return strcmp(e1 -> key , e2 -> key);
}

void put(TH *t, char *key, char *value)
{
    Site* s = malloc(sizeof(Site));
    s -> key = malloc(sizeof(char)*350);
    s -> value = malloc(sizeof(char)*350);
    strcpy(s -> key, key);
    strcpy(s -> value, value);
    addElement(t, (void*)s);
}

void stergere(TH *t, char *key)
{
    Site* del = malloc(sizeof(Site));
    del -> key = malloc(sizeof(char)*350);
    strcpy(del -> key, key);
    removeElement(t, (void*)del);
}

void print(TH *t)
{
    int i;
    for(i = 0; i < t -> M; i++)
    {
        if(t -> v[i].first == NULL )
            continue;
        fprintf(f2, "%d: ", i);
        printList(&t ->v[i]);
        fprintf(f2, "\n");
    }
}

void print_bucket(TH *t, int index)
{
    if(index >= t -> M)
        return;
    printList(&t -> v[index]);
    fprintf(f2, "\n");
}

Site* get(TH *t, char *key)
{
    Site* gett = malloc(sizeof(Site));
    gett -> key =  malloc(sizeof(char)*350);
    strcpy(gett -> key, key);
    return (Site*) getElement(t, (void*)gett);
}

int find(TH *t, char* key)
{
    Site* gett = malloc(sizeof(Site));
    gett -> key =  malloc(sizeof(char)*350);
    strcpy(gett -> key, key);
    return (getElement(t, (void*)gett) != NULL);
}

int M;
int returnHash(void* el)
{
    Site* var = (Site*)el;
    int s = 0;
    int p;

    for(p = 0; var -> key[p] != 0; p++)
        s += var -> key[p];

    return s % M;
}

int main(int argc, char* argv[])
{
    M = atoi(argv[1]);
    f1 = fopen(argv[2] ,"rt");
    f2 = fopen(argv[3] ,"wt");
    char comanda[350];
    TH t = initTable(M, returnHash, freeSite, printElement, cmpElemente);
    while(fscanf(f1, "%s", comanda) > 0)
        {
            if(strcmp(comanda, "print") == 0)
                print(&t);
            else if (strcmp(comanda, "print_bucket") == 0)
            {
                int index;
                fscanf(f1, "%d", &index);

                if( index < t.M && t.v[index].first == NULL)
                    fprintf(f2, "VIDA\n");
                else
                    print_bucket(&t , index);
            }
            else if (strcmp(comanda, "put") == 0)
                {
                char key[350];
                char value[350];
                fscanf(f1, "%s %s", key, value);
                put(&t, key, value);
                }
            else if (strcmp(comanda, "get") == 0)
                {
                    char key[350];
                    fscanf(f1, "%s", key);
                    Site* gett = get(&t, key);
                    if(gett == NULL)
                        fprintf(f2, "NULL\n");
                    else
                        fprintf(f2, "%s\n", gett -> value);
                }
            else if (strcmp(comanda, "find") == 0)
                {
                    char key[350];
                    fscanf(f1, "%s", key);
                    int res = find(&t, key);
                    if(res == 0)
                        fprintf(f2, "False\n");
                    else
                        fprintf(f2, "True\n");
                }
            else if (strcmp(comanda, "remove") == 0)
                {
                    char key[350];
                    fscanf(f1, "%s", key);
                    stergere(&t, key);
                }
        }
    freeTable(&t);
    fclose (f1);
    fclose (f2);
//(10 10 19 9 5 4 4 4 1 4)
    return 0;
}