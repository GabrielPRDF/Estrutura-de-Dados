#include <operacao.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


BigInt* aloca(const char* value)
{
    BigInt* N = (BigInt*) malloc(sizeof(BigInt)); // alocado um espaço de memoria do mesmo tamanho que o tipo BigInt
    N->head= NULL;
    bool ig;
    ig = testeValue(value);
    if(ig == false){
        return N;
    }else{
        const char *pass; // vai separar por caracter para leitura
        int i;  // o valor convertido em int que vai para a função insert
        if(*value == '-'){ // verifica o primeiro caracter que se trata do sinal
            N->sinal = value[0]; // sinal armazenado no cabeçalho
            value++; //passa ao proximo elemento da string
        }else{
            if(*value == '+'){ // verifica o sinal positivo
                value++;
            }
            N->sinal = '+';
        }
        while (*value != '\0' ){ // le cada caracter passado como parametro ate o fim da string
            char get_char = *value;
            i = atoi(&get_char);      // i vai recebendo um caracter por vez para a inserção
            value++;
            insertStart(N, i);     // para cada valor lido passa por parametro na funcao insert a instancia do ponteiro que indica a cabeça
            // e o novo valor lido em i
        }
        return N; //retorna o ponteiro
    }
}

bool testeValue (const char* value){
    if(*value == '-'){
        value++;
    }else{
        if(*value == '+'){
            value++;
        }
    }
    const char *pass;
    while(*value != '\0'){
        pass = value;
        switch (*pass) {
        case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
            value++;
            break;
        default:
            return false;
            break;
        }
    }
    return true;
}

bool insertStart(BigInt* N, int value) { // inserção no inicio  
    if(N == NULL) { // caso seja nulo o endereço de p ele sai da funçao
        return false;
    }
    Noh* p = (Noh*) malloc(sizeof(Noh)); // instancia um ponteiro do tipo Noh alocando espaço em memoria do tamanho de Noh
    p->number = value;   // valor na posicao local do ponteiro recebe o parametro informado no funçao
    p->next = N->head;   // endereço do proximo ponteiro de p sera a cabeça do BigInt informado
    N->head = p; // a cabeça recebe o endereço do ponteiro p
    return true;
}

bool insertEnd (BigInt *N, int value){  // insere no final
    if (N == NULL) {
        return false;
    }
    Noh* p = (Noh*) malloc(sizeof(Noh));
    p->number = value; // armazena o valor passsado no parametro
    p->next = NULL;  // se vai ser o novo ultimo, entao seu proximo sera nulo, certo?, sim

    if (N->head == NULL) { // verifica se o endereço da cabeça e nulo
        N->head = p; //caso sim recebe o endereço de p
    }
    else {
        Noh* q = N->head;  // a cabeça nao sendo nula e feito uma instancia de Noh que recebe o endereço da cabeça
        while (q->next != NULL){ // enquanto essa instancia do Noh for diferente de nulo
            q = q->next;         // vai pulando ao proximo elemento
        }
        q->next = p; // quando encontrar um elemento next que esteja apontando para nulo que significa
    }                // conter endereço disponivel ele recebe o endereço de p
    return true;
}
void imprime(const BigInt* N){ // imprime o BigInt
    printf("Impressao do valor: ");
    if(N->head == NULL){
        printf("Numero NULO!!!\n");
    }else{
        BigInt* M = (BigInt*) malloc(sizeof(BigInt)); // declaração de outro BigInt alocando em memoria o tamanho do seu tipo
        M->head= NULL;
        Noh* i = N->head; // instanciando um ponteiro de Noh com o endereço da cabeça de N
        int aux = 0, ponto = 0;
        while(i != NULL){     // enquando o ponteiro i for diferente nulo(que significa ter algo em sua posicao)
            aux = i->number;  // a variavel auxiliar ira receber o valor do Noh de i que o tenha
            insertStart(M, aux); // insere no começo passando o digito da posicao
            i = i->next;  // i recebe o endereço de seu proximo No
        }
        printf("%c", N->sinal); // imprime o sinal no cabeçalho
        Noh* p = M->head; // declara um ponteiro de uma estrura do tipo Noh
        ponto++;
        while (p != NULL){
            if(ponto == 2){
                printf(".");
                ponto = 0;
            }else{
                ponto++;
            }
            printf("%u", p->number);  //enquanto  p estiver em um endereço diferente NULO
            p = p->next;            // vai imprimindo o valor de seu no e passando ao proximo elemento
        };
        printf("\n");
        desaloca(M); // devolve o espaço de memoria que foi alocado de M
    }
}

