##Arthur Pessoa de Souza 380075

clc;
close all;
clear all;
colormap(gray(256));

lena=imread("4.2.04.jpg");

lenafreq = fft2(lena);
prev1 = fftshift(lenafreq);
prev2 = prev1([128:1:383], [128:1:383]);
prev3 = fftshift(prev2);
final = ifft2(prev3);

x = abs(final);
y = zeros(256,256);
for i=1:256
	for j=1:256
		y(i,j) = (255*x(i,j))/992;
	endfor
endfor

colormap(gray(256));
max(max(abs(final)))
max(max(y))

subplot(2,3,1),image(abs(final));
subplot(2,3,2),image(y);


##Não mantém o nível DC como efeito colateral.
## Foi necessário aplicar função pontal para 