Um array é um bloco de memória no qual você pode guardar tipos e structs de forma consecutiva. A sintaxe para criar um deles no C é `int a[10]`, sendo que `int` pode ser qualquer tipo de dado e o `10` é o tamanho que o array deve ter.

Porém, esses arrays tem um problema: eles tem tamanho fixo determinado em tempo de compilação, por causa disso não se pode ter mais ou menos do que 10 ints no array. Ainda assim existem casos em que não se sabe o tamanho que o array deve ter antes do programa rodar. Uma forma de contornar isso seria gerenciando quanta memória você precisa pro seu array chamando `malloc` e `realloc` para alocar e realocar memória dinâmica conforme necessário, mas lidar com eles diretamente é perigoso e favorável à erros.

Dessa forma no post de hoje vamos criar uma abstração chamada de Array Dinâmico que tem a mesma caracteristica de ter os itens consecutivos na memória, mas que automaticamente aumenta de tamanho conforme necessário.

Para começar vamos criar uma struct que vai armazenar os dados necessários.

```c
#include <stddef.h>
#include <stdint.h>

// Array Dinâmico, não deve ser alterado diretamente
typedef struct Array {
    size_t capacidade;      // Tamanho de memória alocada
    size_t tamanho;         // Quantidade de itens usados
    size_t _tamanho_do_item; // Tamanho em chars de cada item
    uint8_t*  _buffer;          // Bloco de memória
} Array;
```

Mas quando criarmos um Array os dados vão vir aleatórios e se tentarmos usá-lo vamos causar **undefined behavior** (comportamento indefinido), o que não é bom, já que siginifica que nenhuma garantia sobre o que vai acontecer pode ser feita. Por isso precisamos inicializa-lo para um padrão definido e previsivel.  Para fazer isso vamos criar uma função `Array_init`.


```c
// Inicializa um array para itens de tamanho especifico
void Array_init(Array* arr, size_t tamanho_do_item) {
    // Começa sem nenhum item
    arr->tamanho = 0;

    // Só inicializaremos o Array quando for necessário
    arr->_buffer = NULL;
    arr->capacidade = 0;

    // Tamanho que cada item ocupa na memória
    arr->_tamanho_do_item = tamanho_do_item;
}
```

Agora com uma inicialização padrão podemos tomar decisões que levem esse estado em conta. Por exemplo podemos checar se o buffer é `NULL` para saber se temos espaço para colocar os itens e multiplicar o `_tamanho_do_item` pela capacidade para saber o espaço real que estamos ocupando.

O próximo passo é começarmos a adicionar itens nesse array. Como nessa série de posts sobre estruturas de dados estamos optando por manter elas genéricas, vamos precisar receber um ponteiro ao invés do item em si, o que é mais chato, mas permite copiarmos quantos bytes precisarmos. E como definimos o tamanho do item na inicialização podemos assumir que é essa a quantidade de bytes que temos que copiar pro final do array. Vamos fazer isso com `memcpy()` que precisa da fonte, do destino e da quantidade à se copiar.

```c
#include <string.h>

// Adiciona um item de Array._tamanho_do_item ao final do array
void Array_add(Array* arr, const void* item) {
    // Pega a posição do final do array
    char* final_array = arr->_buffer + arr->tamanho * arr->_tamanho_do_item;

    // Copia o item para o final
    memcpy(final_array, item, arr->_tamanho_do_item);
}
```

O problema dessa implementação é que não estamos considerando o caso de o array não ter mais espaço disponivel. Vamos precisar de uma função que seja capaz de mudar a capacidade do array mantendo os itens e depois usá-la para alocar espaço conforme necessário.

Vamos criar a função `_Array_realloc` que vai usar a função `realloc` da biblioteca padrão do C para conseguir mais espaço e atualizar a capacidade.  Ela também vai precisar fazer uma checagem de erros básica para não invalidar o Array quando receber parametros inválidos.

```c
#include <malloc.h>
#include <stdio.h>

// Altera a capacidade do array
void _Array_realloc(Array* arr, size_t capacidade_alvo) {
    // A capacidade_alvo não pode ser menor que a quantidade atual de itens no array
    if (arr->tamanho > capacidade_alvo) {
        printf("ERRO: A capacidade_alvo {%zu} não pode ser menor que Array.tamanho {%zu}", capacidade_alvo, arr->tamanho);
        return;
    }

    // Realoca o buffer com a capacidade_alvo
    arr->_buffer = realloc(arr->_buffer, capacidade_alvo * arr->_tamanho_do_item);
    arr->capacidade = capacidade_alvo;

    // Se não tiver sido possível alocar memória, fecha o programa
    if (arr->_buffer == NULL && capacidade_alvo != 0) {
        printf("ERRO: Não foi possível alterar a capacidade do array");
        exit(-1);
    }
}
```

Perceba que podemos usar `realloc` diretamente, mesmo sem nunca termos usado `malloc`, isso porque quando `realloc` recebe o endereço `NULL` para realocar ele se comporta exatamente como `malloc` se comportaria, então não precisamos checar para ver se já alocamos uma vez antes de realocar, a biblioteca padrão já faz isso por nós.

Vamos voltar para a `Array_add` e fazer ela pedir mais espaço conforme necessário antes de escrever. Existem algumas formas de fazer isso, provavelmente você pensou em alocar mais 1 espaço para cada novo item adicionado. Isso é totalmente possível e é economico em memória.

