#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 1024

int* stack;
int* stackBeg;
int* stackEnd;

void pushIm(int im)
{
	if (stack == stackEnd)
	{
		size_t stackSize = stackEnd - stackBeg;
		size_t newStackSize = stackSize * 2;
		
		int* newStack = (int*)realloc(stackBeg, sizeof(int) * newStackSize);
		stackBeg = newStack;
		stackEnd = stackBeg + newStackSize;
		stack = newStack + stackSize;
	}

	*stack = im;
	stack++;
}

int vars[26];

void pushVar(char var)
{
	pushIm(vars[var - 'a']);
}

int pop()
{
	stack--;
	return *stack;
}

void popVar(char var)
{
	vars[var - 'a'] = pop();
}

void neg()
{
	*(stack - 1) = -*(stack - 1);
}

void fact()
{
	int n = *(stack - 1);
	
	int r = 1;
	while (n > 1)
	{
		r *= n;
		n--;
	}
	
	*(stack - 1) = r;
}

void gcd()
{
	int a = pop();
	int b = *(stack - 1);

    while (b != 0)
    {
        a %= b;
        a ^= b;
        b ^= a;
        a ^= b;
    }

    *(stack - 1) = a;
}

void lntwo()
{
	*(stack - 1) = (int)log2((double)*(stack - 1));
}

void add()
{
	int b = pop();
	int a = *(stack - 1);
	*(stack - 1) = a + b;
}

void sub()
{
	int b = pop();
	int a = *(stack - 1);
	*(stack - 1) = a - b;
}

void mul()
{
	int b = pop();
	int a = *(stack - 1);
	*(stack - 1) = a * b;
}

void divl()
{
	int b = pop();
	int a = *(stack - 1);
	*(stack - 1) = a / b;
}

void compLT()
{
	int b = pop();
	int a = *(stack - 1);
	*(stack - 1) = a < b;
}

void compGT()
{
	int b = pop();
	int a = *(stack - 1);
	*(stack - 1) = a > b;
}

void compGE()
{
	int b = pop();
	int a = *(stack - 1);
	*(stack - 1) = a >= b;
}

void compLE()
{
	int b = pop();
	int a = *(stack - 1);
	*(stack - 1) = a <= b;
}

void compNE()
{
	int b = pop();
	int a = *(stack - 1);
	*(stack - 1) = a != b;
}

void compEQ()
{
	int b = pop();
	int a = *(stack - 1);
	*(stack - 1) = a == b;
}

int main()
{
	stack = (int*)malloc(sizeof(int) * STACK_INIT_SIZE);
	stackBeg = stack;
	stackEnd = stack + STACK_INIT_SIZE;
