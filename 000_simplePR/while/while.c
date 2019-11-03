/**/
/**/
/*#include<stdio.h>*/
int printf(const char * /*restrict*/ format, ...);
int main(int c,char **v){
    int i=-10;
    while( i++){
        printf("    %d\n",
            -i 
	);
    };
    return 0;
}
/**/
/**/

