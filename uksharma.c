/* DNA sequence mapper:
 *
 * Skeleton code written by Jianzhong Qi, April 2022
 * Edited by: Upnishadd Ksharma - 1263652, April 2022
 *
 */

#include <stdio.h>
#include <math.h>

#define ASCII_MIN 33
#define PROB_VAL 10
#define STAGE_NUM_ONE 1						  /* stage numbers */ 
#define STAGE_NUM_TWO 2
#define STAGE_NUM_THREE 3
#define STAGE_NUM_FOUR 4
#define STAGE_NUM_FIVE 5
#define STAGE_HEADER "Stage %d\n==========\n" /* stage header format string */

#define MAX_READ_ID_LENGTH 100				  /* maximum read ID length */
#define MAX_READ_LENGTH 100					  /* maximum read length */
#define MAX_NUM_READS 100					  /* maximum number of reads */
#define MAX_REF_LENGTH 1000				      /* maximum reference DNA length */

typedef char read_id_t[MAX_READ_ID_LENGTH+1]; /* a read ID */
typedef char read_t[MAX_READ_LENGTH+1];		  /* a read */
typedef char score_t[MAX_READ_LENGTH+1];	  /* quality scores of a read */
typedef char ref_t[MAX_REF_LENGTH+1];		  /* a reference DNA sequence */

/****************************************************************/

/* function prototypes */
void take_one_read(read_t one_read, score_t scores_of_one_read);
void print_stage_header(int stage_num);

double error_prob(score_t scores[], int read, int b_index);
double match_score(read_t reads[], score_t scores[], ref_t ref_sequence, 
    int read, int b_idx, int i);

void stage_one(read_t one_read, score_t scores_of_one_read);
void stage_two(read_t reads[], score_t scores[], int *num_reads);
void stage_three(read_t reads[], score_t scores[], int num_reads);
void stage_four(ref_t ref_sequence);
void stage_five(read_t reads[], score_t scores[], int num_reads, 
	ref_t ref_sequence);

/* add your own function prototypes here */
/****************************************************************/

/* main function controls all the action, do NOT modify this function */
int
main(int argc, char *argv[]) {
	/* to hold all input reads and quality scores */
	read_t reads[MAX_NUM_READS];	
	score_t scores[MAX_NUM_READS];
	/* to hold the number of input reads */
	int num_reads = 0;	
	/* to hold the input reference sequence */
	ref_t ref_sequence;
	
	/* stage 1: process one read */
	stage_one(reads[0], scores[0]); 
	num_reads++;
	
	/* stage 2: process all reads */
	stage_two(reads, scores, &num_reads);
	
	/* stage 3: mask bases with high error probability */ 
	stage_three(reads, scores, num_reads);
	
	/* stage 4: process reference sequence */
	stage_four(ref_sequence);
	
	/* stage 5: map reads to the reference sequence */
	stage_five(reads, scores, num_reads, ref_sequence);
	
	/* all done; take some rest */
	return 0;
}

/* print stage header given stage number */
void 
print_stage_header(int stage_num) {
	printf(STAGE_HEADER, stage_num);
}

/****************************************************************/
/* add your code below */

// algorithms are fun

// What do you call 8 Hobbits?
            /*A Hobbyte. */
// open this ^^^            

/* process a read record */

void take_one_read(read_t one_read, score_t scores_of_one_read) {
	/* modify this function for stage 2 */
	
    /* This function isn't used, As I managed to scan each read in one line */
    
    read_id_t id;
	scanf("%s", id);
	scanf("%s", one_read);
	getchar();
	getchar(); // skip '+' and '\n'
	scanf("%s", scores_of_one_read);
}

double error_prob(score_t scores[], int read, int b_index) {
    // Find the error probability p of a base from its quality score.
    double p; 
    p = 1/(pow(PROB_VAL, (double)(scores[read][b_index]-ASCII_MIN)/PROB_VAL));
    return p;
}

double match_score(read_t reads[], score_t scores[], ref_t ref_sequence, 
    int read, int b_idx, int i) {
    // Find the matchscore
    double p;
    if(reads[read][b_idx] == ref_sequence[i]) {
        p = error_prob(scores, read, b_idx);
    } else if (reads[read][b_idx] == '*') p = 0.25; else p = 1;
    // Return the log base 2 of the matchscore
    return log(p)/log(2);
}

/* stage 1: process one read */
void stage_one(read_t one_read, score_t scores_of_one_read) {
	/* print stage header */

	print_stage_header(STAGE_NUM_ONE);
	
	/* add code for stage 1 */
    
    /* skip the Identifier, scan the Read of max 100 chars into an array,
    skip the "+", scan the Quality Scores of max 100 chars into an array. */
    scanf("%*s %100s %*c %100s", one_read, scores_of_one_read);
    
    // Reads are >= 1 char, hence low_val can start at first element
    int val, low_val = one_read[0], low_index;
    char low_base = one_read[0];
    
    /* Iterate thru each score in the array if Quality score value is lower 
    than the previous lowest value, replace it and store corresponding base */
    for(int i = 0; i < 100 && scores_of_one_read[i] != 0; i++){
        val = scores_of_one_read[i];
        if (val < low_val){
            low_val = val;
            low_index = i;
            low_base = one_read[i];
        }
    }
    printf("Base with the smallest quality score: %c\n", low_base);
    printf("Index: %d\n\n", low_index);
}

