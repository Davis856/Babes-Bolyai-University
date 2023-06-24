p1 = normcdf(0,1,5)
p2 = 1 - p1
%b
p3 = normcdf(1,1,5) - normcdf(-1,1,5)
p4 = 1 - p3


#problem 1
alpha = input('alpha=')
beta = input('beta=')
option = input('option=', 's')
switch option
  case 'normal'
    u=input('u=')
    v=input('v=')
    p1 = normcdf(0,u,v)
    p2 = 1 - p1
    p3 = normcdf(1,u,v) - normcdf(-1,u,v)
    p4 = 1 - p3
    x1 = norminv(alpha, u, v)
    x2 = norminv(1-beta, u, v)
  case 'student'
    n=input('n=')
    p1 = tcdf(0, n)
    p2 = 1 - p1
    p3 = tcdf(1, n) - tcdf(-1, n)
    p4 = 1 - p3
    x1 = tinv(alpha, n)
    x2 = tinv(1-beta, n)
  case 'Fischer'
    u=input('u=')
    v=input('v=')
    p1 = fcdf(0, u, v)
    p2 = 1 - p1
    p3 = fcdf(1, u, v) - fcdf(-1, u, v)
    p4 = 1 - p3
    x1 = finv(alpha, u, v)
    x2 = finv(1-beta, u, v)
  otherwise
    fprintf('Error')
end

# problem 2 a
p=input('p=')
for u=1:3:100
  k=0:u;
  prob=binopdf(k,u,p);
  plot(k,prob)
  xlim([0, 100])
  ylim([0, 0.2])
  pause(0.2)
end

# problem 2 b
p=input('p=')
n=input('n=')
lambda=n*p
k=0:n
prob=binopdf(k,n,p);
plot(k, prob)
hold
pois = poisspdf(k, lambda)
plot(k, pois)



