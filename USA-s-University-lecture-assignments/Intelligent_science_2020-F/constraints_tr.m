function [ ineq, cond ] = nonlcon( q )
% 制約条件
a = q(1); b = q(2); c = q(3);
ineq = [-a; -b; -c];
cond = [ a+b+c - 3 ];
end