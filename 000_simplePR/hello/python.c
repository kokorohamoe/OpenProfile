/**/
/**/
/*#include<stdio.h>*/
int printf(const char * /*restrict*/ format, ...);
int main(int c,char **v){
    printf("パイソン使いだけにな！ void*=%d int=%d long=%d\n",
        sizeof(void*),
        sizeof(int),
        sizeof(long)
    );
    return 0;
}
/**/
/**/

