%% define symbolic variables and constants
clear all;
syms q0 q1 q2 q3;   %定义四元数
syms gx_raw  gy_raw  gz_raw;    %定义陀螺仪读数 rad/s
syms ax  ay  az;    %定义加速度读数 m/s^2
syms mx  my  mz;    %定义地磁读数  高斯
syms magN magE magD;
syms g_bx g_by g_bz; %定义陀螺仪bias
syms g_qX g_qY  g_qZ a_qX a_qY a_qZ; %定义陀螺，加速度的噪声
syms dt;
syms P;
%% 一步预测

%状态量-四元数
quat =[q0;q1;q2;q3];
Tbn = Quat2Tbn(quat);
gx = gx_raw; %- g_bx;     %陀螺原始值-bias
gy = gy_raw; %- g_by;
gz = gz_raw;% - g_bz;

F1 = [1 ,-0.5*dt*gx, -0.5*dt*gy ,-0.5*dt*gz;...
      0.5*dt*gx , 1 , 0.5*dt*gz ,-0.5*dt*gy;  ...
      0.5*dt*gy ,-0.5*dt*gz, 1 ,0.5*dt*gx;...
      0.5*dt*gz ,0.5*dt*gy, -0.5*dt*gx ,1 ];
quatNew = F1 * quat;     %四元数状态方程
%状态量-陀螺偏置
g_b =[g_bx;g_by;g_bz];
%F2 = [1,0,0;0,1,0;0,0,1];
g_bNew = g_b;

% 状态量-地磁(地理坐标系)
magNnew = magN;
magEnew = magE;
magDnew = magD;
%状态量合并
stateVector =[quat];
newStateVector =[quatNew];

F = jacobian(newStateVector, stateVector);
%[F,SF]=OptimiseAlgebra(F,'SF');

%% 协方差一步预测
G= jacobian(newStateVector ,[gx_raw;gy_raw;gz_raw]);
distMatrix = diag([g_qX  g_qY  g_qZ ]);   %对角阵
Q = G *distMatrix *transpose(G);
P_pre = F * P * transpose(F)+ Q;      %一步预测  协方差矩阵P

%% 观测方程
gravity = 1;
accMeas = transpose(Tbn)*[0 ; 0;gravity];
magMeas = transpose(Tbn)*[magN;magE;magD];   %地理磁-->机体磁
newMeas = [accMeas;magMeas];
H = jacobian(newMeas, stateVector);
