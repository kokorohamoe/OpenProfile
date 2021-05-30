#include <iostream>
#include <stdio.h>
#include <fstream>

unsigned char buf[1024];
int main(int argc,char *argv[])
{
	FILE* fd;
	fd = fopen(argv[1],"rb");
	if(!fd){
		std::cout <<"file io error"<<std::endl;
	}
	int c = fread (buf,1,1024,fd);
	std::cout << c <<std::endl;
	unsigned int magic=7;
	magic = buf[0]<<24 + buf[1]<<16+buf[2]<<8+buf[3];	
	std::cout << (int)buf[0];
	std::cout <<std::endl;
	unsigned char * ptr = buf;
	unsigned char *end;
	end = ptr + c;
	ptr += 4;//magic
	ptr += 2; //major version
	ptr += 2 ;//jinor ersion
	while(ptr <= end){
		int code = *ptr++;
		int len = *ptr++;
		len = len << 8 + *ptr++;
		ptr += len;
	}	
	return 0;
}

