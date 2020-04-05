xtarget = 1;
ytarget = 1.5;

xpos= 2;
ypos= 1.32;

xadv=0.5;
yadv=1.3;
distlimadv=0.7;
krepadv=1;

distlim=0.18;
katt=170;
krep=1;

grid=0.04;
%X= 0:grid:3;
%Y= 0:grid:2;
X= -1:grid:1;
Y= -1.5:grid:1.5;
sizeX=size(X);
sizex=sizeX(2);
sizeY=size(Y);
sizey=sizeY(2);
[xx,yy]=meshgrid(X,Y);

% obstacle1=zeros(2,sizey); %mur gauche
% obstacle2=3*ones(2,sizey); %mur droite
% for j=1:sizey
%     obstacle1(2,j)=grid*(j-1);
%     obstacle2(2,j)=grid*(j-1);
% end
% obstacle3=zeros(2,sizex); %mur bas
% obstacle4=2*ones(2,sizex); %mur haut
% for j=1:sizex
%     obstacle3(1,j)=grid*(j-1);
%     obstacle4(1,j)=grid*(j-1);
% end
% obstacle5_1=0.8*ones(2,(0.4/grid)+1);
% obstacle5_2=0.4*ones(2,(0.2/grid)+1);
% obstacle5_3=1.0*ones(2,(0.4/grid)+1);
% obstacle6_1=1.4*ones(2,(0.4/grid)+1);
% obstacle6_2=0.4*ones(2,(0.2/grid)+1);
% obstacle6_3=1.6*ones(2,(0.4/grid)+1);
% obstacle7_1=2.0*ones(2,(0.4/grid)+1);
% obstacle7_2=0.4*ones(2,(0.2/grid)+1);
% obstacle7_3=2.2*ones(2,(0.4/grid)+1);
% for j=1:((0.4/grid)+1)
%     obstacle5_1(2,j)=(j-1)*grid;
%     obstacle5_3(2,j)=(j-1)*grid;
%     obstacle6_1(2,j)=(j-1)*grid;
%     obstacle6_3(2,j)=(j-1)*grid;
%     obstacle7_1(2,j)=(j-1)*grid;
%     obstacle7_3(2,j)=(j-1)*grid;
% end
% for j=1:((0.2/grid)+1)
%     obstacle5_2(1,j)=(j-1)*grid+0.8;
%     obstacle6_2(1,j)=(j-1)*grid+1.4;
%     obstacle7_2(1,j)=(j-1)*grid+2.0;
% end
% obstacle8_1=1.88*ones(2,(1.2/grid)+1);
% obstacle8_2=1.2*ones(2,(0.12/grid)+1);
% obstacle9_1=1.88*ones(2,(1.2/grid)+1);
% obstacle9_2=1.8*ones(2,(0.12/grid)+1);
% for j=1:((1.2/grid)+1)
%     obstacle8_1(1,j)=(j-1)*grid;
%     obstacle9_1(1,j)=(j-1)*grid+1.8;
% end
% for j=((0.12/grid)+1)
%     obstacle8_2(2,j)=(j-1)*grid+1.88;
%     obstacle9_2(2,j)=(j-1)*grid+1.88;
% end
% obstacle10_1=0.56*ones(2,(0.24/grid)+1);
% obstacle10_2=0.24*ones(2,(0.56/grid)+1);
% obstacle11_1=0.56*ones(2,(0.24/grid)+1);
% obstacle11_2=2.76*ones(2,(0.56/grid)+1);
% for j=1:((0.24/grid)+1)
%     obstacle10_1(1,j)=(j-1)*grid;
%     obstacle11_1(1,j)=(j-1)*grid+2.76;
% end
% for j=1:((0.24/grid)+1)
%     obstacle10_2(2,j)=(j-1)*grid;
%     obstacle11_2(2,j)=(j-1)*grid;
% end



% obstacle2=ones(2,sizey);
% obstacle1=-ones(2,sizey);
% for j=1:sizey
%     obstacle1(2,j)=-1.5+grid*(j-1);
%     obstacle2(2,j)=-1.5+grid*(j-1);
% end
% obstacle3=-1.5*ones(2,sizex);
% obstacle4=1.5*ones(2,sizex);
% for j=1:sizex
%     obstacle3(1,j)=-1+grid*(j-1);
%     obstacle4(1,j)=-1+grid*(j-1);
% end

