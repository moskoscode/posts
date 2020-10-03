<!--

# À abordar
 - [X] Problemas single-thread
 - [X] O que é multi-threading
 - [ ] Como criar threads
 - [ ] GIL
 - [ ] Threading para IO
 - [ ] Multithreading vs Multiprocessing

# Sugestões
### Título
  - Multithreading em Python

### SubTítulo
  - Se prepare para os piores problemas da sua vida
  - Algumas boas (outras nem tanto) práticas para código concorrente

-->

Você já tentou processar várias imagens com o python? Se sim, provavelmente
percebeu que um grande ponto de demora é o carregamento delas do disco, e esse
é um tempo teoricamente desperdicado, já que você não usa nada da CPU para
carregar, mas ainda assim não pode realmente fazer o trabalho de processamento.
Isso acontece por que o seu código muito provavelmente era *sigle-threaded*, ou
seja tinha apenas um "fio" de execução rodando simultaneamente, e por isso não
era possível executar a função que carregava a proxima imagem ao mesmo tempo
que a anterior era processada. Felizmente esse não é o único jeito de
programar, podemos usar uma coisa chamada *multi-threading* que nos permite
rodar mais de uma função **ao mesmo tempo**.



