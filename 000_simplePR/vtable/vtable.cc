#include<stdio.h>

class c0{ 
    public:
    int (* function)(void);
    c0()
        :function(NULL)
    {
    }
    void main(){
	if(function){
            (*function)();
	}
    }
};

class c1 {
    public:
    virtual int function(void){
        printf("I am C1\\n");
        return 0;
    };
};


int main(int argc,char **argv){
    printf("OK\n");
    c0 c0;
    c0.main();
    return 0;
};



