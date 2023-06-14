/*
O programa simula uma m�quina de venda automatizada que permite aos usu�rios selecionar produtos, inserir dinheiro e receber o produto e o troco. Ele oferece modos de usu�rio e administrador, permitindo a compra de produtos, gerenciamento do estoque e exibi��o do faturamento.
*/

#include <iostream>
#include <string>

using namespace std;

#define MAX_PRODUTOS 10 // Tamanho m�ximo do Vetor de produtos. Deve-se ajustar o limite para adicionar mais produtos. N�o utilizei "Vetor din�mico" pois n�o domino esse conceito, ainda.

/*Fun��o 'exibirInvent�rio' tem como par�metros os vetores: nomes, precos e quantidades, que representam os nomes, pre�os e quantidades dos produtos, respectivamente.
O par�metro numProdutos representa o nr total de produtos no invent�rio.
O loop for perccorre todos os produtos e exibe suas informa��es: c�digo, nome, pre�o e quantidade e os imprime na tela.*/

void exibirInventario(const string nomes[], const double precos[], const int quantidades[], int numProdutos) {
    cout << "Invent�rio:\n";
    for (int i = 0; i < numProdutos; i++) {
        cout << "C�digo: " << i + 1 << " - " << nomes[i] << " - R$" << precos[i] << " - Quantidade: " << quantidades[i] << endl;
    }
}

/*Fun��o exibirFaturamento mostra o faturamento total da m�quina. Recebe como par�metro o valor do faturamento e o imprime na tela.*/

void exibirFaturamento(double faturamento) {
    cout << "Faturamento total: R$" << faturamento << endl;
}

/* Essa fun��o buscarProduto � respons�vel por buscar um produto pelo c�digo. Ela tem como par�metros o vetor nomes, o n�mero total de produtos e o c�digo do produto que se est� buscando.
A essa fun��o ser� retornado um valor que � o codigo do produto no vetor produtos (por isso � int e n�o void). Se o produto n�o for encontrado, o retorno da fun��o ser� -1 gerando a mensagem para o usu�rio */

int buscarProduto(const string nomes[], int numProdutos, int codigo) {
    for (int i = 0; i < numProdutos; i++) {
        if (i + 1 == codigo) {
            return i; // Retorna o �ndice do produto encontrado
        }
    }
    return -1; // Retorna -1 se o produto n�o foi encontrado
}
/*Essa fun��o � o modo usu�rio da maquina de venda. Recebe os par�metros nomes, pre�os e quantidades e o numero total de produtos e o faturamento total.
1� ela exibe o inventario dos produtos, depois solicita ao usu�rio que informe o codigo do produto desejado, faz a busca pelo produto, e, se o produto existe, est� dispon�vel e o dinheiro inserido � suficiente, ela retorna "Retire o produto", "Retire o troco" e atualiza o faturamento e a quantidade do produto. */

void modoUsuario(string nomes[], double precos[], int quantidades[], int numProdutos, double& faturamento) {
    cout << "Modo Usu�rio\n";

    exibirInventario(nomes, precos, quantidades, numProdutos);

    int codigoProduto;
    cout << "Digite o c�digo do produto desejado: ";
    cin >> codigoProduto;

    int indiceProduto = buscarProduto(nomes, numProdutos, codigoProduto);
    if (indiceProduto != -1) {
        if (quantidades[indiceProduto] > 0) {
            double valorInserido;
            cout << "Digite o valor inserido na m�quina: ";
            cin >> valorInserido;

            if (valorInserido >= precos[indiceProduto]) {
                cout << "Retire o produto: " << nomes[indiceProduto] << endl;
                cout << "Retire o troco: R$" << valorInserido - precos[indiceProduto] << endl;
                faturamento += precos[indiceProduto];
                quantidades[indiceProduto]--;
            } else {
                cout << "Valor insuficiente para comprar o produto.\n";
                cout << "Retire seu dinheiro de volta: R$" << valorInserido << endl;
            }
        } else {
            cout << "Produto indispon�vel no momento. Retire seu dinheiro de volta.\n";
        }
    } else {
        cout << "C�digo do produto inv�lido.\n";
    }
}

/* Essa fun��o � o modo administrador da m�quina de venda. Ele recebe os mesmos par�metros da fun��o modoUsuario. Ela exibe o inventario dos produtos e o faturamento total usando as fun��es exibirInventario e exibirFaturamento.*/


void modoAdministrador(string nomes[], double precos[], int quantidades[], int numProdutos, double faturamento) {
    cout << "Modo Administrador\n";

    exibirInventario(nomes, precos, quantidades, numProdutos);
    exibirFaturamento(faturamento);
}

/*Ponto de entrada do programa, fun��o main.
S�o declarados 3 vetores para armazenar os nomes, pre�os e quantidades dos produtos.
Tamb�m s�o declaradas vari�veis numProdutos (que representa o nr total de produtos) e faturamento (que rastreia o faturamento total).*/

int main() {
    string nomes[MAX_PRODUTOS] = {
        "Biscoito",
        "Chocolate",
        "Refrigerante",
        "Salgadinho",
        "�gua mineral",
        "Barra de cereal",
        "Iogurte",
        "Bebida energ�tica",
        "Chocolate branco"
    };
    double precos[MAX_PRODUTOS] = { 2.50, 3.0, 4.0, 2.50, 1.50, 3.00, 3.50, 4.50, 2.80 };
    int quantidades[MAX_PRODUTOS] = { 5, 10, 3, 5, 10, 5, 7, 3, 6 };
    int numProdutos = 9;
    double faturamento = 0.0;

    int modo; //vari�vel para armazenar a op��o selecionada pelo usu�rio no menu de sele��o de modos do programa

  //loop para o usu�rio selecionar o modo
  do {
        cout << "Selecione o modo:\n";
        cout << "1. Modo Usuario\n";
        cout << "2. Modo Administrador\n";
        cout << "0. Sair\n";
        cin >> modo;

        switch (modo) {
            case 1:
                modoUsuario(nomes, precos, quantidades, numProdutos, faturamento);
                break;
            case 2:
                modoAdministrador(nomes, precos, quantidades, numProdutos, faturamento);
                break;
            case 0:
                cout << "Saindo do programa...\n";
                break;
            default:
                cout << "Op��o inv�lida! Tente novamente.\n";
                break;
        }
    } while (modo != 0);

    return 0;
}
