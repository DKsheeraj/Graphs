#include <stdio.h>
#include <stdlib.h>
#define SIZE 20

struct queue
{
  int items[SIZE];
  int front;
  int rear;
};

struct queue *createQueue()
{
  struct queue *q = malloc(sizeof(struct queue));
  q->front = -1;
  q->rear = -1;
  return q;
}

// Check if the queue is empty
int isEmpty(struct queue *q)
{
  if (q->rear == -1)
    return 1;
  else
    return 0;
}

// Adding elements into queue
void ENQUEUE(struct queue *q, int value)
{
  if (q->rear == SIZE - 1)
    printf("\nQueue is Full!!");
  else
  {
    if (q->front == -1)
      q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
  }
}

// Removing elements from queue
int DEQUEUE(struct queue *q)
{
  int item;
  if (isEmpty(q))
  {
    printf("Queue is empty\n");
    item = -1;
  }
  else
  {
    item = q->items[q->front];
    q->front++;
    if (q->front > q->rear)
    {
    //   printf("Resetting queue ");
      q->front = q->rear = -1;
    }
  }
  return item;
}

// Print the queue
void printQueue(struct queue *q)
{
  int i = q->front;

  if (isEmpty(q))
  {
    printf("Queue is empty");
  }
  else
  {
    printf("Queue contains ");
    for (i = q->front; i < q->rear + 1; i++)
    {
      printf("%d ", q->items[i]);
    }
  }
  printf("\n");
}

typedef struct node
{
    int value;
    struct node *next;
}N;


typedef struct V
{
    int value;
    int parent;
    char colour;
    int distance;
} V;

N *CREATE(int a)
{
    N *V1 = (N *)malloc(sizeof(V));
    V1->next = NULL;
    V1->value = a;

    return V1;
}



typedef struct graph{
    V **vertices;
    int Nvertices;
}G;

N **ADJ;
G *graph;
void _INIT_(int source, int Nvertices)
{
    graph = (G*)malloc(sizeof(G));
    graph->Nvertices = Nvertices;
    graph->vertices = (V**)malloc(Nvertices*sizeof(V*));

    ADJ = (N**)malloc(Nvertices*sizeof(N*));

    
    for (int i = 0; i < Nvertices; i++)
    {
        graph->vertices[i] = (V *)malloc(sizeof(V));
        if (i == source)
            continue;

        graph->vertices[i]->colour = 'W';
        graph->vertices[i]->distance = 10000;
        graph->vertices[i]->parent = -2;
        graph->vertices[i]->value = i;
    }
    graph->vertices[source]->colour = 'O';
    graph->vertices[source]->distance = 0;
    graph->vertices[source]->parent = -2;
    graph->vertices[source]->value = source;

    for(int i = 0; i < Nvertices; i++){
        ADJ[i] = (N*)malloc(sizeof(N));
        ADJ[i]->value = i;
        ADJ[i]->next = NULL;
    }
}

void ADD_EDGE(N **ADJ, int a, int b)
{
    N *p1 = ADJ[a];
    N *p2 = ADJ[b];

    N *V1 = CREATE(a);
    N *V2 = CREATE(b);

    while (p1->next != NULL)
    {
        p1 = p1->next;
    }
    p1->next = V2;

    while (p2->next != NULL)
    {
        p2 = p2->next;
    }
    p2->next = V1;
}

void BFS(int source, N **ADJ, G *graph)
{
  struct queue *Q = createQueue();
  ENQUEUE(Q, source);
  while (!isEmpty(Q))
  {
    // printQueue(Q);
    int u = DEQUEUE(Q);
    N *helper = ADJ[u]->next;

    while (helper != NULL)
    {
      if (graph->vertices[helper->value]->colour == 'W')
      {
        ENQUEUE(Q, helper->value);
        // printQueue(Q);
        graph->vertices[helper->value]->colour = 'O';
        graph->vertices[helper->value]->distance = graph->vertices[u]->distance + 1;
        graph->vertices[helper->value]->parent = u;
      }

      helper = helper->next;
    }

    graph->vertices[u]->colour = 'G';
    printf("%d ", u);
  }
}

int main()
{
    _INIT_(0, 8);
    ADD_EDGE(ADJ, 0, 1);
    ADD_EDGE(ADJ, 0, 3);
    ADD_EDGE(ADJ, 1, 2);
    ADD_EDGE(ADJ, 3, 4);
    ADD_EDGE(ADJ, 3, 7);
    ADD_EDGE(ADJ, 4, 7);
    ADD_EDGE(ADJ, 4, 5);
    ADD_EDGE(ADJ, 6, 5);
    ADD_EDGE(ADJ, 6, 7);
    

    for (int i = 0; i < 8; i++)
    {
        printf("%d[%c]->", ADJ[i]->value, graph->vertices[i]->colour);
        N *A = ADJ[i]->next;
        while (A)
        {
            printf("%d[%c]->", A->value,graph->vertices[A->value]->colour);
            A = A->next;
        }
        printf("NULL\n");
    }

    BFS(0, ADJ, graph);

    for (int i = 0; i < 8; i++)
    {
        printf("%d[%c]->", ADJ[i]->value, graph->vertices[i]->colour);
        N *A = ADJ[i]->next;
        while (A)
        {
            printf("%d[%c]->", A->value,graph->vertices[A->value]->colour);
            A = A->next;
        }
        printf("NULL\n");
    }



    return 0;
}