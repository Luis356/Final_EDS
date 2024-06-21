/*
AUTOR:  LUIS RICARDO DE SOUZA - ESW 2.º SEMESTRE - 193407
DATA:   18/06/2024
OBJETIVO:   SISTEMA DE GERENCIAMENTO DE PRODUTOS E MOVIMENTAÇÕES
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>

/*
    CRIANDO AS ESTRUTURAS E LISTAS A SEREM UTILIZADAS NO SISTEMA
*/

//  ESTRUTURA DOS PRODUTOS
typedef struct
{
    int cd_produto;
    char ds_produto[50];
    char ds_unid_med[3];
    char dt_validade[11];
    float qt_produto;
    float vl_custo_medio;
    float vl_total;
} Produto;

//  DEFININDO O APONTADOR DE TIPO PRODUTO
typedef struct TipoProduto *TipoApontadorProduto;

//  DEFININDO O TIPO DE PRODUTO
typedef struct TipoProduto
{
    Produto conteudo;
    TipoApontadorProduto proximo;
} TipoProduto;

//  DEFININDO A LISTA DE PRODUTOS
typedef struct
{
    TipoApontadorProduto PrimeiroProduto;
    TipoApontadorProduto UltimoProduto;
} ListaProduto;

//  ESTRUTURA DAS MOVIMENTAÇÕES
typedef struct
{
    char dt_movim[11];
    int cd_prod_movim;
    char tp_movim;
    float qt_movim;
    float vl_unit_movim;
    float vl_total_movim;
} MovProduto;

//  DEFININDO O APONTADOR DO TIPO MOVIMENTAÇÃO
typedef struct TipoMovimentacao *TipoApontadorMovimentacao;

//  DEFININDO O TIPO DE MOVIMENTAÇÃO
typedef struct TipoMovimentacao
{
    TipoApontadorMovimentacao movAnterior;
    MovProduto ctMovimentacao;
    TipoApontadorProduto movProximo;
} TipoMovimentacao;

//  DEFININDO A LISTA DE MOVIMENTAÇÃO
typedef struct
{
    TipoApontadorMovimentacao Pri_movim;
    TipoApontadorMovimentacao Ult_movim;
} ListaMovimentacao;

/*
    DECLARAÇÃO DE FUNÇÕES
*/

void RetornaMenu();
void MenuMovimentacoes();
void MenuListaProdutos();
int LerEntradaInteiro();

/*
    TELAS UTILIZADAS NO SISTEMA
*/

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = (short)x;
    coord.Y = (short)y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void TelaBase(char *mensagemSubmenu)
{
    int linha;
    system("color 0f");
    system("cls");

    for (linha = 1; linha <= 24; linha++)
    {
        gotoxy(1, linha);
        printf("|");
        gotoxy(80, linha);
        printf("|");
    }

    gotoxy(1, 1);
    printf("+------------------------------------------------------------------------------+\n");

    gotoxy(3, 2);
    printf("UNICV");
    gotoxy(20, 2);
    printf("SISTEMA DE CONTROLE DE ESTOQUE");
    gotoxy(62, 2);
    printf("ESTRUTURA DE DADOS");
    gotoxy(68, 3);
    printf("LUIS RICARDO");

    gotoxy(1, 4);
    printf("+------------------------------------------------------------------------------+\n");

    for (linha = 5; linha <= 24; linha++)
    {
        gotoxy(1, linha);
        printf("|");
        gotoxy(80, linha);
        printf("|");
    }
    gotoxy(20, 3);
    printf("%s", mensagemSubmenu);

    gotoxy(1, 24);
    printf("+------------------------------------------------------------------------------+\n");
}

void TelaMenu()
{
    TelaBase("Menu Principal");
    // Menu de opções
    gotoxy(20, 10);
    printf("1 - MENU PRODUTOS\n");
    gotoxy(20, 12);
    printf("2 - MENU MOVIMENTACOES\n");
    gotoxy(20, 14);
    printf("3 - FINALIZAR PROGRAMA\n");
    gotoxy(1, 22);
    printf("+------------------------------------------------------------------------------+\n");
}

void TelaMenuProduto()
{
    system("cls");
    TelaBase("Menu de produtos");

    // Menu de opções
    gotoxy(10, 7);
    printf("OPCOES:\n");

    gotoxy(10, 8);
    printf("1 - CADASTRAR PRODUTO NO FINAL\n");

    gotoxy(10, 9);
    printf("2 - CADASTRAR PRODUTO NO INICIO\n");

    gotoxy(10, 10);
    printf("3 - CADASTRAR EM UMA POSICAO\n");

    gotoxy(10, 11);
    printf("4 - REMOVER PRODUTO NO FINAL\n");

    gotoxy(10, 12);
    printf("5 - REMOVER PRODUTO NA POSICAO\n");

    gotoxy(10, 13);
    printf("6 - REMOVER PRODUTO NO INICIO\n");

    gotoxy(10, 14);
    printf("7 - CONSULTAR PRODUTOS\n");

    gotoxy(10, 15);
    printf("8 - ALTERAR DADOS PRODUTO\n");

    gotoxy(10, 16);
    printf("9 - RETORNAR AO MENU INICIAL\n");
}

void TelaMenuConsultaProduto()
{
    system("cls");
    TelaBase("Consulta de Produtos");

    gotoxy(10, 7);
    printf("CONSULTAR POR: ");

    gotoxy(10, 8);
    printf("1 - FICHARIO\n");

    gotoxy(10, 9);
    printf("2 - ORDEM DE CODIGO\n");

    gotoxy(10, 10);
    printf("3 - ORDEM ALFABETICA\n");

    gotoxy(10, 11);
    printf("4 - CODIGO\n");

    gotoxy(10, 12);
    printf("5 - RETORNAR AO MENU\n");
}

void TelaRegistroMovimentacao()
{
    system("cls");
    TelaBase("Registro de movimentações");

    gotoxy(10, 7);
    printf("TIPO DE MOVIMENTACAO (E - ENTRADA / S - SAIDA): ");

    gotoxy(10, 8);
    printf("QUANTIDADE DE PRODUTOS: \n");
}

void TelaMenuMovimentacao()
{
    TelaBase("Menu Movimentacao");
    // Menu de opções
    gotoxy(20, 10);
    printf("1 - CADASTRA MOVIMENTACAO DE ESTOQUE\n");
    gotoxy(20, 12);
    printf("2 - LISTA MOVIMENTACAO DE ESTOQUE\n");
    gotoxy(20, 14);
    printf("3 - RETORNAR AO MENU\n");
    gotoxy(1, 22);
    printf("+------------------------------------------------------------------------------+\n");
}

void TelaAlteraProduto()
{
    TelaBase("Alterar registro de produto");
    // Menu de opções
    gotoxy(20, 10);
    printf("1 - ALTERAR UM CAMPO\n");
    gotoxy(20, 12);
    printf("2 - ALTERAR TODOS OS CAMPOS\n");
    gotoxy(20, 14);
    printf("3 - RETORNAR AO MENU\n");
    gotoxy(1, 22);
    printf("+------------------------------------------------------------------------------+\n");
}

