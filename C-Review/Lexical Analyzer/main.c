#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"
#include "tools.h"

static void run(const char*source){
    initScanner(source);
    int line=-1;
    for(;;){
        Token token =scanToken();
        if(token.line!=line){
            printf("%4d",token.line);
            line=token.line;
        }else{
            printf("  |");
        }
        char *str=convert_to_str(token);
        printf("%s '%.*s'\n",str,token.length,token.start);
        if(token.type==TOKEN_EOF)break;
    }
}

static void repl(){
    char line[1024];
    for(;;){
        printf("> ");
        if(fgets(line,sizeof(line),stdin)==NULL){
            printf("\n");
            break;
        }
        run(line);
    }
}

static char* readFile(const char*path){
    FILE*file=fopen(path,"rb");
    if(file==NULL){
        fprintf(stderr,"Could not open file\"%s\".\n",path);
        exit(1);
    }
    fseek(file,0L,SEEK_END);
    size_t fileSize=ftell(file);
    rewind(file);
    char*buffer=(char*)malloc(fileSize+1);
    if(buffer==NULL){
        fprintf(stderr,"Not enough memory to read\"%s\".\n",path);
        exit(1);
    }
    size_t byteRead=fread(buffer,sizeof(char),fileSize,file);
    if(bytesRead<fileSize){
        fprintf(stderr,"could not read file \"%s\".\n",path);
        exit(1);
    }
    buffer[bytesRead]='\0';
    fclose(file);
    return buffer;
}


int main()
{
    printf("Hello world\n");
    return 0;
}

