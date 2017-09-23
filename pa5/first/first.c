#include"first.h"

Variable* findMatch(char target, Variable* inputVariables, Variable* outVariables, Variable* tempVariables, int num, int numVars, int numOut){
	
	int i = 0;
	
	//Searching through inputs and temp vars
	if(num == 0){
		for(i = 0; i < numVars; i++){
			if(target == inputVariables[i].letter){
				return &inputVariables[i];
			}
		}
		
		for(i = 0; i < 26; i++){
			if(target == tempVariables[i].letter){
				return &tempVariables[i];
			}
		}
		for(i = 0; i < 26; i++){
			if(tempVariables[i].letter == '0'){
				tempVariables[i].letter = target;
				tempVariables[i].value = 0;
				
				return &tempVariables[i];
			}
		}
		
	}
	
	//Searching through outputs and temp vars
	else if(num == 1){
		for(i = 0; i < numVars; i++){
			if(target == tempVariables[i].letter){
				return &tempVariables[i];
			}
		}
		for(i = 0; i < numOut; i++){
			if(target == outVariables[i].letter){
				return &outVariables[i];
			}
		}
		for(i = 0; i < 26; i++){
			if(tempVariables[i].letter == '0'){
				tempVariables[i].letter = target;
				tempVariables[i].value = 0;
				
				return &tempVariables[i];
			}
		}
	}
	
	//Searching through inputs, outputs, and temp vars
	else{
		for(i = 0; i < numVars; i++){
			if(target == inputVariables[i].letter){
				return &inputVariables[i];
			}
		}
		
		for(i = 0; i < 26; i++){
			if(target == tempVariables[i].letter){
				return &tempVariables[i];
			}
		}
		for(i = 0; i < numOut; i++){
			if(target == outVariables[i].letter){
				return &outVariables[i];
			}
		}
		
		for(i = 0; i < 26; i++){
			if(tempVariables[i].letter == '0'){
				tempVariables[i].letter = target;
				tempVariables[i].value = 0;
				
				return &tempVariables[i];
			}
		}
	}
	
	return NULL;
}

void orBits(Variable* firstMatch, Variable* secondMatch, Variable* saveToMatch){
	if((firstMatch->value == 1) || (secondMatch->value == 1)){
		saveToMatch->value = 1;
	}
	else{
		saveToMatch->value = 0;
	}
	
}

void andBits(Variable* firstMatch, Variable* secondMatch, Variable* saveToMatch){

	if((firstMatch->value == 1) && (secondMatch->value == 1)){
		saveToMatch->value = 1;
	}
	else{
		saveToMatch->value = 0;
	}	

}

void notBits(Variable* firstMatch, Variable* saveToMatch){
	if(firstMatch->value == 1){
		saveToMatch->value = 0;
	}
	else{
		saveToMatch->value = 1;
	}
	
}

int* grayCode(int numBits){
	int* grayResult = (int*) malloc(sizeof(int) * numBits);
	int i = 0;
	
	for(i = 0; i < numBits; i++){
		grayResult[i] = i^(i/2);
		
		//printf("grayInt = %d\n", grayResult[i]);
	}
	
	return grayResult;
}

void muxBits(Variable* muxVariables, Variable* selectorVariables, int numMux, int numSelector, Variable* saveToMatch){
	
	//Going to have to do some binary conversion!
	int index = 0;
	int i = 0;
	int mult = 0;
	
	
	int* gray;

	
	for(i = numSelector - 1; i > -1; i--){
		index = index + (selectorVariables[i].value * pow(2, mult));
		mult++;
	}
	
	gray = grayCode(numMux);
	
	for(i = 0; i < numMux; i++){
		if(index == gray[i]){
			break;
		}
	}
	
	saveToMatch->value = muxVariables[i].value;
	
}


