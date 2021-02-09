Um array é um bloco de memória no qual você pode guardar tipos e structs de
forma consecutiva. A sintaxe para criar um deles no C é `int a[10]`, sendo que
`int` pode ser qualquer tipo de dado e o `10` é o tamanho que o array deve ter.

Porém, esses arrays tem um problema: eles tem tamanho fixo determinado em tempo
de compilação, por causa disso não se pode ter mais ou menos do que 10 ints no
array. Ainda assim existem casos em que não se sabe o tamanho que o array deve
ter antes do programa rodar. Uma forma de contornar isso seria gerenciando
quanta memória você precisa pro seu array chamando `malloc` e `realloc` para
alocar e realocar memória dinâmica conforme necessário, mas lidar com eles
diretamente é perigoso e favorável à erros.

Dessa forma no post de hoje vamos criar uma abstração chamada de Array Dinâmico
que tem a mesma caracteristica de ter os itens consecutivos na memória, mas que
automaticamente aumenta de tamanho conforme necessário.

Para começar vamos criar uma struct que vai armazenar os dados necessários.

```c
#include <stddef.h>

// Array Dinâmico, não deve ser alterado diretamente
typedef struct Array {
    size_t capacidade;      // Tamanho de memória alocada
    size_t tamanho;         // Quantidade de itens usados
    size_t _tamanho_do_item; // Tamanho em chars de cada item
    uint8_t*  _buffer;          // Bloco de memória
} Array;
```

Mas quando criarmos um Array os dados vão vir aleatórios e se tentarmos usá-lo
vamos causar **undefined behavior** (comportamento indefinido), o que não é
bom, já que siginifica que nenhuma garantia sobre o que vai acontecer pode ser
feita. Por isso precisamos inicializa-lo para um padrão definido e previsivel.
Para fazer isso vamos criar uma função `Array_init`.


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

Agora com uma inicialização padrão podemos tomar decisões que levem esse estado
em conta. Por exemplo podemos checar se o buffer é `NULL` para saber se temos
espaço para colocar os itens e multiplicar o `_tamanho_do_item` pela capacidade
para saber o espaço real que estamos ocupando.

O próximo passo é começarmos a adicionar itens nesse array. Como nessa série de
posts sobre estruturas de dados estamos optando por manter elas genéricas,
vamos precisar receber um ponteiro ao invés do item em si, o que é mais chato,
mas permite copiarmos quantos bytes precisarmos. E como definimos o tamanho do
item na inicialização podemos assumir que é essa a quantidade de bytes que
temos que copiar pro final do array. Vamos fazer isso com `memcpy()` que
precisa da fonte, do destino e da quantidade à se copiar.

```c
#include <string.h>

// Adiciona um item de Array._tamanho_do_item ao final do array
void Array_add(Array* arr, const void* item) {
    // Pega a posição do final do array
    char* final_array = arr->buffer + arr->tamanho * arr->_tamanho_do_item;

    // Copia o item para o final
    memcpy(final_array, item, arr->_tamanho_do_item);
}
```




