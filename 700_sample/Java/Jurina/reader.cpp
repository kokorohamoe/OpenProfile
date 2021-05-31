#include <iostream>
#include <string.h>

int main(int argc,const char*argv[]){
	int v;
	char buffer[1024];
	while(1){
		printf("input\n");
		scanf("%s%d",buffer,&v);
		if(strcmp(buffer,"print")==0)
			printf( "public class base{\n"
   				"public static void main(String[] args){\n"
        			"int i = %d;\n"
        			"System.out.println(i);}}\n",v);
   	}
	return 0;
}
