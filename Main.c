#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>

void RetornaMenu();
void MenuProdutos();
void MenuMovimentacoes();
void MenuListaProdutos();
int LerEntradaInteiro();

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

void LimparLinha(int linha)
{
    gotoxy(2, linha);
    printf("                                                                                "); // 80 espaços para limpar a linha
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

//  FUNÇÃO PARA BUSCAR UM PRODUTO POR CÓDIGO
TipoApontadorProduto BuscaProdutoCodigo(ListaProduto *ListaBuscaProduto, int codigo)
{
    TipoApontadorProduto aux = ListaBuscaProduto->PrimeiroProduto->proximo;
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

//  FUNÇÃO PARA LER OS DADOS DOS PRODUTOS E ARMAZENAR NA LISTA
Produto LerDadosProdutos(char *tipoInclusao)
{
    system("cls");
    TelaBase(tipoInclusao);
    Produto NovoProduto;

    gotoxy(14, 8);
    printf("Codigo do produto........: "); // CODIGO
    NovoProduto.cd_produto = LerEntradaInteiro("Codigo do produto: ");
    gotoxy(41, 8);
    printf("%d", NovoProduto.cd_produto); // PRINTA CODIGO DO PRODUTO

    gotoxy(10, 10);
    printf("1 - Descricao do produto.....: "); //  DESCRIÇÃO
    MostraMSG(" Descricao do produto: ");
    scanf("%s", NovoProduto.ds_produto);
    LimparLinha(23);
    gotoxy(41, 10);
    printf("%s", NovoProduto.ds_produto); // PRINTA DESCRIÇÃO DO PRODUTO

    gotoxy(10, 12);
    printf("2 - Unidade de medida........: "); // UNIDADE DE MEDIDA
    MostraMSG(" Unidade de medida do produto: ");
    scanf("%s", NovoProduto.ds_unid_med);
    LimparLinha(23);
    gotoxy(41, 12);
    printf("%s", NovoProduto.ds_unid_med); // PRINTA UNIDADE DE MEDIDA

    gotoxy(10, 14);
    printf("3 - Data de Validade.........: ");
    MostraMSG(" Data de validade do produto: ");
    scanf("%s", NovoProduto.dt_validade); // DATA DE VALIDADE
    LimparLinha(23);
    gotoxy(41, 14);
    printf("%s", NovoProduto.dt_validade); // PRINTA UNIDADE DE MEDIDA

    NovoProduto.qt_produto = 0;
    NovoProduto.vl_custo_medio = 0.0;
    NovoProduto.vl_total = 0.0;

    return NovoProduto;
}

//  FUNÇÃO PARA INICIAR A LISTA DE PRODUTOS
void IniciarListaProduto(ListaProduto *ListaProduto)
{
    ListaProduto->PrimeiroProduto = (TipoApontadorProduto)malloc(sizeof(TipoProduto));
    ListaProduto->UltimoProduto = ListaProduto->PrimeiroProduto;
    ListaProduto->PrimeiroProduto->proximo = NULL;
}

void CadastraProdutoInicio(ListaProduto *ListaProdutoInicio)
{
    Produto ProdutoNovoInicio = LerDadosProdutos("Cadastra no inicio");

    TipoApontadorProduto NovoProduto = (TipoApontadorProduto)malloc(sizeof(TipoProduto));
    NovoProduto->conteudo = ProdutoNovoInicio;
    NovoProduto->proximo = ListaProdutoInicio->PrimeiroProduto->proximo;
    ListaProdutoInicio->PrimeiroProduto->proximo = NovoProduto;

    if (ListaProdutoInicio->UltimoProduto == ListaProdutoInicio->PrimeiroProduto)
    {
        ListaProdutoInicio->UltimoProduto = NovoProduto;
    }
    RetornaMenu();
}

void CadastraProdutoFinal(ListaProduto *ListaProdutoFinal)
{
    Produto ProdutoNovoFim = LerDadosProdutos("Cadastra no Final");
    ListaProdutoFinal->UltimoProduto->proximo = (TipoApontadorProduto)malloc(sizeof(TipoProduto));
    ListaProdutoFinal->UltimoProduto = ListaProdutoFinal->UltimoProduto->proximo;
    ListaProdutoFinal->UltimoProduto->conteudo = ProdutoNovoFim;
    ListaProdutoFinal->UltimoProduto->proximo = NULL;
    RetornaMenu();
}

void CadastraProdutoPosicao(ListaProduto *ListaProdutoPosicao)
{
    int posicao;
    int contador = 0;

    Produto ProdutoNovoPosicao = LerDadosProdutos("Cadastra em uma posicao");

    posicao = LerEntradaInteiro("Digite a posicao para inserir o produto: ");
    TipoApontadorProduto NovoProduto = (TipoApontadorProduto)malloc(sizeof(TipoProduto));
    NovoProduto->conteudo = ProdutoNovoPosicao;

    TipoApontadorProduto Aux = ListaProdutoPosicao->PrimeiroProduto;

    while (Aux != NULL && contador < posicao - 1)
    {
        Aux = Aux->proximo;
        contador++;
    }
    if (Aux == NULL)
    {
        printf("Posição inválida!\n");
        free(NovoProduto);
        return;
    }

    NovoProduto->proximo = Aux->proximo;
    Aux->proximo = NovoProduto;

    if (NovoProduto->proximo == NULL)
    {
        ListaProdutoPosicao->UltimoProduto = NovoProduto;
    }
    RetornaMenu();
}

void ExcluiProdutoInicio(ListaProduto *ListaRemoveProdutoInicio)
{
    if (ListaRemoveProdutoInicio == NULL)
    {
        printf("A lista tá vazia!");
        return;
    }

    TipoApontadorProduto aux = ListaRemoveProdutoInicio->PrimeiroProduto;
    ListaRemoveProdutoInicio->PrimeiroProduto = ListaRemoveProdutoInicio->PrimeiroProduto->proximo;

    if (ListaRemoveProdutoInicio->PrimeiroProduto == NULL)
    {
        ListaRemoveProdutoInicio->UltimoProduto = NULL;
    }
    free(aux);
    printf("Produto removido com sucesso...");
}

void ExcluiProdutoFinal(ListaProduto *ListaRemoveProdutoFinal)
{
    if (ListaRemoveProdutoFinal == NULL)
    {
        printf("A lista tá vazia!");
        return;
    }

    TipoApontadorProduto atual = ListaRemoveProdutoFinal->PrimeiroProduto;
    TipoApontadorProduto anterior = NULL;

    while (atual->proximo != NULL)
    {
        anterior = atual;
        atual = atual->proximo;
    }

    if (anterior == NULL)
    {
        ListaRemoveProdutoFinal->PrimeiroProduto = NULL;
    }
    else
    {
        anterior->proximo = NULL;
    }

    ListaRemoveProdutoFinal->UltimoProduto = anterior;
    free(atual);
    printf("Produto excluído com sucesso.\n");
}

void ExcluirProdutoPosicao(ListaProduto *ListaRemovePosicao)
{
    int posicao;
    if (ListaRemovePosicao->PrimeiroProduto == NULL)
    {
        printf("A lista está vazia.\n");
        return;
    }

    posicao = LerEntradaInteiro("Digite a posicao para retirar o produto: ");

    if (posicao < 1)
    {
        printf("Posição inválida.\n");
        return;
    }

    TipoApontadorProduto atual = ListaRemovePosicao->PrimeiroProduto;
    TipoApontadorProduto anterior = NULL;

    for (int i = 1; atual != NULL && i < posicao; i++)
    {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL)
    {
        printf("Posição inválida.\n");
        return;
    }

    if (anterior == NULL)
    {
        ListaRemovePosicao->PrimeiroProduto = atual->proximo;
    }
    else
    {
        anterior->proximo = atual->proximo;
    }

    if (atual->proximo == NULL)
    {
        ListaRemovePosicao->UltimoProduto = anterior;
    }

    free(atual);
    printf("Produto excluído com sucesso.\n");
}

void ExibirProdutoCodigo(ListaProduto *ListaProdutoExibir)
{
    int codigo;
    system("cls");
    TelaBase("Exibe produto por codigo");

    codigo = LerEntradaInteiro("Digite o codigo que deseja exibir: ");
    TipoApontadorProduto produto = BuscaProdutoCodigo(ListaProdutoExibir, codigo);

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

        TipoApontadorProduto Aux = ListaProdutoExibir->PrimeiroProduto->proximo;
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
        TelaBase("Produto Não Encontrado");
        gotoxy(10, 10);
        printf("Produto com código %d não encontrado.\n", codigo);
    }
    RetornaMenu();
}

void ExibirProduto(TipoProduto *produto)
{
    gotoxy(5, 8);
    printf("+----------------------------------------------------------------------+\n");
    gotoxy(5, 9); // INICIO LISTA
    printf("|");
    gotoxy(11, 9); // CODIGO PRODUTO
    printf("|");
    gotoxy(25, 9); // DESCRIÇÃO PRODUTO
    printf("|");
    gotoxy(40, 9); // UNIDADE DE MEDIDA
    printf("|");
    gotoxy(52, 9); // DATA VALIDADE
    printf("|");
    gotoxy(62, 9); // VALOR UNIDADE
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
    printf("|"); // DATA VALIDADE
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
    printf("%.2f", produto->conteudo.qt_produto);
    gotoxy(63, 11);
    printf("%.2f", produto->conteudo.vl_total);

    gotoxy(5, 12);
    printf("+----------------------------------------------------------------------+\n");
}

void ExibirProdutoFichario(ListaProduto *ListaProdutoFichario)
{
    TipoApontadorProduto aux = ListaProdutoFichario->PrimeiroProduto->proximo;
    TipoApontadorProduto produtoAnterior = NULL;

    char comando;
    while (1)
    {
        system("cls");
        TelaBase("Exibe produto fichario");

        if (aux != NULL)
        {
            // ExibirProduto(aux);
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
            }
            else if (comando == 'a' || comando == 'A')
            {
                if (produtoAnterior != NULL)
                {
                    aux = produtoAnterior;
                    produtoAnterior = NULL; // Reset para evitar ciclo
                }
            }
            else if (comando == 'r' || comando == 'R')
            {
                break;
            }
        }
        else
        {
            gotoxy(2, 21);
            printf("Nenhum produto encontrado.\n");
            MostraMSG("Pressione 'r'/'R' para retornar ao menu.");
            comando = _getch();
            if (comando == 'r' || comando == 'R')
            {
                break;
            }
        }
    }
}

