delete(instrfindall);
s=serial('COM14');	
s.BytesAvailableFcnMode='byte';	%?串口设置??
s.InputBufferSize=4096;	
s.OutputBufferSize=1024;	
s.BytesAvailableFcnCount=5;
s.ReadAsyncMode='continuous';	
s.Terminator='CR';	
fopen(s);%打开串口
tic;
x=0;
out=fread(s,5,'uint8');	%一次读出10个字符????
fprintf('%3d',out);	%一个字符占三位输出,%c字符，%d整型?

t=toc;