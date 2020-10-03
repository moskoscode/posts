<!--

# À abordar
 - [X] Problemas single-thread
 - [X] O que é multi-threading
 - [X] Como criar threads
 - [ ] GIL
 - [ ] Threading para IO
 - [ ] MultiThreading vs Multiprocessing

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
que a anterior era processada. Felizmente esse não é o único jeito de
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
funcao_demorada carregada

real    0m1.033s
user    0m0.021s
sys     0m0.013s
```

E como podemos ver o programa concluí em 1 segundo, sendo que demoraria 2
normalmente.