void desaloca(BigInt* N){
    while (N->head != NULL) { // euquando a cabeça estiver apontada para endereço diferente de nulo
        Noh* p = N->head;     // uma instancia do Noh sendo p local vai recebendo esse endereço
        N->head = p->next;    // a cabeça vai apontando ao proximo no
        free(p);              // liberando em memoria o espaço reservado do tamanho ocupado
    }
    free(N); // libera o espaço do tamanho do BigInt informado no parametro
}

BigInt* copia(const BigInt* N){  // copia o valor de um conjunto de digitos para outro conjunto
    BigInt* M = (BigInt*) malloc(sizeof(BigInt)); //instancia um BigINt
    M->head = NULL;   // aponta o endereço do Noh da cabeça do BigInt local para NULO
    if(N->head == NULL){
        return M;
    }
    M->sinal = N->sinal; // o sinal da novo BigInt instancia sera o mesmo passado no parametro de copia
    int aux = 0;
    Noh* p = N->head; // instancia um tipo Noh que recebe o endereço cabeça que eh outra estrutura
    while(p != NULL){  // enquanto a instancia do Noh estiver apontando para um endereço diferente de nulo a variavel auxiliar vai recebendo os valoresd de cada noh
        aux = p->number; // copia em uma variavel local para inserir em outro BigINt
        insertEnd(M, aux); // vai passando o valor coletado de cada no para o novo BIgInt
        p = p->next;  // p aponta para o proximo
    }
    return M; // retorna o conjunto copiado no novo BigINt
}

bool igual(const BigInt* N, const BigInt* M){
    if(N->head == NULL || M->head == NULL){
        printf("Numeros incorretos!!!\n");
        return false;
    }
    int contador1 = 0, contador2 = 0;
    Noh* p = N->head;
    Noh* j = M->head;
    if(N->sinal != M->sinal){ // verica o sinal das duas sentenças numericas no cabeçalho se sao diferentes
        return false;

    }else{                // sendo os sinais iguais prossegue
        /*while (p->next != NULL){ // enquanto o proximo no estiver apontando para algo diferente de null
            p = p->next;    // p aponta para o proximo no
            ++contador1;    // incrementa o contador
        }
        while (j->next != NULL){  // enquanto apontamento de proximo elemento de noh de j for diferente de nulo
            j = j->next;  // j aponta para o proximo noh
            ++contador2;  // incrementa o segundo contador indicando assim numero de digitos
        }*/
        //if(contador1 == contador2){  // verifica se os contadores sao iguais que significa o numero de digitos
            p = N->head;         // ambos p e j apontando para seus cabeçalhos
            j = M->head;
            while(p != NULL && j != NULL){ // sentro da condiçao de digitos iguais verifica se os ponteiros p e j sao diferentes de nulo
                if(p->number == j->number){  // enquanto isso for verdade verifica a igualdade no valor de cada noh
                    p = p->next;  // sendo isso comprovado segue apontando para o proximo elemento
                    j = j->next;
                }else{                     // se os valores dos nohs de p e j forem diferentes ja retorna false
                    return false;
                }
            }
            return true;

        /*}else{
            return false;
        }*/
    }

}

bool diferente(const BigInt* N, const BigInt* M){  // verifica se sao diferentes e retorna
    if(N->head == NULL || M->head == NULL){
        printf("Numeros incorretos!!!\n");
        return false;
    }else{
        bool ig;
        ig = igual(N,M);
        if(ig == true){
            return false;
        }else{
            return true;
        }
    }
}