```c
// Adiciona um item de Array._tamanho_do_item ao final do array
void Array_add(Array* arr, const void* item) {
    // Se toda a capacidade já estiver ocupada, aloque mais um espaço
    if (arr->tamanho == arr->capacidade)
        _Array_realloc(arr, arr->capacidade + 1);

    // Pega a posição do final do array
    char* final_array = arr->_buffer + arr->tamanho * arr->_tamanho_do_item;

    // Copia o item para o final
    memcpy(final_array, item, arr->_tamanho_do_item);

    // Aumenta o tamanho do Array
    arr->tamanho++;
}
```

Porém essas realocações são caras já que `malloc` é (relativamente) demorado e é necessário copiar todos os items. Além disso a complexidade algoritimica de adicionar um novo item se torna **O(n)** o que não é bom (vamos fazer um post sobre isso em breve).

Um jeito melhor de fazer as coisas, se você puder pagar pela memória, é com menos realocações que alocam mais. Por exemplo, se cada vez que o Array estiver cheio nós dobrarmos a capacidade, as vezes que precisamos mudar todos os itens de lugar vão ser menos e mais espalhadas pelo tempo. Com essa segunda abordagem temos uma complexidade de **tempo constante amortizado**, ou seja, distribuimos as operações mais custosas ao longo do tempo de forma que no geral nossa operação sempre demora o mesmo tempo.

Podemos fazer isso também de forma simples:

```c
// Adiciona um item de Array._tamanho_do_item ao final do array
void Array_add(Array* arr, const void* item) {
    // Se toda a capacidade já estiver ocupada, dobre a capacidade
    if (arr->tamanho == arr->capacidade)
        _Array_realloc(arr, 2 * arr->capacidade);

    // Pega a posição do final do array
    char* final_array = arr->_buffer + arr->tamanho * arr->_tamanho_do_item;

    // Copia o item para o final
    memcpy(final_array, item, arr->_tamanho_do_item);

    // Aumenta o tamanho do Array
    arr->tamanho++;
}
```

Mas nesse caso, como iniciamos nosso Array para capacidade 0, vamos sempre tentar alocar zero espaços (já que `2 * 0 = 0`) e vamos ter uma falha de segmentação. Então precisamos de um caso especial que lide com o Array no estado inicial.

```c
// Adiciona um item de Array._tamanho_do_item ao final do array
void Array_add(Array* arr, const void* item) {
    // Se a capacidade for 0, aloque 1 espaço
    if (arr->capacidade == 0)
        _Array_realloc(arr, 1);

    // Se toda a capacidade já estiver ocupada, dobre a capacidade
    else if (arr->tamanho == arr->capacidade)
        _Array_realloc(arr, 2 * arr->capacidade);

    // Pega a posição do final do array
    char* final_array = arr->_buffer + arr->tamanho * arr->_tamanho_do_item;

    // Copia o item para o final
    memcpy(final_array, item, arr->_tamanho_do_item);

    // Aumenta o tamanho do Array
    arr->tamanho++;
}
```

Também vamos precisar de uma função para ler um item com base no índice.

```c
// Lê um item do array
void* Array_get(Array* arr, size_t index) {
    // Não é possível ler fora do Array
    if (index >= arr->tamanho)
        return NULL;

    return arr->_buffer + index * arr->_tamanho_do_item;
}
```

E por último uma função para fazer a limpeza da memória do Array para quando tivermos terminado de usá-lo.

```c
// Limpa a memória do array
void Array_deinit(Array* arr) {
    free(arr->_buffer);
}
```

Vamos então criar um main que teste esse array dinâmico.

```c
#include <time.h>

int main() {
    srand(time(0));  // Seta o gerador de números aleatórios

    // Cria e inicializa um Array para guardar ints
    Array ints;
    Array_init(&ints, sizeof(int));

    // Define uma quantidade entre 1 e 10 de ints para adicionar
    size_t quantos_ints = rand() % 10 + 1;

    printf("Array começa com %zu ints e vamos adicionar %zu deles\n", ints.tamanho, quantos_ints);

    // Adiciona uns items aleatórios
    for (size_t i = 0; i < quantos_ints; ++i) {
        int temp = rand() % 100;  // Precisamos de uma váriavel temporária para podermos usar o endereço dela
        Array_add(&ints, &temp);
    }

    printf("Array agora tem %zu ints, que são: [", ints.tamanho);

    // Lemos e imprimimos cada item
    printf("%i", *(int*) Array_get(&ints, 0));

    for (size_t i = 1; i < ints.tamanho; ++i)
        printf(", %i", *(int*) Array_get(&ints, i));

    printf("]\n");

    Array_deinit(&ints);
}
```

E agora só testar!

```bash
$ gcc array.c -o array && ./array
Array começa com 0 ints e vamos adicionar 8 deles
Array agora tem 8 ints, que são: [83, 86, 77, 15, 93, 35, 86, 92]
```

Espero que você tenha se divertido com esse post e aprendido uma coisa ou duas.  Deixo um desafio para vocês de criar uma função que consiga remover um item do Array com base na posição dele. Uma implementação possível está lá no fim do post, deixe um comentário se tiver conseguido resolver sem ver a solução. Até semana que vêm!




Implementação possível de `Array_remove`
```c
// Remove um item do Array
void Array_remove(Array* arr, size_t index) {
    // Não é possível remover um item fora do Array
    if (index >= arr->tamanho)
        return;

    // Pega a posição do item para remover
    uint8_t* rem = arr->_buffer + index * arr->_tamanho_do_item;

    // Itens que vão sobreescrever o que vai ser removido
    uint8_t* itens = rem + arr->_tamanho_do_item;

    // Quantos bytes copiar
    size_t qnts = (arr->tamanho - index) * arr->_tamanho_do_item;

    // Sobreescreve
    memcpy(rem, itens, qnts);

    // Diminui o tamanho
    arr->tamanho--;
}
```
