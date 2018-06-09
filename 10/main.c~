#include <stdio.h>
#include <stdlib.h>
#define max_input 100010

//#define debug_input
//#define debug_graph
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

struct house_vertex{
    int height;
    int num;
};
typedef struct house_vertex house_vertex;

void swap(house_vertex *a, house_vertex *b);
int Partition(house_vertex *arr, int front, int end);
void QuickSort(house_vertex *arr, int front, int end);

house_vertex input[max_input];
house_vertex sorting[max_input];

int main()
{
    int N,M;
    int i,j,k=0;
    scanf("%d %d",&N,&M);
    for(i=0;i<N;i++){
        for(j=0;j<M;j++){
            scanf("%d",&input[k].height);
            input[k].num=k+1;
            k++;
        }
    }
    #ifdef debug_input
        k=0;
        for(i=0;i<N;i++){
            for(j=0;j<M;j++){
                printf("%d %d ",input[k].height,input[k].num);
                k++;
            }
            printf("\n");
        }
    #endif // debug_input
    Graph*graph=create_graph(max_input);
    for(i=0;i<N;i++){
        for(j=0;j<M;j++){
            sorting[j]=input[M*i+j];
        }
        /*sorting一列共M個元素*/
        QuickSort(sorting,0,M-1);
        for(j=0;j<M-1;j++){
            add_edge(graph,sorting[j].num,sorting[j+1].num);
        }
    }
    for(j=0;j<M;j++){
        for(i=0;i<N;i++){
            sorting[i]=input[M*i+j];
        }
        /*sorting 一行共N個元素*/
        QuickSort(sorting,0,N);
        for(i=0;i<N-1;i++){
            add_edge(graph,sorting[i].num,sorting[i+1].num);
        }
    }
    #ifdef debug_graph
        print_graph(graph);
    #endif // debug_graph
    return 0;
}
void swap(house_vertex *a, house_vertex *b){
    house_vertex temp = *a;
    *a = *b;
    *b = temp;
}
int Partition(house_vertex *arr, int front, int end){
    int pivot = arr[end].height;
    int i = front -1;
    int j;
    for (j = front; j < end; j++) {
        if (arr[j].height < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    i++;
    swap(&arr[i], &arr[end]);
    return i;
}
void QuickSort(house_vertex *arr, int front, int end){
    if (front < end) {
        int pivot = Partition(arr, front, end);
        QuickSort(arr, front, pivot - 1);
        QuickSort(arr, pivot + 1, end);
    }
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

