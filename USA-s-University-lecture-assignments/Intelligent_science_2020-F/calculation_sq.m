qinit = [0.1;0.1;0.1;0.1;0.1];
[q,gmin] = fmincon(@area, qinit, ...
[], [], [], [], [], [], @nonlcon);
smax=-gmin
q
gmin
smax