function q = getInitQ(accX ,accY, accZ, magX,magY ,magZ)
%功能：粗初始对准
%     accX,accY,accZ,...         %加速度原始值 m/s^2
%     %magX,magY,magZ,...        %地磁原始值

%    0.5352
%    -0.1529
%    -0.8266
%    -0.0836
xAxis = [1,0,0]; 
acc =[accX ;accY;accZ];
%  pitch = -atan2(accel[0], sqrt(accel[1] * accel[1] + accel[2] * accel[2]));
pitch = -atan2(accX ,sqrt(accY * accY + accZ * accZ));
% roll
temp1 = cross(acc,xAxis);
temp2 = cross(xAxis,temp1);
roll =  atan2(temp2(1,:), temp2(2,:));

% yaw
%mag_x = magnetom[0] * cos_pitch + magnetom[1] * sin_roll * sin_pitch + magnetom[2] * cos_roll * sin_pitch;
mag_x = magX*cos(pitch)+magY*sin(roll)*sin(pitch)+magZ*cos(roll)*sin(pitch);
mag_y = magY * cos(roll) - magZ * sin(roll);
yaw = atan2(-mag_y, mag_x);
q=[pitch,roll,yaw];