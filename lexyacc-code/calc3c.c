#include <stdio.h>
#include "calc3.h"
#include "calc3.y.h"

static int lbl;

int ex(nodeType *p) {
    int lbl1, lbl2;

    if (!p) return 0;
    switch(p->type) {
    case typeCon:       
        printf("\tpushIm(%d);\n", p->con.value); 
        break;
    case typeId:
        printf("\tpushVar('%c');\n", p->id.i + 'a'); 
        break;
    case typeOpr:
        switch(p->opr.oper) {
        case WHILE:
			printf("\twhile(1)\n\t\{\n");
            ex(p->opr.op[0]);
			printf("\tif(pop() == 0) break;\n");
            ex(p->opr.op[1]);
			printf("\t}\n");
            break;
        case IF:
            ex(p->opr.op[0]);
            if (p->opr.nops > 2) {
                /* if else */
				printf("\tif(pop() != 0)\n\t{\n");
                ex(p->opr.op[1]);
				printf("\t}\n");
				printf("\telse\n");
				printf("\t{\n");
                ex(p->opr.op[2]);
				printf("\t}\n");
            } else {
                /* if */
				printf("\tif(pop() != 0)\n\t{\n");
                ex(p->opr.op[1]);
				printf("\t}\n");
            }
            break;
        case PRINT:     
            ex(p->opr.op[0]);
            printf("\tprintf(\"%%d\\n\", pop());\n");
            break;
        case '=':       
            ex(p->opr.op[1]);
			printf("\tpopVar('%c');\n", p->opr.op[0]->id.i + 'a');
            break;
        case UMINUS:    
            ex(p->opr.op[0]);
            printf("\tneg();\n");
            break;
	case FACT:
  	    ex(p->opr.op[0]);
	    printf("\tfact();\n");
	    break;
	case LNTWO:
	    ex(p->opr.op[0]);
	    printf("\tlntwo();\n");
	    break;
        default:
            ex(p->opr.op[0]);
            ex(p->opr.op[1]);
            switch(p->opr.oper) {
	    case GCD:   printf("\tgcd();\n"); break;
            case '+':   printf("\tadd();\n"); break;
            case '-':   printf("\tsub();\n"); break; 
            case '*':   printf("\tmul();\n"); break;
            case '/':   printf("\tdivl();\n"); break;
            case '<':   printf("\tcompLT();\n"); break;
            case '>':   printf("\tcompGT();\n"); break;
            case GE:    printf("\tcompGE();\n"); break;
            case LE:    printf("\tcompLE();\n"); break;
            case NE:    printf("\tcompNE();\n"); break;
            case EQ:    printf("\tcompEQ();\n"); break;
            }
        }
    }
    return 0;
}
