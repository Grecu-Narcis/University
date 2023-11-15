N = input("Enter the number of simulations: ")

U = rand(3, N); # generates a matrix of 3xN with random values in [0, 1]
Y = (U < 0.5);
X = sum(Y); # computes the sum on each row

clf # clears the figure
hist(X); # plots a bar graph from a vector

