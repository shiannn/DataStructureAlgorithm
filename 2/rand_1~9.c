#include<stdio.h>
#include<stdlib.h>
int main(){
	int i;
	for(i=0;i<10000;i++){
		printf("%d",rand()%9+1);
	}
	printf("\n");
	printf("2\n");
}

