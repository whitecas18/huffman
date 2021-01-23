// CSCI 2530
// Assignment: 8
// Author:     Cason White
// File:       unhuffman.cpp
// Tab stops:  8

// unhuffman.cpp takes a compressed .cmp file created with huffman.cpp and
// decompresses it to a given text file.

// An example of usage on a binary file containing the compressed
// text "aaabbccd    " is as follows (using the -t flag):

// ./unhuffman -t test.cmp test.txt
// File to decompress: test.cmp
// Destination file: test.txt
// Reading binary tree...Done

// Printing converted tree:
// ((b,a),(space,((d,\n),c)))

// Copying decompressed text to test.txt...Done
// Decompression Complete.


#include <cstdio>
#include <iostream>
#include <cstring>
#include "tree.h"
#include "trace.h"
#include "binary.h"

using namespace std;


//readTree(f) takes an open binary file f and returns a huffman tree.

Tree readTree(BFILE* f)
{
	if(readBit(f) == 1)
	{
		return new Node(readByte(f));
	}
	else
	{
		Tree left = readTree(f);
		Tree right = readTree(f);

		return new Node(left, right);
		
	}
}


// readChar(f, huff) takes an open binary file f and a huffman tree huff and
// returns an integer representation of a character from binary file f.

int readChar(BFILE* f, Tree huff)
{
	if(huff->kind == leaf)
	{
		return huff->ch;
	}
	else
	{
		int bit = readBit(f);
		if(bit == 0)
		{
			return readChar(f, huff->left);
		}
		else if(bit == 1)
		{
			return readChar(f,huff->right);
		}
		else
		{
			return EOF;
		}
	}
	
}

// decompress(infile, outfile, huff) takes an open binary file infile, a
// file name outfile, and a huffman tree huff and places a decompressed file
// into a file named outfile.

void decompress(BFILE* infile, char* outfile, Tree huff)
{
	FILE* f = fopen(outfile, "w");
	
	char ch = readChar(infile, huff);
	while(ch != EOF)
	{
		putc(ch, f);
		ch = readChar(infile, huff);
	}
}


int main(int argc, char* argv[])
{
	tracing(argc, argv);

	char *infile, *outfile;

	if(TRACING_ENABLED)
	{
		infile = argv[2];
		outfile = argv[3];
		
		cout << "File to decompress: " << infile << endl;
		cout << "Destination file: " << outfile << endl;
	}
	else
	{
		infile = argv[1];
		outfile = argv[2];
	}

	

	BFILE* bin = openBinaryFileRead(infile);

	if(TRACING_ENABLED)
	{
		cout << "Reading binary tree...";
	}	
	Tree t = readTree(bin);
	
	
	if(TRACING_ENABLED)
	{
		cout << "Done\n\n" << "Printing converted tree:" << endl;
	}
	printTree(t);

	if(TRACING_ENABLED)
	{
		cout << endl << endl <<
		    "Copying decompressed text to " << outfile << "...";
	}
	
	decompress(bin, outfile, t);
	closeBinaryFileRead(bin);

	if(TRACING_ENABLED)
	{
		cout << "Done" << endl << "Decompression Complete." << endl;
	}
	
	
	return 0;
}
