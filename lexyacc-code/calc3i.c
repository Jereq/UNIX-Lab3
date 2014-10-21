#include <stdio.h>
#include "calc3.h"
#include "calc3.y.h"

static int lbl;

int ex(nodeType *p)
{
	int lbl1, lbl2;

	if (!p) return 0;
	switch(p->type)
	{
	case typeCon:
		printf("\tpushl\t$%d\n", p->con.value); 
		break;
	 case typeId:
		printf("\tpushl\tvars + %d * 4\n", p->id.i); 
		break;
	 case typeOpr:
		switch(p->opr.oper)
		{
		case WHILE:
			printf("L%03d:\n", lbl1 = lbl++);
			ex(p->opr.op[0]);
			printf("\tpopl\t%%eax\n");
			printf("\tcmpl\t$0, %%eax\n");
			printf("\tjz\tL%03d\n", lbl2 = lbl++);
			ex(p->opr.op[1]);
			printf("\tjmp\tL%03d\n", lbl1);
			printf("L%03d:\n", lbl2);
			break;
		case IF:
			ex(p->opr.op[0]);
			if (p->opr.nops > 2)
			{
				/* if else */
				printf("\tpopl\t%%eax\n");
			printf("\tcmpl\t$0, %%eax\n");
				printf("\tjz\tL%03d\n", lbl1 = lbl++);
				ex(p->opr.op[1]);
				printf("\tjmp\tL%03d\n", lbl2 = lbl++);
				printf("L%03d:\n", lbl1);
				ex(p->opr.op[2]);
				printf("L%03d:\n", lbl2);
			}
			else
			{
				/* if */
				printf("\tpopl\t%%eax\n");
			printf("\tcmpl\t$0, %%eax\n");
				printf("\tjz\tL%03d\n", lbl1 = lbl++);
				ex(p->opr.op[1]);
				printf("L%03d:\n", lbl1);
			}
			break;
		case PRINT:
			ex(p->opr.op[0]);
			printf("\tpushl\t$ifmt\n");
			printf("\tcall\tprintf\n");
			printf("\taddl\t$8, %%esp\n");
			break;
		case '=':
			ex(p->opr.op[1]);
			printf("\tpopl\tvars + %d * 4\n", p->opr.op[0]->id.i);
			break;
		case UMINUS:
			ex(p->opr.op[0]);
			printf("\tnegl\t(%%esp)\n");
			break;
		case FACT:
			ex(p->opr.op[0]);
			printf("\tcall\tfact\n");
			printf("\tmovl\t%%eax, (%%esp)\n");
			break;
		case LNTWO:
			ex(p->opr.op[0]);
			printf("\tcall\tlntwo\n");
			printf("\tmovl\t%%eax, (%%esp)\n");
			break;
		default:
			ex(p->opr.op[0]);
			ex(p->opr.op[1]);
			switch(p->opr.oper)
			{
			case GCD:
				printf("\tcall\tgcd\n");
				printf("\tmovl\t%%eax, 4(%%esp)\n");
				printf("\taddl\t$4, %%esp\n");
				break;
			case '+':
				printf("\tpopl\t%%eax\n");
				printf("\taddl\t%%eax, (%%esp)\n");
				break;
			case '-':
				printf("\tpopl\t%%eax\n");
				printf("\tsubl\t%%eax, (%%esp)\n");
				break;
			case '*':
				printf("\tpopl\t%%eax\n");
				printf("\timull\t(%%esp)\n");
				printf("\tmovl\t%%eax, (%%esp)\n");
				break;
			case '/':
				printf("\tpopl\t%%ebx\n");
				printf("\tpopl\t%%eax\n");
				printf("\tcdq\n");
				printf("\tidivl\t%%ebx\n");
				printf("\tpushl\t%%eax\n");
				break;
			case '<':
				printf("\tpopl\t%%eax\n");
				printf("\tcmpl\t%%eax, (%%esp)\n");
				printf("\tsetl\t%%al\n");
				printf("\tmovzbl\t%%al, %%eax\n");
				printf("\tmovl\t%%eax, (%%esp)\n");
				break;
			case '>':
				printf("\tpopl\t%%eax\n");
				printf("\tcmpl\t%%eax, (%%esp)\n");
				printf("\tsetg\t%%al\n");
				printf("\tmovzbl\t%%al, %%eax\n");
				printf("\tmovl\t%%eax, (%%esp)\n");
				break;
			case GE:
				printf("\tpopl\t%%eax\n");
				printf("\tcmpl\t%%eax, (%%esp)\n");
				printf("\tsetge\t%%al\n");
				printf("\tmovzbl\t%%al, %%eax\n");
				printf("\tmovl\t%%eax, (%%esp)\n");
				break;
			case LE:
				printf("\tpopl\t%%eax\n");
				printf("\tcmpl\t%%eax, (%%esp)\n");
				printf("\tsetle\t%%al\n");
				printf("\tmovzbl\t%%al, %%eax\n");
				printf("\tmovl\t%%eax, (%%esp)\n");
				break;
			case NE:
				printf("\tpopl\t%%eax\n");
				printf("\tcmpl\t%%eax, (%%esp)\n");
				printf("\tsetne\t%%al\n");
				printf("\tmovzbl\t%%al, %%eax\n");
				printf("\tmovl\t%%eax, (%%esp)\n");
				break;
			case EQ:
				printf("\tpopl\t%%eax\n");
				printf("\tcmpl\t%%eax, (%%esp)\n");
				printf("\tsete\t%%al\n");
				printf("\tmovzbl\t%%al, %%eax\n");
				printf("\tmovl\t%%eax, (%%esp)\n");
				break;
			}
		}
	}
	return 0;
}

