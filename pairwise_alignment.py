'''
Created on October 09, 2019

@author: Mattia (https://github.com/mett29)

Needleman-Wunsch and Smith-Waterman algorithms to compute respectively the global e local alignment of two generic sequences.

More info here: 
- https://en.wikipedia.org/wiki/Needleman%E2%80%93Wunsch_algorithm
- https://en.wikipedia.org/wiki/Smith%E2%80%93Waterman_algorithm

NB:
- I did not use a substitution matrix like BLOSUM62 for simplicity of implementation.
- During the traceback, I did not implement the possibility to retrieve ALL the possible paths (if > 1).
- The program can for sure be written in a much more efficient way. I wrote this program just to better understand
every single step of the two algorithms and also for fun, of course.

'''

import numpy as np

gap_penalty = -1
# For this example we will not consider a substitution matrix like BLOSUM62, thus we can choose the score for a match to simply be +2
match_score = +2

def initialize_global_matrix(seq1, seq2):
    # Fill the matrix with zeros (+1 wrt the length to take into account the initial zero)
    matrix = np.zeros(shape=(len(seq2) + 1, len(seq1) + 1))

    matrix[0][0] = 0
    # First row
    for i in range(1, len(matrix[0])):
        matrix[0][i] = matrix[0][i-1] + gap_penalty
    # First column
    for i in range(1, len(matrix[:,0])):
        matrix[i][0] = matrix[i-1][0] + gap_penalty

    return matrix 

def initialize_local_matrix(seq1, seq2):
    # In this case we can simply return a matrix of zeros
    return np.zeros(shape=(len(seq2) + 1, len(seq1) + 1))

def global_alignment(matrix, seq1, seq2):
    for i in range(1, len(matrix[:,0])):
        for j in range(1, len(matrix[0])):
            # Compute V(i,j)
            if (seq1[j-1] == seq2[i-1]): # Match (+2 in our example)
                matrix[i, j] = max(matrix[i-1, j-1] + match_score, matrix[i-1, j] + gap_penalty, matrix[i, j-1] + gap_penalty)
            else: # Mismatch
                matrix[i, j] = max(matrix[i-1, j-1] + gap_penalty, matrix[i-1, j] + gap_penalty, matrix[i, j-1] + gap_penalty)

    return matrix

def traceback_global_alignment(matrix, seq1, seq2):

    alignment1 = []
    alignment2 = []

    # Starting from the bottom-right cell...
    i = len(matrix[:,0]) - 1
    j = len(matrix[0]) - 1
    
    while (i > 0 or j > 0):
        if (i > 0 and j > 0 and seq1[j-1] == seq2[i-1] and matrix[i][j] == matrix[i-1][j-1] + match_score) or (i > 0 and j > 0 and matrix[i][j] == matrix[i-1][j-1] + gap_penalty):
            alignment1.append(seq1[j-1])
            alignment2.append(seq2[i-1])
            i = i - 1
            j = j - 1
        elif (i > 0 and matrix[i][j] == matrix[i-1, j] + gap_penalty):
            alignment1.append('-')
            alignment2.append(seq2[i-1])
            i = i - 1
        elif (j > 0 and matrix[i][j] == matrix[i, j-1] + gap_penalty):
            alignment1.append(seq1[j-1])
            alignment2.append('-')
            j = j - 1

    return alignment1, alignment2

def local_alignment(matrix, seq1, seq2):
    for i in range(1, len(matrix[:,0])):
        for j in range(1, len(matrix[0])):
            # Compute V(i,j)
            if (seq1[j-1] == seq2[i-1]): # Match (+2 in our example)
                matrix[i, j] = max(0, matrix[i-1, j-1] + match_score, matrix[i-1, j] + gap_penalty, matrix[i, j-1] + gap_penalty)
            else: # Mismatch
                matrix[i, j] = max(0, matrix[i-1, j-1] + gap_penalty, matrix[i-1, j] + gap_penalty, matrix[i, j-1] + gap_penalty)
    
    return matrix

def traceback_local_alignment(matrix, seq1, seq2):

    alignment1 = []
    alignment2 = []
    
    # Get the indices of the maximum element in the matrix
    i, j = np.unravel_index(matrix.argmax(), matrix.shape)
    # Apply the same algorithm used for global traceback, with the extra condition of matrix[i][j] != 0
    while (i > 0 or j > 0) and (matrix[i][j] != 0):
        if (i > 0 and j > 0 and seq1[j-1] == seq2[i-1] and matrix[i][j] == matrix[i-1][j-1] + match_score) or (i > 0 and j > 0 and matrix[i][j] == matrix[i-1][j-1] + gap_penalty):
            alignment1.append(seq1[j-1])
            alignment2.append(seq2[i-1])
            i = i - 1
            j = j - 1
        elif (i > 0 and matrix[i][j] == matrix[i-1, j] + gap_penalty):
            alignment1.append('-')
            alignment2.append(seq2[i-1])
            i = i - 1
        elif (j > 0 and matrix[i][j] == matrix[i, j-1] + gap_penalty):
            alignment1.append(seq1[j-1])
            alignment2.append('-')
            j = j - 1

    return alignment1, alignment2

def main():
    # The two sequences that must be aligned
    sequence1 = "CADBD"
    sequence2 = "ACBCDB"

    ''' ---------------- '''
    ''' GLOBAL ALIGNMENT '''
    ''' ---------------- '''
    global_alignment_matrix = initialize_global_matrix(sequence1, sequence2)
    print("Computing the global alignment...")
    global_alignment_matrix = global_alignment(global_alignment_matrix, sequence1, sequence2)
    print(global_alignment_matrix)
    print(end="\n")
    print("Traceback...")
    alignment1, alignment2 = traceback_global_alignment(global_alignment_matrix, sequence1, sequence2)
    print(alignment1)
    print(alignment2)

    ''' --------------- '''
    ''' LOCAL ALIGNMENT '''
    ''' --------------- '''
    print("\nComputing the local alignment...")
    local_alignment_matrix = initialize_local_matrix(sequence1, sequence2)
    local_alignment_matrix = local_alignment(local_alignment_matrix, sequence1, sequence2)
    print(local_alignment_matrix)
    print(end="\n")
    print("Traceback...")
    alignment1, alignment2 = traceback_local_alignment(local_alignment_matrix, sequence1, sequence2)
    print(alignment1)
    print(alignment2)

if __name__ == '__main__':
	main()