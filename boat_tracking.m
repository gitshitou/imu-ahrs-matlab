function boat_tracking
%%
clc; clear;
T = 1; %�״�ɨ������
N = 80/T; % ������
X = zeros(4,N); %��ʵλ�ã��ٶ�
X(:,1) = [-100,2,200,20]; % ��ʼ�ٶ�
Z = zeros(2,N);   %�۲���
Z(:,1) = [X(1,1),X(3,1)];  %�۲��ʼ��
delta_w = 1e-2;
Q = delta_w *diag([0.5,1,0.5,1]);
R = 2 *eye(2);   % 2X2����
F = [1,T,0,0; 0,1,0,0; 0,0,1,T;0,0,0,1];  % ����ת�ƾ���
H = [1,0,0,0;0,0,1,0];    %�۲����
%%%%%%%%%%%%%%%%%%%%%%%%
for k=2:N
    X(:,k) = F*X(:,k-1)+ sqrt(Q)*randn(4,1);
    Z(:,k) = H*X(:,k)+sqrt(R)*randn(2,1);
end 
%%%%%%%%%%%%%%%%%%%%%%%%%
Xkf = zeros(4,N);
Xkf(:,1) = X(:,1);  %%�˲�״̬��ʼ��
Plater = eye(4);    %%Э�����ʼ��Ϊ4�鵥λ����
for i=2:N
    Xpre = F* Xkf(:,i-1);
    Ppre = F * Plater * F'+Q;
    K = Ppre * H' * inv(H *Ppre*H'+R);  %����
    Xkf(:,i) = Xpre + K*(Z(:,i)-H*Xpre);  
    Plater = (eye(4) - K*H) *Ppre;   %����Э����
end
%������
% for i=1:N
%     Err_ob(i) = rms(X(:,i),Z(:,i));
%     Err_kalman(i) = rms(X(:,i),Xkf(:,i));
% end

%%%%%%%%%%%%%%%%
figure
hold on;box on;
plot(X(1,:) ,X(3,:),'-k');   %%��ʵ�켣
plot(Xkf(1,:) ,Xkf(3,:),'-b');  %%������Ԥ��ֵ
plot(Z(1,:) ,Z(2,:),'-r+');    %%�۲�ֵ
legend('��ʵ�켣','kalmanԤ��켣','�۲�켣');
xlabel('������X/m');
ylabel('������Y/m');

    
 



