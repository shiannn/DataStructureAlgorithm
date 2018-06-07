#include <stdio.h>
#include <stdlib.h>
#define max_events 52

//#define debug_input
//#define debug_graph
#define max_vertex 524288//(2^19)

#define WHITE 0
#define BLACK 2
#define GRAY 1
#define infinte 2147483647
#define NIL -1
struct node_attribute{
    int color;
    int distance;
    //int parent;
};
typedef struct node_attribute node_attribute;

struct adjacency_node{
    int number;
    struct adjacency_node*next;
};
typedef struct adjacency_node adjacency_node;

struct adjacency_list{
    struct adjacency_node*head;
};
typedef struct adjacency_list adjacency_list;

struct Graph{
    int num_of_vertex;
    struct adjacency_list*list_array;
};
typedef struct Graph Graph;

void print_graph(Graph*graph);
struct Graph* create_graph(int num_vertex);
void add_edge(Graph*graph,int start,int end);
struct adjacency_node*add_node(int num);

struct Queue{
    int front,rear,size;
    unsigned int capacity;
    int *array;
};
typedef struct Queue Queue;

Queue*create_queue(unsigned int create_capacity);
void enqueue(Queue*queue,int item);
int dequeue(Queue*queue);
int isFull(Queue*queue);
int isEmpty(Queue*queue);

void BFS(Graph*graph,int start);

int events_array[max_events];
int events_times[max_events];
node_attribute attribute_array[max_vertex];

int main()
{
    Graph*graph=create_graph(max_vertex);
    /*0~524287*/
    int N_events;
    scanf("%d",&N_events);
    int i,j,XOR_result,Events,Events_times;
    for(i=0;i<N_events;i++){
        //scanf("%d %d",&events_array[i],&events_times[i]);
        scanf("%d %d",&Events,&Events_times);
        #ifdef debug_input
            printf("%d %d\n",Events,Events_times);
        #endif // debug_input
        for(j=0;j<max_vertex;j++){
            XOR_result=j^Events;
            /*在j和XOR_result之間建立一條邊*/
            add_edge(graph,j,XOR_result);
        }
    }
    BFS(graph,0);
    int Q_s_t;
    scanf("%d",&Q_s_t);
    int s,t,goal;
    for(i=0;i<Q_s_t;i++){
        scanf("%d %d",&s,&t);
        #ifdef debug_input
            printf("%d %d\n",s,t);
        #endif // debug_input
        goal=s^t;
        /*藉由BFS已知0到goal的最短距離*/
        if(attribute_array[goal].distance==0){
            if(goal==0){
                printf("%d\n",attribute_array[goal].distance);
            }
            else{
                printf("UNREACHABLE\n");
            }
        }
        else{
            printf("%d\n",attribute_array[goal].distance);
        }
    }

    #ifdef debug_input
        printf("N_events==%d\n",N_events);
        for(i=0;i<N_events;i++){
            //printf("events==%d events_times==%d\n",events_array[i],events_times[i]);

        }
    #endif // debug_input
    #ifdef debug_graph
        print_graph(graph);
    #endif // debug_graph
    return 0;
}
int main01(){/*test graph ds*/
    Graph*graph=NULL;
    graph=create_graph(10);
    /*edge只有0~9*/
    add_edge(graph,0,1);
    add_edge(graph,2,5);
    add_edge(graph,0,9);
    add_edge(graph,1,6);
    //print_graph(graph);
    BFS(graph,0);
    int i;
    for(i=0;i<10;i++){
        printf("%d %d %d\n",attribute_array[i].color\
                            ,attribute_array[i].distance\
                            /*,attribute_array[i].parent*/);
    }
}
int main02(){//test queue ds
    Queue*queue=create_queue(10);
    enqueue(queue,3);
    enqueue(queue,2);
    enqueue(queue,10);
    dequeue(queue);
    dequeue(queue);
    printf("%d\n",queue->array[queue->front]);
}
void BFS(Graph*graph,int start){
    int i;
    /*
    for(i=0;i<graph->num_of_vertex;i++){
        attribute_array[i].color=WHITE;
        attribute_array[i].distance=infinte;
        attribute_array[i].parent=NIL;
    }
    */
    attribute_array[start].color=GRAY;
    //attribute_array[start].parent=NIL;
    attribute_array[start].distance=0;

    Queue*queue=create_queue(max_vertex);
    enqueue(queue,start);
    int u,v;
    adjacency_node*ptr;
    while(!isEmpty(queue)){
        u=dequeue(queue);
        ptr=graph->list_array[u].head;
        while(ptr!=NULL){
            v=ptr->number;
            if(attribute_array[v].color==WHITE){
                attribute_array[v].color=GRAY;
                attribute_array[v].distance=\
                    attribute_array[u].distance+1;
                //attribute_array[v].parent=u;
                enqueue(queue,v);
            }
            ptr=ptr->next;
        }
        attribute_array[u].color=BLACK;
    }
}
void print_graph(Graph*graph){
    adjacency_node*ptr;
    int i;
    for(i=0;i<graph->num_of_vertex;i++){
        printf("adj_list of %d :",i);
        ptr=graph->list_array[i].head;
        while(ptr!=NULL){
            printf("->%d",ptr->number);
            ptr=ptr->next;
        }
        printf("\n");
    }
    return;
}
struct Graph* create_graph(int num_vertex){
     struct Graph* graph=(struct Graph*)\
        malloc(sizeof(struct Graph));
     graph->num_of_vertex=num_vertex;
     graph->list_array=(adjacency_list*)\
        malloc(num_vertex*sizeof(adjacency_list));
     int i;
     for(i=0;i<num_vertex;i++){
        graph->list_array[i].head=NULL;
     }
     return graph;
}
void add_edge(Graph*graph,int start,int end){
    struct adjacency_node*new_node=add_node(end);
    new_node->next=graph->list_array[start].head;
    graph->list_array[start].head=new_node;
}
struct adjacency_node*add_node(int num){
    adjacency_node* ptr_new_node=\
        (adjacency_node*)malloc(sizeof(adjacency_node));
    ptr_new_node->next=NULL;
    ptr_new_node->number=num;
    return ptr_new_node;
};

Queue*create_queue(unsigned int create_capacity){
    Queue*queue=(Queue*)malloc(sizeof(Queue));
    queue->capacity=create_capacity;
    queue->array=\
        (int*)malloc(queue->capacity*sizeof(int));
    queue->front=queue->size=0;
    queue->rear=queue->capacity-1;
    /*front在rear的右邊*/
    return queue;
}
void enqueue(Queue*queue,int item){
    if(isFull(queue)){
        printf("FULL\n");
        return;
    }
    queue->rear=(queue->rear+1)%queue->capacity;
    queue->array[queue->rear]=item;
    queue->size++;
}
int dequeue(Queue*queue){
    if(isEmpty(queue)){
        printf("Empty\n");
        return -2147483648;
    }
    int item=queue->array[queue->front];
    queue->front=(queue->front+1)%queue->capacity;
    queue->size--;
    return item;
}
int isFull(Queue*queue){
    return (queue->size==queue->capacity);
}
int isEmpty(Queue*queue){
    return (queue->size==0);
}

