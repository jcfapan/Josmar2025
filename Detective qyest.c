#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura Sala
typedef struct Sala {
    char nome[100];           // Nome do cômodo
    struct Sala *esquerda;    // Ponteiro para o cômodo à esquerda
    struct Sala *direita;     // Ponteiro para o cômodo à direita
} Sala;

/**
 * Função criarSala: cria dinamicamente uma sala com nome fornecido.
 * @param nome Nome da sala a ser criada.
 * @return Ponteiro para a nova sala.
 */
Sala* criarSala(const char* nome) {
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    if (novaSala == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    strcpy(novaSala->nome, nome);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    return novaSala;
}

/**
 * Função explorarSalas: permite ao jogador navegar pela árvore interativamente.
 * @param salaAtual Ponteiro para a sala atual na exploração.
 */
void explorarSalas(Sala* salaAtual) {
    if (salaAtual == NULL) {
        return;
    }

    // Exibe o nome da sala atual
    printf("\nVocê está na: %s\n", salaAtual->nome);

    // Verifica se é um nó folha (sem caminhos)
    if (salaAtual->esquerda == NULL && salaAtual->direita == NULL) {
        printf("Parabéns! Você encontrou o culpado aqui!\n");
        return;
    }

    // Pede ao jogador para escolher a direção
    char escolha;
    printf("Escolha seu caminho:\n");
    printf("  'e' para ir à esquerda\n");
    printf("  'd' para ir à direita\n");
    printf("  's' para sair do jogo\n");
    printf("Sua escolha: ");
    scanf(" %c", &escolha); // O espaço antes de %c ignora espaços e quebras de linha

    switch (escolha) {
        case 'e':
            if (salaAtual->esquerda != NULL) {
                explorarSalas(salaAtual->esquerda);
            } else {
                printf("Não há caminho à esquerda. Tente outro caminho.\n");
                explorarSalas(salaAtual); // Volta para escolher novamente
            }
            break;
        case 'd':
            if (salaAtual->direita != NULL) {
                explorarSalas(salaAtual->direita);
            } else {
                printf("Não há caminho à direita. Tente outro caminho.\n");
                explorarSalas(salaAtual); // Volta para escolher novamente
            }
            break;
        case 's':
            printf("Você decidiu sair do jogo. Até a próxima!\n");
            exit(0);
            break;
        default:
            printf("Opção inválida! Por favor, escolha 'e', 'd' ou 's'.\n");
            explorarSalas(salaAtual); // Permite tentar novamente
            break;
    }
}

/**
 * Função main: monta o mapa inicial da mansão e inicia a exploração.
 */
int main() {
    printf("Bem-vindo ao Detective Quest!\n");
    printf("Explore a mansão para encontrar o culpado.\n");
    printf("Você começa no Hall de entrada.\n\n");

    // Monta a árvore binária manualmente (como solicitado)
    Sala* hallEntrada = criarSala("Hall de entrada");
    Sala* salaEstar = criarSala("Sala de estar");
    Sala* cozinha = criarSala("Cozinha");
    Sala* jardim = criarSala("Jardim");
    Sala* biblioteca = criarSala("Biblioteca");
    Sala* quartoPrincipal = criarSala("Quarto Principal");
    Sala* porao = criarSala("Porão");

    // Define as conexões (estrutura da árvore)
    hallEntrada->esquerda = salaEstar;
    hallEntrada->direita = cozinha;

    salaEstar->esquerda = biblioteca;
    salaEstar->direita = quartoPrincipal;

    cozinha->esquerda = jardim;
    cozinha->direita = porao;

    // Biblioteca, Quarto Principal, Jardim e Porão são folhas (sem filhos)
    // (já foram inicializados com NULL nos campos esquerda/direita)

    // Inicia a exploração a partir do Hall de entrada
    explorarSalas(hallEntrada);

    // Libera memória (opcional, mas boa prática)
    // Em um projeto real, você deveria implementar uma função para liberar toda a árvore.
    // Para este exercício, como é simples e termina com o jogo, pode ser omitido.

    return 0;
}