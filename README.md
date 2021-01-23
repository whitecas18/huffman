# Huffman  
A simple txt file compressor which uses huffman codes.  
All code is authored by Cason White, unless it is specified otherwise  

# Compilation Instructions  
run  
>make huffman  

to make the file compressor
and
>make unhuffman
  
to make the file decompressor  

# Usage  
To compress a file, start huffman followed by the name of the input txt file and the  
name you would like to choose for your output .cmp file.  
Add a -t flag if you would like verbose output. (which also displays the huffman tree)  
>./huffman [-t] data output
 
To decompress a file, do the same, with the .cmp file as input and the new text file name  
as output.
>./unhuffman [t] data output  
