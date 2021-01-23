// CSCI 2530
// Assignment: 8
// Author:     Cason White
// File:       huffman.cpp
// Tab stops:  8

// huffman.cpp is a program that utilizes huffman codes to compress a given
// text file to a binary .cmp file.

// Huffman is used in the following manner:
// huffman [-t] filetocompress.txt destination.cmp
// if the tracing flag is enabled then additional information
// on the process will be printed to the screen, including a
// tree representation, a list of the frequency of characters in the
// input file, and a printout of the huffman codes of each character.

// An example of usage on a text file containing (with the -t flag)
// "aaabbccd" is as follows:

// File to compress: test.txt
// Destination file: test.cmp

// Printing character frequencies:
// \n : 1
// a : 3
// b : 2
// c : 2
// d : 1


// Building huffman tree...Done
// Creating  huffman code prefixes...Done

// Printing completed Tree:
// (((d,\n),c),(b,a))

// Printing char huffman codes:
// \n : 001
// a : 11
// b : 10
// c : 01
// d : 000

// Writing Binary Tree to test.cmp...Done
// Writing compressed chars to test.cmp...Done

// Compression Complete.

#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include "pqueue.h"
#include "trace.h"
#include "tree.h"
#include "binary.h"

using namespace std;


//zeroArray(Array) zeros out a given 256 length int array.

void zeroArray(int* Array)
{
	for(int i = 0; i < 256; i++)
	{
		Array[i] = 0;
	}
}


//nullCharArray(a) sets each index in a char** array equal to NULL.

void nullCharArray(char** a)
{
	for(int i = 0; i < 256; i++)
	{
		a[i] = NULL;
	}
}


//getFrequency(fileName, freq) reads a file named fileName, and
// places the number of times each seen character appears in an
// array freq, with the index number equivalent to the ASCII code.
// getFrequency returns true if a file of name fileName exists, and
// false if the fileName does not exist.

bool getFrequency(const char* fileName, int* freq)
{
	
	zeroArray(freq);
	
	FILE* f = fopen(fileName, "r");
	if(f == NULL)
	{
		return false;
	}

	int c = getc(f);
	while(c != EOF)
	{
		unsigned x = (unsigned) c;
		freq[x]++;
		c = getc(f);
	}
	
	fclose(f);

	return true;
}


// buildQueue(freq) takes a character frequency array and makes a
// priority queue with the data, sorting the characters by least used
// to most used.  buildQueue then returns a pointer to the newly created
// priority queue.

PriorityQueue* buildQueue(int* freq)
{
	PriorityQueue* freqList = new PriorityQueue;
	for(int i = 0; i < 256; i++)
	{
		if(freq[i] > 0)
		{
			Tree t = new Node(i);
			insert(*freqList, t, freq[i]);
		}
	}

	return freqList;
}


// buildHuff(freq) takes a character frequency array and returns a
// huffman tree with the given data.

Tree buildHuff(int* freq)
{
	Tree r, s;
	int f1, f2;
	
	PriorityQueue* q = buildQueue(freq);

	while(true)
	{
		remove(*q, r, f1);
		
		if(isEmpty(*q))
		{
			return r;
		}

		remove(*q, s, f2);
		
		Tree t = new Node(r, s);
		
		insert(*q, t, f1 + f2);
	}

		
}


// nextPrefix(prefix, bit) returns a new string that is a concatenation
// of prefix and bit.

char* nextPrefix(char* prefix, const char* bit)
{
	char* n = new char[strlen(prefix) + 2];
	strcpy(n, prefix);
	strcat(n, bit);
	return n;
}
	

// buildCode(t, Code, prefix) takes a huffman tree, an empty string array
// and an empty string and stores a list of huffman codes in Code.

void buildCode(Tree t, char** Code, char* prefix)
{
	if(t->kind == leaf)
	{
		unsigned x = (unsigned) t->ch;
		Code[x] = prefix;
		
	}
	else
	{
			
		buildCode(t->left, Code, nextPrefix(prefix, "0"));
		buildCode(t->right, Code, nextPrefix(prefix, "1"));

		delete prefix;

	}
}


// writeBinTree(f, t), takes an open binary file f and a huffman tree t,
// and writes a binary version of the tree to f.

void writeBinTree(BFILE* f, Tree t)
{
	if(t->kind == leaf)
	{
		writeBit(f, 1);
		writeByte(f, t->ch);
	}
	else
	{
		writeBit(f, 0);
		writeBinTree(f, t->left);
		writeBinTree(f, t->right);
	}
}


// writeBitString(binary, outfile) takes a binary string binary and writes the
// actual binary contained in the string to open binary file outfile.

void writeBitString(char* binary, BFILE* outfile)
{
	for(size_t i = 0; i < strlen(binary); i++)
	{
		writeBit(outfile, binary[i] - '0');
	}
}

// compressFile(Code, outfile, infile) writes the compressed version of a text
// file named infile to binary file outfile, using huffman code array Code.

void compressFile(char** Code, BFILE* outfile, const char* infile)
{
	FILE* f = fopen(infile, "r");

	int c = getc(f);

	while(c != EOF)
	{
		unsigned x = (unsigned) c;
		writeBitString(Code[x], outfile);
		c = getc(f);
	}

	fclose(f);
}

int main(int argc, char* argv[])
{
	tracing(argc, argv);
	char *infile, *outfile;
	int* f = new int[256];
	
	char** Code = new char*[256];
	nullCharArray(Code);
	
	char* prefix = new char[1];
	prefix[0] = '\0';

	
	Tree t;

	if(TRACING_ENABLED)
	{
		infile = argv[2];
		outfile = argv[3];
		cout << "File to compress: " << infile << endl;
		cout << "Destination file: " << outfile << endl << endl;

	}
	else
	{
		infile = argv[1];
		outfile = argv[2];
	}
	
      	
	
	BFILE* bin = openBinaryFileWrite(outfile);
	
	bool fileExists = getFrequency(infile, f);
	if(!fileExists)
	{
		cout << "File " << infile << " not found." << endl;
		return 1;
	}

	if(TRACING_ENABLED)
	{
		cout << "Printing character frequencies:" << endl;
	}
	freqCount(f);

	if(TRACING_ENABLED)
	{
		cout << endl << "Building huffman tree...";
	}
	
	t = buildHuff(f);

	if(TRACING_ENABLED)
	{
		cout << "Done" << endl;
		cout << "Creating  huffman code prefixes...";
	}

	
	buildCode(t, Code, prefix);

	if(TRACING_ENABLED)
	{
		cout << "Done" << endl << endl <<
			"Printing completed Tree:" << endl;
	}
	
	printTree(t);

	if(TRACING_ENABLED)
	{
		cout << endl << endl << "Printing char huffman codes:" << endl;
	}

	showCode(Code);

	if(TRACING_ENABLED)
	{
		cout << endl << "Writing Binary Tree to " << outfile << "...";
	}

	writeBinTree(bin, t);

	if(TRACING_ENABLED)
	{
		cout << "Done" << endl << "Writing compressed chars to " <<
			outfile << "...";
	}
	
	compressFile(Code, bin, infile);


	closeBinaryFileWrite(bin);

	if(TRACING_ENABLED)
	{
		cout << "Done" << endl << endl << "Compression Complete."
		     << endl;
	}
	
	return 0;
}
