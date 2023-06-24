# A)

x = [
    7,7,4,5,9,9 ...
    4,12,8,1,8,7 ...
    3,13,2,1,17,7 ...
    12,5,6,2,1,13 ...
    14,10,2,4,9,11 ...
    3,5,12,6,10,7
    ]

# a)
s = 5
X = mean(x)
n = 36
alpha=0.05
z1 = norminv(1-(alpha/2))
z2 = norminv(alpha/2)
m1 = X-(s/sqrt(n)) * z1
m2 = X-(s/sqrt(n)) * z2

# b)
X = mean(x)
n = 36
s = std(x)
t1 = tinv(1-(alpha/2), n-1)
t2 = tinv(alpha/2, n-1)
m1 = X-(s/sqrt(n))* t1
m2 = X-(s/sqrt(n)) * t2

# c)
n = 36
s = var(x)
x1 = chi2inv(1-alpha/2, n-1)
x2 = chi2inv(alpha/2, n-1)
m1 = ((n-1)*s)/x1
m2 = ((n-1)*s)/x2
m1 = sqrt(m1)
m2 = sqrt(m2)

# B)
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
s1 = var(pr)
s2 = var(reg)
x1 = mean(pr)
x2 = mean(reg)
n1 = 10
n2 = 10
sp = ((n1-1)*s1 + (n2-1)*s2)/(n1+n2-2)
sp = sqrt(sp)
t1 = tinv(1-(alpha/2), n1+n2-2)
m1 = (x1-x2-t1*sp*sqrt((1/n1 + 1/n2)))
m2 = (x1-x2+t1*sp*sqrt((1/n1 + 1/n2)))


# b)
t1 = tinv(1-(alpha/2), n)
c = (s1/n1)/((s1/n1 + s2/n2))
n5 = (pow2(c)/n1-1 + pow2(1-c)/n2-1)
n = 1/n5
m1 = (x1-x2-t1*sqrt((s1/n1 + s2/n2)))
m2 = (x1-x2+t1*sqrt((s1/n1 + s2/n2)))

# c)
f1 = finv(1-alpha/2, n1-1, n2-1)
f2 = finv(alpha/2, n1-1, n2-1)
m1 = 1/f1 * s1/s2
m2 = 1/f2 * s1/s2

# A)
x = [20,21,22,23,24,25,26,27 ...
    2,1,3,6,5,9,2,2]
y = [75,76,77,78,79,80,81,82 ...
    3,2,2,5,8,8,1,1]
n =
X = mean(x)
Y = mean(y)

# b)
sx = var(X,1)
sy = var(Y,1)

# c)
c = cov(x,y,1)

# d)
coc = corrcoef(x,y)
c(1,2)
