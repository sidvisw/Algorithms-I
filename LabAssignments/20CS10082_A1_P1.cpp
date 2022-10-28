#include <string>
#include <fstream>
#include <iostream>
using namespace std;

// defining structure for node
struct operatorNode {
	char data;
	struct operatorNode* next;
};
// defining structure for stack
struct operatorStack {
	int size;
	struct operatorNode* top;
};
// stack creating function
struct operatorStack* createStack(){
	struct operatorStack *stack=new struct operatorStack;
	stack->size=0;
	stack->top=NULL;
	return stack;
}
// function to check whether the stack is empty or not
bool isEmpty(struct operatorStack* stack){
	return stack->top==NULL;
}
// peek function for stack
char peek(struct operatorStack* stack){
	if(!isEmpty(stack)){
		return stack->top->data;
	}
	else{
		exit(-1);
	}
}
// pop function for stack
char pop(struct operatorStack* stack){
	struct operatorNode*ptr=stack->top;
	stack->top=stack->top->next;
	char del_data=ptr->data;
	delete ptr;
	stack->size--;
	return del_data;
}
// push function for stack
void push(struct operatorStack* stack, char op){
	struct operatorNode*ptr=new struct operatorNode;
	ptr->data=op;
	ptr->next=stack->top;
	stack->top=ptr;
	stack->size++;
}

// function to determine the order of precedence of two operators
int precedence(char op1,char op2){
	int val1,val2;
	if(op1=='/'||op1=='*'||op1=='%')
		val1=2;
	else
		val1=1;
	if(op2=='/'||op2=='*'||op2=='%')
		val2=2;
	else
		val2=1;
	if(val1>=val2)
		return 1;
	else
		return 0;
}

// the working function to convert an infix notation to postfix notation
char *convert(const char *exp) {
	int i,index=0;
	char *rp_exp;
	struct operatorStack*stack=createStack();
	for(i=0;exp[i];++i){
		if(exp[i]==' ')
			continue;
		else if(isdigit(exp[i])){
            while(isdigit(exp[i]))
            {
				rp_exp[index++]=exp[i];
                i++;
            }
            i--;
			rp_exp[index++]=' ';
		}
		else if(exp[i]=='+'||exp[i]=='-'||exp[i]=='/'||exp[i]=='*'||exp[i]=='%'){
			if(!isEmpty(stack)&&peek(stack)!='('){
				while(!isEmpty(stack)&&precedence(peek(stack),exp[i])){
					rp_exp[index++]=pop(stack);
					rp_exp[index++]=' ';
				}
			}
			push(stack,exp[i]);
		}
		else if(exp[i]=='(')
			push(stack,exp[i]);
		else if(exp[i]==')'){
			while(peek(stack)!='('){
				rp_exp[index++]=pop(stack);
				rp_exp[index++]=' ';
			}
			pop(stack);
		}
	}
	while(!isEmpty(stack)){
		rp_exp[index++]=pop(stack);
		rp_exp[index++]=' ';
	}
	rp_exp[index-1]='\0';
	return rp_exp;
}

// driver function
int main() {
	string line;
	ifstream input_file("input.txt");
	ofstream part_1_output_file("20CS10082_A1_P1_output.txt");
	if (input_file.is_open()) {
		while (getline(input_file,line)) {
			// First part: Implement convert function and associated linked list impl. of stack 
			char* rp_exp = convert(line.c_str());
			part_1_output_file << rp_exp << endl;
		}
		input_file.close();
	}
	else cout << "Unable to open file"; 
	part_1_output_file.close();
	return 0;
}

