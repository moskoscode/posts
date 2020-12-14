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

Vamos ver isso na prática:

Digamos que temos uma função que faz vários cálculos e ela demora um bom tempo
pra executar

```cpp
#include <cstdint>
#include <iostream>

// Demora cerca de 5 segundos no meu computador
void umMonteDeCalculos() {
    for (std::size_t i = 0; i < 10000000000; ++i);
}

int main() {
    umMonteDeCalculos();
    std::cout << "Pronto" << std::endl;
}
```

Pra facilitar o exemplo nossa função não faz nada, ela só incrementa um
contador até 10 bilhões. Só que temos um problema ainda: os compiladores
modernos são muito espertos e vão perceber que nossa função
`umMonteDeCalculos()` é besteira e não calcula nada. Por isso que quando
executamos esse exemplo o tempo que ele demora é tipo 0.

```bash
$ c++ cputhread.cpp -O3 -pthread && time ./a.out
Pronto

real    0m0.002s
user    0m0.002s
sys     0m0.001s
```

Precisamos de um jeito para convencer o compilador a manter nosso loop no
programa. Para isso vamos usar uma técnica de benchmarking que permite dizermos
precisamente o que não deve ser otimizado, vamos usar um pedaço de *assembly
volátil* que não faz nada, mas que é indecifrável pro compilador, de forma que
ele é obrigado a manter o código que leva até ele.

```cpp
#include <cstdint>
#include <iostream>

// Garante que um caminho de código exista
static void naoOtimizar() {
    asm volatile("" : : : );
}

// Demora cerca de 5 segundos no meu computador
void umMonteDeCalculos() {
    for (std::size_t i = 0; i < 10000000000; ++i) naoOtimizar();
}

int main() {
    umMonteDeCalculos();
    std::cout << "Pronto" << std::endl;
}
```

Esse programa sim funciona como o esperado, demora cerca de 5 segundos para
executar:

```bash
$ c++ cputhread.cpp -O3 -pthread && time ./a.out
Pronto

real    0m4.982s
user    0m4.979s
sys     0m0.000s
```

Agora digamos que ao invés de executar apenas uma vez, precisamos rodar essa
função 4 vezes. Sem threads o tempo de execução escala linearmente, demora 4
vezes mais, ou seja cerca de 20 segundos

```cpp
int main() {
    umMonteDeCalculos();
    std::cout << "1" << std::endl;
    umMonteDeCalculos();
    std::cout << "2" << std::endl;
    umMonteDeCalculos();
    std::cout << "3" << std::endl;
    umMonteDeCalculos();
    std::cout << "4" << std::endl;
}
```

```bash
$ c++ cputhread.cpp -O3 -pthread && time ./a.out
1
2
3
4

real    0m19.841s
user    0m19.815s
sys     0m0.008s
```

Mas se implementarmos paralelismo (e seu computador tiver cores o suficientes),
podemos voltar a demorar apenas 5 segundos pra executar essa mesma quantidade
de cálculos.

```cpp
#include <thread>

int main() {
    std::thread t1 (umMonteDeCalculos);
    std::thread t2 (umMonteDeCalculos);
    std::thread t3 (umMonteDeCalculos);
    std::thread t4 (umMonteDeCalculos);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    std::cout << "Pronto" << std::endl;
}
```

```bash
$ c++ cputhread.cpp -O3 -pthread && time ./a.out
Pronto

real    0m5.438s
user    0m21.587s
sys     0m0.008s
```

Então **esse** é o poder dos threads.

Veja que podemos ter essa economia com até no máximo a quantidade de *cores
lógicos* do processador do usuário. Minha máquina tem 6 deles, então posso usar
até 6 threads demorando quase o mesmo tempo.

```cpp
int main() {
    std::thread t1 (umMonteDeCalculos);
    std::thread t2 (umMonteDeCalculos);
    std::thread t3 (umMonteDeCalculos);
    std::thread t4 (umMonteDeCalculos);
    std::thread t5 (umMonteDeCalculos);
    std::thread t6 (umMonteDeCalculos);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();

    std::cout << "Pronto" << std::endl;
}
```

```bash
$ c++ cputhread.cpp -O3 -pthread && time ./a.out
Pronto

real    0m5.874s
user    0m33.050s
sys     0m0.020s
```

Mas assim que eu passar disso, por 1 thread que seja, a diferença já vai
aparecer.

```cpp
int main() {
    std::thread t1 (umMonteDeCalculos);
    std::thread t2 (umMonteDeCalculos);
    std::thread t3 (umMonteDeCalculos);
    std::thread t4 (umMonteDeCalculos);
    std::thread t5 (umMonteDeCalculos);
    std::thread t6 (umMonteDeCalculos);
    std::thread t7 (umMonteDeCalculos);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();

    std::cout << "Pronto" << std::endl;
}
```

```bash
$ c++ cputhread.cpp -O3 -pthread && time ./a.out
Pronto

real    0m7.178s
user    0m38.464s
sys     0m0.024s
```

Por outro lado, se o trabalho principal dos threads for de IO (entrada/saída de
dados), como baixar imagens da internet ou ler algo do disco rígido, você pode
criar muito mais deles com um ganho em performance. Nesse caso, a quantidade
com maior benefício é mais difícil de determinar do que no caso anterior, já
que depende do quanto você está usando da CPU, da velocidade de transferência
de dados da sua internet/disco rígido/memória, entre outros. Mas que qualquer
forma, uma quantidade em torno de o dobro do número de cores lógicos do seu
processador deve funcionar bem.

Vamos dar uma olhada em um exemplo simulado novamente.

````cpp

```
