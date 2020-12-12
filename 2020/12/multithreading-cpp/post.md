Já abordamos multithreading aqui no blog, mas em Python. Um dos grandes
empecilhos que vimos lá era a **GIL** (Trava Global do Interpretador) que
impede que mais do que um thread interprete código python a qualquer momento.
Em C++ não temos essa limitação! Mas, para compensar, temos que ser extra
cuidadosos com nossa memória, já que escrever nela ao mesmo tempo que outro
thread a usa pode causar bugs bastante nefários.

Um thread nada mais é do que uma linha de execução de código no processador do
computador. Os primeiros programas que você escreve na sua carreira são
provavelmente single-threaded (com um thread único), ou seja apenas uma parte
do código executa a cada vez. Multi-threading (usar threads múltiplos) por
outro lado, permite fazer diversas operações simultaneamente, por exemplo, você
poderia calcular o processo físico de um jogo ao mesmo tempo que processa as
ações do jogador, ou ainda carregar várias imagens para processamento ao mesmo
tempo, ao invés de uma de cada vez.

Para fazer isso em C++ podemos usar o objeto `std::thread` que faz parte da
biblioteca padrão. Ele permite inicializar um novo thread com um *chamável*,
tipo o endereço de uma função. Vamos ver como funciona:

```cpp
#include <iostream>
#include <thread>

// Espera até apertar enter
void espera_enter() {
    std::cin.get();
}

int main() {
    espera_enter();
    std::cout << "Terminado" << std::endl;
}
```

Ainda não usamos threads, mas isso é para poder comparar melhor como funciona.
Nesse caso a mensagem `"Terminado"` vai aparecer só depois de apertarmos enter.

```bash
$ g++ main.cpp && ./a.out
    # <enter>
Terminado
```

Mas se lancarmos o `espera_enter()` em outro thread, vamos ver que a mensagem
aparece antes de apertarmos.

```cpp
#include <iostream>
#include <thread>

// Espera até apertar enter
void espera_enter() {
    std::cin.get();
}

int main() {
    std::thread t(espera_enter);
    std::cout << "Terminado" << std::endl;

    t.join();  // Espera completar
}
```

```bash
$ g++ main.cpp -pthread && ./a.out  # Precisamos usar `-pthread` para compilar com suporte à threads.
Terminado
  # <enter>
$
```

Isso acontece porque quando criamos o `std::thread` o código de
`espera_enter()` começa imediatamente a executar em outra linha, que não
interfere na continuidade da função atual, isso até chamarmos
`std::thread::join()` que sincroniza e faz as linhas se unirem.

Teoricamente podemos criar threads ilimitados em todos os sistemas operacionais
modernos, porém se as funções chamadas tiverem muita carga de processamento
contínuo, normalmente só vale a pena criar um thread para cada core lógico do
processador. Mais do que isso e haverá uma tendência para a **degradação** da
performance, já que os cores vão precisar fazer malabarismo com os threads, o
que causa custos de mudança de contexto.

Por outro lado, se o trabalho principal dos threads for de IO (entrada/saída de
dados), como baixar imagens da internet ou ler algo do disco rígido, você pode
criar muito mais deles com um ganho em performance. Nesse caso, a quantidade
com maior benefício é mais difícil de determinar do que no caso anterior, já
que depende do quanto você está usando da CPU, a velocidade de transferência de
dados da sua internet/disco rígido/memória. Mas que qualquer forma, uma
quantidade em torno do dobro do número de cores lógicos do seu processador
ainda deve funcionar bem.


