delete(instrfindall);
s=serial('COM14');	
s.BytesAvailableFcnMode='byte';	%?��������??
s.InputBufferSize=4096;	
s.OutputBufferSize=1024;	
s.BytesAvailableFcnCount=5;
s.ReadAsyncMode='continuous';	
s.Terminator='CR';	
fopen(s);%�򿪴���
tic;
x=0;
out=fread(s,5,'uint8');	%һ�ζ���10���ַ�????
fprintf('%3d',out);	%һ���ַ�ռ��λ���,%c�ַ���%d����?

t=toc;