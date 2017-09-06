function [xcheck,ycheck,Nfinal]=cleanCloseObjectCluster(x,y, cx, cy, D, L, M)

r=round(D/2.0);
checkInd=true(length(x),1);
tmp=zeros([L L]);

% repartir los N puntos generados en distintos clusters
nc = length(cx);
if nc == 0
    ppc = length(x);
else
    ppc = ceil(length(x)/nc);
end
printf('n = %i     nc = %i    ppc = %i\ndistributing clusters.......', length(x), nc, ppc);
for j=0:nc-1
    k=j*ppc;
    while(k < length(x) && k < (j*ppc + ppc))
        %x(k+1) = mod(x(k+1) + (cx(j+1) - round((L - L/2)/2)), L - D - 2*M) + r + M;
        %y(k+1) = mod(y(k+1) + (cy(j+1) - round((L - L/2)/2)), L - D - 2*M) + r + M;
        x(k+1) = max(min(x(k+1) + cx(j+1) - round(L/2), L-round(D/2)), round(D/2));
        y(k+1) = max(min(y(k+1) + cy(j+1) - round(L/2), L-round(D/2)), round(D/2));
        %printf('x %i     y %i\n', x(k+1), y(k+1));
        k = k+1;
    end
end
printf('ok\n');
     

printf('solving collisions..........');
for i=1:length(x)
    xl=max(round(x(i))-D,1):min(round(x(i))+D, L);
    yl=max(round(y(i))-D,1):min(round(y(i))+D, L);
    [XL,YL]=meshgrid(xl,yl);
    
    indxl=sub2ind([L L], YL, XL);
    if sum(sum(tmp(indxl))) > 0
        %ahora verificacion euclideana
        indtocheck=find(tmp(indxl)>0);
        tocheck=tmp(indxl(indtocheck));
        dsts=sqrt((round(x(tocheck))-round(x(i))).^2 + (round(y(tocheck))-round(y(i))).^2);
        if sum( dsts < D ) > 0
            checkInd(i)=0;
        else
            tmp(y(i),x(i))=i;
        end
    else
        tmp(y(i),x(i))=i;
    end
end
xcheck=x(checkInd);
ycheck=y(checkInd);
printf('ok\n');

Nfinal = length(find(xcheck));
fprintf('Ninitial %d -->  Nfinal %d\n', length(x), Nfinal);

end
