#include <stdio.h>
#include <stdlib.h>

#define namelength 10
#define max_length 30000010
#define mod 1000000007
//#define debug_input
//#define debug_prefix_function

char N_large_text[max_length];
char M_short_pattern[max_length];

int M_prefix_function[max_length];
int N_most_same[max_length];//N最多可和M比到幾位
unsigned long long int add_up[max_length];//所有抓到目標的prefix字元數和
int times[max_length];//抓到次數

int main()
{
    char Name1[namelength];
    char Name2[namelength];

    scanf("%s",Name1);
    scanf("%s",Name2);
    /*從陣列的index 1開始*/
    scanf("%s",N_large_text+1);
    scanf("%s",M_short_pattern+1);

    #ifdef debug_input
        printf("%s\n%s\n%s\n%s\n",Name1,Name2,\
               N_large_text+1,M_short_pattern+1);
    #endif // debug_input

    /*先求出小字串的prefix_function*/
    int M_length=strlen(M_short_pattern+1);
    compute_prefix_function(M_short_pattern,\
                            M_prefix_function,M_length);

    #ifdef debug_prefix_function
        int i;
        for(i=1;i<=M_length;i++){
            printf("%d\n",M_prefix_function[i]);
        }
    #endif // debug_prefix_function

    /*得到小字串的prefix_function */
    /*M_prefix_function 駐標從1開始 總共M_length格*/

    /*算N的最多比到位N_most_same*/
    int N_length=strlen(N_large_text+1);
    KMP_Matcher(N_large_text,N_length,\
                M_short_pattern,M_length,\
                M_prefix_function,N_most_same);

    /*算add_up陣列和times陣列*/
    /*利用compute_prefix_function*/

    /*add_up的總和是prefix字元cover總數*/
    /*times的總和是兩個人畫底線總次數*/
    int cover_sum=0,times_sum=0;
    int i;
    for(i=1;i<=N_length;i++){
        /*總字元數*/
        cover_sum=(cover_sum%mod+add_up[N_most_same[i]]%mod)%mod;
        /*總次數*/
        times_sum=(times_sum%2+times[N_most_same[i]]%2)%2;
    }
    if(times_sum%2==1){
        /*第一個人贏*/
        printf("%s\n",Name1);
    }
    else{
        printf("%s\n",Name2);
    }
    printf("%d\n",cover_sum);

    return 0;
}

void KMP_Matcher(const char N_large_text[],int N_length,\
                 const char M_short_pattern[],int M_length,\
                 int M_prefix_function[],int N_most_same[]){
    int q=0;
    int i;
    for(i=1;i<=N_length;i++){
        while(q>0&&M_short_pattern[q+1]!=N_large_text[i]){
            q=M_prefix_function[q];
        }
        if(M_short_pattern[q+1]==N_large_text[i]){
            q=q+1;
        }
        N_most_same[i]=q;//填入該i位最多匹配數q
        if(q==M_length){
            //printf("pattern occur with shift %d-%d\n",i,M_length);
            q=M_prefix_function[q];
        }
    }
}

int main01(){
    int most[20];
    int pi[20]={0};
    char N[20];
    char M[20];
    scanf("%s",N+1);
    scanf("%s",M+1);//從index==1開始寫入
    int lm=strlen(M+1);
    int ln=strlen(N+1);
    compute_prefix_function(M,pi,lm);
    KMP_Matcher(N,ln,M,lm,pi,most);
    int i;
    for(i=1;i<=ln;i++){
        printf("%d\n",most[i]);
    }
    for(i=1;i<=lm;i++){
        printf("%llu %d\n",add_up[i],times[i]);
    }
}
void compute_prefix_function(char string[],\
                             int prefix_function[],\
                             int m_length){

    prefix_function[1]=0;//index從1開始

    add_up[0]=0;
    add_up[1]=1;

    times[0]=0;
    times[1]=1;

    int k=0;
    int q;
    for(q=2;q<=m_length;q++){//連string都要從1開始
        while(k>0&&string[k+1]!=string[q]){
            k=prefix_function[k];
        }
        if(string[k+1]==string[q]){
            k=k+1;
        }
        prefix_function[q]=k;

        add_up[q]=q+add_up[prefix_function[q]];
        times[q]=1+times[prefix_function[q]];
    }
    return ;
}

