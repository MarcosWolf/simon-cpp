# simon-cpp

Jogo clássico Simon implementado em C++ usando SFML (Graphics + Audio). O jogador precisa repetir sequências de cores geradas aleatoriamente; cada cor tem som próprio.

## Sobre

SimonCPP é uma implementação didática do jogo Simon. O objetivo do jogo é memorizar e reproduzir sequências de cores/sons que vão aumentando a cada rodada. O projeto traz:

- Interface simples com 4 botões coloridos.
- Sons por cor e efeito de game over.
- Lógica de estado (mostrar sequência / esperar input).

## Tecnologias Utilizadas

- C++
- SFML 2.6.1

## Estrutura do Projeto
```text
SimonCPP/
├── src/
│   ├── main.cpp
│   ├── Game.cpp
│   ├── Window.cpp
│   └── Button.cpp
├── include/
│   ├── Game.hpp
│   ├── Window.hpp
│   ├── Button.hpp
│   └── AudioManager.hpp
├── resources/
│   ├── sfx/
│   │   ├── green.ogg
│   │   ├── red.ogg
│   │   ├── yellow.ogg
│   │   ├── blue.ogg
│   │   └── gameover.ogg
└── README.md
```
