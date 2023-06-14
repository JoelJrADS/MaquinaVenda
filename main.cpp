/*
O programa simula uma máquina de venda automatizada que permite aos usuários selecionar produtos, inserir dinheiro e receber o produto e o troco. Ele oferece modos de usuário e administrador, permitindo a compra de produtos, gerenciamento do estoque e exibição do faturamento.
*/

#include <iostream>
#include <string>

using namespace std;

#define MAX_PRODUTOS 10 // Tamanho máximo do Vetor de produtos. Deve-se ajustar o limite para adicionar mais produtos. Não utilizei "Vetor dinâmico" pois não domino esse conceito, ainda.

/*Função 'exibirInventário' tem como parâmetros os vetores: nomes, precos e quantidades, que representam os nomes, preços e quantidades dos produtos, respectivamente.
O parâmetro numProdutos representa o nr total de produtos no inventário.
O loop for perccorre todos os produtos e exibe suas informações: código, nome, preço e quantidade e os imprime na tela.*/

void exibirInventario(const string nomes[], const double precos[], const int quantidades[], int numProdutos) {
    cout << "Inventário:\n";
    for (int i = 0; i < numProdutos; i++) {
        cout << "Código: " << i + 1 << " - " << nomes[i] << " - R$" << precos[i] << " - Quantidade: " << quantidades[i] << endl;
    }
}

/*Função exibirFaturamento mostra o faturamento total da máquina. Recebe como parâmetro o valor do faturamento e o imprime na tela.*/

void exibirFaturamento(double faturamento) {
    cout << "Faturamento total: R$" << faturamento << endl;
}

/* Essa função buscarProduto é responsável por buscar um produto pelo código. Ela tem como parâmetros o vetor nomes, o número total de produtos e o código do produto que se está buscando.
A essa função será retornado um valor que é o codigo do produto no vetor produtos (por isso é int e não void). Se o produto não for encontrado, o retorno da função será -1 gerando a mensagem para o usuário */

int buscarProduto(const string nomes[], int numProdutos, int codigo) {
    for (int i = 0; i < numProdutos; i++) {
        if (i + 1 == codigo) {
            return i; // Retorna o índice do produto encontrado
        }
    }
    return -1; // Retorna -1 se o produto não foi encontrado
}
/*Essa função é o modo usuário da maquina de venda. Recebe os parâmetros nomes, preços e quantidades e o numero total de produtos e o faturamento total.
1º ela exibe o inventario dos produtos, depois solicita ao usuário que informe o codigo do produto desejado, faz a busca pelo produto, e, se o produto existe, está disponível e o dinheiro inserido é suficiente, ela retorna "Retire o produto", "Retire o troco" e atualiza o faturamento e a quantidade do produto. */

void modoUsuario(string nomes[], double precos[], int quantidades[], int numProdutos, double& faturamento) {
    cout << "Modo Usuário\n";

    exibirInventario(nomes, precos, quantidades, numProdutos);

    int codigoProduto;
    cout << "Digite o código do produto desejado: ";
    cin >> codigoProduto;

    int indiceProduto = buscarProduto(nomes, numProdutos, codigoProduto);
    if (indiceProduto != -1) {
        if (quantidades[indiceProduto] > 0) {
            double valorInserido;
            cout << "Digite o valor inserido na máquina: ";
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
            cout << "Produto indisponível no momento. Retire seu dinheiro de volta.\n";
        }
    } else {
        cout << "Código do produto inválido.\n";
    }
}

/* Essa função é o modo administrador da máquina de venda. Ele recebe os mesmos parâmetros da função modoUsuario. Ela exibe o inventario dos produtos e o faturamento total usando as funções exibirInventario e exibirFaturamento.*/


void modoAdministrador(string nomes[], double precos[], int quantidades[], int numProdutos, double faturamento) {
    cout << "Modo Administrador\n";

    exibirInventario(nomes, precos, quantidades, numProdutos);
    exibirFaturamento(faturamento);
}

/*Ponto de entrada do programa, função main.
São declarados 3 vetores para armazenar os nomes, preços e quantidades dos produtos.
Também são declaradas variáveis numProdutos (que representa o nr total de produtos) e faturamento (que rastreia o faturamento total).*/

int main() {
    string nomes[MAX_PRODUTOS] = {
        "Biscoito",
        "Chocolate",
        "Refrigerante",
        "Salgadinho",
        "Água mineral",
        "Barra de cereal",
        "Iogurte",
        "Bebida energética",
        "Chocolate branco"
    };
    double precos[MAX_PRODUTOS] = { 2.50, 3.0, 4.0, 2.50, 1.50, 3.00, 3.50, 4.50, 2.80 };
    int quantidades[MAX_PRODUTOS] = { 5, 10, 3, 5, 10, 5, 7, 3, 6 };
    int numProdutos = 9;
    double faturamento = 0.0;

    int modo; //variável para armazenar a opção selecionada pelo usuário no menu de seleção de modos do programa

  //loop para o usuário selecionar o modo
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
                cout << "Opção inválida! Tente novamente.\n";
                break;
        }
    } while (modo != 0);

    return 0;
}
