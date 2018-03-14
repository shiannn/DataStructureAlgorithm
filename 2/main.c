#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define max 10010
#define DATA char
//#define debug_input
//#define debug_process

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

int main()
{
    char tmp;
    char array[max];
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
    for(i=0;array[i]!='\0';i++){
        while(!IsEmptyStack(ptrStack)&&remove_times>0
              &&char_to_int(array[i])<char_to_int(ptrStack->array[ptrStack->top])){
            Pop(ptrStack);
            remove_times--;
        }
        Push(ptrStack,array[i]);
    }

    //Q:已經掃完一遍，但是remove_times卻還有剩?
    //A:取最右邊的total-remove個字就好(因為他們整個一定是遞增的)
    for(i=0;i<total-remove;i++){
        printf("%c",ptrStack->array[i]);
    }

    return 0;
}
