# Genome-Reader
To track variants of a virus, scientists obtain “isolates", which are viruses isolated from infected patients. DNA or RNA are extracted from the isolates, which need to be translated into a sequence of bases. DNA consists of four bases: adenine (A), cytosine (C), guanine (G), and thymine (T), while the four bases of RNA are adenine (A), cytosine (C), guanine (G), and uracil (U). This translation process is referred to as sequencing. After sequencing, the DNA of a virus is represented as a sequence (that is, a string) consisting of four letters 'A', 'C', 'G', and 'T'. Different virus variants can be compared using their DNA strings, and sub-strings of species called patterns (e.g., a gene that makes a variant more infectious) can be identified from the DNA. For example, below are the first 350 bases of the Wuhan-Hu-1 isolate of the SARS-CoV-2 virus:

ATTAAAGGTTTATACCTTCCCAGGTAACAAACCAACCAACTTTCGATCTCTTGTAGATCTGTTCTCTAAACGAACTTTAAAATCTGTGTGGCTGTCACTCGGCTGCATGCTTAGTGCACTCACGCAGTATAATTAATAACTAATTACTGTCGTTGACAGGACACGAGTAACTCGTCTATCTTCTGCAGCTGCTTACGGTTTCGTCCGTGTTGCAGCCGATCATCAGCACATCTAGGTTTCGTCCGGGTGGACCGAAAGGTAAGATGGAGAGCCTTGTCCCTGGTTTCAACGAGAAAACACACGTCCAACTAGTTTGCCTGTTTTACAGGTTCGCGACGTGCTCGTAC

As a preparation step, the DNA of a virus isolate needs to be broken into short pieces, that is, DNA fragments, because it is more di cult to recognise the bases accurately from long DNA fragments. A sequencer machine then recognises the bases from DNA fragments and converts them into short pieces of DNA sequences called reads, which are represented by short strings consisting of four letters 'A', 'C', 'G', and 'T'. Below is an example record of a read (using the FASTQ format).

@MT734046.1-1990/1
TTTGCGCATCTGTTATGAAATAGTTTTTAACTGTACTATCCATAGGAATAAAATCTTCTA
+
CCCGGGCGGGGGGCCGGGGGGGGGGGGGGCCGG=GGGGGGGGGGGGGGGGGGGGGGGCGG

The record of a read consists of four lines:
- Line 1: An Identifier line starting with '@' (You may assume at least 2 and up to 100 characters in this line).
- Line 2: A DNA sequence consisting of four letters 'A', 'C', 'G', and 'T', where each character represents a DNA base (You may assume at least 2 and up to 100 characters in this line).
- Line 3: A line with a single plus sign '+'.
- Line 4: A line of characters of the same length as Line 2. Each character represents a quality score of a base in Line 2, which reflects how confident the sequencer machine is when recognising a base. For example, the first base of the example read, 'T', has a quality score of 'C' (67), while the last base, 'A', has a quality score of 'G' (71). The characters in this line have ASCII values between 33 and 73. 

Stages:
- Stage 1: Process One Read and Print the Base with the Smallest Quality Score
- Stage 2: Process All Reads and Find the Read with the Smallest Average Quality Score
- Stage 3: Revisit the Reads and Convert Any Base with Error Probability Larger than 0.15 to '*'
- Stage 4: Process the Reference Sequence and Print the Numbers of A, C, G, and T Bases




