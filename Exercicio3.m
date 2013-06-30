## Arthur Pessoa de Souza 380075


clc;
close all;
clear all;

lena=imread("4.2.04.jpg");
ruido=imread("lena14.jpg");

subplot(2,3,1),image(lena);
subplot(2,3,2),image(ruido);

x=fft2(lena);
y=fft2(ruido);

for i = 1:512
	for j = 1:512
		z(i,j) = (real(x(i,j))^2 + imag(x(i,j))^2)^0.5;
	endfor
endfor

for i = 1:512
	for j = 1:512
		z2(i,j) = (real(y(i,j))^2 + imag(x(i,j))^2)^0.5;
	endfor
endfor

colormap(gray(256));

subplot(2,3,3),image(z);
subplot(2,3,4),image(z2);


## É possível concluir que a imagem ruidosa possui mais pontos de alta frequẽncia,
## enquanto a imagem sem ruidos possui mais pontos de baixa frequência em relação a imagem ruidosa.
## Logo podemos supor que a quantidade pontos de altas frequências está relacionado a quantidade de ruidos em uma imagem.