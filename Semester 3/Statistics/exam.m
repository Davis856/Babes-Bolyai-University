steel = [4.6, 0.7, 4.2, 1.9, 4.8, 6.1, 4.7, 5.5, 5.4]
glass = [2.5, 1.3, 2.0, 1.8, 2.7, 3.2, 3.0, 3.5, 3.4]

n1 = length(steel)
n2 = length(glass)

alpha = 0.05

[h, p, ci, stat] = vartest2(steel, glass, 'alpha', 0.05, 'tail', 'both');

tta1 = finv(alpha/2, n1-1, n2-1)
tta2 = finv(1-(alpha/2), n1-1, n2-1)

#RR = [-inf, tta1] union [tta2, inf]

if h == 1
  fprintf('The null hypothesis is rejected\n')
  fprintf('Conclusion: population variances seem to differ\n')
else
  fprintf('Not rejected\n')
end


fprintf('RR=(-inf, %1.2f) U (%1.2f, inf)\n', tta1, tta2)
fprintf('The value of the statistic = %1.2f\n', stat.fstat)
fprintf('The p-value = %1.2f\n', p)

# b)
n1 = length(steel)
n2 = length(glass)

[h, p, ci, stat] = ttest2(steel, glass, 'alpha', 0.05, 'tail', 'right')

tta1 = tinv(1-alpha, n1+n2-2)

RR = [tta1, inf]

if h == 1
  fprintf('The null hypothesis is rejected\n')
else
  fprintf('Not rejected\n')
end

fprintf('RR=(%1.2f, %1.2f)\n', RR)
fprintf('The value of the statistic = %1.2f\n', stat.tstat)
fprintf('The p-value = %1.2f\n', p)
