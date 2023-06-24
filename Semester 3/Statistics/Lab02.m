clf
hold on

n=input('Nr of trials=')
p=input('Probs of success=')

x=0:n
px=binopdf(x,n,p)
plot(x,px,'+')

xx=0:0.1:n
fx = binocdf(xx,n,p)
plot(xx,fx,'-')

# a) b)
p1=binopdf(0,3,0.5)
fprintf('%1.4f\n', p1)

# c) P(X!=1)
p2=1-binopdf(1,3,0.5)
fprintf('%1.4f\n', p2)

# d) P(X<=2)
p3=binopdf(2,3,0.5)
fprintf('%1.4f\n', p3)

# P(X<2)
p4=binopdf(1,3,0.5)
fprintf('%1.4f\n', p4)

# e) P(X>=1)
p5=1-binocdf(1,3,0.5)
fprintf('%1.4f\n', p5)

#rand() < 0.5

N=1000
C=rand(3, N)
D=C<0.5
E=sum(D)
hist(E)
