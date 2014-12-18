KMReadGenerator
===============
This command line tool helps generating reads that may have overlap or not.

HOW TO USE ?

./KMReadGenerator -r "chrM.txt" -o "output.fa"

-r: reference address. (required)
	reference file should be in a FASTA format.

-o: output file address(required)

-l: Length of generated reads.[default =100] (optional)
	length should be 10+ 

-v: Variant type [default =none] (optional)
	s=substitution , i=insertion , d=deletion, n=none;

-vp:Variant percentage [default =50] (optional)
	
-n: number of generated reads[default =10]  (optional)
	number should be 1+
	
	
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