void TelaAlteraProdutoCampos()
{
    TelaBase("Alterar registro de produto");

    // Menu de opções
    gotoxy(10, 7);
    printf("CAMPOS DISPONIVEIS PARA ALTERACAO: ");
    gotoxy(20, 10);
    printf("1 - DESCRICAO\n");
    gotoxy(20, 12);
    printf("2 - UNIDADE DE MEDIDA\n");
    gotoxy(20, 14);
    printf("3 - DATA DE VALIDADE\n");
    gotoxy(1, 22);
    printf("+------------------------------------------------------------------------------+\n");
}

void LimparLinha(int linha)
{
    gotoxy(2, linha);
    printf("                                                                 "); // 80 espaços para limpar a linha
    gotoxy(1, 23);
    printf("|");
    gotoxy(80, 23);
    printf("|");
    gotoxy(2, linha); // Volta para o início da linha
}

void MostraMSG(char *MSG)
{
    gotoxy(1, 22);
    printf("+------------------------------------------------------------------------------+\n");
    LimparLinha(23);
    gotoxy(2, 23);
    printf("MSG.: %s", MSG);
}

void TelaListaVazia(char *Mensagem)
{
    system("cls");
    TelaBase(Mensagem);
    gotoxy(2, 21);
    printf("A lista esta vazia!\n");
    RetornaMenu();
}

/*
    FUNÇÕES UTILIZADAS NO SISTEMA
*/

// Função para verificar se a data está no formato correto (nn/nn/nnnn)
int VerificaFormatoData(const char *data)
{
    // Verifica o comprimento
    if (strlen(data) != 10)
    {
        return 0;
    }

    // Verifica os caracteres específicos
    if (data[2] != '/' || data[5] != '/')
    {
        return 0;
    }

    // Verifica se todos os outros caracteres são dígitos
    for (int i = 0; i < 10; i++)
    {
        if (i != 2 && i != 5 && !isdigit(data[i]))
        {
            return 0;
        }
    }

    return 1;
}

void VerificaData(char *data, char *mensagem)
{
    do
    {
        scanf("%10s", data);
        if (!VerificaFormatoData(data))
        {
            gotoxy(2, 21);
            printf("Formato de data invalido. Tente novamente.");
            MostraMSG(mensagem);
        }
    } while (!VerificaFormatoData(data));
    LimparLinha(21);
}

//  DECLARAÇÃO DA FUNÇÃO DE MENU DOS PRODUTOS
void MenuProdutos(ListaProduto *ListaProdutos, ListaMovimentacao *ListaMovimentacoes);
void MenuAlteraProdutos(ListaProduto *ListaSimplesProduto);

TipoApontadorProduto BuscaProdutoCodigo(ListaProduto *ListaBuscaProduto, int codigo) //  FUNÇÃO PARA BUSCAR UM PRODUTO POR CÓDIGO
{
    TipoApontadorProduto aux = ListaBuscaProduto->PrimeiroProduto;
    while (aux != NULL)
    {
        if (aux->conteudo.cd_produto == codigo)
        {
            return aux; // RETORNA O PONTEIRO DO PRODUTO ENCONTRADO
        }
        aux = aux->proximo;
    }
    return NULL; // PRODUTO NÃO ENCONTRADO NA LISTA
}

int VerificaCodigo(ListaProduto *VerificaCodigo, int codigo);

Produto LerDadosProdutos(ListaProduto *VerificaEntrada, char *tipoInclusao) //  FUNÇÃO PARA LER OS DADOS DOS PRODUTOS
{
    system("cls");
    TelaBase(tipoInclusao);
    Produto NovoProduto;

    gotoxy(14, 8);
    printf("Codigo do produto........: "); // CODIGO
    gotoxy(10, 10);
    printf("1 - Descricao do produto.....: "); //  DESCRIÇÃO
    gotoxy(10, 12);
    printf("2 - Unidade de medida........: "); // UNIDADE DE MEDIDA
    gotoxy(10, 14);
    printf("3 - Data de Validade.........: ");

    do
    {
        NovoProduto.cd_produto = LerEntradaInteiro("Codigo do produto: ");

        if (VerificaCodigo(VerificaEntrada, NovoProduto.cd_produto))
        {
            gotoxy(2, 21);
            printf("Codigo ja existente! Digite outro codigo.");
        }
        else
        {
            break; // Código válido, sai do loop
        }

    } while (1);
    LimparLinha(21);

    gotoxy(41, 8);
    printf("%d", NovoProduto.cd_produto); // PRINTA CODIGO DO PRODUTO

    MostraMSG(" Descricao do produto: ");
    scanf("%s", NovoProduto.ds_produto);
    LimparLinha(23);
    gotoxy(41, 10);
    printf("%s", NovoProduto.ds_produto); // PRINTA DESCRIÇÃO DO PRODUTO

    MostraMSG(" Unidade de medida do produto: ");
    scanf("%s", NovoProduto.ds_unid_med);
    LimparLinha(23);
    gotoxy(41, 12);
    printf("%s", NovoProduto.ds_unid_med); // PRINTA UNIDADE DE MEDIDA

    MostraMSG("Data de validade do produto: ");
    VerificaData(NovoProduto.dt_validade, "Data de validade do produto: "); // LÊ E VERIFICA A DATA
    LimparLinha(23);
    gotoxy(41, 14);
    printf("%s", NovoProduto.dt_validade); // PRINTA UNIDADE DE MEDIDA

    NovoProduto.qt_produto = 0;
    NovoProduto.vl_custo_medio = 0.0;
    NovoProduto.vl_total = 0.0;

    return NovoProduto;
}

int VerificaCodigo(ListaProduto *VerificaCodigo, int codigo)
{
    TipoApontadorProduto atual = VerificaCodigo->PrimeiroProduto;
    while (atual != NULL)
    {
        if (atual->conteudo.cd_produto == codigo)
        {
            return 1; // Código existe na lista
        }
        atual = atual->proximo;
    }
    return 0; // Código não existe na lista
}

void OrdenaCodigo(TipoApontadorProduto *Referencia) //  FUNÇÃO PARA ORDENAR A LISTA PELO VALOR DO CODIGO
{
    if (*Referencia == NULL || (*Referencia)->proximo == NULL)
    {
        return; // Lista vazia ou com um único elemento, já está ordenada
    }

    TipoApontadorProduto atual, anterior, prox;
    int trocado;

    do
    {
        trocado = 0;
        anterior = NULL;
        atual = *Referencia;
        prox = atual->proximo;

        while (prox != NULL)
        {
            if (atual->conteudo.cd_produto > prox->conteudo.cd_produto)
            {
                // Realiza a troca
                if (anterior != NULL)
                {
                    anterior->proximo = prox;
                }
                else
                {
                    *Referencia = prox;
                }

                atual->proximo = prox->proximo;
                prox->proximo = atual;

                // Atualiza os ponteiros para continuar a verificação
                anterior = prox;
                prox = atual->proximo;

                // Marca que houve troca
                trocado = 1;
            }
            else
            {
                // Move os ponteiros para o próximo elemento
                anterior = atual;
                atual = prox;
                prox = prox->proximo;
            }
        }
    } while (trocado);
}

