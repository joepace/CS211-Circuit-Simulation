#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

typedef struct Variable{
	char letter;
	int value;
}Variable;

Variable* findMatch(char target, Variable* inputVariables, Variable* outVariables, Variable* tempVariables, int num, int numVars, int numOut);

void orBits(Variable* firstMatch, Variable* secondMatch, Variable* saveToMatch);

void andBits(Variable* firstMatch, Variable* secondMatch, Variable* saveToMatch);

void notBits(Variable* firstMatch, Variable* saveToMatch);

int* grayCode(int numBits);

void muxBits(Variable* muxVariables, Variable* selectorVariables, int numMux, int numSelector, Variable* saveToMatch);
