function [xc,p]=UKFfiter(systemfun,measurefun,xc0,yc,p0,syspara,IMU)
%------------------------------------------
%�˳�����������UKF���޼�kalman�˲����㷨
%����: Jiangfeng
%���ڣ�2012.3.17
%------------------------------------------
global Qf Rf n;
%----------------����ע��-------------------
% xc0---״̬��ֵ(������)  yc---ϵͳ����ֵ
% p0----״̬���Э����    n----ϵͳ״̬����
%systemfun---ϵͳ���� measurefun--��������
%---------------�˲���ʼ��------------------
alp=0.01;                                 %default, tunable
kap=-1;                                   %default, tunable
beta=2;                                   %default, tunable
lamda=alp^2*(n+kap)-n;                    %scaling factor
nc=n+lamda;                               %scaling factor
Wm=[lamda/nc 0.5/nc+zeros(1,2*n)];        %weights for means
Wc=Wm;
Wc(1)=Wc(1)+(1-alp^2+beta);               %weights for covariance
ns=sqrt(nc);
t=syspara(1);h=syspara(2);
%-------------------------------------------

  sxk=0;spk=0;syk=0;pyy=0;pxy=0; p=p0;     
    
%--------------����sigma��-----------------
pk=ns*chol(p); % B=chol(A);meant:A'*A=B;
sigma=xc0;
for k=1:2*n
    if(k<=n)
       sigma=[sigma,xc0+pk(:,k)];
    else
       sigma=[sigma,xc0-pk(:,k-n)];
    end
end
%-------------ʱ�䴫������----------------
for ks=1:2*n+1
    sigma(:,ks)=systemfun(t,h,sigma(:,ks),IMU);%����ϵͳ���̶�״̬Ԥ��
    sxk=Wm(ks)*sigma(:,ks)+sxk;
end 
%----------��ɶ�Pk�Ĺ���
for kp=1:2*n+1
    spk=Wc(kp)*(sigma(:,kp)-sxk)*(sigma(:,kp)-sxk)'+spk;   
end
    spk=spk+Qf*1*Qf';
%-----------------------
for kg=1:2*n+1
    gamma(:,kg)=measurefun(sigma(:,kg));
end
for ky=1:2*n+1
    syk=syk+Wm(ky)*gamma(ky);
end
%--------------�������·���--------------
for kpy=1:2*n+1
    pyy=Wc(kpy)*(gamma(:,kpy)-syk)*(gamma(:,kpy)-syk)'+pyy;
end
    pyy=pyy+0.5;
for kxy=1:2*n+1
    pxy=Wc(kxy)*(sigma(:,kxy)-sxk)*(gamma(:,kxy)-syk)'+pxy;
end
   kgs=pxy/pyy;            %����ϵ��
   xc=sxk+kgs*(yc-syk);            %������Ϣ����״̬
   p=spk-kgs*pyy*kgs';             %���Э���������
%-------------------------------------

end
