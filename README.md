KMReadGenerator
===============
This command line tool helps generating reads that may have overlap or not.

HOW TO USE ?

./KMReadGenerator -r "chrM.txt" -o "output.fa"

-r: reference address. (required)
	reference file should be in a FASTA format.

-o: output file address(required)

-of: output file format[default =fasta] (optional)
	arguments :
	fasta: FastA format
	fastq: FastQ format
	pair: paired end reads 
	pair-mu : pair with having same mutated pattern

-l: Length of generated reads.[default =100] (optional)
	length should be 10+ 

-pfx: PRefix for read names [default: "Read_"] (optional)

-n: number of generated reads[default =10]  (optional)
	number should be 1+
	
-rq: Reads Quality [default = "i"] (optional)
	 if readquality is one character, program will generate reads with the same quality for all nucleotides (for AATG and quality I,  quality will be IIII)
	 if read quality has same length as the read, program will use it for generating quality 
	
-chr Specific chromosome to generate random reads from

-vpt:Variation Pattern [default ="s1"] (optional)
	s=substitution , i=insertion , d=deletion, b=blank(without any change)
	how to use use: variation+length : s5 = 5 substituon
	sample variation pattern: "s1-b5-d1-b3-i4" 

-vp:Variant percentage [default =50] (optional)
	
	
Sample output :

>Read1_0-50
TTGGTATTTTCGTCTGGGGGGTGTGCACGCGATAGCATTGCGAGACGCTG
>Read2_5-100
ATTTTCGTCTGGGGGGTGTGCACGCGATAGCATTGCGAGACGCTGGAGCC
>Read3_10-150
CGTCTGGGGGGTGTGCACGCGATAGCATTGCGAGACGCTGGAGCCGGAGC
>Read4_15-200
GGGGGGTGTGCACGCGATAGCATTGCGAGACGCTGGAGCCGGAGCACCCT
>Read5_20-250
GTGTGCACGCGATAGCATTGCGAGACGCTGGAGCCGGAGCACCCTATGTC
>Read6_25-300
CACGCGATAGCATTGCGAGACGCTGGAGCCGGAGCACCCTATGTCGCAGT
>Read7_30-350
GATAGCATTGCGAGACGCTGGAGCCGGAGCACCCTATGTCGCAGTATCTG
>Read8_35-400
CATTGCGAGACGCTGGAGCCGGAGCACCCTATGTCGCAGTATCTGTCTTT
>Read9_40-450
CGAGACGCTGGAGCCGGAGCACCCTATGTCGCAGTATCTGTCTTTGATTC
>Read10_45-500
CGCTGGAGCCGGAGCACCCTATGTCGCAGTATCTGTCTTTGATTCCTGCC


Example:
./KMReadGenerator -r "/hg19/chr21.ucsc.hg19.fa" -o "output.fa" -l 30 -vp 100  -n 10 -vpt s1-b5-d1-b1-s2
 
