#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_event 100010
#define max_length 70
#define branch 2

//#define debug_input
char events_to_be_process[max_length];
char events_64bits[max_length];
char oper_events[max_length];

void preprocess_string(char events_64bits[],const char events_to_be_process[]);

struct trie_node{
    int value;/*記錄這個節點是第幾個字的結尾*/
    struct trie_node*children[branch];
};
typedef struct trie_node trie_node;

struct trie{
    int count;/*全部共有幾個字在trie裡面*/
    trie_node*root;
};
typedef struct trie trie;

void delete_string(trie*Trie,char string[]);
int delete_helper(trie_node*Trie_Node,char string[],int level,int len);
void FREE(trie_node*Trie_Node);
int leaf_node(trie_node*Trie_Node);
int can_be_free(trie_node*Trie_Node);
void insert(trie*Trie,char string[]);
void query(trie*Trie,char string[]);
int search(trie*Trie,char string[]);
trie_node*get_node(void);
void initialize(trie *ptr_for_trie);
void preprocess_string(char events_64bits[],const char events_to_be_process[]);
int char_bits_to_int_bits(char a);
int main()
{
    trie TRIE;
    initialize(&TRIE);

    int N_initial_events;
    scanf("%d",&N_initial_events);
    int length,num_of_zero;
    int i;
    for(i=0;i<N_initial_events;i++){
        scanf("%s",events_to_be_process);
        preprocess_string(events_64bits,events_to_be_process);
        #ifdef debug_input
            printf("%s\n",events_to_be_process);
            printf("%s\n",events_64bits);
        #endif // debug_input
        /*補上0後加入trie*/

        insert(&TRIE,events_64bits);
    }
    int M_operations;
    scanf("%d",&M_operations);
    char op[5];
    int j,k;
    for(j=1;j<=M_operations;j++){
        scanf("%s %s",op,oper_events);

        preprocess_string(events_64bits,oper_events);

        if(op[0]=='U'){
            insert(&TRIE,events_64bits);
        }
        else if(op[0]=='D'){
            delete_string(&TRIE,events_64bits);
        }
        else if(op[0]=='Q'){
            query(&TRIE,events_64bits);
        }
    }

    return 0;
}

void query(trie*Trie,char string[]){
    int start=-1;
    int level;
    int length=strlen(string);
    int zero_or_one;
    trie_node*ptr;

    ptr=Trie->root;
    for(level=0;level<length;level++){
        zero_or_one=char_bits_to_int_bits(string[level]);
        /*string在該格是1還是0*/
        if(zero_or_one==1){

            //printf("0");
            if(ptr->children[0]){
                /*走TRIE中0那一條*/
                //answer[level]='0';
                ptr=ptr->children[0];
                //printf("0");
                if(start==1){
                    printf("0");
                }
            }
            else{
                if(start==-1){
                    start=1;
                }
                /*走1那一條*/
                //answer[level]='1';
                ptr=ptr->children[1];
                //printf("1");
                if(start==1){
                    printf("1");
                }
            }
        }
        else if(zero_or_one==0){
            //printf("1");
            if(ptr->children[1]){
                if(start==-1){
                    start=1;
                }
                /*走TRIE中1那一條*/
                //answer[level]='1';
                ptr=ptr->children[1];
                //printf("1");
                if(start==1){
                    printf("1");
                }
            }
            else{
                /*走0那一條*/
                //answer[level]='0';
                ptr=ptr->children[0];
                //printf("0");
                if(start==1){
                    printf("0");
                }
            }
        }
    }
    printf("\n");
}
int search(trie*Trie,char string[]){
    int level;
    int length=strlen(string);
    int zero_or_one;
    trie_node*ptr;

    ptr=Trie->root;

    for(level=0;level<length;level++){
        zero_or_one=char_bits_to_int_bits(string[level]);
        if(!ptr->children[zero_or_one]){
            return 0;
        }
        ptr=ptr->children[zero_or_one];
    }
    return (0!=ptr&&ptr->value);
}
void delete_string(trie*Trie,char string[]){
    int len=strlen(string);
    if(len>0){
        delete_helper(Trie->root,string,0,len);
    }
}
int delete_helper(trie_node*Trie_Node,char string[],int level,int len){
    if(Trie_Node){
        if(level==len){
            if(Trie_Node->value){
                /*不再是某個字的最後位*/
                Trie_Node->value=0;
                /*如果沒子節點 */
                if(can_be_free(Trie_Node)){
                    return 1;
                }
                return 0;
            }
        }
        else{
            int zero_or_one=char_bits_to_int_bits(string[level]);
            if(delete_helper(Trie_Node->children[zero_or_one],string,level+1,len)){
                FREE(Trie_Node->children[zero_or_one]);
                /*往回傳，遇到分支或是另外一個字的結尾後就不能再free了*/
                return (!leaf_node(Trie_Node)&&can_be_free(Trie_Node));
            }
        }
    }
    return 0;
}
void FREE(trie_node*Trie_Node){
    free(Trie_Node);
    Trie_Node=NULL;
}
int leaf_node(trie_node*Trie_Node){
    return (Trie_Node->value != 0);
}
int can_be_free(trie_node*Trie_Node){
    /*判斷是否完全沒有子節點*/
    int i;
    for(i=0;i<2;i++){
        if(Trie_Node->children[i]){
            return 0;
        }
    }
    return 1;
}
void insert(trie*Trie,char string[]){
    /*添加string到trie裡面*/
    int level;//隨著字元數慢慢往下加進trie裡面
    int length=strlen(string);
    int zero_or_one;

    Trie->count++;
    struct trie_node* ptr=Trie->root;

    for(level=0;level<length;level++){
        zero_or_one=char_bits_to_int_bits(string[level]);
        //printf("%d\n",zero_or_one);
        if(ptr->children[zero_or_one]){
            //printf("here\n");
            ptr=ptr->children[zero_or_one];
        }
        else{
            ptr->children[zero_or_one]=get_node();
            ptr=ptr->children[zero_or_one];
        }
    }

    /*記下這是第幾個字*/
    /*同時標為這是某字的結尾*/
    ptr->value=Trie->count;

}

trie_node*get_node(void){
    trie_node*ptr=NULL;
    ptr=(trie_node*)malloc(sizeof(trie_node));
    if(ptr){/*配置記憶體成功*/
        /*初始化value和children*/
        ptr->value=0;
        int i;
        for(i=0;i<branch;i++){
            ptr->children[i]=NULL;
        }
    }
    return ptr;
}
void initialize(trie *ptr_for_trie){
    ptr_for_trie->root=get_node();
    ptr_for_trie->count=0;
}

void preprocess_string(char events_64bits[],const char events_to_be_process[]){
    int length=strlen(events_to_be_process);
    int num_of_zero=64-length;
     /*num_of_zero>0才做*/
    if(num_of_zero>0){
        int j;
        for(j=0;j<num_of_zero;j++){
            events_64bits[j]='0';
        }
        strcpy(events_64bits+num_of_zero,events_to_be_process);
    }
    else if(num_of_zero==0){
        /*不用補了*/
        strcpy(events_64bits,events_to_be_process);
    }
}
int char_bits_to_int_bits(char a){
    if(a=='0'){
        return 0;
    }
    else if(a=='1'){
        return 1;
    }
}

