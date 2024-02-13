# Lab 4

N = input("Please enter the number of simulations: ");
p = input("Please enter the probability of obtaining 1 (0 < p < 1) :");
U = rand(1, N);
X = (U < p);

U_X = [0, 1];
n_X = hist(X, length(U_X)); # how many 0 and 1's are in X
rel_freq = n_X / N

# clear -> clear the variable watch
# clc -> clear the screen
