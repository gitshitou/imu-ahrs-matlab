syms q0 q1 q2 q3;   %定义四元数
syms gx_raw  gy_raw  gz_raw;    %定义陀螺仪读数 rad/s
syms wx  wy  wz;    %定义陀螺仪读数 rad/s
syms t;
syms mag_x mag_y;
MAG_Heading = atan2(-mag_y, mag_x);
mm=[mag_x;mag_y];
%状态量-四元数
% q00 = q0+(-wx*q1-wy*q2-wz*q3)*t/2;
% q11 = q1+(wx*q0+wz*q2-wy*q3)*t/2;
% q22 = q2+(wy*q0-wz*q1+wx*q3)*t/2;
% q33 = q3+(wz*q0+wy*q1-wz*q2)*t/2;
q00 = (-wx*q1-wy*q2-wz*q3)*t/2;
q11 = (wx*q0+wz*q2-wy*q3)*t/2;
q22 = (wy*q0-wz*q1+wx*q3)*t/2;
q33 = (wz*q0+wy*q1-wz*q2)*t/2;
quat =[q0;q1;q2;q3];
quatNew =[q00;q11;q22;q33];
Tbn = Quat2Tbn(quat);
w = [wx;wy;wz];
newStateVector =[quatNew];
F = jacobian(newStateVector, w);
F2 = jacobian(MAG_Heading,mm);
Q = F2*[0.1;0.2]*transpose(F2);