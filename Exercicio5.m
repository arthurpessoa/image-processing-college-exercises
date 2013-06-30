## Arthur Pessoa de Souza 380075

clc;
close all;
clear all;
colormap(gray(256));

lena=imread("lena14.jpg");

baixo = (1/9)*[1 1 1; 1 1 1; 1 1 1];
alto = [-1 -1 -1; -1 8 -1; -1 -1 -1];

x = conv2(lena, alto, "same");
y= conv2(lena, baixo, "same");
z= conv2(y, baixo, "same");
z2= conv2(z, baixo, "same");
x2 = conv2(z2, alto, "same");

subplot(2,3,1),image(lena);
subplot(2,3,2),image(abs(x));
subplot(2,3,3),image(y);
subplot(2,3,4), image(z);
subplot(2,3,5), image(z2);
subplot(2,3,6),image(abs(x2));


%% h0 é o filtro passa alto pois a soma dos valores de sua matriz é 0, e h1 e o filtro passa-baixa porque a soma de sua matriz é 1. Passamos os filtros na imagem com ruído para diminui-los, e então passamos o filtro passa-alta final para realce das bordas. Os filtros passa-baixa foram necessários para melhor identificação das bordas pelo filtro passa-alta, tendo seu resultado otimizado. 