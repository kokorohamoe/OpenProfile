#include <iostream>
#include <stdio.h>
#include <fstream>

unsigned char buf[1024];
unsigned char *ptr=buf;
int u4(const char *name){
	unsigned int target;
	target = *ptr++;
	target <<=8;
	target += *ptr++;
	target <<=8;
        target += *ptr++;
        target <<=8;
        target += *ptr++;
	printf ("%s %x\n",name,target);
	return  target;
}
int u2(const char *name){
        unsigned int target;
        target = *ptr++;
        target <<=8;
        target += *ptr++;
        printf ("%s %x\n",name,target);
        return  target;
}

int main(int argc,char *argv[])
{
	FILE* fd;
	fd = fopen(argv[1],"rb");
	if(!fd){
		std::cout <<"file io error"<<std::endl;
	}
	int c = fread (buf,1,1024,fd);
	std::cout << "read size="<<c <<std::endl;
	u4("magic");
	u2("minor");
	u2("major");
	int constant_pool_count = u2("constant_pool_count");
	return 0;
}

