// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.
struct Territorio{
    char nome[30];
    char cor[10];
    int tropas;
}
// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:
// Funções de setup e gerenciamento de memória:
Territorio* alocarMapa(int quantidade);
void inicializarTerritorios(Territorio *mapa, int quantidade);
void liberarMemoria(Territorio *mapa, char *missao);

void exibirMenuPrincipal();
void exibirMapa(const Territorio *mapa, int quantidade);
void exibirMissao(const char *missao);

void atribuirMissao(char *destino,
                    char *missoes[],
                    int totalMissoes);

void faseDeAtaque(Territorio *mapa,int quantidade);

void simularAtaque(Territorio *atacante,Territorio *defensor);

int verificarVitoria(const char *missao,const Territorio *mapa, int quantidade);

void limparBufferEntrada();
// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.
    srand(time(NULL));

    int quantidade;

    printf("Quantidade de territorios: ");
    scanf("%d", &quantidade);

    Territorio *mapa = alocarMapa(quantidade);

    if(mapa == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    inicializarTerritorios(mapa, quantidade);

    char *missoes[TOTAL_MISSOES] = {
        "Conquistar 3 territorios",
        "Conquistar 4 territorios",
        "Eliminar todos os territorios Vermelho",
        "Eliminar todos os territorios Azul",
        "Controlar metade do mapa"
    };

    char *missaoJogador = (char*) malloc(100);

    atribuirMissao(missaoJogador,missoes,TOTAL_MISSOES
    );

    exibirMissao(missaoJogador);
    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.
 int opcao;
    int venceu = 0;

    do {

        exibirMapa(mapa, quantidade);

        exibirMenuPrincipal();

        printf("Opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {

            case 1:

                faseDeAtaque(mapa,quantidade);

                if(verificarVitoria(issaoJogador,mapa,quantidade)) {

                    printf("\nMISSAO CUMPRIDA!\n");

                    printf("VOCE VENCEU O JOGO!\n");

                    venceu = 1;
                }

                break;

            case 0:

                printf("\nEncerrando jogo...\n");

                break;

            default:

                printf("\nOpcao invalida.\n");
        }

    } while(opcao != 0 && !venceu);
    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.
  liberarMemoria(mapa,missaoJogador);

    return 0;
}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.
Territorio* alocarMapa(int quantidade) {

    return (Territorio*)
    calloc(
        quantidade,
        sizeof(Territorio)
    );
}
// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).
void inicializarTerritorios(
    Territorio *mapa,
    int quantidade) {

    int i;

    for(i = 0; i < quantidade; i++) {

        printf(
        "\nTerritorio %d\n", i);

        printf("Nome: ");
        scanf("%s", mapa[i].nome);

        printf("Cor: ");
        scanf("%s", mapa[i].cor);

        printf("Tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.
void liberarMemoria(
    Territorio *mapa,
    char *missao) {

    free(mapa);
    free(missao);
}
// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.
void exibirMenuPrincipal() {

    printf("\n===== MENU =====\n");
    printf("1 - Atacar\n");
    printf("0 - Sair\n");
}

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.
void exibirMapa(
    const Territorio *mapa,
    int quantidade) {

    int i;

    printf("\n===== MAPA =====\n");

    for(i = 0; i < quantidade; i++) {

        printf(
        "\n[%d] %s | %s | %d tropas",
        i,
        mapa[i].nome,
        mapa[i].cor,
        mapa[i].tropas);
    }

    printf("\n");
}
// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.
void exibirMissao(
    const char *missao) {

    printf(
    "\n===== SUA MISSAO =====\n");

    printf("%s\n", missao);
}
// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.
void faseDeAtaque(
    Territorio *mapa,
    int quantidade) {

    int origem;
    int destino;

    printf(
    "\nIndice atacante: ");
    scanf("%d", &origem);

    printf(
    "Indice defensor: ");
    scanf("%d", &destino);

    if(origem < 0 ||
       origem >= quantidade ||
       destino < 0 ||
       destino >= quantidade) {

        printf(
        "\nIndice invalido.\n");

        return;
    }

    if(strcmp(
        mapa[origem].cor,
        mapa[destino].cor) == 0) {

        printf(
        "\nNao pode atacar aliados.\n");

        return;
    }

    simularAtaque(
        &mapa[origem],
        &mapa[destino]
    );
}

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.
void simularAtaque(
    Territorio *atacante,
    Territorio *defensor) {

    int dadoAtaque =
        rand()%6 + 1;

    int dadoDefesa =
        rand()%6 + 1;

    printf(
    "\nAtaque: %d",
    dadoAtaque);

    printf(
    "\nDefesa: %d\n",
    dadoDefesa);

    if(dadoAtaque >
       dadoDefesa) {

        strcpy(
        defensor->cor,
        atacante->cor);

        defensor->tropas =
        atacante->tropas/2;

        atacante->tropas -=
        defensor->tropas;

        printf(
        "\nTerritorio conquistado!\n");
    }
    else {

        atacante->tropas--;

        printf(
        "\nAtaque falhou!\n");
    }
}

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.
void atribuirMissao(
    char *destino,
    char *missoes[],
    int totalMissoes) {

    int sorteio =
        rand() % totalMissoes;

    strcpy(
        destino,
        missoes[sorteio]
    );
}
// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.
int verificarVitoria(
    const char *missao,
    const Territorio *mapa,
    int quantidade) {

    int i;
    int azul = 0;

    for(i = 0; i < quantidade; i++) {

        if(strcmp(
            mapa[i].cor,
            "Azul") == 0)

            azul++;
    }

    if(strcmp(
        missao,
        "Conquistar 3 territorios") == 0)

        return azul >= 3;

    if(strcmp(
        missao,
        "Conquistar 4 territorios") == 0)

        return azul >= 4;

    return 0;
}
// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
