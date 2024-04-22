# Combinations 

The script initially receives the following from the keyboard:
- N different integers in the range $[1 ... 49] (6 < N \le 49)$.
- A pair of integers $X1, X2$ such that: $0 \le X1 \le X2 \le 6$.
- A pair of integers $Y1, Y2$ such that: $21 \le Y1 \le Y2 \le 279$.

It then calculates and prints all possible combinations of $N$ numbers in $6$ that satisfy the following conditions:
- The number of even numbers in the combination must lie in the interval: $[X1 ... X2]$.
- The sum of the six numbers of the combination must lie in the interval: $[Y1 ... Y2]$.

The numbers of a combination are printed in ascending order. The combinations are also presented sorted in ascending order of the first element. In the
case of equality, the second element of the combination shall be taken into account, and so on.
Finally, the program prints:
- The number of combinations of N numbers per 6.
- The number of combinations that did not satisfy the first condition.
- The number of combinations that met the first condition but did not meet the second condition.
- The number of combinations that were printed. 1 There will be no deliverable for this exercise
- The frequency of occurrence of each of the N numbers in the set of combinations printed.

No global variables are used to implement the program and the "[ ]" operator is not used, anywhere.
➢ Implement the program also for the combinations of N numbers per K (K is entered from the keyboard)2.
