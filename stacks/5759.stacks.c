#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <ctype.h>

#define size 256

/*
 * Item: An item that is being pushed to or popped from the stack
 *       It may be float (to be used while evaluating the postfix)
 *       It may be char* (to be used while converting infix to postfix)
 */
typedef union {
	float fData;
	char* cpData;
} Item;
/*
 *
 */
typedef struct {

        int top;
        Item items [size];

} Stack;
/*
 *
 */
void init(Stack *s) {

	s->top = -1;
}
/*
 *
 */
int isEmpty(Stack *s) {

	if(s->top <= -1){
        return 1;
	}
	else{
        return 0;
	}
}
/*
 *
 */
Item top(Stack *s) {

    if(isEmpty(s) == 0){

        return s->items[s->top];
    }
	else{

        printf("stack empty");
      //  exit(1);
	}
}
/*
 *
 */
Item pop(Stack *s) {

	//int val;

    Item items;

	if(isEmpty(s) == 1){
      exit(1);
	}
	else{

        items = s->items[s->top];
        s->top = s->top - 1;
        return items;
	}

}
/*
 *
 */

 int full(Stack *s)
{
  if(s->top == size - 1)
     return 1;
  else
     return 0;
}

void push(Stack *s, Item val) {

	if(full(s) == 1){
        printf("stack is full");
      //  exit(1);
	}
	else{

        s->top = s->top + 1;
        s->items[s->top] = val;

	}
}
/*
 *
 */
void destroy(Stack *s) {

    Item *x;
	while( s->top > -1){

        x = &s->items[s->top];
        free(x);
        s->top = s->top - 1;
	}

}
/*
 * infixToPostfix: converts an expression in infix notation to
 *					to a postfix notation (Reverse-Polish Notation)
 *					ASSUME single-digit operands
 *					ASSUME ^*+-/ operators
 *					e.g., 2+3 --> 23+
 *					e.g., (2+3)*4 --> 23+4*
 */

int priority(char oper){

        if(oper == '^'){

            return 3;
        }

        else if(oper == '*' || oper == '/'){

            return 2;
        }

        else if(oper == '+' || oper == '-'){

            return 1;
        }

        else{

            return 0;
        }

}

int isOperator(char s)
{
        if(s == '+' || s == '-' || s == '*' || s == '/' || s == '^'){

            return 1;
        }
        else
            return 0;
}

void infixToPostfix(char* infix, char* postfix)
{

        Stack s;
        init(&s);
        char x;
        //Item x;
        Item val;
        int i=0, j=0;
        //printf("reach 1");
        while(infix[i] != '\0')
            {
                //printf("reach 2");
            if(isdigit(infix[i])){

                postfix[j] = infix[i];
                j++;
                postfix[j]= ' ';
                j++;
            }

            else if(infix[i] == '(' ){

                    val.cpData = '(';
                    push(&s,val);

            }

            else if(infix[i] == ')'){

                    while((top(&s).cpData != '(')){

                            x = pop(&s).cpData;
                            postfix[j] = x;
                            j++;
                            postfix[j]= ' ';
                            j++;
                            //pop(&s);
                            //printf("%c",x);
                          }
                          pop(&s); // pops open bracket
            }

            else if (isOperator(infix[i])) {


                    while(priority(infix[i]) <= priority(top(&s).cpData) && !isEmpty(&s) && top(&s).cpData != '(' )
             {
                    x = pop(&s).cpData;
                    postfix[j] = x;
                    j++;
                    postfix[j] = ' ';
                    j++;
                    //strcat(postfix,x);
                    //printf("%c",x);
             }
                    val.cpData = infix[i];
                    push(&s,val);
                }
                i++;
    }

            while(!isEmpty(&s) && top(&s).cpData != '(' )
    {
                    //x = pop(&s);
                    postfix[j] = pop(&s).cpData;
                    j++;
                    postfix[j]= ' ';
                    j++;
                    //strcat(postfix,x);
                    //printf("%c",x);
    }

            postfix[j] = '\0';

}
/*
 * evaluatePostfix: Evaluates an expression in postfix notation
 *					 (Reverse-Polish Notation)
 *					ASSUME single-digit operands
 */

float evaluate(char x,float op1,float op2){

        if(x == '+')
            return(op1 + op2);
        if(x == '-')
            return(op1 - op2);
    if(x == '*')
        return(op1 * op2);
    if(x == '/')
            return(op1 / op2);
        if(x == '^')
            return( pow(op1,op2));

}



float evaluatePostfix(char* postfix)
{
	Stack s;
    init(&s);
    char x;
    Item value1 , value2;
    Item result;
    float op1, op2;
    //Item op1, op2, value, val;
    int i=0;

    while (postfix[i] != '\0'){

        x = postfix[i];
    //     if ( x == ' '){
    //
    //          continue;
    //    }
        if(isdigit(postfix[i]))
        {

            value1.fData = atof(&postfix[i]);
    //        printf("%f",value1.fData);
            push(&s,value1);
        }

        else if (isOperator(postfix[i])){
  //              printf("operator");
                op2 = pop(&s).fData;
                op1 = pop(&s).fData;
                value2.fData = evaluate(postfix[i], op1, op2);
                push(&s, value2);
            }

            //result = pop(&s);
            i++;

}
//printf("hi");
            result = pop(&s);
            return result.fData;

}
/*
 *
 */
void replaceNewLineBySpace(char *s) {
    char *s1 = s;
    while((s1 = strstr(s1, "\n")) != NULL)
        *s1 = ' ';
}
/*
 *
 */
int main(int argc, char**argv) {
    char infixExpr[256] = "";
	char postfixExpr[256] = "";

    printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    while(fgets(infixExpr, 255, stdin) != NULL)
    {
        replaceNewLineBySpace(infixExpr);

        infixToPostfix(infixExpr, postfixExpr);
        printf("Postfix : %s\n", postfixExpr);

		float result = evaluatePostfix(postfixExpr);
        printf("Result: %f\n\n", result);

		printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
	}
	return 0;
}