void DividirListaProdutos(TipoApontadorProduto FonteProdutos, TipoApontadorProduto *InicioProdutos, TipoApontadorProduto *FimProdutos)
{
    TipoApontadorProduto rapido;
    TipoApontadorProduto lento;

    if (FonteProdutos == NULL || FonteProdutos->proximo == NULL)
    {
        *InicioProdutos = FonteProdutos;
        *FimProdutos = NULL;
    }
    else
    {
        lento = FonteProdutos;
        rapido = FonteProdutos->proximo;

        while (rapido != NULL)
        {
            rapido = rapido->proximo;
            if (rapido != NULL)
            {
                lento = lento->proximo;
                rapido = rapido->proximo;
            }
        }
        *InicioProdutos = FonteProdutos;
        *FimProdutos = lento->proximo;
        lento->proximo = NULL;
    }
}

TipoApontadorProduto IntercalarListas(TipoApontadorProduto MetadeUm, TipoApontadorProduto MetadeDois)
{
    TipoApontadorProduto resultado = NULL;

    if (MetadeUm == NULL)
        return MetadeDois;
    else if (MetadeDois == NULL)
        return MetadeUm;

    if (MetadeUm->conteudo.cd_produto <= MetadeDois->conteudo.cd_produto)
    {
        resultado = MetadeUm;
        resultado->proximo = IntercalarListas(MetadeUm->proximo, MetadeDois);
    }
    else
    {
        resultado = MetadeDois;
        resultado->proximo = IntercalarListas(MetadeUm, MetadeDois->proximo);
    }
    return resultado;
}

