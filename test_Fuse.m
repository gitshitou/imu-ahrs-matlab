%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% kalman���ԣ� DRTK�⺽��
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function test_Fuse

N = 120; % ��������Ŀ
CON =25; % ��������ֵ
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%5
Xexpect = CON*ones(1,N); 
X = zeros(1,N);  %%��ʵ�¶�
Xkf =zeros(1,N);   %%����ֵ
Z= zeros(1,N);    %%�۲�ֵ-- �¶ȼ�
P= zeros(1,N);    %%Э���120�����

%%����ֵ
X(1) = 25.1;       %��ʼֵ�����¶�Ϊ25.1 
P(1) = 0.01;       %��ʼֵ��Э����
Z(1) = 24.9;
Xkf(1)= Z(1);     %% �ѳ�ʼ�Ĺ۲�ֵ ��ֵ�� ����ֵ

% ����
Q = 0.25;
R = 0.01;
W = sqrt(Q)*randn(1,N);
V = sqrt(R)*randn(1,N);  

%ϵͳ����
F = 1;
G = 1;
H = 1;
I = eye(1);   %��ϵͳ״̬Ϊ1ά
for k=2:N
    X(k) = F * X(k-1) +G * W(k-1);
    Z(k) = H * X(k) + V(k);
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
for k=2:N  
    % ��һ���� ����ʱ�����ƣ�������ʵ�¶Ȳ����仯

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
legend('����ֵ' , '��ʵֵ' ,'�۲�ֵ','kalman�˲�ֵ');
xlabel('����ʱ��/s');
ylabel('�¶�ֵ/C');

%������ͼ
figure
plot(t ,Err_Meassure ,'-b.',t,Err_Kalman, '-k*');
legend('����ƫ��','kalman�˲�ƫ��');
xlabel('����ʱ��/s');
ylabel('�¶Ȳ���ֵ/C');



