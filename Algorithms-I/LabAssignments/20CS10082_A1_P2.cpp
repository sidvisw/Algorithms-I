#include <string>
#include <fstream>
#include <iostream>
using namespace std;

// defining structure for node
struct operatorNode {
	float data;
	struct operatorNode* next;
};
// defining structure for stack
struct operatorStack {
	int size;
	struct operatorNode* top;
};
// function to create a stack
struct operatorStack* createStack(){
	struct operatorStack *stack=new struct operatorStack;
	stack->size=0;
	stack->top=NULL;
	return stack;
}
// function to check if a stack is empty or not
bool isEmpty(struct operatorStack* stack){
	return stack->top==NULL;
}
// peek function for stack
float peek(struct operatorStack* stack){
	if(!isEmpty(stack)){
		return stack->top->data;
	}
	else{
		exit(-1);
	}
}
// pop function for stack
float pop(struct operatorStack* stack){
	struct operatorNode*ptr=stack->top;
	stack->top=stack->top->next;
	float del_data=ptr->data;
	delete ptr;
	stack->size--;
	return del_data;
}
// push function for stack
void push(struct operatorStack* stack, float op){
	struct operatorNode*ptr=new struct operatorNode;
	ptr->data=op;
	ptr->next=stack->top;
	stack->top=ptr;
	stack->size++;
}

// function to evaluate a postfix expression
float evaluate(const char* exp) {
	int i;
	struct operatorStack*stack=createStack();
	for (i=0;exp[i];++i){
        if(exp[i]==' ')
			continue;
        else if (isdigit(exp[i])){
            float num=0;
            while(isdigit(exp[i])){
            	num=num*10+(int)(exp[i]-'0');
                i++;
            }
            i--;
            push(stack,num);
        }
        else{
            float val1=pop(stack);
            float val2=pop(stack);
            switch (exp[i]){
            	case '+':push(stack,val2+val1);
				break;
            	case '-':push(stack,val2-val1);
				break;
            	case '*':push(stack,val2*val1);
				break;
            	case '/':push(stack,val2/val1);
				break;
            	case '%':push(stack,(int)val2%(int)val1);
				break;
            }
        }
    }
    return pop(stack);
}

// driver function
int main() {
	string line;
	ifstream input_file("20CS10082_A1_P1_output.txt");
	ofstream part_2_output_file("20CS10082_A1_P2_output.txt");
	if (input_file.is_open()) {
		while (getline(input_file,line)) {
			// Second part: Implement evaluate function and associated linked list impl. of stack
			part_2_output_file << evaluate(line.c_str()) << endl;
		}
		input_file.close();
	}
	else cout << "Unable to open file"; 
	part_2_output_file.close();
	return 0;
}

