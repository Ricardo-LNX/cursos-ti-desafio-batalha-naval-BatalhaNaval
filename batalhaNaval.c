// Desafio Batalha Naval - MateCheck
// Este código inicial serve como base para o desenvolvimento do sistema de Batalha Naval.
// Siga os comentários para implementar cada parte do desafio.
#include <stdio.h>

#define TAM 10        // Tamanho do tabuleiro
#define NAVIO 3       // Tamanho de cada navio
#define AGUA 0        // Valor que representa a água 
#define NAVIO_VALOR 3  //Tamanhofixo dos navios

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
    int i, j;

    // 1. Inicializar o tabuleiro com água (0)
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // 2. Definir coordenadas iniciais dos navios
    // Coordenadas: (linha, coluna)
    int linha_horizontal = 2;
    int coluna_horizontal = 4;
    int linha_vertical = 6;
    int coluna_vertical = 1;    

    // 3. Verificar se o navio horizontal cabe no tabuleiro
    if (coluna_horizontal + NAVIO <= TAM) {
        for (j = coluna_horizontal; j < coluna_horizontal + NAVIO; j++) {
            tabuleiro[linha_horizontal][j] = NAVIO_VALOR;
        }
    } else {
        printf("Erro: o navio horizontal excede os limites do tabuleiro.\n");
        return 1;
    }

    // 4. Verificar se o navio vertical cabe e não se sobrepõe
    if (linha_vertical + NAVIO <= TAM) {
        int sobreposicao = 0;
        for (i = linha_vertical; i < linha_vertical + NAVIO; i++) {
            if (tabuleiro[i][coluna_vertical] == NAVIO_VALOR) {
                sobreposicao = 1;
                break;
            }
        }
        if (sobreposicao) {
            printf("Erro: os navios se sobrepõem!\n");
            return 1;
        } else {
            for (i = linha_vertical; i < linha_vertical + NAVIO; i++) {
                tabuleiro[i][coluna_vertical] = NAVIO_VALOR;
            }
        }
    } else {
        printf("Erro: o navio vertical excede os limites do tabuleiro.\n");
        return 1;
    }

    // 5. Exibir o tabuleiro
    printf("\n=== TABULEIRO DE BATALHA NAVAL ===\n\n");
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}    
    // Nível Novato - Posicionamento dos Navios
    // Sugestão: Declare uma matriz bidimensional para representar o tabuleiro (Ex: int tabuleiro[5][5];).
    // Sugestão: Posicione dois navios no tabuleiro, um verticalmente e outro horizontalmente.
    // Sugestão: Utilize `printf` para exibir as coordenadas de cada parte dos navios.

    // Nível Aventureiro - Expansão do Tabuleiro e Posicionamento Diagonal
    // Sugestão: Expanda o tabuleiro para uma matriz 10x10.
    // Sugestão: Posicione quatro navios no tabuleiro, incluindo dois na diagonal.
    // Sugestão: Exiba o tabuleiro completo no console, mostrando 0 para posições vazias e 3 para posições ocupadas.

    // Nível Mestre - Habilidades Especiais com Matrizes
    // Sugestão: Crie matrizes para representar habilidades especiais como cone, cruz, e octaedro.
    // Sugestão: Utilize estruturas de repetição aninhadas para preencher as áreas afetadas por essas habilidades no tabuleiro.
    // Sugestão: Exiba o tabuleiro com as áreas afetadas, utilizando 0 para áreas não afetadas e 1 para áreas atingidas.

    // Exemplos de exibição das habilidades:
    // Exemplo para habilidade em cone:
    // 0 0 1 0 0
    // 0 1 1 1 0
    // 1 1 1 1 1
    
    // Exemplo para habilidade em octaedro:
    // 0 0 1 0 0
    // 0 1 1 1 0
    // 0 0 1 0 0

    // Exemplo para habilidade em cruz:
    // 0 0 1 0 0
    // 1 1 1 1 1
    // 0 0 1 0 0


