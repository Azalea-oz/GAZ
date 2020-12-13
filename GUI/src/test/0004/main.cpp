#include<iostream>
#include<function>


class TESTA{
	void (*print)(int) = 0;
public:
	TESTA(){}
	~TESTA(){}
};

class TESTB : public TESTA{
	int num;
	
};

int main(){
	
	
}