%% nbobstacle_nbpoint=[x y distlim]
%recifs
obstacle5_1=[1 -0.6 0.33];
obstacle5_2=[0.8 -0.6 0.23];
obstacle5_3=[0.7 -0.6 0.19];
obstacle5=[obstacle5_1;obstacle5_2;obstacle5_3];
obstacle6_1=[1 0 0.33];
obstacle6_2=[0.8 0 0.23];
obstacle6_3=[0.7 0 0.19];
obstacle6=[obstacle6_1;obstacle6_2;obstacle6_3];
obstacle7_1=[1 0.6 0.33];
obstacle7_2=[0.8 0.6 0.23];
obstacle7_3=[0.7 0.6 0.19];
obstacle7=[obstacle7_1;obstacle7_2;obstacle7_3];
%bancs de sable longs
obstacle8_1=[-1 -0.3 0.25];
obstacle8_2=[-0.8 -0.3 0.15];
obstacle8_3=[-1 -0.5 0.33];
obstacle8_4=[-1 -0.7 0.33];
obstacle8_5=[-1 -0.9 0.33];
obstacle8_6=[-1 -1.1 0.33];
obstacle8_7=[-1 -1.3 0.33];
obstacle8=[obstacle8_1;obstacle8_2;obstacle8_3;obstacle8_4;obstacle8_5;obstacle8_6;obstacle8_7];
obstacle9_1=[-1 0.3 0.25];
obstacle9_2=[-0.8 0.3 0.15];
obstacle9_3=[-1 0.5 0.33];
obstacle9_4=[-1 0.7 0.33];
obstacle9_5=[-1 0.9 0.33];
obstacle9_6=[-1 1.1 0.33];
obstacle9_7=[-1 1.3 0.33];
obstacle9=[obstacle9_1;obstacle9_2;obstacle9_3;obstacle9_4;obstacle9_5;obstacle9_6;obstacle9_7];
%bancs de sable coins
obstacle10=[0.8 -1.5 0.43];
obstacle11=[0.8 1.5 0.43];
%pitits ilôts de sable
obstacle12=[-0.661 -0.308 0.18];
obstacle13=[-0.661 0.308 0.18];

obstacle=[obstacle5;obstacle6;obstacle7;obstacle8;obstacle9;obstacle10;obstacle11;obstacle12;obstacle13];
%%

distobstacle=300*ones(sizex,sizey); % distance de l'obstacle le plus proche
U=zeros(sizey,sizex);
for i=1:sizex
    for j=1:sizey
%         %distance obstacle1
%         for k=1:sizey
%             dist=sqrt((X(i)-obstacle1(1,k))^2+(Y(j)-obstacle1(2,k))^2);
%             if (dist<distobstacle(i,j))
%                 distobstacle(i,j)=dist;
%             end
%         end
%         %distance obstacle2
%         for k=1:sizey
%             dist=sqrt((X(i)-obstacle2(1,k))^2+(Y(j)-obstacle2(2,k))^2);
%             if (dist<distobstacle(i,j))
%                 distobstacle(i,j)=dist;
%             end
%         end
%         %distance obstacle3
%         for k=1:sizex
%             dist=sqrt((X(i)-obstacle3(1,k))^2+(Y(j)-obstacle3(2,k))^2);
%             if (dist<distobstacle(i,j))
%                 distobstacle(i,j)=dist;
%             end
%         end
%         %distance obstacle4
%         for k=1:sizex
%             dist=sqrt((X(i)-obstacle4(1,k))^2+(Y(j)-obstacle4(2,k))^2);
%             if (dist<distobstacle(i,j))
%                 distobstacle(i,j)=dist;
%             end
%         end
%
%         if (distobstacle(i,j)<10^-5)
%             distobstacle(i,j)=0.03;
%         end
        

        distobst=sqrt((X(i)-obstacle(:,1)).^2+(Y(j)-obstacle(:,2)).^2);
        sizedist=size(distobst);
        K=sizedist(1);
        
        if X(i)<-1+distlim
            U(j,i)=U(j,i)+krep*((1/(X(i)+1 - distlim))^2)/2;
        end
        if X(i)>1-distlim
            U(j,i)=U(j,i)+krep*((1/(1-X(i) - distlim))^2)/2;
        end
        if Y(j)<-1.5+distlim
            U(j,i)=U(j,i)+krep*((1/(Y(j)+1.5 - distlim))^2)/2;
        end
        if Y(j)>1.5-distlim
            U(j,i)=U(j,i)+krep*((1/(1.5-Y(j)-distlim))^2)/2;
        end
        
        for k=1:K
            if distobst(k)<obstacle(k,3)
                U(j,i)=U(j,i)+krep*((1/(distobst(k)-obstacle(k,3)))^2)/2;
            end
        end
        
        disttarget2=(X(i)-xtarget).^2+(Y(j)-ytarget).^2;
        U(j,i)=U(j,i)+katt*disttarget2/2;


        distadv=sqrt((X(i)-xadv)^2+(Y(j)-yadv)^2);
%         if (distadv<10^-5)
%             distadv=0.01;
%         end
        
%         if (distobstacle(i,j)<distlim) 
%             U(j,i)=U(j,i)+krep*((1/distobstacle(i,j) - 1/distlim)^2)/2;
%             %U(j,i)=U(j,i)+krep*(1/(distobstacle(i,j) - distlim))/2;
%         end
        if (distadv<distlimadv) 
            U(j,i)=U(j,i)+krepadv*((1/distadv-distlimadv)^2)/2;
            %U(j,i)=U(j,i)+krepadv*(1/(distobstacle(i,j) - distlim))/2;
        end
        
        
        if U(j,i)>1000
            U(j,i)=1000;
        end
    end
end

figure;

contour(X,Y,U);
hold on
stem(xadv,yadv,'LineStyle','none','MarkerSize',10,'color','r','MarkerFaceColor','r');
hold on

U=-U;
[px,py] = gradient(U,grid,grid);
quiver(X,Y,px,py)
x=xpos/grid +1;
y=ypos/grid +1;
%Fx=px(y,x)
%Fy=py(y,x)
