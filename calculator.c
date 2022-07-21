#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

struct stack{
	char data[100];
	int size;
};

typedef struct stack Stack;

struct array{
	char data[100];
	int size;
};

typedef struct array Array;

void conversionShow();
void conversionSaveCalculate();
void loadHistory();
void deleteHistory();

int main()
{
	int a;
	printf("Calculator\nTechnical requirements: works for 0-9(does not work for a two-digit numbers and more) and signs + - * / ^ ( ) =\nCalculate properly results <=79\n\n Conversion RPN - choose 1\n Calculate - choose 2\n Show results of calculations - choose 3\n Clear history - choose 4\n Exit - choose 5\n\n");

	while(a!=5){
		
		scanf("%d", &a);
	
		if(a==1){
	    	conversionShow();
		}
		else if(a==2){
			conversionSaveCalculate();
		}
		else if(a==3){
			loadHistory();
		}
		else if(a==4){
			deleteHistory();
		}
	
	}
    
    return 0;
}


void conversionShow(){
	
	Stack s;
	char tmp[100];
	s.size=0;
	
    do
    {
    	
    	scanf("%c", &tmp);
    	
        if(tmp[0] >= '0' && tmp[0] <= '9') printf("%c ", tmp[0]);
        
        else
            switch(tmp[0])
            {
                case '+': while(s.size && s.data[s.size-1] != '('){
						  printf("%c " , s.data[--s.size]);
						}
                          s.data[s.size++] = tmp[0];
                          break;
                
                case '-': while(s.size && s.data[s.size-1] != '('){
						  printf("%c " , s.data[--s.size]);
						} 
                          s.data[s.size++] = tmp[0];
                          break;
                          
                case '*': while(s.size && s.data[s.size-1] != '(' && s.data[s.size-1] != '+' && s.data[s.size-1] != '-'){
						  printf("%c " , s.data[--s.size]);
						} 
                          s.data[s.size++] = tmp[0];
                          break;
                
                case '/': while(s.size && s.data[s.size-1] != '(' && s.data[s.size-1] != '+' && s.data[s.size-1] != '-'){
						  printf("%c " , s.data[--s.size]);
						} 
                          s.data[s.size++] = tmp[0];
                          break; 
						   
                case '^': while(s.size && s.data[s.size-1] == '^'){
						  printf("%c " , s.data[--s.size]);
						} 
                          s.data[s.size++] = tmp[0];
                          break;
                          
                case '(': s.data[s.size++] = '(';
                          break;
                          
                case ')': while(s.data[s.size-1] != '('){
						  printf("%c " , s.data[--s.size]);
						} 
                          s.size--;
                          break;
                          
                case '=': while(s.size){
						  printf("%c " , s.data[--s.size]);
						} 
                          printf("=\n\n");
                          break;
            }

    }while(tmp[0] != '=');
}
 	
void conversionSaveCalculate(){
	
	Stack s, s2;
	s.size=0;
	s2.size=0;
	Array a;
	a.size=0;
	char tmp[100];
	
	FILE *file;
	
	file = fopen("history.txt", "a");
	
    do
    {
    	
    	scanf("%c", &tmp);
    	
        if(tmp[0] >= '0' && tmp[0] <= '9'){
        	a.data[a.size] = tmp[0];
        	a.size++;
		} 
        
        else
            switch(tmp[0])
            {
                case '+': while(s.size && s.data[s.size-1] != '(') {
                		  a.data[a.size]=s.data[--s.size];
                		  a.size++;
                		}
                          s.data[s.size++] = tmp[0];
                          break;
                
                case '-': while(s.size && s.data[s.size-1] != '(') {
                		  a.data[a.size]=s.data[--s.size];
                		  a.size++;
                		}
                          s.data[s.size++] = tmp[0];
                          break;
        
                case '*': while(s.size && s.data[s.size-1] != '(' && s.data[s.size-1] != '+' && s.data[s.size-1] != '-'){
                		  a.data[a.size]=s.data[--s.size];
                		  a.size++;
						}
                          s.data[s.size++] = tmp[0];
                          break; 
                
                case '/': while(s.size && s.data[s.size-1] != '(' && s.data[s.size-1] != '+' && s.data[s.size-1] != '-'){
                		  a.data[a.size]=s.data[--s.size];
                		  a.size++;
						}
                          s.data[s.size++] = tmp[0];
                          break; 
						   
                case '^': while(s.size && s.data[s.size-1] == '^'){
                		  a.data[a.size]=s.data[--s.size];                
                		  a.size++;
						}
                          s.data[s.size++] = tmp[0];
                          break;
                          
                case '(': s.data[s.size++] = '(';
                          break;
                          
                case ')': while(s.data[s.size-1] != '('){
                		  a.data[a.size]=s.data[--s.size];
                		  a.size++;
						}	
                          s.size--;
                          break;
                          
                case '=': while(s.size){	
                		  a.data[a.size]=s.data[--s.size];
                		  a.size++;
						}
						  a.data[a.size]='=';
                          break;
            }

    }while(tmp[0] != '=');
    
    a.size=0;
    int operand1, operand2;
    
   	do{
    	if(a.data[a.size] >= '0' && a.data[a.size] <= '9'){
        	s2.data[s2.size]=a.data[a.size];
        	s2.size++;
		}
		
		else{
			operand2 = s2.data[--s2.size]-48;
			operand1 = s2.data[--s2.size]-48;
			switch(a.data[a.size]){
				case '+': operand1 = operand1 + operand2;
				 		  break;
				case '-': operand1 = operand1 - operand2;
						  break;
				case '*': operand1 = operand1 * operand2;
						  break;
				case '/': operand1 = operand1 / operand2;
						  break;
				case '^': operand1 = pow(operand1, operand2);
						  break;
			}
			s2.data[s2.size++] = operand1+48;
		}
		a.size++;
	}while(a.data[a.size]!='=');
	
	printf(" =%d\n\n", s2.data[--s2.size]-48);
	
	fprintf(file, "%d\n" , s2.data[s2.size]-48);
	
	fclose(file);
}

void loadHistory(){
	FILE *file;
	int buffer[255];
	int i=0;
	
	file = fopen("history.txt", "r");
	
	if(!file){
        printf("Error history.txt");
    }
    else{
	    	while(true){		
	        fscanf(file, "%d", &buffer[i]);
	        if(feof(file)!=0) break;
	        printf("\n%d", buffer[i]);
	        i++;
	    }
	}
    
	fclose(file);
	printf("\n\n");
}

void deleteHistory(){
	FILE *file;
	
	file = fopen("history.txt", "w+");
	
	fclose(file);
	printf("\n\n");
}