BigInt* soma(const BigInt* N, const BigInt* M){
    if(N->head == NULL && M->head == NULL){
        BigInt* NEW2 = (BigInt*) malloc(sizeof(BigInt)); // alocado um espaço de memoria do mesmo tamanho que o tipo BigInt
        NEW2->head= NULL;
        printf("Numeros incorretos!!!\n");
        return NEW2;
    }
    if(N->sinal == '-'){
        if(M->sinal == '-'){
            BigInt* NEW = (BigInt*) malloc(sizeof(BigInt)); // alocado um espaço de memoria do mesmo tamanho que o tipo BigInt
            NEW->head= NULL;
            Noh* p = N->head;
            Noh* j = M->head;
            int aux, sobra = 0;
            while(p != NULL || j != NULL){ // enquanto p ou j forem diferentes de nulo o auxiliar recebe 0
                aux = 0;
                if(p != NULL){  // se p for diferente o auxiliar recebe o valor daquele noh e aponta para o proximo
                    aux = p->number;
                    p = p->next;

                    if(j != NULL){  // se dentro da comparacao de p for verificado que j eh diferente de nulo
                        aux += j->number;   // auxiliar vai somar o que possui nele com o valor do noh de j e aponta para o proximo
                        j = j->next;
                    }
                    aux = aux + sobra;  // auxiliar de soma recebe a soma + sobra

                    if(aux >= 10){      // se esse valor for maior ou igual a 10
                        aux = aux -10;  // auxiliar recebera ele menos subtraido de 10 [VERFIFICAR] aqui pode ficar numero negativo tornando as coisas estranhas
                        sobra = 1;      // e a sobra sera colocado 1
                    }else{              // se for menor que 10
                        sobra = 0;      // nao tem sobra para jogar a casa seguinte
                    }
                    insertEnd(NEW, aux); // insere no final da sentaçao um novo BigInt passando o aux como digito do noh
                    aux = 0;
                }else{                   // se p for nulo verfica tambem se j eh diferente de nulo
                    if(j != NULL){
                        aux += j->number;  // auxiliar de soma incrementa dele mesmo somado com o valor do noh atual
                        j = j->next;       // aponta para o proximo noh
                        aux += sobra;      // auxiliar incrementa dele mesmo mais a sobra
                        if(aux >= 10){
                            aux = aux -10;
                            sobra = 1;
                        }else{
                            sobra = 0;
                        }
                        insertEnd(NEW, aux);
                    }else{
                        if(sobra != 0){
                            insertEnd(NEW, sobra);
                            sobra = 0;
                        }
                    }

                }
            }
            if(sobra != 0){
                insertEnd(NEW, sobra);
                sobra = 0;
            }
            NEW->sinal ='-';
            return NEW;
        }else{
            BigInt* CP1 = (BigInt*) malloc(sizeof(BigInt)); // alocado um espaço de memoria do mesmo tamanho que o tipo BigInt
            CP1->head= NULL;  // a nova instancia BigInt tera sua cabeça apontada para nulo
            CP1 = copia(N);
            CP1->sinal = '+';
            BigInt* CP2 = (BigInt*) malloc(sizeof(BigInt)); // alocado um espaço de memoria do mesmo tamanho que o tipo BigInt
            CP2->head= NULL;  // a nova instancia BigInt tera sua cabeça apontada para nulo
            CP2 = copia(M);
            CP2->sinal = '+';
            BigInt* NEW = (BigInt*) malloc(sizeof(BigInt)); // alocado um espaço de memoria do mesmo tamanho que o tipo BigInt
            NEW->head= NULL;  // a nova instancia BigInt tera sua cabeça apontada para nulo
            NEW = subtrai(CP1,CP2); // retorna a subtração das copias locais
            desaloca(CP1);
            if(maior(CP1,CP2) == true){
                NEW->sinal = '-';
            }else{
                NEW->sinal = '+';
            }
            desaloca(CP2);
            retiraZero(NEW);
            return NEW;

        }
    }else{
        if(M->sinal == '-'){
            BigInt* CP1 = (BigInt*) malloc(sizeof(BigInt)); // alocado um espaço de memoria do mesmo tamanho que o tipo BigInt
            CP1->head= NULL;  // a nova instancia BigInt tera sua cabeça apontada para nulo
            CP1 = copia(N);
            CP1->sinal = '+';
            BigInt* CP2 = (BigInt*) malloc(sizeof(BigInt)); // alocado um espaço de memoria do mesmo tamanho que o tipo BigInt
            CP2->head= NULL;  // a nova instancia BigInt tera sua cabeça apontada para nulo
            CP2 = copia(M);
            CP2->sinal = '+';
            BigInt* NEW = (BigInt*) malloc(sizeof(BigInt)); // alocado um espaço de memoria do mesmo tamanho que o tipo BigInt
            NEW->head= NULL;  // a nova instancia BigInt tera sua cabeça apontada para nulo
            NEW = subtrai(CP1,CP2);
            if(maior(CP1,CP2) == true){
                NEW->sinal = '+';
            }else{
                NEW->sinal = '-';
            }
            desaloca(CP1);
            desaloca(CP2);
            retiraZero(NEW);
            retiraZero(NEW);
            return NEW;
        }else{
            BigInt* NEW = (BigInt*) malloc(sizeof(BigInt)); // alocado um espaço de memoria do mesmo tamanho que o tipo BigInt
            NEW->head= NULL;
            NEW->sinal = '+';
            Noh* p = N->head;
            Noh* j = M->head;
            int aux, sobra = 0;
            while(p != NULL || j != NULL){ // enquanto p ou j forem diferentes de nulo o auxiliar recebe 0
                aux = 0;
                if(p != NULL){  // se p for diferente o auxiliar recebe o valor daquele noh e aponta para o proximo
                    aux = p->number;
                    p = p->next;

                    if(j != NULL){  // se dentro da comparacao de p for verificado que j eh diferente de nulo
                        aux += j->number;   // auxiliar vai somar o que possui nele com o valor do noh de j e aponta para o proximo
                        j = j->next;
                    }
                    aux = aux + sobra;  // auxiliar de soma recebe a soma + sobra

                    if(aux >= 10){      // se esse valor for maior ou igual a 10
                        aux = aux -10;  // auxiliar recebera ele menos subtraido de 10 [VERFIFICAR] aqui pode ficar numero negativo tornando as coisas estranhas
                        sobra = 1;      // e a sobra sera colocado 1
                    }else{              // se for menor que 10
                        sobra = 0;      // nao tem sobra para jogar a casa seguinte
                    }
                    insertEnd(NEW, aux); // insere no final da sentaçao um novo BigInt passando o aux como digito do noh
                    aux = 0;
                }else{                   // se p for nulo verfica tambem se j eh diferente de nulo
                    if(j != NULL){
                        aux += j->number;  // auxiliar de soma incrementa dele mesmo somado com o valor do noh atual
                        j = j->next;       // aponta para o proximo noh
                        aux += sobra;      // auxiliar incrementa dele mesmo mais a sobra
                        if(aux >= 10){
                            aux = aux -10;
                            sobra = 1;
                        }else{
                            sobra = 0;
                        }
                        insertEnd(NEW, aux);
                    }else{
                        if(sobra != 0){
                            insertEnd(NEW, sobra);
                            sobra = 0;
                        }
                    }
                }
            }

            if(sobra != 0){
                insertEnd(NEW, sobra);
                sobra = 0;
            }
            return NEW;
        }
    }
}

