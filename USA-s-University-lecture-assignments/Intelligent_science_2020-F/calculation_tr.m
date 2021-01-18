calculation.m
qinit = [1.9;1.8;1.7];
[q,gmin] = fmincon(@area, qinit, ...
[], [], [], [], [], [], @nonlcon);
smax=-gmin
q
gmin
smax