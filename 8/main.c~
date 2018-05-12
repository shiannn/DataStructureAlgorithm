#include <stdio.h>
#include <stdlib.h>

#define max_people 200010
#define max_length 12

//#define debug_input
//#define debug_decrease_heap

int extract_max();
void increase_heapify(int A[],int i);
void decrease_heapify(int A[],int i);
void exchange(int A[],int i,int largest);
int parent(int i);
int left(int i);
int right(int i);
int find(int x);
void myunion(int x,int y);

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
            if(ans>0){//防止已經沒有組別了
                if(NumOfPeopleInGroup[ans]>0){//防止回答空組別
                    printf("%s\n",student_names[ans]);
                }
            }
        }
    }

    return 0;
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
    if(l<=heap_size&&\
       NumOfPeopleInGroup[A[l]]>\
       NumOfPeopleInGroup[A[i]]){
        largest=l;
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
        }
    }
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