BigInt* subtrai(const BigInt* N, const BigInt* M){
    if(N->head == NULL && M->head == NULL){
        BigInt* NEW2 = (BigInt*) malloc(sizeof(BigInt)); // alocado um espaço de memoria do mesmo tamanho que o tipo BigInt
        NEW2->head= NULL;
        printf("Numeros incorretos!!!\n");
        return NEW2;
    }
    if(N->sinal == '-'){
        if(M->sinal == '-'){
            BigInt* NEW = (BigInt*) malloc(sizeof(BigInt)); // alocado um espaço de memoria do mesmo tamanho que o tipo BigInt
            NEW->head= NULL;
            int menos = 0;
            Noh* p = M->head;
            Noh* j = N->head;
            int aux, falta = 0;
            while(p != NULL || j != NULL){
                if(p != NULL){
                    aux = p->number;
                    p = p->next;
                    aux = aux - falta;
                    falta = 0;
                    if(j != NULL){
                        if(j->number < aux){
                            aux = aux - j->number;
                        }else{
                            if(j->number == aux){
                                aux = 0;
                            }else{
                                if(p != NULL){
                                    aux = aux + 10;
                                    aux = aux - j->number;
                                    falta = 1;
                                }else{
                                    aux = j->number - aux;
                                    ++menos;
                                }
                            }
                        }
                        j = j->next;
                    }
                    insertEnd(NEW, aux);
                    aux = 0;
                }else{
                    if(j != NULL){
                        aux = j->number;
                        j = j->next;
                        insertEnd(NEW, aux);
                        menos++;
                    }
                }
            }
            if(menos > 0){
                NEW->sinal = '+';
            }else{
                NEW->sinal = '-';
            }
            retiraZero(NEW);
            return NEW;
        }else{
            BigInt* CP1 = (BigInt*) malloc(sizeof(BigInt)); // alocado um espaço de memoria do mesmo tamanho que o tipo BigInt
            CP1->head= NULL;  // a nova instancia BigInt tera sua cabeça apontada para nulo
            CP1 = copia(M);
            CP1->sinal = '+';
            BigInt* CP2 = (BigInt*) malloc(sizeof(BigInt)); // alocado um espaço de memoria do mesmo tamanho que o tipo BigInt
            CP2->head= NULL;  // a nova instancia BigInt tera sua cabeça apontada para nulo
            CP2 = copia(N);
            CP2->sinal = '+';
            BigInt* NEW = (BigInt*) malloc(sizeof(BigInt)); // alocado um espaço de memoria do mesmo tamanho que o tipo BigInt
            NEW->head= NULL;  // a nova instancia BigInt tera sua cabeça apontada para nulo
            NEW = soma(CP1,CP2);
            desaloca(CP1);
            desaloca(CP2);
            NEW->sinal = '-';
            return NEW;
        }
    }else{
        if(M->sinal == '-'){
            BigInt* CP1 = (BigInt*) malloc(sizeof(BigInt)); // alocado um espaço de memoria do mesmo tamanho que o tipo BigInt
            CP1->head= NULL;  // a nova instancia BigInt tera sua cabeça apontada para nulo
            CP1 = copia(N);
            CP1->sinal = '+';
            BigInt* CP2 = (BigInt*) malloc(sizeof(BigInt)); // alocado um espaço de memoria do mesmo tamanho que o tipo BigInt
            CP2->head= NULL;  // a nova instancia BigInt tera sua cabeça apontada para nulo
            CP2 = copia(M);
            CP2->sinal = '+';
            BigInt* NEW = (BigInt*) malloc(sizeof(BigInt)); // alocado um espaço de memoria do mesmo tamanho que o tipo BigInt
            NEW->head= NULL;  // a nova instancia BigInt tera sua cabeça apontada para nulo
            NEW = soma(CP1,CP2);
            desaloca(CP1);
            desaloca(CP2);
            NEW->sinal = '+';
            return NEW;
        }else{
            BigInt* CP1 = (BigInt*) malloc(sizeof(BigInt)); // alocado um espaço de memoria do mesmo tamanho que o tipo BigInt
            CP1->head= NULL;  // a nova instancia BigInt tera sua cabeça apontada para nulo
            CP1 = copia(N);
            CP1->sinal = '+';
            BigInt* CP2 = (BigInt*) malloc(sizeof(BigInt)); // alocado um espaço de memoria do mesmo tamanho que o tipo BigInt
            CP2->head= NULL;  // a nova instancia BigInt tera sua cabeça apontada para nulo
            CP2 = copia(M);
            CP2->sinal = '+';
            BigInt* NEW = (BigInt*) malloc(sizeof(BigInt)); // alocado um espaço de memoria do mesmo tamanho que o tipo BigInt
            NEW->head= NULL;
            Noh* p;
            Noh* j;
            if(maior(CP1,CP2) == true){
                p = N->head;
                j = M->head;
                NEW->sinal = '+';
            }else{
                p = M->head;
                j = N->head;
                NEW->sinal = '-';
            }
            desaloca(CP1);
            desaloca(CP2);
            int menos = 0;
            int aux, falta = 0;
            while(p != NULL || j != NULL){
                if(p != NULL){
                    aux = p->number;
                    p = p->next;
                    aux = aux - falta;
                    falta = 0;
                    if(j != NULL){
                        if(j->number < aux){
                            aux = aux - j->number;
                        }else{
                            if(j->number == aux){
                                aux = 0;
                            }else{
                                if(p != NULL){
                                    aux = aux + 10;
                                    aux = aux - j->number;
                                    falta = 1;
                                }else{
                                    aux = j->number - aux;
                                }
                            }
                        }
                        j = j->next;
                    }else{
                        if(aux < 0){
                            if(p != NULL){
                                aux = 10 + aux;
                                falta = 1;
                            }
                        }
                    }
                    insertEnd(NEW, aux);
                    aux = 0;
                }else{
                    if(j != NULL){
                        aux = j->number;
                        j = j->next;
                        insertEnd(NEW, aux);
                    }
                }
            }
            retiraZero(NEW);
            return NEW;
        }
    }
}

