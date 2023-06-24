# 1) a)

x = [
    7,7,4,5,9,9 ...
    4,12,8,1,8,7 ...
    3,13,2,1,17,7 ...
    12,5,6,2,1,13 ...
    14,10,2,4,9,11 ...
    3,5,12,6,10,7
    ]

s = 5
u = 9
alpha = 0.05

[h,p,ci,stat] = ztest(x, u, s, 'alpha', 0.05, 'tail', 'left')

tta = norminv(alpha)

RR = [-inf, tta]

if h == 1
  fprintf('The null hypothesis is rejected\n')
else
  fprintf('Not rejected\n')
end

fprintf('RR=(%1.2f, %1.2f)\n', RR)
fprintf('The value of the statistic = %1.2f\n', stat)
fprintf('The p-value = %1.2f\n', p)

u = 5.5

[h, p, ci, stat] = ttest(x, u, 'alpha', 0.05, 'tail', 'right')

n = length(x)

tta = tinv(1-alpha, n-1)

RR = [tta, inf]

if h == 1
  fprintf('The null hypothesis is rejected\n')
else
  fprintf('Not rejected\n')
end

fprintf('RR=(%1.2f, %1.2f)\n', RR)
fprintf('The value of the statistic = %1.2f\n', stat.tstat)
fprintf('The p-value = %1.2f\n', p)

#2) a)
pr = [
      22.4, 21.7 ...
      24.5, 23.4 ...
      21.6, 23.3 ...
      22.4, 21.6 ...
      24.8, 20.0
]
reg = [
       17.7, 14.8 ...
       19.6, 19.6 ...
       12.1, 14.8 ...
       15.4, 12.6 ...
       14.0, 12.0
]

alpha = 0.05

n1 = length(pr)
n2 = length(reg)

[h, p, ci, stat] = vartest2(pr, reg, 'alpha', 0.05, 'tail', 'both');

tta1 = finv(alpha/2, n1-1, n2-1)
tta2 = finv(1-(alpha/2), n1-1, n2-1)

#RR = [-inf, tta1] union [tta2, inf]

if h == 1
  fprintf('The null hypothesis is rejected\n')
else
  fprintf('Not rejected\n')
end


fprintf('RR=(-inf, %1.2f) U (%1.2f, inf)\n', tta1, tta2)
fprintf('The value of the statistic = %1.2f\n', stat.fstat)
fprintf('The p-value = %1.2f\n', p)

# 2) b)

n1 = length(pr)
n2 = length(reg)

[h, p, ci, stat] = ttest2(pr, reg, 'alpha', 0.05, 'tail', 'right')

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
