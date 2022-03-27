import random
from random import randint
# A=int(input())
A = 1000
first_matrix = [[random.uniform(1.5, 1.9) for j in range(A)] for i in range(A)]
second_matrix = [[random.uniform(1.5, 1.9) for j in range(A)] for i in range(A)]
length = len(first_matrix)
result_matrix = [[0 for i in range(length)] for i in range(length)]
for i in range(length):
    for j in range(length):
        for k in range(length):
            result_matrix[i][j] += first_matrix[i][k] * second_matrix[k][j]
print("Done!")
