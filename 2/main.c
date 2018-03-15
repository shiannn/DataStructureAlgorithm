//參考http://blog.csdn.net/qq508618087/article/details/52584133
//參考http://morris821028.github.io/2015/06/26/zj-b415/
//與助教王行健討論
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define max 100000005
#define DATA char
//#define debug_input
//#define debug_process
//#define check

struct ArrayStack{
    int top;
    int capacity;
    DATA*array;
};

struct ArrayStack* CreateStack(){
    struct ArrayStack*S=malloc(sizeof(struct ArrayStack));
    if(!S)return NULL;
    S->capacity=max;
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

int char_to_int(char c){
    return (c-'0');
}

char array[max];
int main()
{
    char tmp;

    int remove;
    scanf("%s",array);
    scanf("%d",&remove);
    int total=strlen(array);
    #ifdef debug_input
        printf("%s\n%d\n%d\n",array,remove,total);
    #endif // debug_input

    //造一個stack
    struct ArrayStack* ptrStack=CreateStack();
    assert(ptrStack!=NULL);


    int i;
    int remove_times=remove;

    //先找出首位
    char first=array[0];
    int pos_of_first=0;
    for(i=0;i<remove_times+1;i++){//0~remove_times都有可能當首位
        if(array[i]!='0'){
            if(char_to_int(array[i])<char_to_int(first)){
                first=array[i];
                pos_of_first=i;
            }
        }
    }
    #ifdef check
        printf("get1\n");
        printf("%c\n%d\n",first,pos_of_first);
    #endif // check

    //得到首位字元first和它的位置pos_of_first
    remove_times=remove_times-pos_of_first;//用在首位的remove
    //首位先不入stack

    #ifdef check
        printf("%d\n",remove_times);
    #endif

    for(i=pos_of_first+1;array[i]!='\0';i++){
        while(!IsEmptyStack(ptrStack)&&remove_times>0
              &&char_to_int(array[i])<char_to_int(ptrStack->array[ptrStack->top])){
            remove_times--;
            Pop(ptrStack);
        }
        Push(ptrStack,array[i]);
    }

    #ifdef check
        printf("get2\n");
    #endif

    //Q:已經掃完一遍，但是remove_times卻還有剩?
    //A:取最右邊的total-remove個字就好(因為他們整個一定是遞增的)

    //printf("%c",first);
    putchar(first);
    ptrStack->array[total-remove-1]='\0';
    puts(ptrStack->array);
    //printf("%s",ptrStack->array);
    /*
    for(i=0;i<total-remove-1;i++){
        printf("%c",ptrStack->array[i]);
    }
    */

    return 0;
}
