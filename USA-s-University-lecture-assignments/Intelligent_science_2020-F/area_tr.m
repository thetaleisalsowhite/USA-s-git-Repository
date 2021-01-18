function s = area ( q )
% 面積
a = q(1); b = q(2); c = q(3);
ms= (a+b+c)/2;
g = sqrt(ms*(ms-a)*(ms-b)*(ms-c));
s=-g;
end