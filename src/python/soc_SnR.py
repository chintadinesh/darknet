import oct2py
import numpy as np
from oct2py import octave
oc = oct2py.Oct2Py()

#Reading the .m file
f = open("../matlab/testbench.m", "r")
content = f.readlines()

#Dimensions of the matrices
M = 1
N = 676
K = 256

#Location of the vectors in the file
A = content[7]  # M x K
B = content[10] # K x N
Cin = content[13] # M x N
Cout = content[16] #M x N

#Pre-processing Matrix A

A_split = A.split(',');
A_float = A_split
A_float =  [[0 for c in range(K)] for r in range(M)]
for row in range(M):
    for col in range(K):
            temp = A_split[K*row+col].replace(']', '')
            temp = temp.replace('[', '') 
            temp = temp.strip()
            A_float[row][col] = float(temp)

#Pre-processing Matrix B

B_split = B.split(',');
B_float = B_split
B_float =  [[0 for c in range(N)] for r in range(K)]
for row in range(K):
    for col in range(N):
            temp = B_split[N*row+col].replace(']', '')
            temp = temp.replace('[', '') 
            temp = temp.strip()
            B_float[row][col] = float(temp)

#Pre-processing Matrix Cin

Cin_split = Cin.split(',');
Cin_float = Cin_split
Cin_float =  [[0 for c in range(N)] for r in range(M)]
for row in range(M):
    for col in range(N):
            temp = Cin_split[N*row+col].replace(']', '')
            temp = temp.replace('[', '') 
            temp = temp.strip()
            Cin_float[row][col] = float(temp)

#Pre-processing Matrix Cout

Cout_split = Cout.split(',');
Cout_float = Cout_split
Cout_float =  [[0 for c in range(N)] for r in range(M)]
for row in range(M):
    for col in range(N):
            temp = Cout_split[N*row+col].replace(']', '')
            temp = temp.replace('[', '') 
            temp = temp.strip()
            Cout_float[row][col] = float(temp)

#Printing the dimensions of each matrix
print(np.shape(A_float))
print(np.shape(B_float))
print(np.shape(Cin_float))
print(np.shape(Cout_float))

f.close()

