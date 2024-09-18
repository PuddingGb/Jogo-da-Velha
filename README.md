**Jogo da Velha**

Este é simples Jogo da Velha que desenvolvi usando raylib. Esse é meu primeiro jogo e também o primeiro programa que criei com uma interface gráfica! Antes disso, eu havia feito uma versão de Jogo da Velha baseada em terminal, e reutilizei parte do código desse projeto para construir esta versão.

Consegui completar o jogo em menos de uma semana, e foi uma ótima experiência para aprender a trabalhar com gráficos, entrada do usuário e lógica de jogo.

**Funcionalidades**

* Jogo da Velha para 2 jogadores.
* Interface gráfica feita com raylib.
* Detecção de vitória para combinações horizontais, verticais e diagonais.
* Detecta quando o jogo termina em velha (empate).

**Requisitos**

* raylib (certifique-se de que está instalada ou vinculada corretamente).
* Um compilador C (usei MinGW 64-bit no Windows).

*Para facilitar, baixe o instalador raylib para windows, e no ambiente w64devkit insira o código a seguir:*

cd "diretório-onde-está-localizado-o-arquivo-do-jogo"

gcc -o jogo-da-velha jogo-da-velha.c -I"C:\raylib\w64devkit\x86_64-w64-mingw32\include" -L"C:\raylib\w64devkit\x86_64-w64-mingw32\lib" -lraylib -lwinmm -lgdi32 -lopengl32
