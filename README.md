KMReadGenerator
===============
This command line tool helps generating reads that may have overlap or not.

HOW TO USE ?

./KMReadGenerator -r "ucsc.hg19.txt" -o "output.fa"

-r: reference address. (required)
	reference file should be in a FASTA format.

-o: output file address(required)

-l: Length of generated reads.[default =100] (optional)
	length should be 10+ 

-v: Variant type [default =none] (optional)
	s=substitution , i=insertion , d=deletion, n=none;

-vp:Variant percentage [default =50] (optional)
	
-n: number of generated reads  (optional)
	number should be 1+
	