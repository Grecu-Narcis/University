n = input("Enter the number of trials: ")
p = input("Enter the probability: ")
N = input("Enter the number of simulations: ")

U = rand(n, N);
X = sum(U < p);

k = 0:n;
p_k = binopdf(k, n, p);
U_X = unique(X);

n_X = hist(X, length(U_X));
rel_freq = n_X / N;

clf # clear figure for plot

# !!! Binomial is discrete distribution

plot(U_X, rel_freq, '*', k, p_k, 'ro')
