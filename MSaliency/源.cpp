#include<cstdio>
#include<iostream>
#include<MSaliency.h>
#include<libITTI.h>
using namespace std;

int main(){
	printf("Hello\n");
	if (!libITTIInitialize()){
		return -1;
	}
	printf("Ö´ÐÐ\n");
	ITTI();
	system("pause");
}