int comparaDescricao(TipoApontadorProduto Pri_Produto, TipoApontadorProduto Sec_Produto) // FUNÇÃO PARA COMPARAR AS DESCRIÇÕES DOS PRODUTOS
{
    /*
    RETORNA NEGATIVO SE O PRIMEIRO VALOR É MENOR
    RETORNA ZERO SE FOREM IGUAIS
    RETORNA POSITIVO SE O SEGUNDO FOR MAIOR
    */
    return strcmp(Pri_Produto->conteudo.ds_produto, Sec_Produto->conteudo.ds_produto); //  RETORNA UM VALOR NEGATIVO SE A PRIMEIRA FU
}

void OrdenaDescricao(ListaProduto *ListaDescricao) // FUNÇÃO PARA ORDENAR A LISTA PELA DESCRIÇÃO DOS PRODUTOS
{

    if (ListaDescricao == NULL || ListaDescricao->PrimeiroProduto == NULL || ListaDescricao->PrimeiroProduto->proximo == NULL) // VERIFICA SE ESTÁ VAZIA OU COM APÉNAS UM PRODUTO
    {
        return;
    }

    TipoApontadorProduto atual, anterior, prox;
    int trocado;
    do
    {
        trocado = 0;
        anterior = NULL;
        atual = ListaDescricao->PrimeiroProduto;
        prox = atual->proximo;

        //  PERCORRE A LISTA ATÉ O FINAL
        while (prox != NULL)
        {
            //  COMPARA A DESCRIÇÃO DO PRODUTO ATUAL E PROXIMO
            if (comparaDescricao(atual, prox) > 0)
            {
                //  SE ERRADA, TROCA OS ELEMENTOS
                if (anterior != NULL)
                {
                    anterior->proximo = prox; // ATUALIZA O PROXIMO DO ANTERIOR PARA APONTAR PARA PROXIMO
                }
                else
                {
                    ListaDescricao->PrimeiroProduto = prox; //  ATUALIZA O INICIO DA LISTA PARA PROXIMO
                }

                //  TROCA OS APONTADORES
                atual->proximo = prox->proximo;
                prox->proximo = atual;

                //  ATUALIZA OS PONTEIROS
                anterior = prox;
                prox = atual->proximo;
                trocado = 1; // MARCA QUE HOUVE UMA TROCA
            }
            else
            { // SE NÃO HOUVE TROCA, AVANÇA OS PONTEIROS
                anterior = atual;
                atual = prox;
                prox = prox->proximo;
            }
        }
    } while (trocado); // REPETE ENQUANTO HOUVER TROCAS
}

void IniciarListaProduto(ListaProduto *ListaProduto) //  FUNÇÃO PARA INICIAR A LISTA DE PRODUTOS
{
    ListaProduto->PrimeiroProduto = NULL;
    ListaProduto->UltimoProduto = NULL;
}

void CadastraProduto(ListaProduto *ListaCadastro, int opcCadastro) // FUNÇÃO PARA CADASTRAR PRODUTOS
{
    Produto novoProduto = LerDadosProdutos(ListaCadastro, "Cadastro de produtos");

    TipoApontadorProduto novoNo = (TipoApontadorProduto)malloc(sizeof(TipoProduto));
    if (novoNo == NULL)
    {
        printf("Erro ao alocar memoria para o novo produto.\n");
        exit(1);
    }
    novoNo->conteudo = novoProduto;
    novoNo->proximo = NULL;

    switch (opcCadastro)
    {

    case 1:                                       //  REALIZA O CADASTRO NO FINAL DA LISTA
        if (ListaCadastro->UltimoProduto == NULL) // Lista vazia
        {
            ListaCadastro->PrimeiroProduto = novoNo;
            ListaCadastro->UltimoProduto = novoNo;
        }
        else
        {
            ListaCadastro->UltimoProduto->proximo = novoNo;
            ListaCadastro->UltimoProduto = novoNo;
        }
        break;

    case 2: //  REALIZA O CADASTRO NO INICIO DA LISTA
        novoNo->proximo = ListaCadastro->PrimeiroProduto;
        ListaCadastro->PrimeiroProduto = novoNo;
        if (ListaCadastro->UltimoProduto == NULL) // Primeira inserção
        {
            ListaCadastro->UltimoProduto = novoNo;
        }
        break;

    case 3: //  REALIZA O CADASTRO EM UMA POSIÇÃO ESPECIFICA DA LISTA
    {
        int contador = 0;
        int posicao = LerEntradaInteiro("Digite a posicao para inserir o produto: ");
        LimparLinha(23);
        TipoApontadorProduto aux = ListaCadastro->PrimeiroProduto;

        while (aux != NULL && contador < posicao - 1)
        {
            aux = aux->proximo;
            contador++;
        }
        if (aux == NULL)
        {
            printf("Posicao Invalida\n");
            free(novoNo);
            return;
        }

        novoNo->proximo = aux->proximo;
        aux->proximo = novoNo;
        if (novoNo->proximo == NULL)
        {
            ListaCadastro->UltimoProduto = novoNo;
        }
    }
    break;

    default:
        printf("Opcao invalida!\n");
        free(novoNo);
        return;
        break;
    }
    RetornaMenu();
}

// Função para verificar se há movimentações registradas para o produto
int ExisteMovimentacao(int codigoProduto, ListaMovimentacao *ListaMov)
{
    TipoApontadorMovimentacao atual = ListaMov->Pri_movim;
    while (atual != NULL)
    {
        if (atual->ctMovimentacao.cd_prod_movim == codigoProduto)
        {
            return 1; // Existe movimentação para o produto
        }
        atual = atual->movProximo;
    }
    return 0; // Não existe movimentação para o produto
}

