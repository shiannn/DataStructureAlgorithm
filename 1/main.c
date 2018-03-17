#include <stdio.h>
#include <stdlib.h>
#define max 1000010

//#define debug_input
//#define into_linklist
#define test_output

struct Node{
    char letter;
    struct Node *next;
    struct Node *prev;
};

char buf[max];

void insert_head(struct Node**head_ref,char letter_to_add);
void insert_after(struct Node*prev_node,char letter_to_add);
void insert_tail(struct Node** head_ref,char letter_to_add);
void deleteNode(struct Node**head_ref,struct Node*del);
void Print_double_Linklist(struct Node*head);
int is_lower_case(char c);
int main()
{
    struct Node*head=(struct Node*)malloc(sizeof(struct Node));
    head->next=NULL;
    head->prev=NULL;
    struct Node*tail=(struct Node*)malloc(sizeof(struct Node));
    tail->next=NULL;
    tail->prev=NULL;

    int T_testcases;
    scanf("%d",&T_testcases);
    int i,j;
    for(i=0;i<T_testcases;i++){
        scanf("%s",buf);
        #ifdef debug_input
        printf("%s\n",buf);
        #endif // debug_input
        //input ok

        #ifdef into_linklist
        //遍歷buf將字元一個個插入double_linklist
        for(j=0;buf[j]!='\0';j++){
            insert_tail(&head,buf[j]);
        }

        Print_double_Linklist(head);
        #endif // into_linklist
        //head->next是起始字元
        struct Node *cursor=head;
        for(j=0;buf[j]!='\0';j++){
            if(is_lower_case(buf[j])){
                /*預留一格head因此基本上只會用到insert_after*/
                insert_after(cursor,buf[j]);
                cursor=cursor->next;
            }
            else{//operation
                if(buf[j]=='H'){//向左一格
                    if(cursor!=head){
                        cursor=cursor->prev;
                    }
                }
                else if(buf[j]=='L'){//向右一格
                    if(cursor->next!=NULL){
                        cursor=cursor->next;
                    }
                }
            }
        }
        #ifdef test_output
        Print_double_Linklist(head->next);
        #endif // test_ouput

        struct Node *ptr=head;
        while(ptr!=NULL){
            deleteNode(&head,ptr);
            ptr=head;//透過傳參考，新的head
        }

    }

    return 0;
}
int main02(){
    struct Node*head=NULL;
    insert_head(&head,'b');
    insert_head(&head,'b');
    insert_head(&head,'b');
    insert_head(&head,'b');
    insert_tail(&head,'c');
    struct Node *ptr=head->next->next;
    insert_after(ptr,'m');

    Print_double_Linklist(head);
}

//傳入head的位址可以直接在函式內部修改head的值
void insert_head(struct Node**head_ref,char letter_to_add){
    struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
    newNode->letter=letter_to_add;

    if(*head_ref==NULL){//head_ref目前是空的
        newNode->next=*head_ref;//(NULL)
        *head_ref=newNode;
        newNode->prev=NULL;
        return;
    }
    //head_ref不是NULL 鏈結串列有東西
    //改待插入節點的prev,next以及前一個的next,後一個的prev
    newNode->next=*head_ref;
    //不會有人在newNode之前
    newNode->prev=NULL;
    newNode->next->prev=newNode;

    //因為是插入在第一位，所以要改head
    *head_ref=newNode;
    return;
}

void insert_after(struct Node*prev_node,char letter_to_add){
    if(prev_node==NULL){
        printf("can not insert after NULL");
        return;
    }
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->letter=letter_to_add;

    //填入四個指標
    newNode->next=prev_node->next;
    prev_node->next=newNode;
    newNode->prev=prev_node;
    if(newNode->next!=NULL){
        newNode->next->prev=newNode;
    }
}

void insert_tail(struct Node** head_ref,char letter_to_add){
    struct Node*newNode=(struct Node*)malloc(sizeof(struct Node));
    newNode->letter=letter_to_add;

    if(*head_ref==NULL){//如果鏈結串列是空的
        newNode->next=NULL;
        newNode->prev=NULL;
        *head_ref=newNode;
        return;
    }
    //如果鏈結串列已經有節點
    struct Node*last=*head_ref;
    while(last->next!=NULL){
        last=last->next;
    }
    //找出最後一個節點last
    newNode->next=NULL;
    last->next=newNode;
    newNode->prev=last;

    return;
}

void Print_double_Linklist(struct Node*head){
    //printf("forward\n");
    struct Node *last=head,*ptr=head;
    while(ptr!=NULL){
        printf("%c",ptr->letter);
        //last=ptr;
        ptr=ptr->next;
    }
    printf("\n");
    /*
    printf("\n");
    //得到last
    printf("backward\n");
    ptr=last;
    while(ptr!=NULL){
        printf("%c ",ptr->letter);
        last=ptr;
        ptr=ptr->prev;
    }
    printf("\n");
    */
}
void deleteNode(struct Node**head_ref,struct Node*del){
    if(*head_ref==NULL||del==NULL){
        printf("delete fail\n");
        return;
    }
    //有東西可以刪
    //要處理del左邊的next和右邊的prev
    if(del->next!=NULL){
        del->next->prev=del->prev;
    }
    if(del->prev!=NULL){
        del->prev->next=del->next;
    }
    if(del==*head_ref){//如果要刪的節點就是head
        *head_ref=del->next;
    }
    free(del);
    return;
}

int is_lower_case(char c){
    if(c>=97&&c<=122){
        return 1;
    }
    return 0;
}

