function y = ekf_6dof(gyroX,gyroY,gyroZ,accX,accY,accZ,dt ,TX)
%function y = test_ekf(gyroX,gyroY,gyroZ,accX,accY,accZ,dt )
%     gyroX,gyroY,gyroZ,...        %陀螺仪原始值
%     accX,accY,accZ,...         %加速度原始值 m/s^2
%     %magX,magY,magZ,...         %地磁原始值
%     dt)  %积分时间
 
%状态转移矩阵..。
A= [1  , -0.5*dt*gyroX   ,-0.5*dt*gyroY  , -0.5*dt*gyroZ;...
    0.5*dt*gyroX , 1  ,  0.5*dt*gyroZ  ,  -0.5*dt*gyroY;...
    0.5*dt*gyroY , -0.5*dt*gyroZ , 1  ,   0.5*dt*gyroX;...
    0.5*dt*gyroZ ,   0.5*dt*gyroY ,   -0.5*dt*gyroX,  1];
%Q
%R
%--- Dataset parameters
%deltat = 1/200;             % Sampling period
%noise_gyro = 2.4e-2;        % Gyroscope noise(discrete), rad/s
%noise_accel = 2.83e-2;      % Accelerometer noise, m/s^2

noise_gyro = 2.4e-3;        % Gyroscope noise(discrete), rad/s
noise_accel = 2.83e-2; 
gravity = 9.81007;          % Gravity magnitude, m/s^2

persistent states_est P_P_est                % Initial state conditions
if isempty(states_est)
    %states_est = [1;0;0;0];              % x_est=[x,y,Vx,Vy,Ax,Ay]'
    states_est = TX; 
    P_P_est = 1e-10 * eye(4);
end

% 状态预测，协方差预测
states_prd = A * states_est;
states_prd = states_prd / norm(states_prd);    %四元数归一化
G = [-states_est(2)  -states_est(3)  -states_est(4); ...
          states_est(1)  -states_est(4)   states_est(3); ...
          states_est(4)   states_est(1)  -states_est(2); ...
         -states_est(3)   states_est(2)   states_est(1)] / 2;
Q = (noise_gyro * dt)^2 * (G * G');   %%原程序
%Q = G*(noise_gyro * dt )^2 * transpose(G);  %%测试一下,结果是一样的
P_P_prd = A * P_P_est * A' + Q;

%估计量
a =[accX; accY; accZ];
% [ -2*q2,  2*q3, -2*q0, 2*q1]
% [  2*q1,  2*q0,  2*q3, 2*q2]
% [  2*q0, -2*q1, -2*q2, 2*q3]
H =[ -2*states_prd(3), 2*states_prd(4), -2*states_prd(1), 2*states_prd(2);...
      2*states_prd(2), 2*states_prd(1),  2*states_prd(4), 2*states_prd(3);...
      2*states_prd(1), -2*states_prd(2), -2*states_prd(3),2*states_prd(4)];
% H =[ (98*states(3))/5, -(98*states(4))/5,  (98*states(1))/5, -(98*states(2))/5;...
%     -(98*states(2))/5, -(98*states(1))/5, -(98*states(4))/5, -(98*states(3))/5;...
%     -(98*states(1))/5,  (98*states(2))/5,  (98*states(3))/5, -(98*states(4))/5];
innvo = a/norm(a) - H*states_prd;
% Measurement noise R.
R_internal = (noise_accel / norm(a))^2 * eye(3);
R_external = (1-gravity/norm(a))^2 * eye(3);
R = R_internal + R_external;

Kg = P_P_prd * H'/(H*P_P_prd*H'+R);                   %Kg= P(k|k-1)HT/(HP(k|k-1)HT+R)
states_est = states_prd + Kg* innvo;
%P_P_est = P_P_prd -P_P_prd * H;    eye(4)
P_P_est = (eye(4) - Kg * H) * P_P_prd;
y = states_est;
end 
