##Arthur Pessoa de Souza 380075

clc;
close all;
clear all;
colormap(gray(256));

lena=imread("4.2.04.jpg");
macaco=imread("4.2.03.jpg");


x=zeros(512,512);
y=zeros(512,512);

for i = 1:512
	for j = 1:256
		
		x(i,j) = lena(i,j);
		
	endfor
endfor

for i = 1:512
	for j = 256:512
		
		y(i,j) = macaco(i,j);
		
	endfor
endfor

dftlena = fft2(x);
dftmac = fft2(y);

dftlena
soma = dftlena + dftmac;

resultante = ifft2(soma);

subplot(2,3,1),image(lena);
subplot(2,3,2),image(macaco);
subplot(2,3,3),image(x);
subplot(2,3,4),image(y);
subplot(2,3,5),image(real(resultante));

## A parte imaginária possui valor igual a zero, devido a seu domínio do espaço apenas possuír parte real.
## Isso é esperado pelos motivos descritos acima.
## Concluímos que, pela propriedade da distributividade da Transformada de Fourier, realizar a soma das duas imagens e então aplicar a transformada teve o mesmo resultado que aplicar a transformada em cada imagem e depois somar o resultado.