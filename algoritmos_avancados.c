Com certeza! Com base nas regras e requisitos que você me forneceu, preparei um código em linguagem C que simula o mapa da mansão como uma Árvore Binária e permite a exploração interativa.

O código está modularizado e documentado, seguindo as melhores práticas de legibilidade.

Código em C para o Detective Quest
C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Para a função tolower

// Definição da estrutura para representar um cômodo (Sala) no mapa
typedef struct Sala {
    char nome[50];          // Nome da sala (ex: "Hall de entrada", "Cozinha")
    struct Sala *esquerda;  // Ponteiro para o cômodo à esquerda (filho esquerdo)
    struct Sala *direita;   // Ponteiro para o cômodo à direita (filho direito)
} Sala;

/**
 * @brief Cria dinamicamente uma nova sala (nó da árvore) com um nome especificado.
 * * @param nome O nome do cômodo a ser criado.
 * @return Um ponteiro para a nova sala criada.
 */
Sala* criarSala(const char* nome) {
    // Aloca dinamicamente memória para a nova sala
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    
    // Verifica se a alocação foi bem-sucedida
    if (novaSala == NULL) {
        perror("Erro ao alocar memória para a sala");
        exit(EXIT_FAILURE); // Sai do programa em caso de erro
    }
    
    // Copia o nome para o campo 'nome' da estrutura
    strncpy(novaSala->nome, nome, 49);
    novaSala->nome[49] = '\0'; // Garante que a string seja terminada
    
    // Inicializa os ponteiros para os filhos como NULL (sem caminhos)
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    
    return novaSala;
}

/**
 * @brief Permite a navegação interativa do jogador pelo mapa da mansão (árvore binária).
 * * A exploração continua até que o jogador chegue a um nó-folha (sala sem caminhos).
 * * @param hallDeEntrada O ponteiro para o nó raiz da árvore (o Hall de entrada).
 */
void explorarSalas(Sala* hallDeEntrada) {
    Sala* salaAtual = hallDeEntrada;
    char escolha;
    
    printf("\n--- INÍCIO DA EXPLORAÇÃO ---\n");
    
    // Loop de exploração contínua
    while (salaAtual != NULL) {
        printf("\nVocê está em: %s\n", salaAtual->nome);

        // Verifica se é um nó-folha (sala sem mais caminhos)
        if (salaAtual->esquerda == NULL && salaAtual->direita == NULL) {
            printf("\nEsta sala não tem mais caminhos. Fim da exploração!\n");
            break; // Sai do loop
        }

        // Exibe as opções de caminho
        printf("Para onde você deseja ir? ");
        if (salaAtual->esquerda != NULL) {
            printf("[E]squerda");
        }
        if (salaAtual->direita != NULL) {
            if (salaAtual->esquerda != NULL) {
                 printf(" ou ");
            }
            printf("[D]ireita");
        }
        printf(" ou [S]air: ");

        // Leitura da escolha do jogador
        if (scanf(" %c", &escolha) != 1) {
            // Trata erro de leitura e limpa o buffer
            printf("Erro na leitura. Saindo...\n");
            break;
        }

        // Converte para minúscula para facilitar a comparação
        escolha = tolower(escolha);

        // Processa a escolha
        if (escolha == 's') {
            printf("\nExploração encerrada pelo jogador. Até a próxima!\n");
            break; // Sai do loop
        } else if (escolha == 'e') {
            // Tentativa de ir para a esquerda
            if (salaAtual->esquerda != NULL) {
                salaAtual = salaAtual->esquerda; // Move para a próxima sala
            } else {
                printf("Caminho para a esquerda não existe aqui! Escolha novamente.\n");
            }
        } else if (escolha == 'd') {
            // Tentativa de ir para a direita
            if (salaAtual->direita != NULL) {
                salaAtual = salaAtual->direita; // Move para a próxima sala
            } else {
                printf("Caminho para a direita não existe aqui! Escolha novamente.\n");
            }
        } else {
            printf("Opção inválida. Digite 'e' para esquerda, 'd' para direita, ou 's' para sair.\n");
        }
    }
}

/**
 * @brief Libera a memória alocada dinamicamente para toda a árvore.
 * * É importante para evitar "memory leaks".
 * * @param raiz O nó raiz da subárvore a ser liberada.
 */
void liberarMapa(Sala* raiz) {
    if (raiz != NULL) {
        liberarMapa(raiz->esquerda);
        liberarMapa(raiz->direita);
        // printf("Liberando memória da sala: %s\n", raiz->nome); // Opcional para debug
        free(raiz);
    }
}


/**
 * @brief Função principal: monta o mapa da mansão e inicia a exploração.
 * * A estrutura do mapa é montada manualmente, conforme os requisitos.
 */
int main() {
    printf("Bem-vindo ao Detective Quest - Mapeamento da Mansão!\n");

    // 1. Montagem da Árvore Binária (O Mapa da Mansão)
    // O mapa é criado de forma automática usando a função criarSala().

    // Nível 0 (Raiz)
    Sala* hallDeEntrada = criarSala("Hall de entrada");

    // Nível 1
    hallDeEntrada->esquerda = criarSala("Sala de estar");
    hallDeEntrada->direita  = criarSala("Cozinha");

    // Nível 2
    Sala* salaDeEstar = hallDeEntrada->esquerda;
    salaDeEstar->esquerda = criarSala("Biblioteca");
    salaDeEstar->direita  = criarSala("Quarto Principal");

    Sala* cozinha = hallDeEntrada->direita;
    cozinha->esquerda = criarSala("Despensa");
    cozinha->direita  = criarSala("Jardim de Inverno");

    // Nível 3 (Nós-folha - Fim de caminhos)
    Sala* biblioteca = salaDeEstar->esquerda;
    biblioteca->direita = criarSala("Escritório Secreto"); // Caminho só para a direita

    // O Escritório Secreto é um nó-folha (sem filhos)

    // A Despensa é um nó-folha
    // O Quarto Principal é um nó-folha
    // O Jardim de Inverno é um nó-folha

    printf("Mapa da Mansão (Árvore Binária) criado com sucesso.\n");

    // 2. Início da exploração interativa
    explorarSalas(hallDeEntrada);

    // 3. Liberação da memória
    liberarMapa(hallDeEntrada);
    printf("\nMemória do mapa liberada. Programa encerrado.\n");
    
    return 0;
}