void ExcluiProduto(ListaProduto *ListaExclusao, ListaMovimentacao *ListaMov, int opcExclusao) // FUNÇÃO PARA EXCLUIR PRODUTOS
{

    if (ListaExclusao == NULL || ListaExclusao->PrimeiroProduto == NULL)
    {
        TelaListaVazia("Exluir produtos");
        return;
    }

    TelaBase("Excluir produtos");

    int codigoProduto = -1; // Inicializa com valor inválido

    if (opcExclusao == 2)
    {
        codigoProduto = LerEntradaInteiro("Digite o codigo do produto para exclusao: ");
    }

    char confirmacao;
    TipoApontadorProduto atual = ListaExclusao->PrimeiroProduto;
    TipoApontadorProduto anterior = NULL;
    switch (opcExclusao)
    {
    // REMOVE O PRODUTO NO FINAL
    case 1:
    {

        if (ExisteMovimentacao(atual->conteudo.cd_produto, ListaMov))
        {
            gotoxy(2, 21);
            printf("Nao e possivel excluir o produto. Existem movimentacoes registradas.\n");
            RetornaMenu();
            return;
        }

        MostraMSG(" Deseja realmente excluir o produto? (S/N): ");
        confirmacao = getch();

        if (confirmacao != 'S' && confirmacao != 's')
        {
            LimparLinha(21);
            gotoxy(2, 21);
            printf("Operação de exclusao cancelada.");
            RetornaMenu();
            return;
        }
        while (atual->proximo != NULL)
        {
            anterior = atual;
            atual = atual->proximo;
        }

        if (anterior == NULL)
        {
            ListaExclusao->PrimeiroProduto = NULL;
        }
        else
        {
            anterior->proximo = NULL;
        }
        ListaExclusao->UltimoProduto = anterior;
        free(atual);
        gotoxy(2, 21);
        printf("Produto removido do final com sucesso.\n");
        RetornaMenu();
    }
    break;

    case 2:
    {
        if (ExisteMovimentacao(codigoProduto, ListaMov))
        {
            gotoxy(2, 21);
            printf("Nao e possivel excluir o produto. Existem movimentacoes registradas.\n");
            RetornaMenu();
            return;
        }

        MostraMSG(" Deseja realmente excluir o produto? (S/N): ");
        confirmacao = getch();

        if (confirmacao != 'S' && confirmacao != 's')
        {
            LimparLinha(21);
            gotoxy(2, 21);
            printf("Operacao de exclusao cancelada.");
            RetornaMenu();
            return;
        }

        while (atual != NULL && atual->conteudo.cd_produto != codigoProduto)
        {
            anterior = atual;
            atual = atual->proximo;
        }

        if (atual == NULL)
        {
            printf("Codigo do produto nao encontrado.\n");
            return;
        }

        if (anterior == NULL)
        {
            ListaExclusao->PrimeiroProduto = atual->proximo;
        }
        else
        {
            anterior->proximo = atual->proximo;
        }

        if (atual->proximo == NULL)
        {
            ListaExclusao->UltimoProduto = anterior;
        }

        free(atual);
        gotoxy(2, 21);
        printf("Produto com codigo %d removido com sucesso.\n", codigoProduto);
        RetornaMenu();
    }
    break;

    case 3:
    {
        TipoApontadorProduto aux = ListaExclusao->PrimeiroProduto;

        if (ExisteMovimentacao(aux->conteudo.cd_produto, ListaMov))
        {
            gotoxy(2, 21);
            printf("Nao e possivel excluir o produto. Existem movimentacoes registradas.\n");
            RetornaMenu();
            return;
        }

        MostraMSG(" Deseja realmente excluir o produto? (S/N): ");
        confirmacao = getch();

        if (confirmacao != 'S' && confirmacao != 's')
        {
            LimparLinha(21);
            gotoxy(2, 21);
            printf("Operacao de exclusao cancelada.");
            RetornaMenu();
            return;
        }

        ListaExclusao->PrimeiroProduto = ListaExclusao->PrimeiroProduto->proximo;
        if (ListaExclusao->PrimeiroProduto == NULL)
        {
            ListaExclusao->UltimoProduto = NULL;
        }
        free(aux);
        gotoxy(2, 21);
        printf("Produto removido do inicio com sucesso.\n");
        RetornaMenu();
    }
    break;

    default:
        printf("Opcao de exclusao invalida.\n");
        break;
    }
}

void ExibirProduto(ListaProduto *ListaExibir, int opcExibir) // FUNÇÃO PARA EXIBIR OS PRODUTOS
{
    switch (opcExibir)
    {
        // EXIBE UM PRODUTO ESPECIFICO PELO CODIGO
    case 1:
        system("cls");
        TelaBase("Exibe produto por codigo");
        int codigo = LerEntradaInteiro("Digite o codigo que deseja exibir: ");
        TipoApontadorProduto produto = BuscaProdutoCodigo(ListaExibir, codigo);

        if (produto != NULL)
        {
            gotoxy(5, 8);
            printf("+----------------------------------------------------------------------+\n");
            gotoxy(5, 9); // INICIO LISTA
            printf("|");
            gotoxy(11, 9); //  CODIGO PRODUTO
            printf("|");
            gotoxy(25, 9); //  DESCRIÇÃO PRODUTO
            printf("|");
            gotoxy(40, 9); //  UNIDADE DE MEDIDA
            printf("|");
            gotoxy(52, 9); //  DATA VALIDADE
            printf("|");
            gotoxy(62, 9); //  VALOR UNIDADE
            printf("|");
            gotoxy(76, 9); // FIM LISTA
            printf("|");

            gotoxy(6, 9);
            printf("COD");
            gotoxy(12, 9);
            printf("DESC. PROD");
            gotoxy(26, 9);
            printf("UN. MED");
            gotoxy(41, 9);
            printf("DT. VAL");
            gotoxy(53, 9);
            printf("VL. UNIT");
            gotoxy(63, 9);
            printf("VL. TOTAL");
            gotoxy(5, 10);
            printf("+----------------------------------------------------------------------+\n");

            gotoxy(5, 11);
            printf("|"); // INICIO LISTA
            gotoxy(11, 11);
            printf("|"); // CODIGO PRODUTO
            gotoxy(25, 11);
            printf("|"); // DESCRIÇÃO PRODUTO
            gotoxy(40, 11);
            printf("|"); // UNIDADE DE MEDIDA
            gotoxy(52, 11);
            printf("|"); //  DATA VALIDADE
            gotoxy(62, 11);
            printf("|"); // VALOR UNIDADE
            gotoxy(76, 11);
            printf("|"); // FIM LISTA

            gotoxy(6, 11);
            printf("%d", produto->conteudo.cd_produto);
            gotoxy(12, 11);
            printf("%s", produto->conteudo.ds_produto);
            gotoxy(26, 11);
            printf("%s", produto->conteudo.ds_unid_med);
            gotoxy(41, 11);
            printf("%s", produto->conteudo.dt_validade);
            gotoxy(53, 11);
            printf("%.2f", produto->conteudo.vl_custo_medio);
            gotoxy(63, 11);
            printf("%.2f", produto->conteudo.vl_total);

            gotoxy(5, 12);
            printf("+----------------------------------------------------------------------+\n");
        }
        else
        {
            system("cls");
            TelaBase("Produto nao encontrado");
            gotoxy(10, 10);
            printf("Produto com codigo '%d' nno encontrado.\n", codigo);
        }
        RetornaMenu();
        break;

    //  EXIBE OS PRODUTOS EM FICHARIOS
    case 2: // Exibir produtos do fichário
    {
        TipoApontadorProduto aux = ListaExibir->PrimeiroProduto;
        TipoApontadorProduto produtoAnterior = NULL;

        char comando;
        do
        {
            system("cls");
            TelaBase("Exibe produto fichario");

            if (aux != NULL)
            {
                gotoxy(2, 5);
                printf("COD");
                gotoxy(2, 6);
                printf("---");

                gotoxy(2, 8);
                printf("%d", aux->conteudo.cd_produto);

                gotoxy(8, 5);
                printf("Descricao do Produto");
                gotoxy(8, 6);
                printf("--------------------");
                gotoxy(8, 8);
                printf("%s", aux->conteudo.ds_produto);

                gotoxy(31, 5);
                printf("Unid");
                gotoxy(31, 6);
                printf("-----");
                gotoxy(31, 8);
                printf("%s", aux->conteudo.ds_unid_med);

                gotoxy(38, 5);
                printf("Data Valid");
                gotoxy(38, 6);
                printf("----------");
                gotoxy(38, 8);
                printf("%s", aux->conteudo.dt_validade);

                gotoxy(51, 5);
                printf("Qtde");
                gotoxy(51, 6);
                printf("----");
                gotoxy(51, 8);
                printf("%.2f", aux->conteudo.qt_produto);

                gotoxy(58, 5);
                printf("Vl. Unit");
                gotoxy(58, 6);
                printf("--------");
                gotoxy(58, 8);
                printf("%.2f", aux->conteudo.vl_custo_medio);

                gotoxy(68, 5);
                printf("Vl. Total");
                gotoxy(68, 6);
                printf("---------");
                gotoxy(68, 8);
                printf("%.2f", aux->conteudo.vl_total);

                MostraMSG("Digite (p/P) - proximo, (a/A) - anterior, (r/R) - retornar: ");
                comando = _getch();

                if (comando == 'p' || comando == 'P')
                {
                    if (aux->proximo != NULL)
                    {
                        produtoAnterior = aux;
                        aux = aux->proximo;
                    }
                    else
                    {
                        MostraMSG("Nao ha mais produtos seguintes.");
                        _getch(); // Aguarda um comando para continuar
                    }
                }
                else if (comando == 'a' || comando == 'A')
                {
                    if (produtoAnterior != NULL)
                    {
                        aux = produtoAnterior;
                        produtoAnterior = NULL; // Reset para evitar ciclo
                    }
                    else
                    {
                        MostraMSG("Este e o primeiro produto da lista.");
                        _getch(); // Aguarda um comando para continuar
                    }
                }
            }
            else
            {
                gotoxy(2, 21);
                printf("Nenhum produto encontrado.\n");
                MostraMSG("Pressione 'r'/'R' para retornar ao menu.");
                comando = _getch();
            }

        } while (comando != 'r' && comando != 'R');
    }
    break;

    default:
        printf("Opcaoo de exclusao invalida.\n");
        break;
    }
}

