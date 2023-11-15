#lab3
#problem 1

pkg load statistics

m = input("m=");
sigma = input("sigma = ");
alpha = input("alpha = ");
beta = input("beta = ");

p1 = normcdf(0, m, sigma);
p2 = 1 - normcdf(0, m, sigma);

# 1.b
# P(a<X<=b) = F(b) - F(a)

p3 = normcdf(1, m, sigma) - normcdf(-1, m, sigma)
#p4 = 1 - P(-1 < X < 1)
p4 = 1 - p3

# 1.c
x_alpha = norminv(alpha, m, sigma)
x_beta = norminv(1-beta, m, sigma)

#problem 2
p=input("Enter the value for p in the interval [0.05, 0.95]: ")

for n=1:3:100
  k = 0:n;
  y = binopdf(k, n, p);
  plot(k, y)
  pause(0.5)
endfor

