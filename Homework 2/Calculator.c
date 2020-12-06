// DISCLAIMER: My peer-mentor Daniel Pietz helped in the creation of this 
// code by explaining a pseudocode layout for a basic calculator program
// and helping me through the debugging phase.

// Andrea Gray
// CEC332 HW 2
// DUE: 8 FEB 2019

// Header Files
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

// #defines
#define MAX_EXPRESSION_LENGTH 128

// Function Prototypes
int getMatching(char* str, int index);
bool isBalanced(char* str);
char * subString(char *s, int i, int f);
char * extractParen(char *str);
char** str_split(char* a_str, int index);
int findFirst(char *s, char c);
int findNext(char *str, char del, int ind);
double evalBinaryExpression(char *expression);
char ** extractSubtraction(char *str);
double extractExpresion(char *str);
char ** extractAddition(char *str);
char ** extractMultiplication(char *str);
char ** extractDivision(char *str);
int returnToken(char *str);

// Global Variables
int countS;
int countA;
int countM;
int countD;

int main(int argc, const char * argv[]) {
    char string[30];
    char *str = string;
	scanf("%s", string);
    countS = 0;
    countA = 0;
    countM = 0;
    countD = 0;
	returnToken(str);
    printf("%f\n",extractExpresion(str));
    return 0;
}

int returnToken(char *str) {
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] == '(' || str[i] == ')') {
			printf("\rspecial_character");
		}
		else if (str[i] == ('+' || '-' || '*' || '/') {
			printf("\roperator");
		}
		else if (str[i] == ' ') {
			printf("\r\u03B5");
		}
		else {
			printf("\rdigit");
		}
	}
	print("$$");
}

int getMatching(char* str, int index) {
    for (int i = index+1, j = 1; i < strlen(str); i++) {
        if(str[i] == '(') {
			j++;
		}
        else if(str[i] == ')') {
			j--;
		}
        if(j == 0) {
			return i;
		}
    }
    return 0;
}

bool isBalanced(char* str) {
    int j = 0;
    for (int i = 0; i < strlen(str); i++) {
        if(str[i] == '(') j++;
        else if(str[i] == ')') j--;
    }
    if(j == 0) return true;
    return false;
}

char * subString(char *s, int i, int f) {
    char * test = (char*) malloc(f-i);
    for (int p = i; p < f; p++) {
        test[p-i] = s[p];
    }
    return test;
}

double extractExpresion(char *str) {
    char **sub = extractSubtraction(str);
    double current = 0;
    for (int A = 0; A < countS; A++) {
        double currentAd = 0;
        char **add = extractAddition(sub[A]);
        double currentMP = 1;
        for (int M = 0; M < countA; M++) {
            char **mult = extractMultiplication(add[M]);
            for (int MP = 0; MP < countM; MP++) {
                currentMP *= atof(mult[MP]);
            }
            currentAd += currentMP;
            currentMP = 1;
        }
        for (int AP = countA; AP >= 0; AP--) {
            current =  currentAd - current;
            currentAd = 0;
        }
    }
    return current;
}

char ** extractSubtraction(char *str) {
    int last = 0;
    char **expressions =(char**)(malloc(strlen(str)*sizeof(char**)));
    int count = 0;
    for (int i = 0; i <= strlen(str); i++) {
        int ind = findNext(str, '-', last);
        if(ind != last) {
            expressions[count] = subString(str, last, ind);
            last = ind+1;
            count++;
        }
        else if (ind == last) {
            expressions[count] = subString(str, last, strlen(str));
            count++;
            break;
        }
    }
    countS = count;
    return expressions;
}

char ** extractAddition(char *str) {
    int last = 0;
    char **expressions = (char**)(malloc(strlen(str)*sizeof(char**)));
    int count = 0;
    for (int i = 0; i <= strlen(str); i++) {
        int ind = findNext(str, '+', last);
        if(ind != last) {
            expressions[count] = subString(str, last, ind);
            last = ind+1;
            count++;
        }
        else if (ind == last) {
            expressions[count] = subString(str, last, strlen(str));
            break;
        }
    }
    countA = count+1;
    return expressions;
}

char ** extractMultiplication(char *str) {\
    int last = 0;
    char **expressions =(char**)(malloc(strlen(str)*sizeof(char**)));
    int count = 0;
    for (int i = 0; i <= strlen(str); i++) {
        int ind = findNext(str, '*', last);
        if(ind != last) {
            expressions[count] = subString(str, last, ind);
            last = ind+1;
            count++;
        }
        else if (ind == last) {
            expressions[count] = subString(str, last, strlen(str));
            break;
        }
    }
    countM = count+1;
    return expressions;
}

char ** extractDivision(char *str) {
    int last = 0;
    char **expressions =(char**)(malloc(strlen(str)*sizeof(char**)));
    int count = 0;
    for (int i = 0; i <= strlen(str); i++) {
        int ind = findNext(str, '/', last);
        if(ind != last) {
            expressions[count] = subString(str, last, ind);
            last = ind+1;
            count++;
        }
        else if (ind == last) {
            expressions[count] = subString(str, last, strlen(str));
            break;
        }
    }
    countD = count;
    return expressions;
}

int findNext(char *str, char del, int ind) {
    for (int i = ind+1; i < strlen(str); i++) {
        if (str[i] == del) {
            return i;
        }
    }
    return ind;
}

char * extractParen(char *str) {
    static char expressions[MAX_EXPRESSION_LENGTH];
    int count = 0;
    int last = 0;
    for (int i = 0; i <= strlen(str); i++) {
        if(str[i] == '(') {
            printf("%s\n",subString(str, last, i));
            printf("%s\n",subString(str, i+1, getMatching(str, i)));
            expressions[count] = *subString(str, i+1, getMatching(str, i));
            count++;
            i = getMatching(str, i);
            last = i+1;
        }
        if(i == strlen(str)) {
            printf("%s\n",subString(str, last, i));
        }
    }
    return expressions;
}

int findFirst(char *s, char c) {
    for(int i = 0; i < strlen(s); i++) {
        if(s[i] == c) {
			return i;
		}
    }
    return -1;
}

double evalBinaryExpression(char *expression) {
    char operators[] = {'+','*','-', '/'};
    int q = 0;
    int ip = 0;
    for(int i = 0; i < sizeof(operators)/sizeof(char); i++) {
        for (int j = 0; j < strlen(expression); j++) {
            if ((int)operators[i] == (int)expression[j]) {
                q = j;
                ip = i;
            }
        }
    }
    char **s = str_split(expression, q);
    switch (operators[ip]) {
        case '+':
            return atof(s[0]) + atof(s[1]);
            break;
        case '*':
            return atof(s[0]) * atof(s[1]);
            break;
        case '-':
            return atof(s[0]) - atof(s[1]);
            break;
        case '/':
            return atof(s[0]) / atof(s[1]);
            break;
        default:
            break;
    }
    return 1;
}

char** str_split(char* a_str, int index)
{
    static char *result[2];
    char *temp =(char*)(malloc(index*sizeof(char*)));
    for (int i = 0; i < index; i++) {
        temp[i] = a_str[i];
    }
    result[0] = temp;
    temp =(char*)(malloc((strlen(a_str)-index)*sizeof(char*)));
    for (int i = index+1; i < strlen(a_str); i++) {
        temp[i-index-1] = a_str[i];
    }
    result[1] = temp;
    return result;
}

char * removeChar(char *s, int c){
    int j, n = strlen(s);
    for (int i=j=0; i<n; i++) {
        if (s[i] != c) {
            s[j++] = s[i];
		}
    }
    s[j] = '\0';
    return s;
}