void ExibeListaProdutos(ListaProduto *ListaOrdenada) //  FUNÇÃO PARA EXIBIR OS PRODUTOS ORDENADOS
{

    system("cls");
    TelaBase("Lista de Produtos");
    gotoxy(5, 6);
    printf("+----------------------------------------------------------------------+\n");
    gotoxy(5, 7); // INICIO LISTA
    printf("|");
    gotoxy(11, 7); //  CODIGO PRODUTO
    printf("|");
    gotoxy(25, 7); //  DESCRIÇÃO PRODUTO
    printf("|");
    gotoxy(40, 7); //  UNIDADE DE MEDIDA
    printf("|");
    gotoxy(52, 7); //  DATA VALIDADE
    printf("|");
    gotoxy(62, 7); //  VALOR UNIDADE
    printf("|");
    gotoxy(76, 7); // FIM LISTA
    printf("|");

    gotoxy(6, 7);
    printf("COD");
    gotoxy(12, 7);
    printf("DESC. PROD");
    gotoxy(26, 7);
    printf("UN. MED");
    gotoxy(41, 7);
    printf("DT. VAL");
    gotoxy(53, 7);
    printf("VL. UNIT");
    gotoxy(63, 7);
    printf("VL. TOTAL");
    gotoxy(5, 8);
    printf("+----------------------------------------------------------------------+\n");

    TipoApontadorProduto atual = ListaOrdenada->PrimeiroProduto;
    int linha = 9;
    while (atual != NULL)
    {

        gotoxy(5, linha);
        printf("|"); // INICIO LISTA
        gotoxy(11, linha);
        printf("|"); // CODIGO PRODUTO
        gotoxy(25, linha);
        printf("|"); // DESCRIÇÃO PRODUTO
        gotoxy(40, linha);
        printf("|"); // UNIDADE DE MEDIDA
        gotoxy(52, linha);
        printf("|"); //  DATA VALIDADE
        gotoxy(62, linha);
        printf("|"); // VALOR UNIDADE
        gotoxy(76, linha);
        printf("|"); // FIM LISTA

        gotoxy(6, linha);
        printf("%d", atual->conteudo.cd_produto);
        gotoxy(12, linha);
        printf("%s", atual->conteudo.ds_produto);
        gotoxy(26, linha);
        printf("%s", atual->conteudo.ds_unid_med);
        gotoxy(41, linha);
        printf("%s", atual->conteudo.dt_validade);
        gotoxy(53, linha);
        printf("%.2f", atual->conteudo.vl_custo_medio);
        gotoxy(63, linha);
        printf("%.2f", atual->conteudo.vl_total);

        gotoxy(5, linha + 1);
        printf("+----------------------------------------------------------------------+\n");
        linha += 2;             // Incrementa a linha para a próxima entrada
        atual = atual->proximo; // Move para o próximo produto
    }
    RetornaMenu();
}

