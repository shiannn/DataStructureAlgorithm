//與助教黃晴、助教曾千育、助教劉瀚聲、同學楊仁傑討論
//參考欣穆老師上課投影片
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define big_prime 37337999 
#define small_prime 739399

#define max 10000010
//#define debug_input
//#define debug_rabin_value
//#define debug_short_relative

char A_long[max];
char B_short[max];

int A_relative_position[max];
int A_relative_position_next[max];
int B_relative_position[max];

int A_alphabet_most_right[26]={0};//0~25
int B_alphabet_most_right[26]={0};//0~25

void Rabin_Karp_Matcher(char Text[],char Pattern[],\
                        int N_text,int N_pattern,\
                        int d_prime_power,int q_mod);

int char_to_int(char c);
void count(long long int array[],int n);

long long int small_prime_power[max];
int main()
{
    /*先算好小質數的各個冪次*/
    count(small_prime_power,max);

    scanf("%s",A_long+1);
    scanf("%s",B_short+1);
    #ifdef debug_input
    printf("%s\n%s\n",A_long+1,B_short+1);
    #endif // debug_input

    /*兩個字串前置處理*/
    int length_short=strlen(B_short+1);
    int length_long=strlen(A_long+1);
    int d_prime=small_prime;
    int q_mod=big_prime;
    int k;
    for(k=1;k<=length_short;k++){
        /*填入B的相對位置*/
        /*index-當前最右*/
        if(B_alphabet_most_right[char_to_int(B_short[k])]==0){
            /*當前最右是0 表示是第一次填入*/
            B_relative_position[k]=0;
            B_alphabet_most_right[char_to_int(B_short[k])]=k;
        }
        else{
            /*不是第一次填入*/
            B_relative_position[k]=k-B_alphabet_most_right[char_to_int(B_short[k])];
            /*當前最右會變成第k格(index)*/
            B_alphabet_most_right[char_to_int(B_short[k])]=k;
        }
    }
    for(k=1;k<=length_long;k++){
        /*填入A的相對位置*/
        /*index-當前最右*/
        if(A_alphabet_most_right[char_to_int(A_long[k])]==0){
            /*當前最右是0 表示是第一次填入*/
            A_relative_position[k]=0;
            A_alphabet_most_right[char_to_int(A_long[k])]=k;
        }
        else{
            /*不是第一次填入*/
            /*前面的跟k的距離*/
            A_relative_position_next[A_alphabet_most_right[char_to_int(A_long[k])]]=k-A_alphabet_most_right[char_to_int(A_long[k])];
            /*k跟前面的距離*/
            A_relative_position[k]=k-A_alphabet_most_right[char_to_int(A_long[k])];
            /*當前最右會變成第k格(index)*/
            A_alphabet_most_right[char_to_int(A_long[k])]=k;
        }
    }

    #ifdef debug_short_relative
        int i;
        for(i=1;i<=length_long;i++){
            printf("%d",A_relative_position[i]);
        }
        printf("\n");
        for(i=1;i<=length_long;i++){
            printf("%d",A_relative_position_next[i]);
        }
        printf("\n");
        for(i=1;i<=length_short;i++){
            printf("%d",B_relative_position[i]);
        }
        printf("\n");
    #endif // short_relative

    Rabin_Karp_Matcher(A_long,B_short,\
                        length_long,length_short,\
                        d_prime,q_mod);

    return 0;
}

void Rabin_Karp_Matcher(char Text[],char Pattern[],\
                        int Num_text,int Num_pattern,\
                        int d_prime_power,int q_mod){

    long long int value_A_long=0,value_B_short=0;
    int i;
    for(i=1;i<=Num_pattern;i++){

        value_A_long=((((value_A_long%q_mod)*d_prime_power)%q_mod)\
                        +A_relative_position[i])%q_mod;

        value_B_short=((((value_B_short%q_mod)*d_prime_power)%q_mod)\
                        +B_relative_position[i])%q_mod;

    }

    #ifdef debug_rabin_value
    printf("%lld\n%lld\n",value_A_long,value_B_short);
    #endif // debug_rabin_value
    int h=small_prime_power[Num_pattern-1];
    int ans=0;
    int temp=0;
    int s;//shift次數
    for(s=0;s<=Num_text-Num_pattern;s++){
        if(value_A_long==value_B_short){
            ans++;
        }
        if(s<Num_text-Num_pattern){//最後一次不用再調整
            /*調整value_A_long*/
            /*比完這次之後，把大字串後面一個數字設為0*/
            /*先記住這個值*/
            temp=A_relative_position[(s+1)+A_relative_position_next[s+1]];
            A_relative_position[(s+1)+A_relative_position_next[s+1]]=0;

            if(A_relative_position_next[s+1]<=Num_pattern-1){
                /*如果會影響到value 要額外減去一個值*/
                value_A_long=((d_prime_power\
                *(((value_A_long%q_mod-(h*A_relative_position[s+1])%q_mod)%q_mod-(temp*small_prime_power[Num_pattern-1-A_relative_position_next[s+1]])%q_mod)%q_mod))%q_mod\
                        +A_relative_position[s+Num_pattern+1])%q_mod;
                while(value_A_long<0){
                    value_A_long=value_A_long+q_mod;
                }
            }
            else{
                /*不影響value 照常運作*/
                value_A_long=((d_prime_power\
                *((value_A_long%q_mod-(h*A_relative_position[s+1])%q_mod)%q_mod))%q_mod\
                        +A_relative_position[s+Num_pattern+1])%q_mod;
                while(value_A_long<0){
                    value_A_long=value_A_long+q_mod;
                }
            }
            /*不包含(s+1) 往後pattern格*/
        }
    }
    printf("%d\n",ans);
    return;
}

int main01(){
    count(small_prime_power,200000);
    int i;
    for(i=0;i<200000;i++){
        printf("%lld\n",small_prime_power[i]);
    }
    return 0;
}
int char_to_int(char c){
    return (c-'a');
}
void count(long long int array[],int n){
    array[0]=1;
    int i;
    for(i=1;i<n;i++){
        array[i]=((small_prime%big_prime)*(array[i-1]%big_prime))%big_prime;
    }
}

