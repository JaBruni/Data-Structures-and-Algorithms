/*********************************************************************************
* Jason Bruni, jabruni
* 2022 Winter CSE101 PA1
* Lex.c
* client module for List ADT
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"

#define MAX_LEN 300

int main(int argc, char * argv[]){
	int line_count=0;
	FILE *in, *out;
	char line[MAX_LEN];
	char* str;
	
	// check command line for correct number of arguments
	if(argc!=3){
		fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}
	
	// open files for reading and writing
	in = fopen(argv[1], "r");
	if(in==NULL){
		printf("unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	
	out = fopen(argv[2], "w");
	if(out==NULL){
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);
	}
	
	// count number of lines
	while(fgets(line, MAX_LEN, in) != NULL){
		str = line;
		line_count++;
	}
	
	// dynamically allocate memory for string array
	char** token_list = calloc(line_count, sizeof(char*));
	int n=0;
	
	// go back to beginning of file
	rewind(in);
	
	// read in strings to the array
	while(fgets(line, MAX_LEN, in) != NULL){
		if(strcmp(line,"\n")==0){
			str = line;
		}
		else{
			str = strtok(line, "\n");
		}
		char* e = calloc(line_count, sizeof(char*) + 1);
		strcpy(e, str);
		token_list[n] = e;
		n++;
	}
	
	List R = newList();
	append(R, 0);
	//insertion sort
	for(int i = 1; i < line_count;i++){
		char* e = token_list[i];
		int j = i-1;
		moveBack(R);
		while(j>=0 && strcmp(e, token_list[get(R)])<=0){
			j--;
			movePrev(R);
		}
		if(index(R)>=0){
			insertAfter(R, i);
		}
		else{
			prepend(R, i);
		}
	}
	
	// print out array
	moveFront(R);
	while(index(R)>=0){
		fprintf(out, "%s\n", token_list[get(R)]);
		moveNext(R);
	}
	freeList(&R);
	
	for(int i=0; i<line_count; i++){
		free(token_list[i]);
	}
	free(token_list);
	
	fclose(in);
	fclose(out);
			
	return(0);
}
