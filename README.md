# Aquário 3D

Este é um projeto da disciplina de Computação Gráfica em linguagem C que simula um aquário 3D, utilizando a biblioteca OpenGL para gráficos e a biblioteca SOIL para manipulação de texturas.

## Compilação

Para compilar o programa no Linux, utilize o seguinte comando:

```bash
gcc -o aquario main.c recursos.c cena.c peixe.c iluminacao.c -lglut -lGLU -lGL -lm -lSOIL