void AlteraProduto(ListaProduto *ListaProdutos, int tipoAlteracao, int codigo) //  FUNÇÃO PARA ALTERAR O/OS PRODUTOS
{

    TipoApontadorProduto produto = BuscaProdutoCodigo(ListaProdutos, codigo);

    if (produto == NULL)
    {
        printf("Produto com codigo %d nao encontrado.\n", codigo);
        return;
    }

    if (tipoAlteracao == 1)
    {
        system("cls");
        TelaAlteraProdutoCampos();
        int campo = LerEntradaInteiro("Digite o numero do campo que deseja alterar: ");

        switch (campo)
        {
        case 1:
            system("cls");
            TelaBase("Alteração de descricao");
            gotoxy(20, 10);
            printf("Nova Descricao: ");
            MostraMSG("Digite a descricao: ");
            fgets(produto->conteudo.ds_produto, sizeof(produto->conteudo.ds_produto), stdin);
            produto->conteudo.ds_produto[strcspn(produto->conteudo.ds_produto, "\n")] = '\0'; // Remove o \n do final
            break;
        case 2:
            system("cls");
            TelaBase("Alteração de Un. Medida");
            gotoxy(20, 10);
            printf("Nova Unidade de Medida: ");
            MostraMSG("Digite a unidade de medida: ");
            fgets(produto->conteudo.ds_unid_med, sizeof(produto->conteudo.ds_unid_med), stdin);
            produto->conteudo.ds_unid_med[strcspn(produto->conteudo.ds_unid_med, "\n")] = '\0'; // Remove o \n do final
            break;
        case 3:
            system("cls");
            TelaBase("Alteração de Dt. Validade");
            gotoxy(20, 10);
            printf("Nova Data de Validade: ");

            char novaData[11];
            VerificaData(novaData, "Nova Data de Validade: ");

            strncpy(produto->conteudo.dt_validade, novaData, sizeof(produto->conteudo.dt_validade));
            produto->conteudo.dt_validade[sizeof(produto->conteudo.dt_validade) - 1] = '\0'; // Garante que a string termine com '\0'
            break;
        default:
            printf("Campo invalido.\n");
            break;
        }
    }
    else if (tipoAlteracao == 2)
    {
        system("cls");
        TelaBase("Alterar Produto");
        TipoApontadorProduto Aux = ListaProdutos->PrimeiroProduto->proximo;

        if (produto != NULL)
        {
            gotoxy(5, 8);
            printf("+----------------------------------------------------------------------+\n");
            gotoxy(5, 9); // INICIO LISTA
            printf("|");
            gotoxy(11, 9); //  CODIGO PRODUTO
            printf("|");
            gotoxy(25, 9); //  DESCRIÇÃO PRODUTO
            printf("|");
            gotoxy(40, 9); //  UNIDADE DE MEDIDA
            printf("|");
            gotoxy(52, 9); //  DATA VALIDADE
            printf("|");
            gotoxy(62, 9); //  VALOR UNIDADE
            printf("|");
            gotoxy(76, 9); // FIM LISTA
            printf("|");

            gotoxy(6, 9);
            printf("COD");
            gotoxy(12, 9);
            printf("DESC. PROD");
            gotoxy(26, 9);
            printf("UN. MED");
            gotoxy(41, 9);
            printf("DT. VAL");
            gotoxy(53, 9);
            printf("VL. UNIT");
            gotoxy(63, 9);
            printf("VL. TOTAL");
            gotoxy(5, 10);
            printf("+----------------------------------------------------------------------+\n");

            gotoxy(5, 11);
            printf("|"); // INICIO LISTA
            gotoxy(11, 11);
            printf("|"); // CODIGO PRODUTO
            gotoxy(25, 11);
            printf("|"); // DESCRIÇÃO PRODUTO
            gotoxy(40, 11);
            printf("|"); // UNIDADE DE MEDIDA
            gotoxy(52, 11);
            printf("|"); //  DATA VALIDADE
            gotoxy(62, 11);
            printf("|"); // VALOR UNIDADE
            gotoxy(76, 11);
            printf("|"); // FIM LISTA

            gotoxy(6, 11);
            printf("%d", Aux->conteudo.cd_produto);
            gotoxy(12, 11);
            printf("%s", Aux->conteudo.ds_produto);
            gotoxy(26, 11);
            printf("%s", Aux->conteudo.ds_unid_med);
            gotoxy(41, 11);
            printf("%s", Aux->conteudo.dt_validade);
            gotoxy(53, 11);
            printf("%.2f", Aux->conteudo.vl_custo_medio);
            gotoxy(63, 11);
            printf("%.2f", Aux->conteudo.vl_total);

            gotoxy(5, 12);
            printf("+----------------------------------------------------------------------+\n");
        }
        else
        {
            system("cls");
            TelaBase("Produto nao encontrado");
            gotoxy(10, 10);
            printf("Produto com codigo '%d' nno encontrado.\n", codigo);
        }

        // Solicita ao usuario para alterar os dados
        printf("Digite os novos valores para o produto:\n");
        MostraMSG("Descricao: ");
        fgets(produto->conteudo.ds_produto, sizeof(produto->conteudo.ds_produto), stdin);
        produto->conteudo.ds_produto[strcspn(produto->conteudo.ds_produto, "\n")] = '\0'; // Remove o \n do final
        gotoxy(26, 11);
        printf("%s", Aux->conteudo.ds_unid_med);

        MostraMSG("Unidade de Medida: ");
        fgets(produto->conteudo.ds_unid_med, sizeof(produto->conteudo.ds_unid_med), stdin);
        produto->conteudo.ds_unid_med[strcspn(produto->conteudo.ds_unid_med, "\n")] = '\0'; // Remove o \n do final
        gotoxy(26, 11);
        printf("%s", Aux->conteudo.ds_unid_med);

        MostraMSG("Data de Validade: ");
        fgets(produto->conteudo.dt_validade, sizeof(produto->conteudo.dt_validade), stdin);
        produto->conteudo.dt_validade[strcspn(produto->conteudo.dt_validade, "\n")] = '\0'; // Remove o \n do final
        gotoxy(41, 11);
        printf("%s", Aux->conteudo.dt_validade);
    }
    else
    {
        printf("Opcao invalida.\n");
    }

    RetornaMenu();
}

int LerEntradaInteiro(char *Mensagem) // FUNÇÃO PARA VERIFICAR A ENTRADA DE VALOR INTEIRO
{
    char entrada[100];
    int valido = 0, numero = 0;

    while (!valido)
    {
        MostraMSG(Mensagem);
        fgets(entrada, sizeof(entrada), stdin); // Usamos fgets para ler a entrada completa

        // Remove o caractere de nova linha do final da string
        entrada[strcspn(entrada, "\n")] = '\0';

        // Verifica se a entrada é um espaço em branco
        if (strlen(entrada) == 0 || (strlen(entrada) == 1 && entrada[0] == ' '))
        {
            continue; // Pede ao usuário para digitar novamente
        }

        valido = 1; // Assume que a entrada é válida até provar o contrário
        for (int i = 0; i < strlen(entrada); i++)
        {
            if (!isdigit(entrada[i]))
            {
                gotoxy(2, 21);
                printf("Entrada invalida. Por favor, digite um valor inteiro.\n");
                valido = 0;
                break;
            }
        }

        if (valido)
        {
            numero = atoi(entrada);
        }
    }

    return numero;
}

float LerEntradaFloat(char *Mensagem) //  FUNÇÃO PARA VERIFICAR A ENTRADA DE VALOR FLUTUANTE
{
    char entrada[100];
    float numero;
    while (TRUE)
    {
        MostraMSG(Mensagem);
        fgets(entrada, sizeof(entrada), stdin);
        if (sscanf(entrada, "%f", &numero) == 1)
        {
            break;
        }
        MostraMSG("Entrada invalida");
    }
    return numero;
}

void MenuMovimentacoes(ListaMovimentacao *ListaMovimentacoes, ListaProduto *ListaProdutos); //  DECLARAÇÃO DA FUNÇÃO DE MENU MOVIMENTAÇÕES

void IniciarMovimentacoes(ListaMovimentacao *IniciaMovimentacao) // FUNÇÃO PARA INICIAR A LISTA DE MOVIMENTAÇÕES
{
    IniciaMovimentacao->Pri_movim = NULL;
    IniciaMovimentacao->Ult_movim = NULL;
}

