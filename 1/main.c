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
void insert_after(struct Node*prev_node,char letter_to_add,struct Node**tail_ref);
void insert_tail(struct Node** head_ref,char letter_to_add);
void deleteNode(struct Node**head_ref,struct Node*del);
void Print_double_Linklist(struct Node*head);
void delete_whole_linklist(struct Node**head_ref);
int is_lower_case(char c);
void char_cover_selection(struct Node* cursor_left,struct Node* cursor_right,char letter_to_add,struct Node**tail_ref);
int main()
{
    struct Node*head=(struct Node*)malloc(sizeof(struct Node));
    head->next=NULL;
    head->prev=NULL;
    struct Node*tail=head;//tail一開始放在head上


    int selection_mode=0;

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
        struct Node *cursor_2=head;//用來select
        int cursor_left_or_right=0;//>0則cursor在右
        for(j=0;buf[j]!='\0';j++){
            if(is_lower_case(buf[j])){
                /*分成在selection_mode以及沒有在selection_mode兩種情況*/
                if(selection_mode==0){
                    /*預留一格head因此基本上只會用到insert_after*/
                    insert_after(cursor,buf[j],&tail);
                    cursor=cursor->next;
                }
                else if(selection_mode==1){
                    /*覆蓋兩個游標之間的內容,使用函式*/
                    //需要掌握cursor和cursor_2誰左誰右
                    if(cursor_left_or_right>0){//cursor在右
                        char_cover_selection(cursor_2,cursor,buf[j],&tail);
                        selection_mode=0;//exit selection_mode
                    }
                    else if(cursor_left_or_right<0){//cursor在左
                        char_cover_selection(cursor,cursor_2,buf[j],&tail);
                        selection_mode=0;//exit selection_mode
                    }
                    else if(cursor_left_or_right==0){//cursor重合
                        /*預留一格head因此基本上只會用到insert_after*/
                        insert_after(cursor,buf[j],&tail);
                        cursor=cursor->next;
                        selection_mode=0;//exit selection_mode
                    }
                }
            }
            else{//operation
                if(buf[j]=='H'){//向左一格
                    if(cursor!=head){
                        cursor=cursor->prev;
                        if(selection_mode==1){
                            cursor_left_or_right--;
                        }
                    }
                }
                else if(buf[j]=='L'){//向右一格
                    if(cursor!=tail){
                        cursor=cursor->next;
                        if(selection_mode==1){
                            cursor_left_or_right++;
                        }
                    }
                }
                else if(buf[j]=='V'){//切換selection mode
                    if(selection_mode==0){
                        selection_mode=1;
                        cursor_2=cursor;//把兩個游標重合
                        cursor_left_or_right=0;//歸零
                    }
                    else if(selection_mode==1){
                        selection_mode=0;
                    }
                }
            }
        }
        #ifdef test_output
        Print_double_Linklist(head->next);
        #endif // test_ouput

        //刪去整個鏈結串列
        delete_whole_linklist(&(head->next));
        tail=head;
    }

    return 0;
}
int main01(){
    struct Node*head=(struct Node*)malloc(sizeof(struct Node));
    head->next=NULL;
    head->prev=NULL;
    struct Node*tail=head;//tail一開始放在head上
    insert_after(head,'a',&tail);
    insert_after(head,'a',&tail);
    insert_after(head,'a',&tail);
    insert_after(head,'a',&tail);
    struct Node *PTR,*ptr=head->next->next;
    insert_after(ptr,'m',&tail);

    for(PTR=head->next;PTR!=tail;PTR=PTR->next){
        printf("%c\n",PTR->letter);
    }
    Print_double_Linklist(head->next);
    delete_whole_linklist(&head);
    if(tail==NULL&&head==NULL){
        printf("NULL");
    }
}
//加入tail在insert_after

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

void insert_after(struct Node*prev_node,char letter_to_add,struct Node**tail_ref){
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
    else{//newNode是新的tail
        *tail_ref=newNode;
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
void delete_whole_linklist(struct Node**head_ref){
    struct Node* current = *head_ref;
    struct Node* next;

    while (current!=NULL){
       next=current->next;
       free(current);
       current=next;
    }
    *head_ref = NULL;
}
void char_cover_selection(struct Node* cursor_left,struct Node* cursor_right,char letter_to_add,struct Node**tail_ref){
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->letter=letter_to_add;

    //接上四個指標
    cursor_left->next=newNode;
    newNode->prev=cursor_left;

    //右邊比較特別
    if(cursor_right==*tail_ref){
        newNode->next=NULL;
        *tail_ref=newNode;
    }
    else{
        newNode->next=(cursor_right->next);
        cursor_right->next->prev=newNode;
    }
}