void incrementa_de(BigInt* N, const BigInt* M){
    if(N->head == NULL && M->head == NULL){
        printf("Parametros INCORRETOS!!!\n");
    }else{
        BigInt* CP1 = (BigInt*) malloc(sizeof(BigInt)); // alocado um espaço de memoria do mesmo tamanho que o tipo BigInt
        CP1->head= NULL;
        BigInt* CP2 = (BigInt*) malloc(sizeof(BigInt)); // alocado um espaço de memoria do mesmo tamanho que o tipo BigInt
        CP2->head= NULL;
        BigInt* NEW = (BigInt*) malloc(sizeof(BigInt)); // alocado um espaço de memoria do mesmo tamanho que o tipo BigInt
        NEW->head= NULL;
        if(N->sinal == '-'){
            if(M->sinal == '-'){
                CP1 = copia(N);
                CP1->sinal = '+';
                CP2 = copia(M);
                CP2->sinal = '+';
                NEW = soma(CP1,CP2);
                desaloca(CP1);
                desaloca(CP2);
                desaloca(N);
                N = copia(NEW);
                N->sinal = '-';
                desaloca(NEW);
            }else{
                CP1 = copia(N);
                CP1->sinal = '+';
                CP2 = copia(M);
                CP2->sinal = '+';
                NEW = subtrai(CP1,CP2);
                if(maior(CP1,CP2) == true){
                    NEW->sinal = '-';
                }else{
                    NEW->sinal = '+';
                }
                desaloca(CP1);
                desaloca(CP2);
                desaloca(N);
                N = copia(NEW);

                desaloca(NEW);
             }
        }else{
            if(M->sinal == '-'){
                CP1 = copia(N);
                CP1->sinal = '+';
                CP2 = copia(M);
                CP2->sinal = '+';
                NEW = subtrai(CP1,CP2);
                if(maior(CP1,CP2) == true){
                    NEW->sinal = '+';
                }else{
                    NEW->sinal = '-';
                }
                desaloca(CP1);
                desaloca(CP2);
                desaloca(N);
                N = copia(NEW);
                desaloca(NEW);
            }else{
                CP1 = copia(N);
                CP1->sinal = '+';
                CP2 = copia(M);
                CP2->sinal = '+';
                NEW = soma(CP1,CP2);
                desaloca(CP1);
                desaloca(CP2);
                desaloca(N);
                N = copia(NEW);
                desaloca(NEW);
            }
        }
    }
}