void RegistraMovimentacao(ListaMovimentacao *ListaMovimentacoes, ListaProduto *ListaProdutos) // FUNÇÃO PARA REGISTRAR UMA MOVIMENTAÇÃO
{
    system("cls");
    TelaBase("Registro de movimentacao");

    gotoxy(10, 8);
    printf("Codigo do produto........: "); // CODIGO
    gotoxy(10, 10);
    printf("Tipo de movimentacao.....: "); //  DESCRIÇÃO
    gotoxy(10, 12);
    printf("Quantidade de produtos movimentados........: "); // UNIDADE DE MEDIDA
    gotoxy(10, 14);
    printf("Valor unitario.........: ");
    gotoxy(10, 16);
    printf("Valor total.........: ");
    gotoxy(10, 18);
    printf("Data da movimentacao.........: ");

    int codigo = LerEntradaInteiro("Digite o codigo do produto: ");
    TipoApontadorProduto produto = BuscaProdutoCodigo(ListaProdutos, codigo);

    if (produto == NULL)
    {
        printf("Produto com codigo %d nao encontrado. ", codigo);
        return;
    }
    else
    {
        gotoxy(41, 8);
        printf("%d - %s", produto->conteudo.cd_produto, produto->conteudo.ds_produto);
    }
    char tipoMov;
    do
    {
        MostraMSG("Digite o tipo de movimentacao (E/S): ");
        scanf(" %c", &tipoMov);
        gotoxy(41, 10);
        printf("%c", tipoMov);

    } while (tipoMov != 'e' && tipoMov != 'E' && tipoMov != 's' && tipoMov != 'S');

    float qtMov = LerEntradaFloat("Digite a quantidade de movimentacao: ");
    gotoxy(55, 12);
    printf("%.2f", qtMov);

    if (tipoMov == 's' && produto->conteudo.qt_produto < qtMov)
    {
        gotoxy(2, 21);
        printf("Quantidade em estoque insulficiente para a saida. ");
        return;
    }

    float vlUnitMov = LerEntradaFloat("Digite o valor unitario: ");
    gotoxy(41, 14);
    printf("%.2f", vlUnitMov);
    gotoxy(41, 16);
    printf("%.2f", qtMov * vlUnitMov);

    MovProduto novaMovimentacao;
    MostraMSG("Digite a data da movimentacao: ");
    VerificaData(novaMovimentacao.dt_movim, "Digite a data da movimentacao: ");
    gotoxy(41, 18);
    printf("%s", novaMovimentacao.dt_movim);

    novaMovimentacao.cd_prod_movim = codigo;
    novaMovimentacao.tp_movim = tipoMov;
    novaMovimentacao.qt_movim = qtMov;
    novaMovimentacao.vl_unit_movim = vlUnitMov;
    novaMovimentacao.vl_total_movim = qtMov * vlUnitMov;

    TipoApontadorMovimentacao novaMov = (TipoApontadorMovimentacao)malloc(sizeof(TipoMovimentacao));
    novaMov->ctMovimentacao = novaMovimentacao;
    novaMov->movAnterior = ListaMovimentacoes->Ult_movim;
    novaMov->movProximo = NULL;

    if (ListaMovimentacoes->Ult_movim != NULL)
    {
        ListaMovimentacoes->Ult_movim->movProximo = novaMov;
    }
    else
    {
        ListaMovimentacoes->Pri_movim = novaMov;
    }
    ListaMovimentacoes->Ult_movim = novaMov;

    if (tipoMov == 'e') // Atualizar a quantidade e valores do produto
    {
        // Calculando o novo custo médio
        float valorEstoqueAtual = produto->conteudo.vl_total;
        float quantidadeEstoqueAtual = produto->conteudo.qt_produto;

        produto->conteudo.qt_produto += qtMov;
        produto->conteudo.vl_total += novaMovimentacao.vl_total_movim;

        produto->conteudo.vl_custo_medio = (valorEstoqueAtual + (vlUnitMov * qtMov)) / produto->conteudo.qt_produto;
    }
    else if (tipoMov == 's')
    {
        produto->conteudo.qt_produto -= qtMov;
        produto->conteudo.vl_total -= novaMovimentacao.vl_total_movim;
        if (produto->conteudo.qt_produto > 0)
        {
            produto->conteudo.vl_custo_medio = produto->conteudo.vl_total / produto->conteudo.qt_produto;
        }
        else
        {
            produto->conteudo.vl_custo_medio = 0;
            produto->conteudo.vl_total = 0;
        }
    }

    gotoxy(2, 21);
    printf("Movimentacao registrada com sucesso ");
    RetornaMenu();
}

void ExibirMovimentacoes(ListaMovimentacao *listaMov, ListaProduto *ListaProdutos) // FUNÇÃO PARA EXIBIR AS MOVIMENTAÇÕES
{

    if (listaMov->Pri_movim == NULL)
    {
        TelaListaVazia("Exibe movimentacoes ");
        return;
    }

    system("cls");
    TelaBase("Exibe movimentacoes");
    int codigoProduto = LerEntradaInteiro("Digite o codigo do produto para exibir as movimentacoes: ");
    TipoApontadorProduto produto = BuscaProdutoCodigo(ListaProdutos, codigoProduto);

    if (produto != NULL)
    {

        gotoxy(5, 6);
        printf("Lista de movimentacoes do produto %s - (%d)", produto->conteudo.ds_produto, produto->conteudo.cd_produto);
        // Exibição das movimentações

        gotoxy(5, 8);
        printf("+--------------------------------------------------------------------+\n");
        gotoxy(5, 9); // INICIO LISTA MOVIMENTAÇÕES / DATA MOVIMENTAÇÃO
        printf("|");
        gotoxy(19, 9); //   TIPO MOVIMENTAÇÃO
        printf("|");
        gotoxy(29, 9); //  QUANTIDADE MOVIMENTAÇÃO
        printf("|");
        gotoxy(39, 9); //  VALOR UNITARIO MOVIMENTAÇÃO
        printf("|");
        gotoxy(49, 9); //  VALOR TOTAL MOVIMENTAÇÃO
        printf("|");
        gotoxy(59, 9); //  CUSTO MÉDIO
        printf("|");
        gotoxy(74, 9); //  FINALIZAÇÃO MOVIMENTAÇÃO
        printf("|");
        gotoxy(5, 10);
        printf("+--------------------------------------------------------------------+\n");

        gotoxy(6, 9);
        printf("DATA MOV");
        gotoxy(20, 9);
        printf("TIPO");
        gotoxy(30, 9);
        printf("QTDE");
        gotoxy(40, 9);
        printf("VL. UNIT");
        gotoxy(50, 9);
        printf("VL. TOTAL");
        gotoxy(60, 9);
        printf("CT. MEDIO");

        int linha = 11;
        TipoApontadorMovimentacao mov = listaMov->Pri_movim;
        TipoApontadorProduto prod = ListaProdutos->PrimeiroProduto;

        while (mov != NULL)
        {
            if (mov->ctMovimentacao.cd_prod_movim == codigoProduto)
            {
                gotoxy(5, linha);
                printf("|");
                gotoxy(19, linha);
                printf("|");
                gotoxy(29, linha);
                printf("|");
                gotoxy(39, linha);
                printf("|");
                gotoxy(49, linha);
                printf("|");
                gotoxy(59, linha);
                printf("|");
                gotoxy(74, linha);
                printf("|");

                gotoxy(6, linha);
                printf("%s", mov->ctMovimentacao.dt_movim);
                gotoxy(20, linha);
                printf("%c", mov->ctMovimentacao.tp_movim);
                gotoxy(30, linha);
                printf("%.2f", mov->ctMovimentacao.qt_movim);
                gotoxy(40, linha);
                printf("%.2f", mov->ctMovimentacao.vl_unit_movim);
                gotoxy(50, linha);
                printf("%.2f", mov->ctMovimentacao.qt_movim * mov->ctMovimentacao.vl_unit_movim);
                gotoxy(60, linha);
                printf("%.2f", prod->conteudo.vl_custo_medio);

                linha++;
            }
            mov = mov->movProximo;
        }

        gotoxy(5, linha);
        printf("+--------------------------------------------------------------------+\n");
    }
    else
    {
        system("cls");
        TelaBase("Produto nao encontrado");
        gotoxy(10, 10);
        printf("Produto com codigo '%d' nao encontrado.\n", codigoProduto);
    }

    RetornaMenu();
}

