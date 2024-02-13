# Left-Tailed Test:
# Null Hypothesis (H₀): The parameter is greater than or equal to a specified value.
# Alternative Hypothesis (H₁): The parameter is less than the specified value.

# Right-Tailed Test:
# Null Hypothesis (H₀): The parameter is less than or equal to a specified value.
# Alternative Hypothesis (H₁): The parameter is greater than the specified value.

# Two-Tailed Test:
# Null Hypothesis (H₀): The parameter is equal to a specified value.
# Alternative Hypothesis (H₁): The parameter is not equal to the specified value.

# ztest - check for mean against a given value when sigma known of a normal distribution population
# ttest - check for mean against a given value when sigma unknown
# ttest2 - check for comparing two means. can be used for populations of different length
# vartest - check for variance of a population agains a given value
# vartest2 - check for comparing variances of two populations

# lab 6
# 1.a
X = [7 7 4 5 9 9 ...
     4 12 8 1 8 7 ...
     3 13 2 1 17 7 ...
     12 5 6 2 1 13 ...
     14 10 2 4 9 11 ...
     3 5 12 6 10 7]

n = length(X)
alpha = input("Enter the significance level: ");

# the null hypothesis is H0: miu = 8.5 (it goes together with
# miu > 8.5, the standard is met)
# the alternative hypothesis is H1: miu < 8.5 (the standard is
# not met)
# left tailed test for miu when sigma known
printf("Using left tailed test for the mean when sigma known\n")

sigma = 5;
m0 = input("Enter the test value m0: ");

[h, pval, ci, zobs] = ztest(X, m0, sigma, 'alpha', 0.05, 'tail', 'left')
z_alpha = norminv(alpha, 0, 1);

RR = [-Inf, z_alpha];

printf("The value of h is %f\n", h);

if h == 1
  printf("The null hypothesis is rejected\n");
  printf("The data suggests that the standard is not met\n");

else
  printf("The null hypothesis is not rejected\n");
  printf("The data suggests that the standard is met\n");
endif

printf("The rejection region is (%4.3f, %4.3f)\n", RR);
printf("The observed value of the test statistic is %4.3f\n", zobs);

printf("The pval of the test is %4.3f\n", pval);

# FOR 1.B USE TTEST
# right tailed test
# the quantiles are following the student law => tinv

m0b = input("Enter the test value for 1.b: ");

[h, pval, ci, stats] = ttest(X, m0b, 'alpha', alpha, 'tail', 'right');

# since is right tail test we compute the quantile for 1-alpha
# for two tailed test we compute the quantile for alpha/2

z_alpha_b = tinv(1 - alpha, stats.df);
RR_b = [z_alpha_b, Inf];

if h == 1
  printf("The null hypothesis is rejected\n");
  printf("The data suggests that the standard is not met\n");

else
  printf("The null hypothesis is not rejected\n");
  printf("The data suggests that the standard is met\n");
end

printf("The rejection region is (%4.3f, %4.3f)\n", RR_b);
printf("The observed value of the test statistic is %4.3f\n", stats.tstat);

printf("The pval of the test is %4.3f\n", pval);

# Problem 2

# for 2.a two tail test for comparing variances
X1 = [22.4 21.7 24.5 23.4 21.6 23.3 22.4 21.6 24.8 20.0];
X2 = [17.7 14.8 19.6 19.6 12.1 14.8 15.4 12.6 14.0 12.2];

n = length(X1);
alpha = 0.05;

[h, pval, ci, stats] = vartest2(X1, X2, 'alpha', alpha, 'tail', 'both');

q1 = finv(alpha/2, stats.df1, stats.df2);
q2 = finv(1 - alpha/2, stats.df1, stats.df2);

if h == 1
  printf("The null hypothesis is rejected, ie. variances do differ!\n");
  printf("The data suggests that the standard is not met\n");

else
  printf("The null hypothesis is not rejected\n");
  printf("The data suggests that the standard is met\n");
end

printf("The rejection region is (-inf, %4.3f) U (%4.3f, +inf)\n", q1, q2);
printf("The observed value of the test statistic is %4.3f\n", stats.fstat);
printf("The pval of the test is %4.3f\n", pval);

vartype = 'equal';

if h == 1
  vartype = 'unequal';
end

# for 2.b right tail test for the difference of means

[h, pval, ci, stats] = ttest2(X1, X2, 'alpha', alpha, 'tail', 'right', 'vartype', vartype);

q = tinv(1-alpha, stats.df);

if h == 1
  printf("The null hypothesis is rejected, ie. gas mileage is higher when premium gasoline is used\n");
  printf("The data suggests that the standard is not met\n");

else
  printf("The null hypothesis is not rejected\n");
  printf("The data suggests that the standard is met\n");
end

printf("The rejection region is (%4.3f, +inf)\n", q);
printf("The observed value of the test statistic is %4.3f\n", stats.tstat);
printf("The pval of the test is %4.5f\n", pval);













