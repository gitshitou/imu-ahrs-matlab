function boat_tracking
%%
clc; clear;
T = 1; %雷达扫描周期
N = 80/T; % 采样数
X = zeros(4,N); %真实位置，速度
X(:,1) = [-100,2,200,20]; % 初始速度
Z = zeros(2,N);   %观测量
Z(:,1) = [X(1,1),X(3,1)];  %观测初始化
delta_w = 1e-2;
Q = delta_w *diag([0.5,1,0.5,1]);
R = 2 *eye(2);   % 2X2矩阵
F = [1,T,0,0; 0,1,0,0; 0,0,1,T;0,0,0,1];  % 过程转移矩阵
H = [1,0,0,0;0,0,1,0];    %观测矩阵
%%%%%%%%%%%%%%%%%%%%%%%%
for k=2:N
    X(:,k) = F*X(:,k-1)+ sqrt(Q)*randn(4,1);
    Z(:,k) = H*X(:,k)+sqrt(R)*randn(2,1);
end 
%%%%%%%%%%%%%%%%%%%%%%%%%
Xkf = zeros(4,N);
Xkf(:,1) = X(:,1);  %%滤波状态初始化
Plater = eye(4);    %%协方差初始化为4介单位矩阵
for i=2:N
    Xpre = F* Xkf(:,i-1);
    Ppre = F * Plater * F'+Q;
    K = Ppre * H' * inv(H *Ppre*H'+R);  %增益
    Xkf(:,i) = Xpre + K*(Z(:,i)-H*Xpre);  
    Plater = (eye(4) - K*H) *Ppre;   %更新协方差
end
%误差分析
% for i=1:N
%     Err_ob(i) = rms(X(:,i),Z(:,i));
%     Err_kalman(i) = rms(X(:,i),Xkf(:,i));
% end

%%%%%%%%%%%%%%%%
figure
hold on;box on;
plot(X(1,:) ,X(3,:),'-k');   %%真实轨迹
plot(Xkf(1,:) ,Xkf(3,:),'-b');  %%卡尔曼预测值
plot(Z(1,:) ,Z(2,:),'-r+');    %%观测值
legend('真实轨迹','kalman预测轨迹','观测轨迹');
xlabel('横坐标X/m');
ylabel('纵坐标Y/m');

    
 



