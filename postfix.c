/* postfix.c
*
* Data Structures, Homework #5
* School of Computer Science at Chungbuk National University
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20
/* stack 내에서 우선순위, lparen = 0 가장 낮음 */


typedef enum{
    lparen = 0, /* ( 왼쪽 괄호 */
    rparen = 9, /* ) 오른쪽 괄호*/
    times = 7, /* * 곱셈 */
    divide = 6, /* / 나눗셈 */
    plus = 5, /* + 덧셈 */
    minus = 4, /* - 뺄셈 */
    operand = 1 /* 피연산자 */
} precedence;
    
char infixExp[MAX_EXPRESSION_SIZE]; /* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE]; /* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE]; /* postfix로 변환을 위해 필요한 스택*/
int evalStack[MAX_STACK_SIZE]; /* 계산을 위해 필요한 스택 */
int postfixStackTop = -1; /* postfixStack용 top */
int evalStackTop = -1; /* evalStack용 top */
int evalResult = 0; /* 계산 결과를 저장 */


void postfixpush(char x); //postfix 스택에 push 하는 함수
char postfixPop();//postfix 스택에서 pop하는 함수
void evalPush(int x); //계산 스택에 push하는 함수
int evalPop();//계산 스택에서 pop하는 함수
void getInfix(); //infix 표기의 계산식을 입력 받는 함수
precedence getToken(char symbol); // 문자의 토큰을 반환하는 함수
precedence getPriority(char x);//문자의 우선순위를 반환하는 함수
void charCat(char* c); //문자 하나를 전달받아, postfixExp에 추가하는 함수
void toPostfix(); //postfix로 변환하는 함수
void debug(); //디버깅용 함수
void reset(); //초기화용 함수
void evaluation(); //계산 함수



int main()
{

printf("[-----[유도현][2022041001]-----]\n\n");
char command; //명령 저장용 변수
do{

   
    printf("----------------------------------------------------------------\n");
    printf(" Infix to Postfix, then Evaluation\n");
    printf("----------------------------------------------------------------\n");
    printf(" Infix=i, Postfix=p, Eval=e, Debug=d,Reset=r, Quit=q \n");
    printf("----------------------------------------------------------------\n");
    printf("Command = "); //양식
    scanf(" %c", &command);//명령 입력 받기
    switch(command) {
    case 'i': case 'I':
        getInfix(); //위와 같이 입력시 infix표기 계산식 입력 받기
        break;
    case 'p': case 'P':
        toPostfix();//위와 같이 입력시 입력 받은 계산식을 postfix로 변환
        break;
    case 'e': case 'E':
        evaluation();//위와 같이 입력시 계산식을 계산
        break;
    case 'd': case 'D':
        debug(); //위와 같이 입력시 디버깅 실행
        break;
    case 'r': case 'R':
        reset(); //위와 같이 입력시 모든 스택 초기화
        break;
    case 'q': case 'Q':
        break;

        default:
        printf("\n >>>>> Concentration!! <<<<<\n"); //예정되지 않은 명령어 입력시 출력
        break;
    }
}while(command != 'q' && command != 'Q'); //q, Q를 입력 받았을 시 반복 종료


return 1;
}



void postfixPush(char x){ //postfix 스택에 push 하는 함수
postfixStack[++postfixStackTop] = x;
//postfix 스택의 top부분의 위치를 하나 위로 올리고 그 위치에 전달받은 데이터 넣기
}


char postfixPop(){
    char x; //임시저장용 변수
    if(postfixStackTop == -1)
        return '\0';//만약 스택이 비어있으면 NULL 반환
    else {
        x = postfixStack[postfixStackTop--];
        //아니라면 postfix 스택의 top위치의 데이터를 x에 넣고 top의 위치를 하나 아래로 
        }
    return x;//x반환
}



void evalPush(int x){//eval 스택에 push하는 함수

    evalStack[++evalStackTop] = x;
    //eval스택의 top 부분의 위치를 하나 위로 올리고 그 위치에 전달 받은 값 넣기
}


int evalPop(){

    if(evalStackTop == -1) //top의 위치가 -1이라면
    return -1; //아래 과정 생략, -1반환
    else //아니라면
    return evalStack[evalStackTop--];//top위치의 데이터 반환후 top의 위치 하나 내리기
}


/**
* infix expression을 입력받는다.
* infixExp에는 입력된 값을 저장한다.
*/


void getInfix() {
    
    printf("Type the expression >>> ");//양식
    scanf("%s",infixExp);//infix 표기의 계산식 입력 받기
}


precedence getToken(char symbol){ //symbol 의 토큰을 반환하는 함수

    switch(symbol) {//전달 받은 변수가
    case '(' : return lparen; //(라면 lparen 반환
    case ')' : return rparen; //)라면 rparen 반환
    case '+' : return plus; //+라면 plus 반환
    case '-' : return minus; //-라면 minus 반환
    case '/' : return divide; // /라면 divide 반환
    case '*' : return times; // *라면 times 반환
    default : return operand; // 전부 아니라면 operand 반환
    }
}
precedence getPriority(char x){//우선순위 반환 함수

    return getToken(x);//x의 토큰을 반환
    }

