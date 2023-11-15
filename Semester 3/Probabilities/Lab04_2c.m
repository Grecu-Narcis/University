#Lab 04 - 2.c
p = input("Please enter the probability of success: ");
N = input("Please enter the number of simulations: ");

X = zeros(1, N);

for i = 1:N
  X(i) = 0;

  while rand() >= p
    X(i) = X(i) + 1;
  endwhile
endfor

k = 0:20;
p_k = geopdf(k, p);

U_X = unique(X);

n_X = hist(X, length(U_X));
rel_freq = n_X / N;

clf # clear figure for plot

plot(U_X, rel_freq, '*', k, p_k, 'ro')