int main(int argc, char* argv[]){
	if(argc != 3){
		printf("Incorrect number of files.\n");
		return 0;
	}
	
	FILE* inputfile = fopen(argv[2], "r");
	FILE* circuitfile = fopen(argv[1], "r");
	
	
	int numVars = 0;
	int numOut = 0;
	int count = 0;
	int i = 0;
	int j = 0;
	int mult = 0;
	int numMux = 0;
	int numSelector = 0;
	int numDecIn = 0;
	int numDecOut = 0;
	int decGrayOne = 0;
	int indexGrayOne = 0;
	
	int* gray;
	
	char currlineCirc[100];
	char currlineInput[100];
	char* tokenCirc = NULL;
	char* tokenInput = NULL;
	char* inputPointer = NULL;
	char* circPointer = NULL;
	char* operation = NULL;
	
	char tokenTemp = '0';
	char first = '0';
	char second = '0';
	char saveTo = '0';

	Variable* firstMatch = NULL;
	Variable* secondMatch = NULL;
	Variable* saveToMatch = NULL;
	
	
	Variable* inputVariables = NULL;
	Variable* outVariables = NULL;
	Variable* tempVariables = NULL;
	Variable* muxVariables = NULL;
	Variable* selectorVariables = NULL;
	Variable* decInVariables = NULL;
	Variable* decOutVariables = NULL;
	
	Variable* temp = NULL;
	
	while(fgets(currlineInput, 100, inputfile) != NULL){
	
		fgets(currlineCirc, 100, circuitfile);
		
		//printf("\nnew input\n");
		
		//printf("%s\n", currlineCirc);
	
		
		//printf("%s\n", currlineInput);
	
		tokenCirc = strtok_r(currlineCirc, " ", &circPointer);
		tokenInput = strtok_r(currlineInput, " ", &inputPointer);
		
		count = 0;
	
		while(tokenCirc != NULL){
			if(count == 1){
				numVars = atoi(tokenCirc);
				
				//printf("numVars = %d\n", numVars);
				
				break;
			}
			tokenCirc = strtok_r(NULL, " ", &circPointer);
			
			//printf("tokenCirc = %s\n", tokenCirc);
			
			count++;
		}
	
	
		inputVariables = (Variable*) malloc(sizeof(Variable) * numVars);
	
		for(i = 0; i < numVars; i++){
			inputVariables[i].letter = '0';
			inputVariables[i].value = 0;
		}
	
		count = 0;
		tokenCirc = strtok_r(NULL, " ", &circPointer);
	
		while(tokenCirc != NULL){
		
		
			inputVariables[count].letter = tokenCirc[0];
			
			//printf("%c = ", inputVariables[count].letter);
		
			inputVariables[count].value = atoi(tokenInput);
			
			//printf("%d\n", inputVariables[count].value);
		
			tokenInput = strtok_r(NULL, " ", &inputPointer);
			tokenCirc = strtok_r(NULL, " ", &circPointer);
			
			//printf("tokenCirc = %s\n", tokenCirc);
		
			count++;
		}
	
		//printf("numVars = %d\n", numVars);
	
		tempVariables = (Variable*) malloc(sizeof(Variable) * 26);
		
		for(i = 0; i < 26; i++){
			tempVariables[i].letter = '0';
			tempVariables[i].value = 0;
		}
	
	
		//NEW LINE = NEW CURRLINE BEFORE NULL
		fgets(currlineCirc, 100, circuitfile);
		
		//printf("%s\n", currlineCirc);
	
		tokenCirc = strtok_r(currlineCirc, " ", &circPointer);
	
		count = 0;
	
		while(tokenCirc != NULL){
			if(count == 1){
				numOut = atoi(tokenCirc);
				break;
			}
			tokenCirc = strtok_r(NULL, " ", &circPointer);
			count++;
		}
	
		count = 0;
	
		outVariables = (Variable*) malloc(sizeof(Variable) * numOut);
	
		tokenCirc = strtok_r(NULL, " ", &circPointer);
	
		while(tokenCirc != NULL){
		
		
			outVariables[count].letter = tokenCirc[0];
			outVariables[count].value = 0;
			count++;
			tokenCirc = strtok_r(NULL, " ", &circPointer);
		}
		
		while(fgets(currlineCirc, 100, circuitfile) != NULL){
		
			//printf("\ncurrlineCirc = %s", currlineCirc);
			
			
			operation = strtok_r(currlineCirc, " ", &circPointer);
			
			//printf("operation = %s\n", operation);
			
			if((strcmp(operation, "AND") == 0) || (strcmp(operation, "OR") == 0)){
				
				tokenCirc = strtok_r(NULL, " ", &circPointer);
				first = tokenCirc[0];
				
				tokenCirc = strtok_r(NULL, " ", &circPointer);
				second = tokenCirc[0];
				
				tokenCirc = strtok_r(NULL, " ", &circPointer);
				saveTo = tokenCirc[0];
				
				//printf("saveTo letter = %c\n\n", saveTo);
				if(first == '1'){
					firstMatch->letter = '1';
					firstMatch->value = 1;
				}
				else if(first == '0'){
					firstMatch->letter = '0';
					firstMatch->value = 0;
				}
				else{
					firstMatch = findMatch(first, inputVariables, outVariables, tempVariables, 0, numVars, numOut);
				}
				
				if(second == '1'){
					secondMatch->letter = '1';
					secondMatch->value = 1;
				}
				else if(second == '0'){
					secondMatch->letter = '0';
					secondMatch->value = 0;
				}
				else{
					secondMatch = findMatch(second, inputVariables, outVariables, tempVariables, 0, numVars, numOut);
				}
				
				
				saveToMatch = findMatch(saveTo, inputVariables, outVariables, tempVariables, 1, numVars, numOut);
	
				if(strcmp(operation, "OR") == 0){
					orBits(firstMatch, secondMatch, saveToMatch);
				}
				else if(strcmp(operation, "AND") == 0){
					andBits(firstMatch, secondMatch, saveToMatch);
				}
				
			}
			else if(strcmp(operation, "NOT") == 0){
				tokenCirc = strtok_r(NULL, " ", &circPointer);
				first = tokenCirc[0];
				//printf("first = %c\n", first);
				
				firstMatch = findMatch(first, inputVariables, outVariables, tempVariables, 2, numVars, numOut);
				
				tokenCirc = strtok_r(NULL, " ", &circPointer);
				saveTo = tokenCirc[0];
				//printf("saveTo = %c\n", saveTo);
				
				saveToMatch = findMatch(saveTo, inputVariables, outVariables, tempVariables, 2, numVars, numOut);
				
				notBits(firstMatch, saveToMatch);
			}
			else if(strcmp(operation, "MULTIPLEXER") == 0){
				numMux = atoi(strtok_r(NULL, " ", &circPointer));
				
				//printf("numMux = %d\n", numMux);
				
				muxVariables = (Variable*) malloc(sizeof(Variable) * numMux);
				
				for(i = 0; i < numMux; i++){
					muxVariables[i].letter = '0';
					muxVariables[i].value = 0;
				}
				
				for(i = 0; i < numMux; i++){
					tokenCirc = strtok_r(NULL, " ", &circPointer);
					tokenTemp = tokenCirc[0];
					
					if(tokenTemp == '0'){
						muxVariables[i].letter = '0';
						muxVariables[i].value = 0;
					}
					else if(tokenTemp == '1'){
						muxVariables[i].letter = '1';
						muxVariables[i].value = 1;
					}
					else{
						temp = findMatch(tokenTemp, inputVariables, outVariables, tempVariables, 2, numVars, numOut);
			
						muxVariables[i].letter = temp->letter;
						muxVariables[i].value = temp->value;
					}
				}
				
				numSelector = log10((double)numMux) / log10(2);
				
				//printf("numSelector = %d\n", numSelector);
				
				
				
				selectorVariables = (Variable*) malloc(sizeof(Variable) * numSelector);
				for(i = 0; i < numSelector; i++){
					selectorVariables[i].letter = '0';
					selectorVariables[i].value = 0;
				}
				
				for(i = 0; i < numSelector; i++){
					tokenCirc = strtok_r(NULL, " ", &circPointer);
					tokenTemp = tokenCirc[0];
					
					//printf("tokenTemp = %c\n", tokenTemp);
					
					if(tokenTemp == '0'){
						selectorVariables[i].letter = '0';
						selectorVariables[i].value = 0;
					}
					else if(tokenTemp == '1'){
						selectorVariables[i].letter = '1';
						selectorVariables[i].value = 1;
					}
					else{
						temp = findMatch(tokenTemp, inputVariables, outVariables, tempVariables, 2, numVars, numOut);
			
						selectorVariables[i].letter = temp->letter;
						selectorVariables[i].value = temp->value;
					}
				}
				
				tokenCirc = strtok_r(NULL, " ", &circPointer);
				saveTo = tokenCirc[0];
				
				//printf("saveTo = %c\n", saveTo);
				
				saveToMatch = findMatch(saveTo, inputVariables, outVariables, tempVariables, 2, numVars, numOut);
				
				//printf("saveToMatch search success\n");
				
				
				muxBits(muxVariables, selectorVariables, numMux, numSelector, saveToMatch);
			}
			else{
				numDecIn = atoi(strtok_r(NULL, " ", &circPointer));
				numDecOut = pow(2, numDecIn);
				
				//printf("numDecIn = %d numDecOut = %d\n", numDecIn, numDecOut);
				
				decInVariables = (Variable*) malloc(sizeof(Variable) * numDecIn);
				
				for(i = 0; i < numDecIn; i++){
					decInVariables[i].letter = '0';
					decInVariables[i].value = 0;
				}
				
				for(i = 0; i < numDecIn; i++){
					tokenCirc = strtok_r(NULL, " ", &circPointer);
					tokenTemp = tokenCirc[0];
					
					//printf("tokenTemp = %c\n", tokenTemp);
					
					if(tokenTemp == '0'){
						decInVariables[i].letter = '0';
						decInVariables[i].value = 0;
					}
					else if(tokenTemp == '1'){
						decInVariables[i].letter = '1';
						decInVariables[i].value = 1;
					}
					else{
						temp = findMatch(tokenTemp, inputVariables, outVariables, tempVariables, 2, numVars, numOut);
			
						decInVariables[i].letter = temp->letter;
						decInVariables[i].value = temp->value;
					}
				}
				
				decGrayOne = 0;
				mult = 0;
				indexGrayOne = 0; 
				for(i = numDecIn - 1; i > -1; i--){
					decGrayOne = decGrayOne + (decInVariables[i].value * pow(2, mult));
					mult++;
				}
				//printf("numDecOut = %d\n", numDecOut);
				
				//printf("decGrayOne = %d\n", decGrayOne);
				
				gray = grayCode(numDecOut);
				
				
				for(i = 0; i < numDecOut; i++){
					if(gray[i] == decGrayOne){
						indexGrayOne = i;
						break;
					}
				}
				
				//printf("indexGrayOne = %d\n", indexGrayOne);
				
				decOutVariables = (Variable*) malloc(sizeof(Variable) * numDecOut);
				
				for(i = 0; i < numDecOut; i++){
					decOutVariables[i].letter = '0';
					decOutVariables[i].value = 0;
				}
				
				for(i = 0; i < numDecOut; i++){
					tokenCirc = strtok_r(NULL, " ", &circPointer);
					tokenTemp = tokenCirc[0];
					
					if(tokenTemp == '0'){
						decOutVariables[i].letter = '0';
						decOutVariables[i].value = 0;
					}
					else if(tokenTemp == '1'){
						decOutVariables[i].letter = '1';
						decOutVariables[i].value = 1;
					}
					else{
						temp = findMatch(tokenTemp, inputVariables, outVariables, tempVariables, 2, numVars, numOut);
			
						decOutVariables[i].letter = temp->letter;
						decOutVariables[i].value = temp->value;
					}
				}
				
				//printf("DECODER RESULTS = ");
				for(i = 0; i < numDecOut; i++){
					if(i == indexGrayOne){
						decOutVariables[i].value = 1;
					}
					else{
						decOutVariables[i].value = 0;
					}
					
					//printf("%c = %d ", decOutVariables[i].letter, decOutVariables[i].value);
				}
				
				for(i = 0; i < 26; i++){
					for(j = 0; j < numDecOut; j++)
						
						if(tempVariables[i].letter == decOutVariables[j].letter){
							tempVariables[i].value = decOutVariables[j].value;
							break;
						}
						
				}
				
				for(i = 0; i < numOut; i++){
					for(j = 0; j < numDecOut; j++){
						if(outVariables[i].letter == decOutVariables[j].letter){
							outVariables[i].value = decOutVariables[j].value;
						}
					}
				}
				
				//printf("\n");
			}
		}
		
		
		for(i = 0; i < numOut; i++){
			//printf("OUTPUT: %c = %d\n", outVariables[i].letter, outVariables[i].value);
			printf("%d ", outVariables[i].value);
		}
		printf("\n");
		//RESETS FOR NEXT INPUT
		free(inputVariables);
		free(outVariables);
		rewind(circuitfile);
	}
	
	
	
	return 0;
}
