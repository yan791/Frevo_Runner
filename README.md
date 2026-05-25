# 🎭 Frevo Runner

Jogo endless runner em C inspirado no **Carnaval de Olinda**, desenvolvido como projeto acadêmico da disciplina de Algoritmos e Estruturas de Dados — CESAR School.

O jogador controla um folião que corre automaticamente por 3 pistas e precisa desviar de obstáculos típicos do carnaval (trio elétrico, boneco gigante, ambulante, estandarte...) enquanto acumula pontuação.

---

## Dependências

- [Raylib](https://www.raylib.com/) — biblioteca gráfica
- GCC e Make

### Instalando o Raylib (Ubuntu/Debian)

```bash
sudo apt install libraylib-dev
```

### Instalando o Raylib (macOS)

```bash
brew install raylib
```

---

## Como compilar e executar

```bash
git clone https://github.com/yan791/Frevo_Runner.git
cd Frevo_Runner
make
./FrevoRunner
```

O `make` já gera os efeitos sonoros automaticamente antes de compilar o jogo.

---

## Controles

| Tecla | Ação |
|---|---|
| `A` / `←` | Mover para a pista de cima |
| `D` / `→` | Mover para a pista de baixo |
| `Espaço` | Pular |
| `R` | Reiniciar (na tela de game over) |
| `M` | Voltar ao menu (na tela de game over) |
| `ESC` | Sair |

---

## Estrutura do projeto

```
Frevo_Runner/
├── src/
│   ├── main.c          # Loop principal e gerenciamento de telas
│   ├── jogador.c       # Lógica de movimento e pulo
│   ├── obstaculos.c    # Lista encadeada de obstáculos
│   ├── ranking.c       # Persistência e ordenação do ranking
│   ├── recursos.c      # Carregamento de sprites e áudio
│   └── telas.c         # Renderização de todas as telas
├── include/            # Headers (.h)
├── assets/             # Sprites e áudio
├── data/               # Arquivo de ranking (ranking.txt)
├── tools_generate_sfx.c # Gerador de efeitos sonoros
└── Makefile
```

---

## Estruturas de dados e algoritmos

- **Lista encadeada simples** — os obstáculos são gerenciados dinamicamente via lista ligada (`struct Obstaculo` com ponteiro `*prox`). Novos obstáculos são inseridos no final e removidos do início conforme saem da tela.
- **Bubble Sort** — o ranking de pontuações é ordenado por Bubble Sort e salvo em `data/ranking.txt`.

---

## Equipe

| Aluno | GitHub |
|---|---|
| Yan Ribeiro | [@yan791](https://github.com/yan791) |
| Caio Leimig | [@caioleimig](https://github.com/caioleimig) |
| Guilherme Burle | [@Guilherme-burle](https://github.com/Guilherme-burle) |

---

## Limpeza

```bash
make clean
```
