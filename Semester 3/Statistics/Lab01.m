#problem 1
#A = [1, 0, -2; 2, 1, 3; 0, 1, 0]
#B = [2, 1, 1; 1, 0, -1; 1, 1, 0]
#C = A - B
#fprintf('C=\n')
#fprintf('%d %d %d\n', C')
#D = A * B
#fprintf('D=\n')
#fprintf('%d %d %d\n', D')
#E = A .* B
#fprintf('E=\n')
#fprintf('%d %d %d\n', E')

#problem 2
x=0:3
y=(x.^5)/10
y1=x.*sin(x)
y2=x.*cos(x)
#plot(x, y, "g")
#plot(x, y1, "b")
#plot(x, y2, "r")
#plot(x, y, "g", x, y1, "b", x, y2, "r")
#title('Lab01')
#legend('x5', 'sine', 'cosine')
#subplot(3, 1, 1): plot(x, y, "r");
#subplot(3, 1, 2): plot(x, y1, "g");
#subplot(3, 1, 3): plot(x, y2, "b");

function func(x)
   y=x+1
endfunction

func(1)