void MenuProdutos(ListaProduto *ListaSimplesProduto, ListaMovimentacao *ListaMovimentacoes) // MENU DE PRODUTOS
{
    int opcao;
    boolean controle = TRUE;

    do
    {
        system("cls");
        TelaMenuProduto();
        opcao = LerEntradaInteiro("Digite sua opcao: ");
        switch (opcao)
        {
        case 1:
            CadastraProduto(ListaSimplesProduto, 1);
            break;

        case 2:
            CadastraProduto(ListaSimplesProduto, 2);
            break;

        case 3:
            CadastraProduto(ListaSimplesProduto, 3);
            break;

        case 4:
            ExcluiProduto(ListaSimplesProduto, ListaMovimentacoes, 1);
            break;

        case 5:
            ExcluiProduto(ListaSimplesProduto, ListaMovimentacoes, 2);
            break;

        case 6:
            ExcluiProduto(ListaSimplesProduto, ListaMovimentacoes, 3);
            break;

        case 7:
            MenuListaProdutos(ListaSimplesProduto);
            break;

        case 8:
            MenuAlteraProdutos(ListaSimplesProduto);
            break;

        case 9:
            gotoxy(2, 21);
            printf("Retornando ao menu inicial...\n");
            controle = FALSE;
            break;

        default:
            break;
        }
    } while (controle);
}

void MenuAlteraProdutos(ListaProduto *ListaSimplesProduto) //  FUNÇÃO PARA ALTERAR OS PRODUTOS
{
    int tipoAlteracao;
    int codigo;

    if (ListaSimplesProduto == NULL || ListaSimplesProduto->PrimeiroProduto == NULL)
    {
        TelaListaVazia("Alterar produto");
        return;
    }

    do
    {
        system("cls");
        TelaAlteraProduto();
        tipoAlteracao = LerEntradaInteiro("Digite sua opcao: ");

        if (tipoAlteracao == 3)
        {
            return;
        }
        else if (tipoAlteracao < 1 || tipoAlteracao > 2)
        {
            printf("Opcao invalida. Tente novamente.\n");
            continue;
        }

        codigo = LerEntradaInteiro("Digite o codigo do produto que deseja alterar: ");

        AlteraProduto(ListaSimplesProduto, tipoAlteracao, codigo);
        break;

    } while (1);
}

void MenuListaProdutos(ListaProduto *ListaSimplesProduto) // FUNÇÃO DOS MENUS PARA EXIBIR PRODUTOS
{
    int opcao;

    if (ListaSimplesProduto == NULL || ListaSimplesProduto->PrimeiroProduto == NULL)
    {
        TelaListaVazia("Exibir produtos");
        return;
    }

    do
    {
        system("cls");
        TelaMenuConsultaProduto();
        opcao = LerEntradaInteiro("Digite sua opcao: ");
        switch (opcao)
        {
        case 1:
            ExibirProduto(ListaSimplesProduto, 2);
            break;

        case 2:
            OrdenaCodigo(ListaSimplesProduto);
            ExibeListaProdutos(ListaSimplesProduto);
            break;

        case 3:
            OrdenaDescricao(ListaSimplesProduto);
            ExibeListaProdutos(ListaSimplesProduto);
            break;

        case 4:
            ExibirProduto(ListaSimplesProduto, 1);
            break;

        case 5:
            gotoxy(10, 20);
            printf("Retornando ao menu inicial...\n");
            break;

        default:
            break;
        }
    } while (opcao != 5);
}

void RetornaMenu() // FUNÇÃO PARA RETORNAR AO MENU INICIAL
{
    char ch;
    do
    {
        gotoxy(1, 22);
        printf("+------------------------------------------------------------------------------+\n");
        LimparLinha(23);
        gotoxy(2, 23);
        printf("MSG.: Digite (R/r) para retornar ao menu: ");
        ch = getchar();
        ch = toupper(ch); // Converte para maiúsculo
    } while (ch != 'R');
}

void MenuMovimentacoes(ListaMovimentacao *ListaMovimentacoes, ListaProduto *ListaProdutos) // MENU DE MOVIMENTAÇÕES
{

    int opcao;
    boolean controle = TRUE;

    do
    {
        system("cls");
        TelaMenuMovimentacao();
        opcao = LerEntradaInteiro("Digite sua opcao: ");

        switch (opcao)
        {
        case 1:
            RegistraMovimentacao(ListaMovimentacoes, ListaProdutos);
            break;

        case 2:
            ExibirMovimentacoes(ListaMovimentacoes, ListaProdutos);
            break;

        case 3:
            printf("Retornando ao menu inicial...\n");
            controle = FALSE;
            break;

        default:
            break;
        }
    } while (controle);
}

void MenuInicio() // FUNÇÃO DO MENU INICIAL
{
    ListaProduto ListaSimplesProduto;
    IniciarListaProduto(&ListaSimplesProduto);
    ListaMovimentacao ListaMovProduto;
    IniciarMovimentacoes(&ListaMovProduto);
    boolean controle = TRUE;

    do
    {
        TelaMenu();
        switch (LerEntradaInteiro("Digite sua opcao: "))
        {
        case 1:
            MenuProdutos(&ListaSimplesProduto, &ListaMovProduto);
            break;

        case 2:
            MenuMovimentacoes(&ListaMovProduto, &ListaSimplesProduto);
            break;

        case 3:
            gotoxy(10, 20);
            printf("Encerrando o programa...\n");
            controle = FALSE;
            break;

        default:
            MostraMSG("Opcao invalida!");
            break;
        }
    } while (controle);
}

int main() // FUNÇÃO PRINCIPAL
{
    MenuInicio();
    return 0;
}