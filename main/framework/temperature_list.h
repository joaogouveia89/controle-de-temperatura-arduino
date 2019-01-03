#ifndef TEMPERATURE_LIST_H
#define TEMPERATURE_LIST_H
#define CALIBRATED 1
#define NOT_CALIBRATED 2

typedef struct List TList;

struct List
{
	float data;
	TList* next;	
};

TList* add(TList* root, float data){
	TList* aux = (TList*) malloc(sizeof(TList));
	aux->data = data;
	aux->next = NULL;

	if(root == NULL)
		return aux;
	else{
		TList* aux2 = root;
		while(aux2->next != NULL)
			aux2 = aux2->next;
		aux2->next = aux;
		return root;
	}
}

void printList(TList* root){
	TList* aux = root;
	while(aux != NULL){
		printf("%f ", aux->data);
		aux = aux->next;	
	}
}

float average(TList* temps, int qtd){
	TList* aux = temps;
	float avg = 0;
	while(aux != NULL){
		avg += aux->data;
		aux = aux->next;
	}
	return avg/(float)qtd;
}

float mod(float val){
	if(val < 0)
		return val*(float)(-1);
	else
		return val;
}

int checkCalibration(TList* temps, float margin, int qtd){
	float avg = average(temps, qtd);
	int status = CALIBRATED;
	int diff;
	TList* aux = temps;
	if(aux != NULL){
		while(aux != NULL && status != NOT_CALIBRATED){
			if(mod(aux->data - avg) > margin)
				status = NOT_CALIBRATED;
			aux = aux->next;		
		}
	}else{
		status = NOT_CALIBRATED;
	}
	return status;
}

TList* popTemperature(TList* temperatures){
	TList* aux = temperatures;
	temperatures = temperatures->next;
	free(aux);
	return temperatures;
}
#endif