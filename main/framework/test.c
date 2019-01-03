#include<stdlib.h>
#include <stdio.h>
#include "temperature_list.h"

int main(){
	TList* list = NULL;
	list = add(list, 22.4);
	list = add(list, 21.1);
	list = add(list, 25.3);
	list = add(list, 25.4);
	list = add(list, 28.12);
	list = add(list, 29.2);
	int cal = checkCalibration(list, 0.5, 6);
	printf("cal = %d", cal);
}