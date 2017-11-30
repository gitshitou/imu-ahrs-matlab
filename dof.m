%% define symbolic variables and constants
clear all;
syms q0 q1 q2 q3;   %������Ԫ��
syms gx_raw  gy_raw  gz_raw;    %���������Ƕ��� rad/s
syms ax  ay  az;    %������ٶȶ��� m/s^2
syms mx  my  mz;    %����شŶ���  ��˹
syms magN magE magD;
syms g_bx g_by g_bz; %����������bias
syms g_qX g_qY  g_qZ a_qX a_qY a_qZ; %�������ݣ����ٶȵ�����
syms dt;
syms P;
%% һ��Ԥ��

%״̬��-��Ԫ��
quat =[q0;q1;q2;q3];
Tbn = Quat2Tbn(quat);
gx = gx_raw; %- g_bx;     %����ԭʼֵ-bias
gy = gy_raw; %- g_by;
gz = gz_raw;% - g_bz;

F1 = [1 ,-0.5*dt*gx, -0.5*dt*gy ,-0.5*dt*gz;...
      0.5*dt*gx , 1 , 0.5*dt*gz ,-0.5*dt*gy;  ...
      0.5*dt*gy ,-0.5*dt*gz, 1 ,0.5*dt*gx;...
      0.5*dt*gz ,0.5*dt*gy, -0.5*dt*gx ,1 ];
quatNew = F1 * quat;     %��Ԫ��״̬����
%״̬��-����ƫ��
g_b =[g_bx;g_by;g_bz];
%F2 = [1,0,0;0,1,0;0,0,1];
g_bNew = g_b;

% ״̬��-�ش�(��������ϵ)
magNnew = magN;
magEnew = magE;
magDnew = magD;
%״̬���ϲ�
stateVector =[quat];
newStateVector =[quatNew];

F = jacobian(newStateVector, stateVector);
%[F,SF]=OptimiseAlgebra(F,'SF');

%% Э����һ��Ԥ��
G= jacobian(newStateVector ,[gx_raw;gy_raw;gz_raw]);
distMatrix = diag([g_qX  g_qY  g_qZ ]);   %�Խ���
Q = G *distMatrix *transpose(G);
P_pre = F * P * transpose(F)+ Q;      %һ��Ԥ��  Э�������P

%% �۲ⷽ��
gravity = 1;
accMeas = transpose(Tbn)*[0 ; 0;gravity];
magMeas = transpose(Tbn)*[magN;magE;magD];   %�����-->�����
newMeas = [accMeas;magMeas];
H = jacobian(newMeas, stateVector);
