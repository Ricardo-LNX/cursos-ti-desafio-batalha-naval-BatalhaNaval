// Desafio Batalha Naval - MateCheck
// Este código inicial serve como base para o desenvolvimento do sistema de Batalha Naval.
// Siga os comentários para implementar cada parte do desafio.

#include <stdio.h>

#define TAM 10            // tamanho do tabuleiro (10x10)
#define AGUA 0
#define NAVIO 3
#define AREA_HABILIDADE 5
#define H 5               // dimensão das matrizes de habilidade (5x5)
#define CENTRO (H/2)      // índice do centro (2 para H=5)
#define TAM_NAVIO 3       // tamanho fixo dos navios

// Função para inicializar o tabuleiro com água (zeros)
void inicializarTabuleiro(int tab[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tab[i][j] = AGUA;
}

// Função que verifica se uma posição está dentro do tabuleiro
int dentroLimites(int linha, int coluna) {
    return (linha >= 0 && linha < TAM && coluna >= 0 && coluna < TAM);
}

// Posiciona navio reto (orientacao 0 = horizontal, 1 = vertical) ou diagonal (diagonal = 1 principal, 2 inversa)
// Supõe que já foi verificado que cabe e não sobrepõe (simplificação).
void posicionarNavio(int tab[TAM][TAM], int linha, int coluna, int orientacao, int diagonal) {
    for (int k = 0; k < TAM_NAVIO; k++) {
        int r = linha;
        int c = coluna;
        if (diagonal == 0) {
            if (orientacao == 0) c = coluna + k;   // horizontal → move coluna
            else r = linha + k;                   // vertical → move linha
        } else if (diagonal == 1) { // diagonal principal ↘
            r = linha + k;
            c = coluna + k;
        } else { // diagonal inversa ↙
            r = linha + k;
            c = coluna - k;
        }

        if (dentroLimites(r,c)) tab[r][c] = NAVIO;
    }
}

// Verifica se um navio vai sobrepor alguma célula já ocupada (NAVIO)
int sobrepoeNavio(int tab[TAM][TAM], int linha, int coluna, int orientacao, int diagonal) {
    for (int k = 0; k < TAM_NAVIO; k++) {
        int r = linha;
        int c = coluna;
        if (diagonal == 0) {
            if (orientacao == 0) c = coluna + k;
            else r = linha + k;
        } else if (diagonal == 1) {
            r = linha + k;
            c = coluna + k;
        } else {
            r = linha + k;
            c = coluna - k;
        }
        if (!dentroLimites(r,c)) return 1;      // considera inválido (fora) como sobreposição/erro
        if (tab[r][c] == NAVIO) return 1;      // sobrepõe
    }
    return 0; // não sobrepõe
}

// Exibe o tabuleiro com índices de linha/coluna
void exibirTabuleiro(int tab[TAM][TAM]) {
    printf("\n=== TABULEIRO (0=água, 3=navio, 5=área habilidade) ===\n\n");
    printf("    ");
    for (int c = 0; c < TAM; c++) printf("%2d ", c);
    printf("\n");
    printf("   +");
    for (int c = 0; c < TAM; c++) printf("---");
    printf("\n");

    for (int r = 0; r < TAM; r++) {
        printf("%2d |", r);
        for (int c = 0; c < TAM; c++) {
            // imprimimos os números (0,3,5) com espaçamento
            printf(" %d ", tab[r][c]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    int tab[TAM][TAM];
    inicializarTabuleiro(tab);

    // ---------- POSICIONAMENTO DE NAVIOS (4 navios) ----------
    // Cada navio: {linha, coluna, orientacao, diagonal}
    // orientacao: 0=horizontal,1=vertical
    // diagonal: 0=reto (usar orientacao), 1=diagonal principal(↘), 2=diagonal inversa(↙)
    int navios[4][4] = {
        {2, 1, 0, 0},  // navio 1: linha2,col1 horizontal
        {5, 6, 1, 0},  // navio 2: linha5,col6 vertical
        {0, 0, 0, 1},  // navio 3: diagonal principal a partir de (0,0)
        {3, 9, 0, 2}   // navio 4: diagonal inversa a partir de (3,9)
    };

    // validar e posicionar navios
    for (int i = 0; i < 4; i++) {
        int linha = navios[i][0];
        int coluna = navios[i][1];
        int orient = navios[i][2];
        int diag = navios[i][3];

        if (sobrepoeNavio(tab, linha, coluna, orient, diag)) {
            printf("Aviso: navio %d inválido (fora ou sobrepoe). Pulando posicionamento.\n", i+1);
        } else {
            posicionarNavio(tab, linha, coluna, orient, diag);
        }
    }

        // ---------- CRIAÇÃO DINÂMICA DAS MATRIZES DE HABILIDADE (5x5) ----------
    int cone[H][H];    // cone apontando para baixo (topo no topo do 5x5)
    int cruz[H][H];    // cruz com centro no centro do 5x5
    int octaedro[H][H];// "losango" (diamante) com centro no centro do 5x5

    // Construção do CONE (topo no topo, se expande para baixo)
    // Regra usada: para linhas r = 0..H-1
    // definimos um "comprimento útil" do cone; usaremos as 3 primeiras linhas (r=0..2)
    for (int r = 0; r < H; r++) {
        for (int c = 0; c < H; c++) {
            // inicializa com 0
            cone[r][c] = 0;

            // Para as 3 primeiras linhas, aplicamos a condição abs(c-centro) <= r
            // r=0 => só o centro, r=1 => 3 células centrais, r=2 => 5 células (linha cheia)
            if (r <= 2) {
                int diff = (c - CENTRO);
                if (diff < 0) diff = -diff;
                if (diff <= r) cone[r][c] = 1;
            }
        }
    }

    // Construção da CRUZ
    for (int r = 0; r < H; r++) {
        for (int c = 0; c < H; c++) {
            cruz[r][c] = 0;
            // cruz = toda a linha central e toda a coluna central
            if (r == CENTRO || c == CENTRO) cruz[r][c] = 1;
        }
    }

    // Construção do "OCTAEDRO" (vista frontal -> losango/diamante)
    // Usaremos a condição de distância de Manhattan <= 1 (raio = 1) para obter o padrão pedido
    for (int r = 0; r < H; r++) {
        for (int c = 0; c < H; c++) {
            octaedro[r][c] = 0;
            int manhattan = ( (r > CENTRO ? r - CENTRO : CENTRO - r) +
                              (c > CENTRO ? c - CENTRO : CENTRO - c) );
            if (manhattan <= 1) octaedro[r][c] = 1;
        }
    }

    // ---------- PONTOS DE ORIGEM (centro) PARA CADA HABILIDADE NO TABULEIRO ----------
    // Valores definidos diretamente no código (linha, coluna)
    int origemConeLinha = 1, origemConeColuna = 4;     // o topo do cone ficará centrado aqui
    int origemCruzLinha = 6, origemCruzColuna = 2;
    int origemOctLinha = 7, origemOctColuna = 7;

    // ---------- SOBRESCREVER O TABULEIRO COM ÁREA DE HABILIDADE (marcar com 5) ----------
    // Repare: não sobrescrevemos navios (3). Se uma célula já contiene NAVIO, mantemos NAVIO.
    // Utilizamos loops aninhados para sobrepor centralizando HxH em cada origem.
    int dr, dc;
    // Função inline: aplicar uma matriz HxH sobre tabuleiro, centrando em (origLinha, origCol)
    // se valor da matriz == 1 e célula do tabuleiro == AGUA -> marca como AREA_HABILIDADE
    // Validamos limites antes de escrever
    // Aplicar CONE
    for (int r = 0; r < H; r++) {
        for (int c = 0; c < H; c++) {
            if (cone[r][c] == 1) {
                // deslocamento do centro da matriz para a célula do tabuleiro
                dr = origemConeLinha + (r - CENTRO);
                dc = origemConeColuna + (c - CENTRO);
                if (dentroLimites(dr, dc)) {
                    if (tab[dr][dc] == AGUA) tab[dr][dc] = AREA_HABILIDADE;
                    // se houver NAVIO, mantemos NAVIO (3) para visualização
                }
            }
        }
    }

    // Aplicar CRUZ
    for (int r = 0; r < H; r++) {
        for (int c = 0; c < H; c++) {
            if (cruz[r][c] == 1) {
                dr = origemCruzLinha + (r - CENTRO);
                dc = origemCruzColuna + (c - CENTRO);
                if (dentroLimites(dr, dc)) {
                    if (tab[dr][dc] == AGUA) tab[dr][dc] = AREA_HABILIDADE;
                }
            }
        }
    }

    // Aplicar OCTAEDRO
    for (int r = 0; r < H; r++) {
        for (int c = 0; c < H; c++) {
            if (octaedro[r][c] == 1) {
                dr = origemOctLinha + (r - CENTRO);
                dc = origemOctColuna + (c - CENTRO);
                if (dentroLimites(dr, dc)) {
                    if (tab[dr][dc] == AGUA) tab[dr][dc] = AREA_HABILIDADE;
                }
            }
        }
    }
    
    // ---------- EXIBIÇÃO: imprimimos tabuleiro com legenda ----------
    exibirTabuleiro(tab);
    printf("Legenda: 0 = água, 3 = navio, 5 = área de habilidade\n\n");

    // Opcional: mostrar as matrizes de habilidade impressas (para ver como foram geradas)
    printf("Matriz - CONE (1=afetado,0=não):\n");
    for (int r = 0; r < H; r++) {
        for (int c = 0; c < H; c++) printf("%d ", cone[r][c]);
        printf("\n");
    }
    printf("\nMatriz - CRUZ (1=afetado,0=não):\n");
    for (int r = 0; r < H; r++) {
        for (int c = 0; c < H; c++) printf("%d ", cruz[r][c]);
        printf("\n");
    }
    printf("\nMatriz - OCTAEDRO (1=afetado,0=não):\n");
    for (int r = 0; r < H; r++) {
        for (int c = 0; c < H; c++) printf("%d ", octaedro[r][c]);
        printf("\n");
    }

    return 0;
}