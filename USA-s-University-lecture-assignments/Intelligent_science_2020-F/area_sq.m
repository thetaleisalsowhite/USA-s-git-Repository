function s = area ( q )
% 面積
a = q(1); 
b = q(2); 
c = q(3);
d = q(4);
x = q(5);
ms1= (a+b+x)/2;
ms2= (c+d+x)/2;
g = sqrt(ms1*(ms1-a)*(ms1-b)*(ms1-x))+sqrt(ms2*(ms2-c)*(ms2-d)*(ms2-x));
s=-g;
end