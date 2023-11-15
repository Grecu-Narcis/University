pkg load statistics

# lab 2 ex 2
# a)
# We ask the user to input the
# required values for the binomial

n = input("Give the number of trials n=");
p = input("Give the probability of success p =");

# n natural number
# p value between 0 and 1
# x is the number of successes
x = 0:1:n

px = binopdf(x,n,p);
plot(x, px, 'r+')

# lab 2.b
# if you wish to have multiple graphs in the same window
# wrute the command "hold on"

# to give values for the cdf you must
# always simulate continuity
# !!! use pdf when P(X=something)
# !!! use cdf when P(X <= x)
xx = 0:0.01:n
fx = binocdf(xx, n, p);
plot(xx, fx, 'b')

# 2.c)
p1 = binopdf(0, 3, 0.5)
p2 = 1 - binopdf(1, 3, 0.5)

# 2.d)
p3 = binocdf(2, 3, 0.5)
p4 = binocdf(1, 3, 0.5)

# 2.e)
# P5 = 1 - P(X<1) = 1 - P (x <= 0) = 1 - P(X=0)
p5 = 1 - binocdf(0, 3, 0.5)
p6 = 1 - binocdf(1, 3, 0.5)










































