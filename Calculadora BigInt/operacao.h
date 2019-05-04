#ifndef LISTAS_H
#define LISTAS_H
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


typedef struct BigInt BigInt; // definição da struct BigInt
typedef struct Noh Noh;       // definição da struct Noh
struct Noh{                   // dentro dessa mesma struct ha um elemento que eh uma nova instancia do mesmo tipo Noh
    int number;               // cada caracter informado sera lido e tratado como um unico digito
    struct Noh* next;         // instancia do mesmo tipo que a struct e essa apontara para o proximo digito
};
struct BigInt {
    struct Noh* head;         // head eh uma instancia do mesmo tipo Noh mas colocada dentro da estrutura BigInt
    char sinal;
};
BigInt* aloca(const char* value);// Cria uma nova “variavel” desse tipo
// (a string contem a cadeia de numeros
// como foi lida do usuario)
void desaloca(BigInt*);
// Libera a “variavel” da memoria
void imprime(const BigInt*); // Imprime o numero longo na tela
BigInt* copia(const BigInt*); // Operacao de atribuicao (copia)
bool igual(const BigInt*, const BigInt*); // big1 == big2
bool diferente(const BigInt*, const BigInt*); // big1 != big2
bool menor(const BigInt*, const BigInt*); // big1 < big2
bool maior(const BigInt*, const BigInt*); // big1 > big2
bool menor_igual(const BigInt*, const BigInt*); // big1 <= big2
bool maior_igual(const BigInt*, const BigInt*); // big1 >= big2
void oposto(BigInt*);
// Inverte o sinal do proprio numero
BigInt* soma(const BigInt*, const BigInt*); // big1 + big2
void incrementa_de(BigInt*, const BigInt*); // big1 += big2
BigInt* subtrai(const BigInt*, const BigInt*); // big1 – big2
void decrementa_de(BigInt*, const BigInt*); // big1 –= big2
BigInt* multiplica(const BigInt*, const BigInt*); // big1 * big2
BigInt* potencia(const BigInt*, const BigInt*); //
//Lista Encadeada
bool insertEnd(BigInt*,int);
bool insertStart(BigInt*,int);
bool testeValue(const char* value);
bool heZero (BigInt* N);
#endif // LISTAS_H0



//#ifndef LISTAS_H
