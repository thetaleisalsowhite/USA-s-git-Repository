function [ ineq, cond ] = nonlcon( q )
% 制約条件
a = q(1); 
b = q(2); 
c = q(3); 
d = q(4);
x = q(5);
ineq = [-a; -b; -c; -d; -x];
cond = [ a+b+c+d - 4 ];
end