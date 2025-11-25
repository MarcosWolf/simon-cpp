# simon-cpp

Jogo clássico Simon implementado em C++ usando SFML (Graphics + Audio). O jogador precisa repetir sequências de cores geradas aleatoriamente; cada cor tem som próprio.

## Sobre

SimonCPP é uma implementação didática do jogo Simon. O objetivo do jogo é memorizar e reproduzir sequências de cores/sons que vão aumentando a cada rodada. O projeto traz:

- Interface simples com 4 botões coloridos.
- Sons por cor e efeito de game over.
- Lógica de estado (mostrar sequência / esperar input).

## Tecnologias Utilizadas

- <b>C++:</b> Linguagem de programação principal
- <b>SFML 2.6.1:</b> Biblioteca multimídia utilizada para gráficos, áudio e controle de eventos

## Executando a Aplicação

Clone o repositório:

```bash
git clone https://github.com/MarcosWolf/simon-cpp.git
cd simon-cpp
```

### Windows

1. Acesse a pasta:
```bash
simon-cpp/dist/
```

2. Execute: 
```bash
simon-cpp.exe
```

> Certifique-se de ter as DLLs da SFML ao lado do executável:
 ```bash
sfml-system-2.dll, sfml-window-2.dll, sfml-graphics-2.dll, sfml-audio-2.dll e openal32.dll
```

### Linux

1. Instale a SFML:
```bash
sudo apt install libsfml-dev
```

2. Compile: 
```bash
g++ src/*.cpp -I include -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -o simon
```

3. Execute:
```bash
./simon
```

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
