%tamagno de la imagen a generar
%caudrada
sizeimage=500;
%nro de particular (dist uniforme)
%notar que pueden ser menos pues no 
%se revisa que no esten a distancia
%menor factorD*D
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%parametros de las particulas
D=10.0;
w=1.4273;
Margin=2;

arg_list = argv();
if( length(arg_list) != 9 )
    printf('error must run as: octave script.m prefix folder fD L Ngen A B Nc seed\n;');
else
    prefix = arg_list{1};
    folder = arg_list{2};
    factorD = str2num(arg_list{3});
    sizeimage = str2num(arg_list{4});
    N = str2num(arg_list{5});
    alpha = str2num(arg_list{6});
    beta = str2num(arg_list{7});
    Nc = str2num(arg_list{8});
    seed = str2num(arg_list{9});
    printf('args: %s  D=%i   L=%i  Ninitial=%i   alpha=%i   beta=%i   Nc = %i seed = %i\n', prefix, D, sizeimage, N, alpha, beta, Nc, seed);

    % set seed
    rand('seed',seed);
    randn('seed',seed);

    % gen betadist random numbers
    x=ceil(D/2) + Margin + ceil( (sizeimage - D - 2*Margin)*betarnd(alpha,beta, N, 1) );
    y=ceil(D/2) + Margin + ceil( (sizeimage - D - 2*Margin)*betarnd(alpha,beta, N, 1) );
    cx = randi([ceil(sizeimage/8) ceil(sizeimage - sizeimage/8)], Nc, 1);
    cy = randi([ceil(sizeimage/8) ceil(sizeimage - sizeimage/8)], Nc, 1);
    tic;
    %[xcheck,ycheck,Nfinal]=cleanCloseObject2(x,y,D*factorD,sizeimage);
    [xcheck,ycheck,Nfinal]=cleanCloseObjectCluster(x,y,cx,cy,D*factorD,sizeimage, Margin);
    toc;
    I=zeros([sizeimage sizeimage], 'uint8');

    indx=sub2ind(size(I), ycheck, xcheck);
    BW=false(size(I));
    BW(indx)=1;

    %generar imagen basado en convolution
    printf('Generating Image............');
    x=-50:50;
    y=x;
    [X,Y]=meshgrid(x,y);
    ipi=(1-tanh((sqrt(X.^2+Y.^2)-D/2)/w))/2;
    resultado1=conv2(BW*1.0,ipi, 'same');
    %figure(1), imshow(resultado1);

    %nombre imagen de salida (.tif)
    PACKD = Nfinal * 3.14159265359 * (D/2)^2 / (sizeimage^2);
    printf('ok\n');
    printf('(density %i)\n', PACKD*100.0);
    printf('saving......................');
    outputfilename=sprintf('%s/%s_fD%i_A%i_B%i_L%d_N%d_NC%d_d%f.tif', folder, prefix, factorD, alpha, beta, sizeimage, Nfinal, Nc, PACKD*100);
    imwrite(uint8(255 - 255.0*resultado1), outputfilename);
    printf('ok\n');
end
clear
