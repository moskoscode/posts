Uma HashTable é uma estrutura de dados que permite associar chaves à valores.
Por exemplo: ao invés de acessar os items através das posições nas quais eles
foram guardados, você pode dar nomes à eles! Hoje vamos explorar uma
implementação básica desse conceito na linguagem de programação ubíqua: C.

A principal vantagem da hashtable nesses casos sobre um array simples no qual
você procura a chave que você quer (além da conveniência) é a *complexidade
algoritimica* (que é uma medida de o quão demorado fica com base na quantidade
de items guardados). Enquanto o array não ordenado tem complexidade de procura
`O(n)`, que significa que achar um item em um array com `n` itens é `n` vezes
mais demorado que em um array com apenas 1 item. Já a HashTable tem
complexidade média de `O(1)` (para uma boa hash e suficientes *buckets*), o que
significa que, idependente do número de itens, o tempo para achar um deles é o
mesmo. Na pratica isso permite que sejam guardadas milhões de informações sem
degradação significativa na performance.

Poderiamos usar esse tipo de estrutura para, por exemplo, no sistema de um
zoológico, associar os animais às comidas que eles devem receber. Ou ainda
associar os nomes das comidas à quantidade em estoque de cada uma delas. São
exatamente esses exemplos que vamos implementar hoje.

Uma HashTable é composta básicamente de uma função de hash (que computa um
valor para cada chave) e um array de listas ligadas (existem outras estruturas
possíveis). O funcionamento dela é usar a função de hash para computar um
indice no array para guardar um par de `chave + valor` e o coloca no fim da
lista linkada dessa posição para lidar com possíveis colisões de hash (quando
duas chaves diferentes tem a mesma hash). Já para fazer a procura de um item já
inserido, a hash é computada e se procura na lista correspondente.

Vamos começar criando uma `struct` para armazenar nossa função de hash e array.

```c
#include <stddef.h>

#define TAMANHO 128

typedef struct HashTable {
    Par* pares[TAMANHO];              // Listas ligadas
    size_t (*hash)(void*, size_t n);  // Função de hash
} HashTable;
```

Precisamos tambem definir o que é um par.

```c
#include <stddef.h>

#define TAMANHO 128

typedef struct Par {
    void* chave;     // Chave
    size_t chave_n;  // Tamanho da chave
    void* valor;     // Valor
    size_t valor_n;  // Tamanho do valor

    struct Par* proximo;  // Proxímo par da lista
} Par;

typedef struct HashTable {
    Par* pares[TAMANHO];            // Listas ligadas
    size_t (*hash)(void*, size_t);  // Função de hash
} HashTable;
```

Podemos definir uma função de hash simples (mas lerda) somando todos os `void*`
até `n` e pegando o resto pela divisão por `TAMANHO` (que nos dá uma posição no
array de pares).

```c
// [...] O resto do código até agora está aqui em cima

size_t hash_simples(void* dados, size_t n) {
    size_t ret = 0;

    for (; n > 0; --n)
        ret += *(unsigned char*)dados;  // Soma todos os dados

    return ret % TAMANHO;
}

```

O jeito canônico de indicar o fim de uma lista ligada é com um `NULL`, só que
em C novas structs e arrays tem valor indefinido (vem com lixo, basicamente),
por isso precisamos de uma função que faça a limpeza da nossa HashTable antes
de podermos usa-la

```c
// [...]

// Limpa a HashTable
void HashTable_init(HashTable* table) {
    for (size_t i = 0; i < TAMANHO; ++i) {
        table->pares[i] = NULL;
    }

    table->hash = hash_simples;  // Define nossa hash_simples como padrão
}

```

Então agora podemos criar uma função que adicione itens à HashTable, daquele
jeito que comentei antes: 1- Computa a hash da chave, 2- Procura a posição
certa na lista ligada (o fim, ou substitui o par antigo se a chave já tiver sido
adicionada) e 3- Adiciona o Par.

