/*考慮selection mode 取0位數？*/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define max 1000010
//#define debug_left_and_right
//#define debug_tail
struct alpha{
    struct alpha* next;
    struct alpha* pre;
    char the_alpha;
};
//string 是 node
typedef struct alpha string;
void printout(string ** print1,string** now){
    /*從print1印到NULL*/
 string *print2=*print1;
 printf("******test*******\n");
 for (; (print2)!=NULL;(print2)=(print2)->next ) {
 printf("%c",(print2)->the_alpha);
 }
 printf("   now:%c",(*now)->the_alpha);
 printf("\n*****************\n");
 }

/*char tar[1000001];*/
int main(int argc, const char * argv[]) {
    int times;
    scanf("%d",&times);
    int i;
    for (i=0; i<times; i++) {
        char tar[max];
        scanf("%s",tar);
        string *head=NULL;
        string *now=head;
        string *select_prob1=NULL;
        string *select_prob2=NULL;
        string *clipboard_head=NULL;
        string *clipboard_tail=NULL;
        string *tail=head;
        head=(string*)malloc(sizeof(string));
        head->next=NULL;
        head->pre=NULL;
        head->the_alpha='!';
        now=head;
        int count_of_selection_mode=0;
        int mode=1;/* 1 正常插入 0 selection mode */
        unsigned long int len=strlen(tar);
        int j;
        for (j=0;j<len;j++){
            if (islower(tar[j])) {
                if (mode){//count_of_selection_mode==0??
                    if (now->next==NULL) {
                        string *tmp=NULL;
                        tmp=(string*)malloc(sizeof(string));
                        tmp->next=NULL;
                        tmp->pre=now;
                        tmp->the_alpha=tar[j];
                        now->next=tmp;
                        now=now->next;
                        tail=now;
                    }
                    else{
                        string *tmp=NULL;
                        tmp=(string*)malloc(sizeof(string));
                        tmp->next=now->next;
                        tmp->pre=now;
                        tmp->the_alpha=tar[j];
                        now->next->pre=tmp;
                        now->next=tmp;
                        now=now->next;
                    }
                    mode=1;//prob==prob
                }else{
                    mode=(!mode);
                    string *tmp=NULL;

                    tmp=(string*)malloc(sizeof(string));
                    tmp->pre=NULL;
                    tmp->next=NULL;
                    tmp->the_alpha=tar[j];
                    /***********************/
                    if (select_prob2==select_prob1) {
                        tmp->pre=select_prob1;
                        tmp->next=select_prob1->next;
                        if (select_prob1->next!=NULL) {
                            select_prob1->next->pre=tmp;
                        }
                        select_prob1->next=tmp;
                        now=tmp;
                        if (now->next==NULL) {
                            tail=now;
                        }
                        select_prob1=select_prob2=NULL;
                        continue;
                    }
                    /***********************/
                    if (count_of_selection_mode<0) {
                        string *swp=select_prob1;
                        select_prob1=select_prob2;
                        select_prob2=swp;
                    }

                    string *cleaner;
                    cleaner=select_prob1->next;
                    //////check here check here
                    if (select_prob1==head) {

                        tmp->pre=head;
                        tmp->next=select_prob2->next;
                        head->next=tmp;
                        if (select_prob2->next!=NULL){
                            select_prob2->next->pre=tmp;
                        }

                    }
                    else{

                        tmp->pre=select_prob1;
                        tmp->next=select_prob2->next;
                        select_prob1->next=tmp;
                        if (select_prob2->next!=NULL) {
                            select_prob2->next->pre=tmp;
                        }
                    }
                    ////////////selectprob2==NULL??
                    /*
                    while (cleaner!=select_prob2) {
                        cleaner=cleaner->next;
                        free(cleaner->pre);
                    }
                    */
                    /////////////
                    //free(select_prob2);
                    now=tmp;
                    if (now->next==NULL) {
                        tail=now;
                    }
                    select_prob2=select_prob1=NULL;
                }
            }else{
                switch (tar[j]){
                    case 'H':
                        if (now->pre!=NULL) {
                            now=now->pre;
                            if (!mode) {//反白
                                //紀錄左右
                                count_of_selection_mode--;
                                select_prob2=now;
                                if (select_prob2==select_prob1) {
                                    count_of_selection_mode=0;
                                }
                            }
                        }


                        break;
                    case 'L':
                        if (now->next!=NULL) {
                            now=now->next;
                            if (!mode) {
                                count_of_selection_mode++;
                                select_prob2=now;
                                if (select_prob1==select_prob2) {
                                    count_of_selection_mode=0;
                                }
                            }
                        }


                        break;
                    case 'I':
                        now=head;
                        if (!mode) {
                            select_prob2=head;
                            if (select_prob2==select_prob1) {
                                count_of_selection_mode=0;
                            }else count_of_selection_mode=(-100000001);
                        }

                        break;
                    case 'A':
                        now=tail;
                        if (!mode) {
                            select_prob2=now;
                            if (select_prob2==select_prob1) {
                                count_of_selection_mode=0;
                            }else count_of_selection_mode=100000001;
                        }
                        break;
                    case 'V':
                        if (!mode) {
                            mode=1;
                        }else{
                            mode=0;
                            select_prob2=select_prob1=now;
                        }
                        count_of_selection_mode=0;
                        break;
                    case 'D':
                        if (!mode&&select_prob1!=select_prob2) {
                            mode=(!mode);
                            if (count_of_selection_mode==0) {
                                break;
                            }
                            if (count_of_selection_mode<0) {
                                string* swap=select_prob1;
                                select_prob1=select_prob2;
                                select_prob2=swap;
                            }
                            /*總是讓select_prob2在右*/
                            clipboard_head=select_prob1->next;
                            clipboard_tail=select_prob2;
                            select_prob1->next=select_prob2->next;
                            if(select_prob2->next!=NULL)
                                select_prob2->next->pre=select_prob1;
                            /////
                            now=select_prob1;
                            ////herehereherehere
                            if (now->next==NULL) {
                                tail=now;
                            }
                            select_prob1=select_prob2=NULL;
                        }

                        break;
                    case 'P':
                        /*剪貼簿沒東西*/
                        if (clipboard_head==NULL) {
                            if (mode) {
                                break;
                            }else{
                                mode=(!mode);
                            }
                            /*在選取模式內*/
                            if (count_of_selection_mode==0) {
                                break;
                            }
                            /*真的有選取到文字*/
                            if (count_of_selection_mode<0) {
                                string *swap=select_prob1;
                                select_prob1=select_prob2;
                                select_prob2=swap;
                            }
                            /*始終讓select_prob2在右*/
                            select_prob1->next=select_prob2->next;
                            if (select_prob2->next!=NULL) {
                                select_prob2->next->pre=select_prob1;
                            }
                            else{
                                tail=select_prob1;
                            }
                            //沒有維護tail

                            break;
                        }
                        /*不是用空白 剪貼簿有東西*/
                        if (!mode) {
                            /*selection mode*/
                            /*有選到某一段*/
                            mode=(!mode);
                            if (select_prob2==select_prob1) {
                                clipboard_tail->next=select_prob1->next;
                                if (select_prob1->next!=NULL) {
                                    select_prob1->next->pre=clipboard_tail;
                                }
                                select_prob1->next=clipboard_head;
                                clipboard_head->pre=select_prob1;
                                now=clipboard_tail;
                                if (now->next==NULL) {
                                    tail=now;
                                }
                                break;

                            }
                            string *cleaner;
                            if (count_of_selection_mode<0) {
                                string *swap=select_prob1;
                                select_prob1=select_prob2;
                                select_prob2=swap;
                            }
                            cleaner=select_prob1->next;
                            clipboard_head->pre=select_prob1;
                            clipboard_tail->next=select_prob2->next;
                            /**here**/
                            select_prob1->next=clipboard_head;
                            if (select_prob2->next!=NULL) {
                                select_prob2->next->pre=clipboard_tail;
                            }
                            /*cleaning prob*/
                           //////////////////////////////////////
                            /*
                            while (cleaner!=select_prob2) {
                                cleaner=cleaner->next;
                                free(cleaner->pre);
                            }
                            */
                            //////////////////////////////////////
                        }else{
                            /*沒有選到selection*/
                            /******/
                            if (now->next==NULL) {
                                now->next=clipboard_head;
                                clipboard_head->pre=now;
                                clipboard_tail->next=NULL;
                                now=clipboard_tail;
                            }else{
                            /******/
                                now->next->pre=clipboard_tail;
                                clipboard_tail->next=now->next;
                                now->next=clipboard_head;
                                clipboard_head->pre=now;

                            }
                        }
                        now=clipboard_tail;
                        if (now->next==NULL) {
                            tail=now;
                        }
                        clipboard_tail=NULL;
                        clipboard_head=NULL;
                        break;
                }
                #ifdef debug_tail
                    printf("tail = %c\n",tail->the_alpha);
                #endif // debug_tail
            }
           //     printout(&head, &now);
           #ifdef debug_left_and_right
                printf("mode==%d\n",mode);
                printf("%d\n",count_of_selection_mode);
           #endif // debug_left_and_right

        }
        for(now=head->next;now!=NULL;now=now->next){
            //free(now->pre);
            printf("%c",now->the_alpha);
        }

        printf("\n");
    }
    return 0;
}
/*
333
VaHVLDkp
xyzwHHVLDbLLLmP
aaaaHHVLDbLLLmP
aaaIVLLLDcccbbVHHP
fffHHHkkVIDgLP
fffHHHkkVADgLP
aaaIVIDAoP
aaaVHHHDbbbHVHLP
*/
/*ans
 kp
 xybwmz
 aabama
 cccaaa
 gfkkff
 kkgfff
 o
 bbaaab
*/



