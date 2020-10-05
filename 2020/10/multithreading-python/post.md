<!--

# À abordar
 - [X] Problemas single-thread
 - [X] O que é multi-threading
 - [X] Como criar threads
 - [X] GIL
 - [X] Sincronização

# Sugestões
### Título
  - MultiThreading em Python

### SubTítulo
  - Se prepare para os piores problemas da sua vida
  - Algumas boas (outras nem tanto) práticas para código concorrente

-->

Você já tentou processar várias imagens com o python? Se sim, provavelmente
percebeu que um grande ponto de demora é o carregamento delas do disco, e esse
é um tempo teoricamente desperdiçado, já que você não usa nada da CPU para
carregar, mas ainda assim não pode realmente fazer o trabalho de processamento.
Isso acontece por que o seu código muito provavelmente era *single-threaded*, ou
seja tinha apenas um "fio" de execução rodando simultaneamente, e por isso não
era possível executar a função que carregava a proxima imagem ao mesmo tempo
*que a anterior era processada. Felizmente esse não é o único jeito de
programar, podemos usar uma coisa chamada *multi-threading* que nos permite
rodar mais de uma função **ao mesmo tempo**.

Para fazer isso vamos usar uma das bibliotecas padrões do python, a
"threading".

```py
import threading
```

Agora para iniciar mais um thread de execução criamos a classe
`threading.Thread` com um argumento `target`, que é a função a ser rodada
assincronicamente, e usamos o método `start` para iniciar a execução. Aí quando
precisarmos que ele tenha concluído podemos usar o `join`, que vai esperar ele
terminar.

```py
import threading
import time


def funcao_demorada():
    print("funcao_demorada carregando")
    time.sleep(1)
    print("funcao_demorada carregada")

def outra_funcao_demorada():
    print("outra_funcao_demorada carregando")
    time.sleep(1)
    print("outra_funcao_demorada carregada")


thread = threading.Thread(target=funcao_demorada)  # Cria o Thread
thread.start()  # Coloca ele pra trabalhar

outra_funcao_demorada()

thread.join()  # Garante que o outro thread terminou antes de o programa fechar
```

E é basicamente isso, não tem muita mágica não pra ser bem sincero.

Agora se rodarmos esse programa vamos ver que ele consegue "carregar" as duas
funções ao mesmo tempo, o que, dependendo de como for nosso programa, pode dar
um boost considerável na velocidade de execução dele.

```shell
$ time python3 teste-multithreading.py
funcao_demorada carregando
outra_funcao_demorada carregando
outra_funcao_demorada carregada
*funcao_demorada carregada

real    0m1.033s
user    0m0.021s
sys     0m0.013s
```

E como podemos ver: o programa concluí em 1 segundo, sendo que demoraria 2
normalmente.

Porém, em Python existem alguns poréns nessa coisa toda. Enquanto em outras
linguagens é comum o uso de threads para fazer cálculos em paralelo, em python
isso não é possível, já que exite algo conhecido como a **GIL**. Ela é a
*Global Interpreter Lock* (Trava Global do Interpretador) e é o motivo de muita
dificuldade para escrever programas em Python que usem múltiplos cores do
processador. Ela é uma trava que impede que o interpretador Python (que lê o
código e gera o código a ser executado pela CPU) seja executado em mais de um
thread ao mesmo tempo, ela foi criada para resolver alguns problemas
encontrados pelos desenvolvedores do Python e infelizmente até hoje coloca uma
barreira no poder que multithreading têm.

Por causa disso, threading no python serve apenas para resolver apenas
problemas que chamamos de *"IO bound"* (Determinado por IO), que é qualquer
coisa que demore por que está esperando por IO (Input, entrada/Output,
saída) como carregar imagens do disco, enviar um pedido para um servidor, fazer
download de vídeos, esse tipo de coisa.

Se você realmente precisa executar cálculos pesados em paralelo, é possível
usar *multiprocessing* (que tem seus próprios problemas), usar algo como
o projeto `Cython` (que permite transpilar Python para C) ou talvez considerar
se outra linguagem não é mais adequada para o trabalho que você está tentando
fazer.

Um benefício que a GIL trás é que facilita muito o trabalho de sincronizar
threads. Em uma linguagem como C++ na qual threads independentes realmente
podem trabalhar ao mesmo tempo é necessário um grande trabalho para garantir
que não modifiquem a mesma memória ao mesmo tempo, já que isso pode corrompe-la
e trazer grandes problemas para a execução. Mas em python, por causa da GIL,
nada disso acontece. Porém isso não significa que não exitem cuidados a serem
tomados.

Como os threads rodam um interrompendo o outro (concorrentemente) existe o
risco de que duas operações que devem ocorrer juntas sejam interrompidas no
meio. Por exemplo, o código seguinte estaria perfeitamente correto em um
ambiente normal, com apenas um thread rodando.

```python
lista_local = lista_global.copy()  # Cria um cópia da lista
lista_global.clear()  # Limpa a lista antiga
```

Mas em um ambiente em que outro thread atualiza essa `lista_global` pode surgir
um problema que não é muito óbvio a primeira vista: O Python pode interromper
esse código entre as duas funções para rodar o código que atualiza a lista.

```python
lista_local = lista_global.copy()  # Cria um cópia da lista

#
# Pode ser que a `lista_global` mude
#

lista_global.clear()  # Limpa a lista antiga
```

E se isso acontecer, *boa sorte* pra encontrar esse bug.

Felizmente como sabemos desse risco podemos evitar que o problema venha a
ocorrer usando uma Lock (trava) para garantir a sincronização entre os Threads.
O que ela faz é proteger uma variável ao garantir que duas funções que a
modificam não possam rodar simultaneamente. Só que tenha em mente que a
associação entre uma variável e uma Lock existe puramente na sua mente, não há
como conectá-las no código (a menos que você crie uma classe que administre as
duas e faça todas as suas operações por meio da dita classe). No nosso exemplo
simples ficaria assim:

```python
with LOCK:
    lista_local = lista_global.copy()  # Cria um cópia da lista
    lista_global.clear()  # Limpa a lista antiga
```

Só que com o porém de que essa `LOCK` teria que ter sido criada antes e ter
sido usada também na função que atualiza a `lista_global`. Um exemplo mais
completo de como isso seria:

```python
import threading
import time

LOCK = threading.Lock()  # Cria a Lock
lista_global = []

def processar_lista():
    global lista_global

    while True:
        lista_local = []

        with LOCK:
            lista_local = lista_global.copy()  # Cria um cópia da lista
            lista_global.clear()  # Limpa a lista antiga

        # imprime a lista_local
        for i in lista_local:
            print(i)
            if i == -1:  # Termina de rodar se a lista acabar
                return

def criar_lista():
    global lista_global

    for i in range(10):
        time.sleep(0.01)
        with LOCK:
            lista_global.append(i)

    with LOCK:
        lista_global.append(-1)  # Indica que a lista acabou

processar = threading.Thread(target=processar_lista)
criar = threading.Thread(target=criar_lista)

# Inicia os threads
processar.start()
criar.start()

# Termina os threads
processar.join()
criar.join()
```

E o resultado será esse:

```shell
$ python3 main.py
0
1
2
4
5
6
7
8
9
-1
```

Se você estiver na dúvida se a Lock é realmente necessária, experimente tirar
ela e rodar o programa algumas vezes. Você verá que mesmo nesse caso simples
alguns números já não são impressos na tela.

Mas então é isso por hoje, threading é muito útil, só não se esqueça de
sincronizar seus acessos às variáveis. Até semana que vem.

