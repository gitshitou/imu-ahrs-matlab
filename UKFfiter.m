function [xc,p]=UKFfiter(systemfun,measurefun,xc0,yc,p0,syspara,IMU)
%------------------------------------------
%此程序用于描述UKF（无迹kalman滤波）算法
%作者: Jiangfeng
%日期：2012.3.17
%------------------------------------------
global Qf Rf n;
%----------------参数注解-------------------
% xc0---状态初值(列向量)  yc---系统测量值
% p0----状态误差协方差    n----系统状态量数
%systemfun---系统方程 measurefun--测量方程
%---------------滤波初始化------------------
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
    
%--------------构造sigma点-----------------
pk=ns*chol(p); % B=chol(A);meant:A'*A=B;
sigma=xc0;
for k=1:2*n
    if(k<=n)
       sigma=[sigma,xc0+pk(:,k)];
    else
       sigma=[sigma,xc0-pk(:,k-n)];
    end
end
%-------------时间传播方程----------------
for ks=1:2*n+1
    sigma(:,ks)=systemfun(t,h,sigma(:,ks),IMU);%利用系统方程对状态预测
    sxk=Wm(ks)*sigma(:,ks)+sxk;
end 
%----------完成对Pk的估计
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
%--------------测量更新方程--------------
for kpy=1:2*n+1
    pyy=Wc(kpy)*(gamma(:,kpy)-syk)*(gamma(:,kpy)-syk)'+pyy;
end
    pyy=pyy+0.5;
for kxy=1:2*n+1
    pxy=Wc(kxy)*(sigma(:,kxy)-sxk)*(gamma(:,kxy)-syk)'+pxy;
end
   kgs=pxy/pyy;            %修正系数
   xc=sxk+kgs*(yc-syk);            %测量信息修正状态
   p=spk-kgs*pyy*kgs';             %误差协方差阵更新
%-------------------------------------

end