void decrementa_de(BigInt* N, const BigInt* M){
    if(N->head == NULL && M->head == NULL){
        printf("Parametros INCORRETOS!!!\n");
    }else{
        BigInt* CP1 = (BigInt*) malloc(sizeof(BigInt)); // alocado um espaço de memoria do mesmo tamanho que o tipo BigInt
        CP1->head= NULL;
        BigInt* CP2 = (BigInt*) malloc(sizeof(BigInt)); // alocado um espaço de memoria do mesmo tamanho que o tipo BigInt
        CP2->head= NULL;
        BigInt* NEW = (BigInt*) malloc(sizeof(BigInt)); // alocado um espaço de memoria do mesmo tamanho que o tipo BigInt
        NEW->head= NULL;
        if(N->sinal == '-'){
            if(M->sinal == '-'){
                CP1 = copia(M);
                CP1->sinal = '+';
                CP2 = copia(N);
                CP2->sinal = '+';
                NEW = subtrai(CP1,CP2);
                if(maior(CP1,CP2) == true){
                    NEW->sinal = '+';
                }else{
                    NEW->sinal = '-';
                }
                desaloca(CP1);
                desaloca(CP2);
                desaloca(N);
                N = copia(NEW);
                desaloca(NEW);
            }else{
                CP1 = copia(N);
                CP1->sinal = '+';
                CP2 = copia(M);
                CP2->sinal = '+';
                NEW = soma(CP1,CP2);
                desaloca(CP1);
                desaloca(CP2);
                desaloca(N);
                N = copia(NEW);
                N->sinal = '-';
                desaloca(NEW);
            }
        }else{
            if(M->sinal == '-'){
                CP1 = copia(N);
                CP1->sinal = '+';
                CP2 = copia(M);
                CP2->sinal = '+';
                NEW = soma(CP1,CP2);
                desaloca(CP1);
                desaloca(CP2);
                desaloca(N);
                N = copia(NEW);
                desaloca(NEW);
            }else{
                CP1 = copia(N);
                CP1->sinal = '+';
                CP2 = copia(M);
                CP2->sinal = '+';
                NEW = subtrai(CP1,CP2);
                if(maior(CP1,CP2) == true){
                    NEW->sinal = '+';
                }else{
                    NEW->sinal = '-';
                }
                desaloca(CP1);
                desaloca(CP2);
                desaloca(N);
                N = copia(NEW);
                desaloca(NEW);
            }
        }
    }
}
bool menor(const BigInt* N, const BigInt* M){
    if(N->head == NULL || M->head == NULL){
        printf("PARAMETROS INCORRETOS!!!\n");
    }else{
        if(N->sinal == '-'){
            if(M->sinal == '-'){
                BigInt* CP1 = (BigInt*) malloc(sizeof(BigInt)); // alocado um espaço de memoria do mesmo tamanho que o tipo BigInt
                CP1->head= NULL;  // a nova instancia BigInt tera sua cabeça apontada para nulo
                CP1 = copia(N);
                CP1->sinal = '+'; // coloca o sinal do BigInt local como positivo
                BigInt* CP2 = (BigInt*) malloc(sizeof(BigInt)); // alocado um espaço de memoria do mesmo tamanho que o tipo BigInt
                CP2->head= NULL;  // a nova instancia BigInt tera sua cabeça apontada para nulo
                CP2 = copia(M);
                CP2->sinal = '+';
                bool ig;
                ig = maior(CP1,CP2); // verifica entre as copias locais se primeira e maior que a segunda
                desaloca(CP1);
                desaloca(CP2); // desaloca depois do uso
                return ig;
            }else{
                return true;
            }
        }else{
            if(M->sinal == '-'){
                return false;
            }else{
                Noh* p = N->head;
                Noh* j = M->head;
                int contador1 = 0, contador2 = 0, i = 0, aux = 0;
                while (p->next != NULL){
                    p = p->next;
                    ++contador1;
                }
                while (j->next != NULL){
                    j = j->next;
                    ++contador2;
                }
                if(contador1 > contador2){
                    return false;
                }else{
                    if (contador1 < contador2){
                        return true;
                    }else{
                        p = N->head;
                        j = M->head;
                        while(contador1 != 0){
                            while(i < contador1){
                                p = p->next;
                                j = j->next;
                                i++;
                            }

                            if(p->number == j->number){
                                aux++;
                            }
                            if(p->number > j->number){
                                return false;

                            }else{
                                p = N->head;
                                j = M->head;
                                --contador1;
                                i = 0;
                            }
                        }
                    }
                }
                if(aux == contador2){
                    return false;
                }else{
                    return true;
                }
            }
        }
    }
}

