// trace.cpp is a tool meant to be used in conjunction with either
// huffman.cpp or unhuffman.cpp and prints out extra information if the
// TRACING_ENABLED global is set to 1, which can be set using the tracing
// function.

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include "tree.h"


using namespace std;

int TRACING_ENABLED = 0;


// printDesc(c) prints out a character description cooresponding with
// character c.

void printDesc(const unsigned char c)
{
	if(TRACING_ENABLED)
	{
		if(isprint(c))
		{
			if(c == ' ')
			{
				cout << "space";
			}
			else
			{
				cout << c;
			}
		}
		else if(c == '\n')
		{
			cout << "\\n";
		}
		else if(c == '\t')
		{
			cout << "\\t";
		} 
		else
		{
			cout << "\\" << (int) c;
		}
	}
}


//printTree(t) prints out a textual representation of Tree t.

void printTree(const Tree t)
{
    if(TRACING_ENABLED)
    {
	if(t->kind == leaf)
	{
		printDesc(t->ch);
	}
	else
	{
		cout << "(";
		printTree(t->left);
		cout << ",";
		printTree(t->right);
		cout << ")";
	}
    }
}

// freqCount(freq) prints out a list of character frequencies from
// array freq.

void freqCount(int* freq)
{
	if(TRACING_ENABLED)
	{
		for(int i = 0; i < 256; i++)
		{
			if(freq[i] > 0)
			{
				printDesc(i);
				cout << " : " << freq[i] << endl;
			}
		}

		cout << endl;
	}
}

// tracing(argc, argv) sets the TRACING_ENABLED global to 1 if the -t flag is
// added

void tracing(int argc, char* argv[])
{
	if(argc == 3)
	{
		TRACING_ENABLED = 0;
	}
	else if(argc == 4 && strcmp(argv[1], "-t") == 0)
	{
		TRACING_ENABLED = 1;
	}
	else
	{
		cout << "usage: " << argv[0] << " [-t] data output\n";
		exit(1);
	}
}


//showCode(Code) prints out a list of huffman codes from string array Code

void showCode(char** Code)
{
    if(TRACING_ENABLED)
    {
	    for(int i = 0; i < 256; i++)
	    {
		    if(Code[i] != NULL)
		    {
			    printDesc(i);
			    cout << " : " << Code[i]  << endl;
		    }
	    }
    }
}
