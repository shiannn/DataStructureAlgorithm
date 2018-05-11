#include <stdio.h>
#include <stdlib.h>

#define max_people 200010
#define max_length 12

//#define debug_input
//#define debug_decrease_heap
#define debug_minId
#define debug_largest
char student_names[max_people][max_length];
int leader[max_people];
int NumOfPeopleInGroup[max_people];
int minId[max_people];
int position_in_heap[max_people];

int heap[max_people];
int heap_size,heap_capacity;

int main()
{
    int N_student,M_events;
    scanf("%d",&N_student);
    heap_capacity=N_student;
    heap_size=N_student;

    int i;
    for(i=1;i<=N_student;i++){
        scanf("%s",student_names[i]);
        leader[i]=i;
        /*剛開始大家都是自己的隊長*/
        NumOfPeopleInGroup[i]=1;
        /*一開始每組只有一個人*/
        minId[i]=i;
        /*每組最小id*/
        heap[i]=i;
        /*heap第i格就是第i個人*/
        /*人數都一樣 id由小到大*/
        position_in_heap[i]=i;
        /*第i個人在heap中第i個位置*/
    }

    scanf("%d",&M_events);
    #ifdef debug_input
        printf("%d\n",N_student);
        for(i=1;i<=N_student;i++){
            printf("%s\n",student_names[i]);
        }
        printf("%d\n",M_events);

    #endif // debug_input
    int type,group1,group2;
    int ans;
    for(i=0;i<M_events;i++){
        scanf("%d",&type);
        if(type==1){
            scanf("%d %d",&group1,&group2);
            /*合併union*/
            myunion(group1,group2);
        }
        else if(type==2){
            /*輸出最大組最小人name*/
            ans=extract_max();
            printf("%s\n",student_names[ans]);
        }
        #ifdef debug_input
            printf("%d\n",type);
            if(type==1){
                printf("%d %d\n",group1,group2);
            }
        #endif // debug_input
    }

    return 0;
}
int main11(){/*測試disjoint set*/
    int a;
    for(a=1;a<=10;a++){
        leader[a]=a;
    }
    myunion(3,7);
    myunion(2,5);
    myunion(4,6);
    myunion(10,2);
    for(a=1;a<=10;a++){
        printf("%d\n",find(a));
    }

}
int main22(){/*測試heap*/
    int arr[20]={-1,1,2,3,4,5,6,7};
    heap_size=7;
    int i;
    for(i=1;i<=7;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
    //increase_heapify(arr,4);
    //increase_heapify(arr,4);
    //decrease_heapify(arr,1);
    for(i=1;i<=7;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}
int main33(){/*測試extract max*/
    int i;
    heap_size=20;
    for(i=1;i<=20;i++){
        heap[i]=21-i;
    }
    printf("%d\n",extract_max());
    printf("%d\n",extract_max());
    printf("%d\n",extract_max());
    printf("%d\n",extract_max());
    printf("%d\n",extract_max());
}
int main44(){//測試用組內人數做heap
    int i;
    for(i=1;i<=10;i++){
        heap[i]=i;
    }
    heap_size=10;
    for(i=1;i<=10;i++){
        NumOfPeopleInGroup[i]=11*i-i*i;
    }
    for(i=1;i<=10;i++){
        printf("%d ",heap[i]);
    }
    printf("\n");
    //increase_heapify(heap,5);
    decrease_heapify(heap,3);
    //printf("minID of 5==%d\n",minId[5]);
    for(i=1;i<=10;i++){
        printf("%d ",heap[i]);
    }
}
int main55(){/*測試union和heap連動*/
    int i;
    for(i=1;i<=10;i++){
        minId[i]=i;
    }
    for(i=1;i<=10;i++){
        leader[i]=i;
    }
    for(i=1;i<=10;i++){
        position_in_heap[i]=i;
        NumOfPeopleInGroup[i]=1;
    }
    for(i=1;i<=10;i++){
        heap[i]=i;
    }
    heap_size=10;
    for(i=1;i<=10;i++){
        printf("%d ",heap[i]);
    }
    printf("\n");
    myunion(2,3);
    for(i=1;i<=10;i++){
        printf("%d ",leader[i]);
    }
    printf("\n");
    for(i=1;i<=10;i++){
        printf("%d ",heap[i]);
    }
    printf("\n");
}
int extract_max(){
    int ret;
    if(heap_size==0)return -1;
    if(heap_size==1){
        ret=heap[heap_size];
        heap_size--;
        return ret;
    }
    ret=heap[1];
    heap[1]=heap[heap_size];
    heap_size--;
    decrease_heapify(heap,1);
    return ret;
}
void increase_heapify(int A[],int i){
    int pos=i;
    while(pos!=1&&\
          NumOfPeopleInGroup[A[parent(pos)]]\
          <NumOfPeopleInGroup[A[pos]]){
        /*組內人數比上面的大就往上*/
        exchange(A,pos,parent(pos));
        pos=parent(pos);
    }
    while(pos!=1&&\
          minId[A[parent(pos)]]>minId[A[pos]]){
        /*組內最小id比上面小 就往上*/
        exchange(A,pos,parent(pos));
        pos=parent(pos);
    }
}
void decrease_heapify(int A[],int i){//人變少
    int l=left(i);
    int r=right(i);
    int largest=i;
    #ifdef debug_decrease_heap
        printf("l==%d r==%d i==%d\n",l,r,i);
        printf("heap_size==%d A[l]==%d A[i]==%d\n",heap_size,A[l],A[i]);
    #endif // debug_decrease_heap
    if(l<=heap_size&&\
       NumOfPeopleInGroup[A[l]]>\
       NumOfPeopleInGroup[A[i]]){
        #ifdef debug_decrease_heap
            printf("left big\n");
        #endif // debug_decrease_heap
        largest=l;
        //printf("here\n");
    }
    else if(l<=heap_size&&\
            NumOfPeopleInGroup[A[l]]<\
            NumOfPeopleInGroup[A[i]]){
        largest=i;
    }
    else if(l<=heap_size&&\
            NumOfPeopleInGroup[A[l]]==\
            NumOfPeopleInGroup[A[i]]){
        if(minId[A[l]]<minId[A[i]]){
            largest=l;
        }
        else if(minId[A[l]]>minId[A[i]]){
            largest=i;
        }
    }
    /*
    printf("large num peo==%d\n",NumOfPeopleInGroup[A[largest]]);
    printf("r==%d\n",r);
    printf("r num peo==%d\n",NumOfPeopleInGroup[A[r]]);
    */
    if(r<=heap_size&&\
       NumOfPeopleInGroup[A[r]]>\
       NumOfPeopleInGroup[A[largest]]){

        largest=r;
    }
    else if(r<=heap_size&&\
       NumOfPeopleInGroup[A[r]]==\
       NumOfPeopleInGroup[A[largest]]){
        if(minId[A[r]]<minId[A[largest]]){
            largest=r;
            //printf("here2\n");
        }
    }
    #ifdef debug_decrease_heap
        printf("i==%d largest==%d\n",i,largest);
    #endif // debug_decrease_heap
    if(largest!=i){
        exchange(A,i,largest);
        decrease_heapify(A,largest);
    }
}
void exchange(int A[],int i,int largest){
    int temp;
    /*交換position_in_heap*/
    temp=position_in_heap[A[largest]];
    position_in_heap[A[largest]]=\
    position_in_heap[A[i]];
    position_in_heap[A[i]]=temp;
    /*交換heap中的值*/
    temp=A[i];
    A[i]=A[largest];
    A[largest]=temp;

}
int parent(int i){
    return (i/2);
}
int left(int i){
    return (2*i);
}
int right(int i){
    return (2*i+1);
}
int find(int x){
    return x==leader[x]? x:(leader[x]=find(leader[x]));
}
void myunion(int x,int y){
    /*組別id比較小的人當老大*/
    int x_leader=find(x),y_leader=find(y);
    if(x_leader==y_leader)return;
    if(x_leader<y_leader){
        /*x_leader這團人數增加*/
        NumOfPeopleInGroup[x_leader]\
        +=NumOfPeopleInGroup[y_leader];
        /*維護heap*/
        increase_heapify(heap\
                ,position_in_heap[x_leader]);
        /*y的人數歸零*/
        NumOfPeopleInGroup[y_leader]=0;
        decrease_heapify(heap\
                ,position_in_heap[y_leader]);
        /*投靠*/
        leader[y]=x_leader;


        return;
    }
    else if(y_leader<x_leader){
        /*y_leader這團人數增加*/
        NumOfPeopleInGroup[y_leader]\
        +=NumOfPeopleInGroup[x_leader];
        /*維護heap*/
        increase_heapify(heap\
                ,position_in_heap[y_leader]);
        /*x的人數歸零*/
        NumOfPeopleInGroup[x_leader]=0;
        /*維護heap*/
        decrease_heapify(heap\
                ,position_in_heap[x_leader]);

        /*投靠*/
        leader[x]=y_leader;


        return;
    }
}