bool maior(const BigInt* N, const BigInt* M){
    if(N->head == NULL || M->head == NULL){
        printf("PARAMETROS INCORRETOS!!!\n");
    }else{
        if(N->sinal == '-'){
            if(M->sinal == '-'){
                BigInt* CP1 = (BigInt*) malloc(sizeof(BigInt)); // alocado um espaço de memoria do mesmo tamanho que o tipo BigInt
                CP1->head= NULL;  // a nova instancia BigInt tera sua cabeça apontada para nulo
                CP1 = copia(N);
                CP1->sinal = '+';
                BigInt* CP2 = (BigInt*) malloc(sizeof(BigInt)); // alocado um espaço de memoria do mesmo tamanho que o tipo BigInt
                CP2->head= NULL;  // a nova instancia BigInt tera sua cabeça apontada para nulo
                CP2 = copia(M);
                CP2->sinal = '+';
                bool ig;
                ig = menor(CP1,CP2);
                desaloca(CP1);
                desaloca(CP2);
                return ig;
            }else{
                return false;
            }
        }else{
            if(M->sinal == '-'){
                return true;
            }else{
                Noh* p = N->head;
                Noh* j = M->head;
                int contador1 = 0, contador2 = 0, i = 0, aux = 0;
                while (p->next != NULL){
                    p = p->next;
                    ++contador1;
                }
                while (j->next != NULL){
                    j = j->next;
                    ++contador2;
                }
                if(contador1 > contador2){
                    return true;
                }else{
                    if (contador1 < contador2){
                        return false;
                    }else{
                        p = N->head;
                        j = M->head;
                        while(contador1 != 0){
                            while(i < contador1){
                                p = p->next;
                                j = j->next;
                                i++;
                            }
                            if(p->number == j->number){
                                aux++;
                            }
                            if(p->number > j->number){
                                return true;
                            }else{
                                p = N->head;
                                j = M->head;
                                --contador1;
                                i = 0;
                            }
                        }
                    }
                }
                if(aux == contador2){
                    return false;
                }else{
                    return false;
                }
            }
        }
    }
}

bool menor_igual(const BigInt* N, const BigInt* M){
    if(N->head == NULL || M->head == NULL){
        printf("PARAMETROS INCORRETOS!!!\n");
        return false;
    }else{
        if(igual(N,M) == true || menor(N,M) == true)
            return true;
        else
            return false;
    }
}
bool maior_igual(const BigInt* N, const BigInt* M){
    if(N->head == NULL || M->head == NULL){
        printf("PARAMETROS INCORRETOS!!!\n");
        return false;
    }else{
        if(igual(N,M) == true || maior(N,M) == true)
            return true;
        else
            return false;
    }
}

BigInt*potencia(const BigInt* N, const BigInt* M) // realiza a operacao de potencia do valor numerico da primeira lista pela segunda
{
    if(N->head == NULL || M->head == NULL /*|| M->sinal == '-' */){  // faz a checagem para ver se foi passado vazio nos capos de BigInt
        BigInt* poten =(BigInt*) malloc(sizeof(BigInt));
        poten->head = NULL;
        poten->sinal = '+';
        return poten;
    }else{  //senao forem vazios prossegue
        BigInt* poten =(BigInt*) malloc(sizeof(BigInt));
        poten->head = NULL;
        poten = copia(M);  // copia o numero do expoente
        poten->sinal = '+'; // determina o sinal resultante como positivo
        if(heZero(poten) == true){  // verifica se seu ultimo digito eh zero
            BigInt* Result =(BigInt*) malloc(sizeof(BigInt));  // instancia um BigInt para guardar o resultado
            Result->head = NULL;
            Result->sinal = '+';
            insertEnd(Result, 1);  // insere no final da sentença numerica
            //printf("Acho que nao vai rolar um segmentation fault \n");
            return Result;
        }else{  // se nao for zero ou ultimo numero da sentença
            BigInt* valor =(BigInt*) malloc(sizeof(BigInt));  // instancia outro BigInt
            valor->head = NULL;
            valor->sinal = '+';
            insertEnd(valor, 1); // serere 1 no final da sentença do novo BigInt
            decrementa_de(poten, valor); // decrementa o numero que estiver em valor de poten
            return (multiplica(N,potencia(N, poten))); // multiplica resursivamente o resultado da potencia de N por potenc pelo proprio N
        }
    }

}

