#include <stdio.h>
#include <stdlib.h>
#define max_input 100010
#define DATA int

//#define debug_input
//#define debug_graph
//#define debug_stack
//#define debug_update
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

void mergeSort(house_vertex *arr,int l,int r);
void merge(house_vertex*arr,int l,int m,int r);

struct ArrayStack{
    int top;
    int capacity;
    DATA*array;
};
struct ArrayStack* CreateStack();
int IsEmptyStack(struct ArrayStack *S);
int IsFullStack(struct ArrayStack *S);
void Push(struct ArrayStack*S,DATA data);
DATA Pop(struct ArrayStack*S);

void topology_sort(Graph*graph,int visit_array[],struct ArrayStack*ptrStack,int start);

house_vertex input[max_input];
house_vertex sorting[max_input];
int visit[max_input];

struct distance_and_repeat{
    int distance;
    int repeat;
};
typedef struct distance_and_repeat distance_and_repeat;
distance_and_repeat array[max_input]={0,0};

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
    unsigned int height_kind=0;
    if(N==1){
        mergeSort(input,0,M-1);
        for(k=0;k<=M-2;k++){
            if(input[k].height!=input[k+1].height){
                height_kind++;
            }
        }
        height_kind++;
        printf("%u\n",height_kind);
        return 0;
    }
    else{
        if(M==1){
            mergeSort(input,0,N-1);
            for(k=0;k<=N-2;k++){
                if(input[k].height!=input[k+1].height){
                    height_kind++;
                }
            }
            height_kind++;
            printf("%u\n",height_kind);
            return 0;
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
        QuickSort(sorting,0,N-1);
        for(i=0;i<N-1;i++){
            add_edge(graph,sorting[i].num,sorting[i+1].num);
        }
    }
    #ifdef debug_graph
        print_graph(graph);
    #endif // debug_graph

    struct ArrayStack*ptr_stack=CreateStack();
    for(i=1;i<=N*M;i++){
        if(visit[i]==0){
            topology_sort(graph,visit,ptr_stack,i);
        }
    }
    #ifdef debug_stack
        while(!IsEmptyStack(ptr_stack)){
            printf("%d\n",Pop(ptr_stack));
        }
    #endif // debug_stack
    //int distance[max_input]={0};
    while(!IsEmptyStack(ptr_stack)){
        int start_point=Pop(ptr_stack);
        /*將其周圍的點距離更新為更長*/
        adjacency_node*ptr=graph->list_array[start_point].head;
        while(ptr!=NULL){
            #ifdef debug_update
                printf("start == %d start_point_dis==%d adj_point==%d adj_point_dis==%d\n",start_point,distance[start_point],ptr->number,distance[ptr->number]);

            #endif // debug_update
            if(input[start_point-1].height==input[ptr->number-1].height){
                if((array[start_point].distance)>(array[ptr->number].distance)){//可以更新
                    array[ptr->number].distance=array[start_point].distance;
                }
                //不能更新 維持原樣
            }
            else{
                if((array[start_point].distance)+1>(array[ptr->number].distance)){
                    array[ptr->number].distance=array[start_point].distance+1;
                    //array[ptr->number].repeat=array[start_point].repeat;
                    /*
                    if(input[start_point-1].height==input[ptr->number-1].height){//房高一樣就重複
                        array[ptr->number].repeat++;

                    }
                    */
                }
            }
            ptr=ptr->next;
        }
    }
    int max_path=0;
    for(i=1;i<=N*M;i++){
        if(array[i].distance>max_path){
            max_path=array[i].distance;
        }
    }
    printf("%d\n",max_path+1);
    return 0;
}
void topology_sort(Graph*graph,int visit_array[],struct ArrayStack*ptrStack,int start){
    visit_array[start]=1;
    adjacency_node*ptr;
    for(ptr=graph->list_array[start].head;ptr!=NULL;ptr=ptr->next){
        if(visit_array[ptr->number]==0){
            topology_sort(graph,visit_array,ptrStack,ptr->number);
        }
    }
    Push(ptrStack,start);
}
void merge(house_vertex*arr,int l,int m,int r){
    int i,j,k;
    int n1=m-l+1;
    int n2=r-m;

    int *L=(int*)malloc(n1*sizeof(int));
    int *R=(int*)malloc(n2*sizeof(int));
    for (i=0;i<n1;i++)
        L[i]=arr[l+i].height;
    for (j =0;j<n2;j++)
        R[j]=arr[m+1+j].height;
    i = 0;
    j = 0;
    k = l;
    while (i<n1&&j<n2)
    {
        if (L[i]<=R[j])
        {
            arr[k].height=L[i];
            i++;
        }
        else
        {
            arr[k].height=R[j];
            j++;
        }
        k++;
    }
    while (i<n1)
    {
        arr[k].height=L[i];
        i++;
        k++;
    }
    while (j<n2)
    {
        arr[k].height=R[j];
        j++;
        k++;
    }
}
void mergeSort(house_vertex *arr,int l,int r){
    if(l<r){
        int m=l+(r-l)/2;

        mergeSort(arr,l,m);
        mergeSort(arr,m+1,r);
        merge(arr,l,m,r);
    }
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

struct ArrayStack* CreateStack(){
    struct ArrayStack*S=malloc(sizeof(struct ArrayStack));
    if(!S)return NULL;
    S->capacity=max_input;
    S->top=-1;
    S->array=(DATA *)malloc(S->capacity*sizeof(DATA));
    if(!S->array)return NULL;
    return S;
};

int IsEmptyStack(struct ArrayStack *S){
    return (S->top==-1);
}

int IsFullStack(struct ArrayStack *S){
    return (S->top==S->capacity-1);
}

void Push(struct ArrayStack*S,DATA data){
    if(IsFullStack(S))
        printf("Stack Overflow");
    else
        S->array[++S->top]=data;
}

DATA Pop(struct ArrayStack*S){
    if(IsEmptyStack(S)){
        printf("Stack is Empty");
        return 0;
    }
    else
        return (S->array[S->top--]);
}
/*
10 1
12
21
15
3
2
6
50
78
9
30
*/
