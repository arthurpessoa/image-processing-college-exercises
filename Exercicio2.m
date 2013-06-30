## Arthur Pessoa de Souza 380075

clc;
close all;
clear all;
colormap(gray(256));
#a
s=0;
w=2*3.14;
x = 0:0.1:2;
for (i=1:2:1)
        s=(1/i) * sin(i*w*x) + s;
        end
#b
s1=0;
for (i=1:2:5)
        s1=(1/i) * sin(i*w*x) + s1;
        end
#c
s2=0;
for (i=1:2:9)
        s2=(1/i) * sin(i*w*x) + s2;
        end
#d
s3=0;
for (i=1:2:17)
        s3=(1/i) * sin(i*w*x) + s3;
        end

subplot(2,2,1),plot(x,s);
subplot(2,2,2),plot(x,s1);
subplot(2,2,3),plot(x,s2);
subplot(2,2,4),plot(x,s3);

##Sua forma de onda possui vários picos de altas e baixas frequências, com transições rápidas.
##Nesse Caso, quanto maior o número que estamos usando na função, vemos ainda mais como fica quadrado, então podemos concluir que quanto maior números ##usamos na função, mais parecida com ondas quadradas.
##Uma curiosidade da convergência da representação através da série de Fourier para a onda quadrada é o fenômeno de Gibbs. Artefatos pulsantes em ondas quadradas não ideais podem ser demonstrados como relacionados a este fenômeno. O fenômeno de Gibbs pode ser evitado através do uso da aproximação sigma, que utiliza o fator sigma de Lanczospara auxiliar a sequência a convergir mais suavemente.

