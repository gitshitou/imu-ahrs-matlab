%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% kalman测试， DRTK测航向
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function test_Fuse

N = 120; % 采样点数目
CON =25; % 室温理论值
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%5
Xexpect = CON*ones(1,N); 
X = zeros(1,N);  %%真实温度
Xkf =zeros(1,N);   %%估计值
Z= zeros(1,N);    %%观测值-- 温度计
P= zeros(1,N);    %%协方差，120个点的

%%赋初值
X(1) = 25.1;       %初始值房间温度为25.1 
P(1) = 0.01;       %初始值的协方差
Z(1) = 24.9;
Xkf(1)= Z(1);     %% 把初始的观测值 赋值给 估计值

% 噪声
Q = 0.25;
R = 0.01;
W = sqrt(Q)*randn(1,N);
V = sqrt(R)*randn(1,N);  

%系统矩阵
F = 1;
G = 1;
H = 1;
I = eye(1);   %本系统状态为1维
for k=2:N
    X(k) = F * X(k-1) +G * W(k-1);
    Z(k) = H * X(k) + V(k);
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
for k=2:N  
    % 第一步： 随着时间推移，房间真实温度波动变化

%     
    X_pre = F *Xkf(k-1);
    P_pre = F * P(k-1) * F' + Q;
    Kg = P_pre * inv(H * P_pre * H' + R);
    e = Z(k) - H * X_pre;
    Xkf(k) = X_pre + Kg *e;
    P(k) = (I - Kg * H) * P_pre;
    
    

end 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Err_Meassure = zeros(1 ,N);
Err_Kalman = zeros(1 , N);
for k=1:N
    Err_Meassure(k) = abs(Z(k) - X(k));
    Err_Kalman(k) = abs(Xkf(k) -X(k));
end
t =1:N;
figure
plot(t ,Xexpect, '-b',t, X, '-r.',t, Z, '-ko',t ,Xkf, '-g*');
legend('期望值' , '真实值' ,'观测值','kalman滤波值');
xlabel('采样时间/s');
ylabel('温度值/C');

%误差分析图
figure
plot(t ,Err_Meassure ,'-b.',t,Err_Kalman, '-k*');
legend('测量偏差','kalman滤波偏差');
xlabel('采样时间/s');
ylabel('温度测量值/C');



