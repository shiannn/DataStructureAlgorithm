#include <stdio.h>
#include <stdlib.h>

#define max_events 52
#define max_vertex 600000
#define WHITE 0
#define GRAY 1
#define BLACK 2

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


int Events[max_events];
int distance[max_vertex];
int color[max_vertex];
int main()
{
    int N_events;
    scanf("%d",&N_events);
    int i,Events_times;
    for(i=0;i<N_events;i++){
        //scanf("%d %d",&events_array[i],&events_times[i]);
        scanf("%d %d",&Events[i],&Events_times);
        #ifdef debug_input
            printf("%d %d\n",Events,Events_times);
        #endif // debug_input
    }

    Queue *queue=create_queue(max_vertex);
    distance[0]=0;
    color[0]=GRAY;
    enqueue(queue,0);
    int u,v;
    while(!isEmpty(queue)){
        u=dequeue(queue);
        for(i=0;i<N_events;i++){
            v=u^Events[i];
            if(color[v]==WHITE){
                distance[v]=distance[u]+1;
                color[v]=GRAY;
                enqueue(queue,v);
            }
        }
        color[u]=BLACK;
    }

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
        if(distance[goal]==0){
            if(goal==0){
                printf("%d\n",distance[goal]);
            }
            else{
                printf("UNREACHABLE\n");
            }
        }
        else{
            printf("%d\n",distance[goal]);
        }
    }
    return 0;
}

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
/*
2
5 2
4 1
3
0 5
1 0
1 2
*/

