#ifndef TRACE_H
#define TRACE_H

extern int TRACING_ENABLED;


void printDesc(const unsigned char c);
void printTree(const Tree t);
void freqCount(int* freq);
void tracing(int argc, char* argv[]);
void showCode(char** Code);


#endif