/**
* 문자하나를 전달받아, postfixExp에 추가
*/
void charCat(char* c){

    if (postfixExp[0] == '\0')//만약 postfix 문자열이 이 비어있다면
    strncpy(postfixExp, c, 1);//문자열 시작 부분에 c 복사
    else//아니라면
    strncat(postfixExp, c, 1);//문자열이 끝나는 위치 뒤에 c 붙이기 (append)
    }

/**
* infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
* 변경된 postfix는 postFixExp에 저장된다.
*/

void toPostfix(){
    /* infixExp의 문자 하나씩을 읽기위한 포인터 */
    char *exp = infixExp;
    char x; /* 문자하나를 임시로 저장하기 위한 변수 */
    /* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
    while(*exp != '\0')//infix 배열이 끝날때 까지
    {
        if(getPriority(*exp) == operand) { //만약 배열 요소의 우선순위가 피연산자라면
             x = *exp; //x에 exp가 가리키는 값 넣기
        charCat(&x);//postfix 문자열에 피연산자 집어넣기
    }
 else if(getPriority(*exp) == lparen) {//만약 배열 요소의 우선순위가 좌괄호라면
        postfixPush(*exp);  //postfix 스택에 push하기
        }        
        
        else if(getPriority(*exp) == rparen) {  //만약 배열 요소 우선순위가 우괄호라면
            
            while((x = postfixPop()) != '(') {//postfix 스택에서 좌괄호가 pop 될때까지
                    charCat(&x); //postfix 문자열에 x를 append        
            }        
        }        
        
        else{            //아니라면
            while(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp)){   
                    //만약 postfix 스택의 top부분의 우선순위가 infix 배열 요소의 우선순위보다 높다면
                x = postfixPop();           
                charCat(&x);     //postfix 스택에서 pop한 값을 postfix 문자열에 append       
                }            
            postfixPush(*exp);  //배열 요소를 postfix 스택에 push
            }        
            exp++; //가리키는 배열 요소 위치를 하나 뒤로
            }    
            
            while(postfixStackTop != -1){    //poxtfix 스택이 비어있을때 까지
                x = postfixPop();   
                charCat(&x);   //postfix 스택의 값을 pop해서 postfix 문자열에 append
            }




    /* 필요한 로직 완성 */
    }

void debug()
{
    printf("\n---DEBUG\n");
    printf("infixExp = %s\n", infixExp); //infix 문자열 출력
    printf("postExp = %s\n", postfixExp);//postfix 문자열 출력
    printf("eval result = %d\n", evalResult); //계산 결과 출력
    printf("postfixStack : ");
    for(int i = 0; i < MAX_STACK_SIZE; i++)
        printf("%c ", postfixStack[i]);
        printf("\n"); 
    }//postfix 스택의 요소를 전부 출력


void reset(){ //초기화 함수

    for(int i = 0; i < MAX_STACK_SIZE; i++){ //최대스택크기 만큼 반복
        infixExp[i] = '\0'; //infix 배열 초기화
        postfixExp[i] = '\0'; //postfix 배열 초기화
        postfixStack[i] = '\0'; //postfix 스택 초기화
        postfixStackTop = -1; //postfix 스택의 top을 -1로 초기화
        evalStackTop = -1; // eval 스택의 top을 -1로 초기화
        evalResult = 0; // 계산 결과 0으로 초기화
    }

}

void evaluation(){ //계산 함수

    int opr1, opr2, i; //피연산자 1, 피연산자 2, 반복용 변수

    int length = strlen(postfixExp); //길이 = postfix 문자열의 길이
    char symbol; //문자 저장 변수
    evalStackTop = -1; //eval 스택의 top 위치를 -1로

    for(i = 0; i < length; i++) { //length 동안 반복
        symbol = postfixExp[i]; //문자 = postfix 배열의 i번째 요소
        if(getToken(symbol) == operand){ //만약 문자가 피연사자라면
             evalPush(symbol - '0'); //eval 스택에 문자를 숫자로 변환해서 저장
        } 
        
        else { 
            opr2 = evalPop(); //eval 스택에서 pop한 값을 연산자 2로 설정
            opr1 = evalPop(); //eval 스택에서 pop한 값을 연산자 1로 설정
            switch(getToken(symbol)) { //문자의 토큰이
                case plus: //더하기라면
                evalPush(opr1 + opr2); //두 연산자를 더한 값을 eval 스택에 push
                break; 
                
                case minus: //빼기라면
                
                evalPush(opr1 - opr2); //두 연산자를 뺀 값을 eval 스택에 push 
                break; 
                
                case times: //곱하기라면
                
                evalPush(opr1 * opr2); //두 연산자를 곲한 값을 eval 스택에 push
                break; 
                
                case divide: //나누기라면
                
                evalPush(opr1 / opr2); //두 연산자를 나눈 값을 eval 스택에 push
                break;
                
                default: break; 
                } 
                } 
                } 
                
    evalResult = evalPop(); //연산이 전부 끝난 후 eval 스택에서 pop한 값이 계산 결과
}