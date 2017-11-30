MPU9150      = load ('DataSets/eV50p/Sequencia1/MPU9150',      'MATLABtime', 'ABBquaternion', 'ABBposition', 'SENSgyro', 'SENSacc', 'SENSmag'); % Invensense
%×ø±êÖáºÍABB¶ÔÆë
aux = MPU9150.SENSmag(1,:);                 % magx = ABBy
MPU9150.SENSmag(1,:)= MPU9150.SENSmag(2,:); % magy = ABBx
MPU9150.SENSmag(2,:)= aux;
MPU9150.SENSmag(3,:)=-MPU9150.SENSmag(3,:); % magz = -ABBz