```c
// [...]

// Adiciona/Substitui items na HashTable
void HashTable_colocar(HashTable* table, const void* chave, size_t chave_n, const void* valor, size_t valor_n) {
    // 1- Computa a Hash da Chave
    size_t hash = table->hash(chave, chave_n);

    Par** par = &table->pares[hash];  // Lista para inserir

    // 2- Procura a posição certa na lista
    while (     *par != NULL                              // Enquanto existir um Par
            || (*par)->chave_n != chave_n                 // Ou o tamanho da chave for diferente
            || memcmp((*par)->chave, chave, chave_n) != 0 // Ou a chave for diferente
            ) {
        par = &(*par)->proximo;  // Avançe para o proximo par
    }

    // 3- Adiciona/Substitui par

    // Se precisamos adicionar um novo par
    if (*par == NULL) {
        *par = malloc(sizeof(Par));  // Aloca memoria para um novo par

        (*par)->chave = malloc( chave_n );  // Aloca memoria para a chave
        (*par)->chave_n = chave_n;

        (*par)->valor   = NULL;
        (*par)->valor_n =    0;

        (*par)->proximo = NULL;

        // Só precisamos copiar a chave se estamos adicionando um novo par,
        // fora isso a chave é a mesma de antes
        memcpy((*par)->chave, chave, chave_n);
    }

    // Libera a memoria do valor anterior (nada acontece se for NULL)
    free( (*par)->valor );

    (*par)->valor = malloc( valor_n );      // Aloca memoria para o valor
    memcpy((*par)->valor, valor, valor_n);  // Copia o valor
}

```

E antes de poder usar só precisamos de uma função para ler o valor guardado, é
um tanto parecida com a anterior, ela precisa: 1- Computar a Hash, 2- Achar o
par certo e 3- Retornar o `valor` e `valor_n` (por meio dos parametros de retorno)

```c
// [...]

// Lê items da HashTable e retorna se os encontrou ou não
int HashTable_ler(HashTable* table, const void* chave, size_t chave_n, void** valor, size_t* valor_n) {
    // 1- Computa a Hash da Chave
    size_t hash = table->hash(chave, chave_n);

    Par* par = table->pares[hash];  // Lista para inserir

    // 2- Procura a posição certa na lista
    while (    par != NULL                             // Enquanto existir um Par
            || par->chave_n != chave_n                 // Ou o tamanho da chave for diferente
            || memcmp(par->chave, chave, chave_n) != 0 // Ou a chave for diferente
            ) {
        par = par->proximo;  // Avançe para o proximo par
    }

    // 3- Copia o valor para as variaveis de retorno

    if (par == NULL)
        return 0;  // Chave não existe

    *valor = par->valor;
    *valor_n = par->valor_n;

    return 1;
}

```

Então agora podemos implementar nosso pseudo zoológico:

```c
int main() {
    HashTable anim_com;  // Animais e comidas
    HashTable_init(&anim_com);

    HashTable com_qt;   // Quantidade de comida
    HashTable_init(&com_qt);


    // Adiciona informações às tabelas
    const char* m = "macaco";
    const char* b = "banana";
    HashTable_colocar(&anim_com, m, strlen(m)+1, b, strlen(b)+1);    // Macaco come banana

    size_t b_q = 10;
    HashTable_colocar(&com_qt, b, strlen(b)+1, &b_q, sizeof(size_t));     // 10 bananas


    const char* g = "girafa";
    const char* a = "arvores altas";
    HashTable_colocar(&anim_com, g, strlen(g)+1, a, strlen(a)+1);    // Girafa come arvores altas

    size_t a_q = 3;
    HashTable_colocar(&com_qt, a, strlen(a)+1, &a_q, sizeof(size_t));     // 3 Árvores altas

    const char* c = "carro";
    const char* ga = "gasolina";
    HashTable_colocar(&anim_com, c, strlen(c)+1, ga, strlen(ga)+1);  // Carro come gasolina

    size_t ga_q = 7;
    HashTable_colocar(&com_qt, ga, strlen(ga)+1, &ga_q, sizeof(size_t));  // 7l de gasolina


    // Busca as informações
    const char* animal = "girafa";

    const char* comida = NULL;
    const size_t* quantidade = NULL;
    size_t s = 0;

    if (
        HashTable_ler(&anim_com, animal, strlen(animal)+1, (void**)&comida, &s) &&
        HashTable_ler(&com_qt  , comida, strlen(comida)+1, (void**)&quantidade, &s)) {

            printf("Animal: %s come %s, da qual temos %zi em estoque\n", animal, comida, *quantidade);
    } else {
            printf("Não possuimos do animal %s em nosso zoológico\n", animal);
    }
}
```

Você pode substituir o valor de `animal` para ver como as tabelas se comportam
com os outros animais (ou com animais inexistentes).

E sim, eu sei que a sintaxe não é das melhores, mas isso é por que estamos
usando C e sendo genéricos quanto ao tipo de chave/valor. Se fizessemos uma
tabela, por exemplo, especificamente com chaves e valores `char*`, poderiamos
omitir o tamanho da string já que poderiamos assumir que ela terminaria em
`'\0'`. Mas esse é um preço que se paga entre generalidade X usabilidade.

Espero que você tenha gostado e entendido nossa implementação, qualquer dúvida
nos mande um email ou deixe um comentário que tentarei responder o mais breve
possíve o mais breve possível. Até semana que vêm.