void MergeSort(TipoApontadorProduto *Referencia)
{
    TipoApontadorProduto cabeca = *Referencia;
    TipoApontadorProduto MetadeUm, MetadeDois;

    if ((cabeca == NULL) || (cabeca->proximo == NULL))
    {
        return;
    }
    DividirListaProdutos(cabeca, &MetadeUm, &MetadeDois);

    MergeSort(&MetadeUm);
    MergeSort(&MetadeDois);

    *Referencia = IntercalarListas(MetadeUm, MetadeDois);
}

void ExibeOrdenadoCodigo(ListaProduto *ListaProdutosCodigo)
{
    MergeSort(&ListaProdutosCodigo->PrimeiroProduto->proximo);

    TipoApontadorProduto aux = ListaProdutosCodigo->PrimeiroProduto->proximo;
    while (aux != NULL)
    {
        printf("Codigo: %d, Descricao: %s\n", aux->conteudo.cd_produto, aux->conteudo.ds_produto);
        aux = aux->proximo;
    }
    RetornaMenu();
}

int LerEntradaInteiro(char *Mensagem)
{
    char entrada[100];
    int valido = 0, numero = 0;

    while (!valido)
    {
        MostraMSG(Mensagem);
        scanf("%s", entrada);

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

        if (!valido)
        {
            MostraMSG("Entrada inválida. Por favor, digite um número inteiro.\n");
        }
        else
        {
            numero = atoi(entrada);
        }
    }

    return numero;
}

