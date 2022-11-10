#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct V
{
    int value;
    int parent;
    int distance;
    struct V *ptr;
} V;

V *create(V *head)
{
    V *temp = (V *)malloc(sizeof(V));
    temp->distance = head->distance;
    temp->ptr = NULL;
    temp->parent = head->parent;
    temp->value = head->value;
    return temp;
}


V *getnewhead(V *head)
{
    V *temp = head;
    head = head->ptr;

    return head;
}

void copy(V *v1, V *v2)
{
    v2->distance = v1->distance;
    v2->parent = v1->parent;
    v2->ptr = NULL;
    v2->value = v1->value;
}




V *insert(V *head, V *helper)
{ 
    
    V *vertex = (V*)malloc(sizeof(V));
    copy(helper, vertex);

    if(head == NULL) return vertex;

    if (head->distance >= vertex->distance)
    {

        vertex->ptr = head;
        return vertex;
    }

    

    else
    {
        V *start = head;
        V *startprev = head;

        while (vertex->distance >= start->distance)
        {
            if (start->ptr != NULL)
            {
                startprev = start;
                start = start->ptr;
            }

            else
            {
                start->ptr = vertex;
                return head;
            }
        }

        

        startprev->ptr = vertex;
        vertex->ptr = start;

        return head;
    }
}

typedef struct box
{
    int value;
    int weight;
    struct box *next;
} N;

N *CREATE(int a)
{
    N *V1 = (N *)malloc(sizeof(V));
    V1->next = NULL;
    V1->value = a;
    V1->weight = 0;

    return V1;
}

typedef struct graph
{
    V **vertices;
    int Nvertices;
} G;

N **ADJ;
G *graph;
V *pq;
void _INIT_(int source, int Nvertices)
{
    graph = (G *)malloc(sizeof(G));
    graph->Nvertices = Nvertices;
    graph->vertices = (V **)malloc(Nvertices * sizeof(V *));

    ADJ = (N **)malloc(Nvertices * sizeof(N *));

    for (int i = 0; i < Nvertices; i++)
    {
        graph->vertices[i] = (V *)malloc(sizeof(V));
        if (i == source)
            continue;

        graph->vertices[i]->distance = 10000;
        graph->vertices[i]->parent = -2;
        graph->vertices[i]->value = i;
        graph->vertices[i]->ptr = NULL;
    }
    graph->vertices[source]->distance = 0;
    graph->vertices[source]->parent = -2;
    graph->vertices[source]->value = source;
    graph->vertices[source]->ptr = NULL;

    for (int i = 0; i < Nvertices; i++)
    {
        ADJ[i] = (N *)malloc(sizeof(N));
        ADJ[i]->value = i;
        ADJ[i]->weight = 0;
        ADJ[i]->next = NULL;
    }
}

void ADD_EDGE(N **ADJ, int a, int b, int weight)
{
    N *p1 = ADJ[a];
    N *p2 = ADJ[b];

    N *V2 = CREATE(b);
    N *V1 = CREATE(a);

    while (p1->next != NULL)
    {
        p1 = p1->next;
    }
    p1->next = V2;
    V2->weight = weight;

    while (p2->next != NULL)
    {
        p2 = p2->next;
    }
    p2->next = V1;
    V1->weight = weight;
}

void printQ(V *head1)
{
    V *head = head1;
    while (head)
    {
        printf("(%d %d)->", head->value, head->distance);
        head = head->ptr;
    }
    printf("NULL\n");
}



V *delete (V *pq, int value)
{
    V *h = pq, *to_be_freed;
    if (h != NULL){
        if (h->value == value)
        {
            pq = h->ptr;
            free(h);
            
            return pq;
        }
        else
        {
            while (h->ptr)
            {
                if (h->ptr->value == value)
                {
                    to_be_freed = h->ptr;
                    h->ptr = h->ptr->ptr;
                    free(to_be_freed);
                    return pq;
                }
                h = h->ptr;
            }

            return pq;
        }
    }

}

int search(V *pq, N *temp){
    V *h = pq;
    while(h){
        if(temp->value == h->value) return 1;
        h = h->ptr;
    }

    return 0;
}

void Prim(G *graph, N **ADJ){
    pq = (V*)malloc(sizeof(V));
    pq = NULL;

    for(int i = 0; i < graph->Nvertices; i++){
        if(pq == NULL){
            pq = create(graph->vertices[i]);
        }else{
            pq =insert(pq, graph->vertices[i]);
        }
    }
    while(pq != NULL){
        V *vertex = (V *)malloc(sizeof(V));
        copy(pq, vertex);
        pq = getnewhead(pq);

        N *A = ADJ[vertex->value]->next;
        while (A)
        {
            if (search(pq, A) == 1 && (A->weight < graph->vertices[A->value]->distance))
            {
                graph->vertices[A->value]->distance = A->weight;
                graph->vertices[A->value]->parent = vertex->value;
                pq = delete(pq, A->value);
                pq = insert(pq, graph->vertices[A->value]);
                
            }
            A = A->next;
        }


        
    
    }
}



int main()
{

    _INIT_(0, 9);

    ADD_EDGE(ADJ, 0, 1, 4);
    ADD_EDGE(ADJ, 0, 7, 8);
    ADD_EDGE(ADJ, 1, 7, 11);
    ADD_EDGE(ADJ, 1, 2, 8);
    ADD_EDGE(ADJ, 2, 3, 7);
    ADD_EDGE(ADJ, 2, 8, 2);
    ADD_EDGE(ADJ, 2, 5, 4);
    ADD_EDGE(ADJ, 3, 4, 9);
    ADD_EDGE(ADJ, 3, 5, 14);
    ADD_EDGE(ADJ, 4, 5, 10);
    ADD_EDGE(ADJ, 6, 5, 2);
    ADD_EDGE(ADJ, 6, 7, 1);
    ADD_EDGE(ADJ, 6, 8, 6);
    ADD_EDGE(ADJ, 7, 8, 7);

    for (int i = 0; i < graph->Nvertices; i++)
    {
        printf("%d->", ADJ[i]->value);
        N *t1 = ADJ[i]->next;

        while (t1)
        {
            printf("%d[%d]", t1->value, t1->weight);
            t1 = t1->next;
        }
        printf("\n");
    }

    Prim(graph, ADJ);

    for (int i = 0; i < graph->Nvertices; i++)
    {
        if (i == 0)
        {
            printf("%c %d %c\n", 'A' + i, graph->vertices[i]->distance, 'A' + 0);
        }
        else
        {

            printf("%c %d %c\n", 'A' + i, graph->vertices[i]->distance, 'A' + graph->vertices[i]->parent);
        }
    }


    return 0;
}