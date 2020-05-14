#include <stdio.h>
#include <stdbool.h>


void eval();
int fetch();
void printStack();



//registers
typedef enum {
  A,	B,	C,	D,	E,	F,
					IP, SP,
	NUM_OF_REGISTERS
} Registers;


int registers[NUM_OF_REGISTERS];



//my instruction set
typedef enum {
  PSH,
  ADD,
  POP,
  SET,
  HLT,
	JMP,
	NOP
} InstructionSet;

 
 
  
// my writen program
const int program[] = {
    PSH, 5,
    PSH, 6,
		JMP, 1,
    JMP, 0,
		ADD,
    PSH, 1,
		PSH,-3,
		ADD,
		ADD,
		NOP,
		POP,
		PSH, 4,
		POP,
		NOP,
    HLT,
		
};

// initial instruction pointer
int ip = 0;
int sp = -1;
int stack[256];

bool running = true;

#define sp (registers[SP])
#define ip (registers[IP])

int main() {

	while(running){
		eval(fetch());
		ip++;
	}
	return 0;
}





void eval(int instruction) {
	switch(instruction) {
	case HLT: 
			running = false;
			printf("HLT\t program stop\n");
			break;
	case PSH:
			sp++;
			stack[sp] = program[++ip];
			printf("PSH %d\t Insert %d on the stack\t",stack[sp],stack[sp]);
			printStack();
			break;		
	case POP:
			registers[A] = stack[sp--];
			printf("POP\t Popped %d from the stack", registers[A]);
			printStack();
			break;
	case JMP:
			registers[E] = program[++ip];
			ip = ip + registers[E];
			printf("JMP\t Jumped for %d back\t", registers[E]);
			printStack();	
	case ADD:
			registers[A] = stack[sp--];
			registers[B] = stack[sp--];
			registers[C]= registers[A] + registers[B];
			sp++;
			stack[sp] = registers[C];
			printf("ADD %d %d\t Added two numbers\t",registers[A],registers[B]);
			printStack();
			break;		
	case NOP:
			printf("NOP \t No operation\t\t");
			printStack();
      break;
		}	

}




//just returns actual ip instruction
int fetch() {
	return program[ip];
}


//debugging method print stack
void printStack(){
	printf("\t[ ");
	for(int i = 0; i < sp; i++){
	printf("%d ", stack[i+1]);
	}
	printf("]\n");

}
