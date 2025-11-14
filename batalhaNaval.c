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





























#include <stdio.h>

#define TAM 10        // Tamanho do tabuleiro
#define NAVIO 3       // Tamanho de cada navio
#define AGUA 0        // Valor que representa a água 
#define NAVIO_VALOR 3  //Tamanhofixo dos navios
#define TAMANHO_NAVIO 3  // Tamanho fixo dos navios

// Função para inicializar o tabuleiro com zeros (água)
void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para verificar se o navio cabe no tabuleiro (sem sair dos limites)
int posicaoValida(int linha, int coluna, int orientacao, int diagonal) {
    // orientacao: 0 = horizontal, 1 = vertical
    // diagonal: 0 = não, 1 = diagonal principal, 2 = diagonal inversa
    if (diagonal == 0) {
        if (orientacao == 0 && coluna + TAMANHO_NAVIO <= TAM) return 1; // horizontal
        if (orientacao == 1 && linha + TAMANHO_NAVIO <= TAM) return 1;  // vertical
    } else if (diagonal == 1) { // diagonal principal (↘)
        if (linha + TAMANHO_NAVIO <= TAM && coluna + TAMANHO_NAVIO <= TAM) return 1;
    } else if (diagonal == 2) { // diagonal inversa (↙)
        if (linha + TAMANHO_NAVIO <= TAM && coluna - (TAMANHO_NAVIO - 1) >= 0) return 1;
    }
    return 0;
}


// Função para verificar sobreposição de navios
int sobrepoeNavio(int tabuleiro[TAM][TAM], int linha, int coluna, int orientacao, int diagonal) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int r = linha, c = coluna;

        if (diagonal == 0) { // Navio reto
            if (orientacao == 0) c += i;  // horizontal
            else r += i;                 // vertical
        } else if (diagonal == 1) {      // diagonal principal (↘)
            r += i;
            c += i;
        } else if (diagonal == 2) {      // diagonal inversa (↙)
            r += i;
            c -= i;
        }

        if (tabuleiro[r][c] == NAVIO) return 1; // sobreposição
    }
    return 0;
}

// Função para posicionar um navio no tabuleiro
void posicionarNavio(int tabuleiro[TAM][TAM], int linha, int coluna, int orientacao, int diagonal) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (diagonal == 0) { // navio reto
            if (orientacao == 0) tabuleiro[linha][coluna + i] = NAVIO;  // horizontal
            else tabuleiro[linha + i][coluna] = NAVIO;                  // vertical
        } else if (diagonal == 1) { // diagonal principal ↘
            tabuleiro[linha + i][coluna + i] = NAVIO;
        } else if (diagonal == 2) { // diagonal inversa ↙
            tabuleiro[linha + i][coluna - i] = NAVIO;
        }
    }
}


// Função para exibir o tabuleiro no console
void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\n=== TABULEIRO BATALHA NAVAL ===\n\n");
    printf("   ");
    for (int c = 0; c < TAM; c++) printf("%2d ", c);
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAM; j++) {
            printf("%2d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    int tabuleiro[TAM][TAM];

    // 1. Inicializar o tabuleiro
    inicializarTabuleiro(tabuleiro);

    // 2. Posicionar 4 navios de tamanho 3
    // Navios horizontais/verticais
    int navios[4][4] = {
        {2, 1, 0, 0},  // linha 2, coluna 1, horizontal
        {5, 6, 1, 0},  // linha 5, coluna 6, vertical
        {0, 0, 0, 1},  // diagonal principal
        {3, 9, 0, 2}   // diagonal inversa
    };

    // 3. Posicionar navios no tabuleiro
    for (int n = 0; n < 4; n++) {
        int linha = navios[n][0];
        int coluna = navios[n][1];
        int orientacao = navios[n][2];
        int diagonal = navios[n][3];

        if (!posicaoValida(linha, coluna, orientacao, diagonal)) {
            printf("Erro: navio %d fora dos limites do tabuleiro.\n", n + 1);
            continue;
        }

        if (sobrepoeNavio(tabuleiro, linha, coluna, orientacao, diagonal)) {
            printf("Erro: navio %d sobrepõe outro.\n", n + 1);
            continue;
        }

        posicionarNavio(tabuleiro, linha, coluna, orientacao, diagonal);
    }


    // 4. Exibir tabuleiro completo
    exibirTabuleiro(tabuleiro);

    return 0;
}