/* stage 2: process all reads */
void stage_two(read_t reads[], score_t scores[], int *num_reads) {
    /* print stage header */
    
    print_stage_header(STAGE_NUM_TWO);
    
    /* add code for stage 2 */
    
    // The identifier can be upto 100 chars
    int n_reads = *num_reads;
    char identifier[100];
    
    /* Scan remaining reads by iterating upto 99 times, if the identifier 
    begins with a '#' stop the loop as all remaing reads have been found */
    for (int read = 1; read < 100; read++) {
        scanf("%s", identifier);
        if (identifier[0] != 35){
            scanf("%100s %*c %100s", reads[read], scores[read]); n_reads++;
        }
        else {break;}
        
    }
    *num_reads = n_reads;
    
    /* l_index is used to store the index of the read with lowest average. */
    double avrg; int sum; int count; double low_avrg; int l_index;
    // Iterate thru all the reads
    for (int r_index = 0; r_index < *num_reads; r_index++) {
        // b_index refers to index of each base within a read
        int b_index = 0; sum = 0; count = 0;
        /* Iterate thru all bases of a read, summing the scores of the quality 
        scores and counting the length of the read */
        for(; b_index < 100 && scores[r_index][b_index] != 0; b_index++){
            sum += scores[r_index][b_index]; count ++;
        }     
        /* if the read exists, find the average score, and if the score is the 
        lowest encountered yet remember the average score and the reads index */
        if (count != 0){
            avrg = (double) sum / count;
            if (r_index == 0) {low_avrg = avrg; l_index = 0;}
            if (avrg < low_avrg) {low_avrg = avrg; l_index = r_index;}
        }
    }
    printf("Total number of reads: %d\n", *num_reads);
    printf("Smallest average quality score: %0.2lf\n", low_avrg);
    printf("Read with the smallest average quality score:\n%s", reads[l_index]);
    printf("\n\n");
}

/* stage 3: mask bases with high error probability */ 
void stage_three(read_t reads[], score_t scores[], int num_reads) {
    /* print stage header */
    print_stage_header(STAGE_NUM_THREE);
	
    /* add code for stage 3 */
    
    /* Iterate thru each read, correcting any bases with 
    error probability score greater than 0.15 */
    for(int read = 0; read < num_reads; read++){
        int b_index = 0;
        for(; b_index < 100 && scores[read][b_index] != 0; b_index++){
            double p = error_prob(scores, read, b_index);
            if (p > 0.15){
                reads[read][b_index] = '*';
            }
        }
        printf("%s\n", reads[read]);
    }
    printf("\n");
}

/* stage 4: process reference sequence */
void stage_four(ref_t ref_sequence) {
    /* print stage header */
    
    print_stage_header(STAGE_NUM_FOUR);
	
    /* add code for stage 4 */
    
    // Counters for each base and total bases 
    int A = 0, C = 0, G = 0, T = 0, Total = 0;
    // Scan reference sequence for upto 1000 bases
    scanf("%1000s", ref_sequence);
    // Iterate thru and adding to the counters for each base
    for(int i = 0; i < 1000; i++){
        if(ref_sequence[i] != 0){
            if(ref_sequence[i] == 'A') A++;
            else if(ref_sequence[i] == 'C') C++;
            else if(ref_sequence[i] == 'G') G++;
            else if(ref_sequence[i] == 'T') T++;
            Total++;
        } 
    }
    printf("Length of the reference sequence: %d\n", Total);
    printf("Number of A bases: %d\nNumber of C bases: %d\n", A, C);
    printf("Number of G bases: %d\nNumber of T bases: %d\n\n", G, T);
    
}

/* stage 5: map reads to the reference sequence */
void stage_five(read_t reads[], score_t scores[], int num_reads, 
    ref_t ref_sequence) {
    /* print stage header */
    print_stage_header(STAGE_NUM_FIVE);
    /* add code for stage 5  */ 
   
    // Find length of the reference sequence
    int Total = 0;
    for(int i = 0; i < 1000; i++){
        if(ref_sequence[i] != 0){
            Total++;
        }
    } 
    // Iterate thru all reads
    for(int read = 0; read < num_reads; read++){
        int len_read = 0, b_index = 0;
        // length needed for the substrings from length of read
        for(; b_index < 100 && scores[read][b_index] != 0; b_index++){
            len_read++;
        }
        int count = 0, max_string_i; double max_match = 0;
        
        /* Iterate thru the reference sequence taking substrings of required 
        length */
        for(int s_min = 0; s_min + len_read <= Total; s_min++){
            count++;
            double match_substring = 0; int b_idx = 0; double match_index;
            for(int i = s_min; i < s_min + len_read; i++){              
                match_index=match_score(reads,scores,ref_sequence,read,b_idx,i); 
                match_substring += match_index;
                b_idx++;
            }
            match_substring = -1*match_substring;
            // store the substring with highest match score
            if (match_substring > max_match) {
                max_match = match_substring; max_string_i = s_min;
            }
        }
        printf("Read:  %s\nMatch: ", reads[read]);
        for(int start = max_string_i; start<max_string_i+len_read; start++){
            printf("%c", ref_sequence[start]);
        }
        printf("\n");
    }    
}