void RetornaMenu()
{
    char ch;
    do
    {
        gotoxy(1, 22);
        printf("+------------------------------------------------------------------------------+\n");
        gotoxy(2, 23);
        printf("MSG.: Digite (R/r) para retornar ao menu: ");
        ch = getchar();
        ch = toupper(ch); // Converte para maiúsculo
    } while (ch != 'R');
}

void MenuInicio()
{
    boolean controle = TRUE;
    do
    {
        system("cls");
        TelaMenu();
        switch (LerEntradaInteiro("Digite sua opcao: "))
        {
        case 1:
            MenuProdutos();
            break;

        case 2:
            gotoxy(10, 20);
            printf("Encerrando o programa...\n");
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

void MenuProdutos()
{
    ListaProduto ListaSimplesProduto;
    IniciarListaProduto(&ListaSimplesProduto);
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
            CadastraProdutoFinal(&ListaSimplesProduto);
            break;

        case 2:
            CadastraProdutoInicio(&ListaSimplesProduto);
            break;

        case 3:
            CadastraProdutoPosicao(&ListaSimplesProduto);
            break;

        case 4:
            gotoxy(10, 20);
            printf("Remove no final produtos\n");
            ExcluiProdutoFinal(&ListaSimplesProduto);
            break;

        case 5:
            gotoxy(10, 20);
            printf("Remove na posicao\n");
            ExcluirProdutoPosicao(&ListaSimplesProduto);
            break;

        case 6:
            gotoxy(10, 20);
            printf("Remove no inicio\n");
            ExcluiProdutoInicio(&ListaSimplesProduto);
            break;

        case 7:
            MenuListaProdutos(&ListaSimplesProduto);
            break;

        case 8:
            gotoxy(10, 20);
            printf("Altera produto\n");
            break;

        case 9:
            gotoxy(10, 20);
            printf("Retornando ao menu inicial...\n");
            controle = FALSE;
            break;

        default:
            break;
        }
    } while (controle);
}

void MenuListaProdutos(ListaProduto *ListaSimplesProduto)
{
    int opcao;
    do
    {
        system("cls");
        TelaMenuConsultaProduto();
        opcao = LerEntradaInteiro("Digite sua opcao: ");

        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            ExibirProdutoFichario(ListaSimplesProduto);
            break;

        case 2:
            ExibeOrdenadoCodigo(ListaSimplesProduto);
            break;

        case 3:
            // ordem alfabetica
            break;

        case 4:
            ExibirProdutoCodigo(ListaSimplesProduto);
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

int main()
{
    MenuInicio();
    return 0;
}