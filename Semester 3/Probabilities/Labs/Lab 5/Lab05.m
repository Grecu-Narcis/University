# pkg load statistics in command line
# miu is the population mean (theoretical mean)
# sigma ^ 2 = population variance (theoretical variance)
# x with bar over is the sample mean
# s ^ 2 is the sample variance
# s ^ 2 = var(X) in octave
# norm_inv gets the quantiles

X = [7 7 4 5 9 9 ...
     4 12 8 1 8 7 ...
     3 13 2 1 17 7 ...
     12 5 6 2 1 13 ...
     14 10 2 4 9 11 ...
     3 5 12 6 10 7]

one_minus_alpha = input("Please enter the confidence level: ");
alpha = 1 - one_minus_alpha;
n = length(X);

sigma = 5;

m1 = mean(X) - sigma / sqrt(n) * norminv(1 - alpha / 2, 0, 1);
m2 = mean(X) - sigma / sqrt(n) * norminv(alpha / 2, 0, 1);
printf("The confidence interval for the theoretical mean when sigma is known \n")
printf("is (%4.3f,%4.3f) \n", m1, m2)

# sigma is the population stantard deviation
# s - sample standard deviation

# quantiles squared inv -> chi2inv
# std(X) - standard deviation
# B.1.b

m1b = mean(X) - std(X) / sqrt(n) * tinv(1 - alpha / 2, n - 1);
m2b = mean(X) - std(X) / sqrt(n) * tinv(alpha / 2, n - 1);

printf("The confidence interval for the theoretical mean when sigma is unknown\n")
printf("is (%4.3f, %4.3f)\n", m1b, m2b)

# B.1.c
v1 = (n - 1) * var(X) / chi2inv(1 - alpha / 2, n - 1);
v2 = (n - 1) * var(X) / chi2inv(alpha / 2, n - 1);

printf("The confidence interval for the variance\n")
printf("is (%4.3f, %4.3f)\n", v1, v2)

# for the confidence of standard deviation
# standard deviation = sqrt(variance)
s1 = sqrt(v1);
s2 = sqrt(v2);

printf("The confidence interval for the standard deviation\n")
printf("is (%4.3f, %4.3f)\n", s1, s2)