BigInt* multiplica(const BigInt* N, const BigInt* M){
    if(N->head == NULL && M->head == NULL){   // verifica se a cabeça dos dois BigInt sao invalidos apontando para nulo
        BigInt* NEW2 = (BigInt*) malloc(sizeof(BigInt)); // alocado um espaço de memoria para um novo BigInt
        NEW2->head= NULL; // esse novo tambem nulo na cabeça
        printf("Numeros incorretos!!!\n");
        return NEW2;
    }else{ // senao forem invalidos
        BigInt* NEW = (BigInt*) malloc(sizeof(BigInt)); // alocado um espaço de memoria do mesmo tamanho que o tipo BigInt
        NEW->head= NULL;
        Noh* p = N->head; // o novo noh recebe o endereço da cabeça
        int sin = p->number; // pega o digito
        float sinFinal = sin % 2;  // ultimo digito recebe o resto da divisao por 2
        NEW->sinal = '+';
        Noh* j = M->head; // a instancia do Noh recebe o endereço da cabeça do segundo BigInt
        int multi, sobra = 0, aux = 0;
        int auxZERO = 0, zeroLeft = 0;
        while(p != NULL){ // enquanto o primeiro BigINt for diferente de nulo
            multi = p->number; // vai coletando os digitos do primeiro BigiInt
            p = p->next; // apontando para o proximo noh
            BigInt* NEWAUX = (BigInt*) malloc(sizeof(BigInt)); // alocado um espaço de memoria do mesmo tamanho que o tipo BigInt
            NEWAUX->head = NULL;  //aponta para nulo a cabeça do BigInt auxiliar na operacao
            NEWAUX->sinal = '+'; // digito permaneceo o mesmo definido acima
            while(j != NULL){    // verificado se a objeto instanciado do Noh do segundo BigInt esta apontando para algum lugar
                aux = multi * j->number; // sendo isso afirmativo a variavel axuliar recebe a multiplicação do digito coletado do
                aux += sobra;            // primeiro BigInt pelo segundo da mesma casa , entao incrementado dele mesmo + sobra
                sobra = 0; // depois da operacao reset o valor em 0 da sobra
                while(aux >= 10){ // enquanto o auxiliar for menor ou igual a 10
                    aux -= 10;    // recebe ele mesmo decrementando 10
                    ++sobra;      // incrementa mais um a sobra
                }
                insertEnd(NEWAUX, aux); //insere no fim do novo BigInt o valor resultante aux
                j = j->next; // apontando para o proximo noh
            }
            if(sobra != 0){
                insertEnd(NEWAUX, sobra);
                sobra = 0;
            }
            if(auxZERO >= 0){
                int a = 0;
                while(a != auxZERO){
                    insertStart(NEWAUX, zeroLeft);
                    ++a;
                }
            }
            incrementa_de(NEW, NEWAUX);
            desaloca(NEWAUX);
            j = M->head;
            auxZERO++;
        }
        if(N->sinal == '-'){
            if(M->sinal == '-'){
                NEW->sinal = '+';
            }else{
                NEW->sinal = '-';
            }
        }else{
            if(M->sinal == '-'){
                NEW->sinal = '-';
            }else{
                NEW->sinal = '+';
            }
        }
        return NEW;
    }
}
void oposto(BigInt* N){ // inverte o sinal do BigInt
    if(N->head == NULL){  // verifica se a instancia de Noh esta apontando para nulo,se for entao nao existe numero
        printf("Parametro INCORRETO!!!\n");
    }else{  // senao for nulo entao significa que temos digitos no BigInt
        if(N->sinal == '-'){  // check o sinal e transforma em oposto
            N->sinal = '+';
        }else{
            N->sinal = '-';
        }
    }
}

void retiraZero (BigInt* N){ // retira o excesso de zeros
    Noh* p = N->head;  // instancia um noh que possui o endereço de memoria do cabelho do BigInt
    Noh* ant = p;  // outra instancia que sera igual a primeira
    while(p != N){  // enquanto p for diferente de N que significa que existe mudança na instancia local com o BigINt passado por parametro
        while(p->next != NULL){  // verifica na instancia local de bigInt se seu proximo elemento nao eh nulo
            ant = p;            // se nao for nulo anterior pega o endereço de p
            p = p->next;        // p vai receber o endereço do seu proximo noh, uma forma de deslocamento
        }
        if(p->number == 0){  // se o digito do noh for 0
            if(p != N->head){    // verifica se a instancia eh diferente de N
                ant->next = NULL; // se for, o proximo do anterior que seria a si mesmo vira nulo
                ant = p; // anterior recebe p
                free(ant); // libera anterior
                p = N->head; //
            }else{
                break;
            }
        }else{
            break;
        }
    }
}

bool heZero (BigInt* N){  // funcao para verificao se existe um digito zero no Noh e apos isso tem algum NULO, se for significa ser o ultimo
    Noh* p = N->head;  // a instancia do noh pega o endereço do cabeçalho do BigInt
    if(p->number == 0){
        if(p->next == NULL){
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}
