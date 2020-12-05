
<!--
 Título:
  - Visualizando Bubble e Merge Sort em p5.js
 Sugestões de Subtítulos:
  - Computador com TOC vs Código de Barras
-->

Em 98.76777% dos programas de computador vai ser necessário ordenar *alguma*
lista (estatística inventada). Por isso muito tempo foi investido tentado
descobrir a forma mais eficiente possível de fazer isso, o que resultou na
criação de inúmeros algoritimos com esse propósito, cada um deles com alguma
prioridade: economizar memória, economizar tempo, atingir um balanco agradável
entre os dois, ser fácil de implementar, ser engraçado...

Entender uma grande variedade deles pode ser fundamental em uma entrevista de
emprego, nas quais muitas vezes cobram uma implementação em quadro negro, ou na
hora de resolver um problema análogo. E que jeito melhor de entender algo do
que vendo acontecer?

Por isso no post de hoje vamos implementar 2 algoritimos (e um extra) de
ordenação: BubbleSort e MergeSort, só que de uma forma que possamos gerar uma
visualização do progresso deles - o que, se prepare, vai dificultar
consideravelmente o processo.

Vamos fazer isso em javascript usando a *framework* de programação criativa
**p5.js**, isso pra facilitar o trabalho de criar a janela, desenhar linhas e
tals. Mas se você já tiver alguma experiencia de programação, pode acompanhar
na sua linguagem de preferência.

# Bubble Sort

BubbleSort é muito fácil de implementar. Nele primeiro você compara o primeiro
item com o próximo, se for maior deve-se trocá-los de lugar. Você repete isso
até chegar ao final da lista, nesse momento você tem certeza que o último item
é o maior e por isso não é mais necessário compará-lo, então se volta para o
primeiro passo, mas parando antes dos items que já estão na posição certa.
Assim vai, até não ter mais pares para comparar.

Podemos implementar isso em javascript com poucas linhas de código:

```javascript
// Ordena a lista com BubbleSort
function bubble_sort(lista) {
  // Controla qual o último item que ainda devemos comparar
  var final = lista.length;

  // Enquanto ainda temos itens não posicionados
  while (final > 1) {

    // Olha todos os items da lista, trocando os errados
    for (var i = 0; i < final; ++i) {
      if (lista[i] > lista[i + 1]) {
        troca(lista, i, i + 1);
      }
    }

    // Marca que o último item foi posicionado
    --final;
  }
}

// Troca 2 itens de lugar
function troca(lista, pos1, pos2) {
  var temp = lista[pos1];
  lista[pos1] = lista[pos2];
  lista[pos2] = temp;
}
```

Mas, isso só nos resulta a lista organizada. Se tentarmos visualizar isso com o
p5.js vai ser super chato:

<iframe style="width: 400px; height: 200px; overflow: hidden;" scrolling="no" frameborder="10"
src="https://editor.p5js.org/eduardommosko@gmail.com/embed/4OqLkrUQ3"></iframe>

```javascript
var lista = [];
var ordenada = false;
const tamanho = 400;

// Inicializa programa
function setup() {
  createCanvas(tamanho, 200);
  frameRate(1);  // Atualiza uma vez a cada segundo
}

// Desenha visualização
function draw() {
  background(220);

  // Alterna entre encher e ordenar
  if ((ordenada = !ordenada)) {
    encher(lista);
  } else {
    bubble_sort(lista);
  }

  desenhar(lista);
}

// Enche a lista com números aleatórios
function encher(l) {
  l.length=0;  // Esvazia a lista
  for (var i = 0; i < tamanho; ++i) lista.push(random(0, 255));
}

// Desenha a lista na tela
function desenhar(l) {
  for (var i = 0; i < l.length; ++i) {
    stroke(l[i]);
    line(i, 0, i, 400);
  }
}
```

Então pra poder realmente ver o que acontece em cada parte do processo, temos
que fazer de um jeito que dê para mostrar na tela cada operação. No caso do
BubbleSort isso é bem fácil, já que os loops estão bem ali é só decompor os
passos para acontecerem um de cada vez. Então vamos criar uma função
`passo_bubble_sort()` e mover a variável `final` para fora da função, para que
ela mantenha seu valor entre invocações.


```javascript
// - Váriaveis BubbleSort
var final = null;    // Controla qual o último item que ainda devemos comparar
var bubble_pos = 0;  // Controla o próximo item que devemos comparar

// Dá um passo na ordenação da lista com BubbleSort
function passo_bubble_sort(lista) {
  // Inicializa o final se ainda não tiver sido
  if (final === null) final = lista.length;

  // Se ainda temos itens não posicionados
  if (final > 1) {
    // Olha o próximo item da lista e troca se estiver errado
    if (lista[bubble_pos] > lista[bubble_pos + 1]) {
      troca(lista, i, i + 1);
    }

    // Avança para o próximo item
    ++bubble_pos;
  }

  // Se estivermos no fim, marca que o último item foi posicionado e volta pro começo
  if (bubble_pos > final) {
    bubble_pos = 0;
    --final;
  }
}
```

E com isso fica melhor de visualizar:

<iframe style="width: 400px; height: 200px; overflow: hidden;" scrolling="no" frameborder="10"
src="https://editor.p5js.org/eduardommosko@gmail.com/embed/k4uOl16VR"></iframe>

```javascript
var lista = [];
var ordenada = false;
const tamanho = 400;

// Inicializa programa
function setup() {
  createCanvas(tamanho, 200);
  frameRate(15);
  encher(lista);
}

// Desenha visualização
function draw() {
  background(220);

  // Avança um tanto a ordenação
  for (var i=0; i<60; ++i)
    passo_bubble_sort(lista);

  // Se terminar, enche a lista de novo
  if (final < 2) {
    encher(lista);
    final = null;
  }

  desenhar(lista);
}
```

Agora dá pra **ver** o quão ineficiente o BubbleSort realmente é. Pega cada
barrinha e leva pro final comparando uma por uma até o final e aí faz de novo e
de novo e de novo...

Certamente tem como fazer melhor que isso né??

# MergeSort

Agora entramos no universo do MergeSort, um algoritimo **muito** mais rápido.
Mas como tudo, isso tem um preço: precisa de **muito** mais memória do que o
BubbleSort. Enquanto o máximo que aquele usa é uma váriavel temporária, o
MergeSort (em sua forma básica) precisa de uma segunda lista **inteira** do mesmo
tamanho da primeira!

Então vamos lá, como ele funciona? O estilo dele é o que chamamos de "Dividir e
Conquistar" já que ele

Esse algoritimo parte de 2 ideias base: A primeira é que se tivermos 2 listas
pré-ordenadas podemos mescla-las com (muito) menos comparações do que
precisáriamos pra ordenar uma lista do mesmo tamanho. Como? Se sabemos que o
primeiro item das duas listas são os menores que há, só precisamos saber qual
deles é o mais menor e já teremos **certeza** que esse será o primeiro da lista
final. A segunda ideia é que cada número em si pode ser considerado uma lista
de apenas um item, tal qual está **sempre** em ordem.

Desses princípios parte a conclusão: se eu tenho várias listas pré-ordenadas e
meclar duas delas é tão mais rápido que ordenar, isso significa que mesclar
elas entre si vai me dar listas pré-ordenadas cada vez maiores, e quando chegar
no tamanho da lista inicial ainda vai ser mais rápido que ordenar comparando
item por item.

A forma mais comum de implementar isso é com uma função recursiva, já que isso
se encaixa muito bem no problema.

```javascript
var buffer = null;

// Ordena a lista com MergeSort
function merge_sort(lista, comeco = 0, fim = lista.length) {
  // Inicializa um buffer auxiliar para guardarmos as listas intermediárias
  if (buffer === null) {
    buffer = [];
    buffer.length = lista.length; // JavaScript ¯\_(ツ)_/¯
  }

  if (fim - comeco > 1) {
    var meio = (int)((fim + comeco) / 2);

    // Pré-ordena cada metade da lista
    merge_sort(lista, comeco, meio);
    merge_sort(lista, meio, fim);

    // Copia a seção da lista pro buffer
    for (var i = comeco; i < fim; ++i) {
      buffer[i] = lista[i];
    }

    // Mescla as duas metades ordenadas
    var c = comeco;
    var m = meio;
    var i = comeco;

    while (c < meio && m < fim) {  // Enquanto não chegar no fim de uma das metades
      if (buffer[c] < buffer[m]) {  // Copia a parte menor pra lista
        lista[i] = buffer[c];
        ++i;
        ++c;
      } else {
        lista[i] = buffer[m];
        ++i;
        ++m;
      }

      while (c < meio) {  // Copia a metade esquerda até o final
        lista[i] = buffer[c];
        ++i;
        ++c;
      }

      while (m < meio) {  // Copia a metade direita até o final
        lista[i] = buffer[m];
        ++i;
        ++m;
      }

    }

  }
}
```

Mas dessa forma temos o mesmo problema de antes: não podemos visualizar. E
nesse caso como a implementação é recursiva não é tão óbvio de adaptar.
Felizmente toda implementação recursiva pode ser traduzida em um loop,
inclusive com mais eficiência grande parte das vezes. A forma que eu pensei em
fazer isso é "simulando" a recursividade com uma estrutura de dados de
**stack** (*pilha*) que guarda uma pilha de estados do processamento, como se
devemos ordenar ou mesclar. Dessa forma, quando formos ordenar colocamos na
seção da lista que queremos que seja organizada na pilha, aí e o processamento
só voltará para a seção atual quando a outra estiver ordenada. Vamos ver isso
em ação:

```
// Ordena a lista com MergeSort em loop
function merge_sort_loop(lista, comeco = 0, fim = lista.length) {
  var buffer = [];
  buffer.length = lista.length; // JavaScript ¯\_(ツ)_/¯

  var stack = [];
  stack.push(new Estado(comeco, fim, md.ORDENAR));

  // Enquanto tiverem itens na stack
  while (stack.length > 0) {
    var estado = ultimo(stack);
    console.log(estado)
    console.log(lista.slice(estado.comeco, estado.fim))
    var mm;

    switch (estado.modo) {
      case md.ORDENAR:
        if (estado.fim - estado.comeco < 2) {
          stack.pop();
          break;
        }
        stack.push(new Estado(estado.comeco, estado.meio));
        stack.push(new Estado(estado.meio, estado.fim));
        estado.modo = md.MESCLAR;
        break;

      case md.MESCLAR:
        var i;

        // Copia a seção da lista pro buffer
        for (i = estado.comeco; i < estado.fim; ++i) {
          buffer[i] = lista[i];
        }

        // Mescla as duas metades ordenadas
        var c = estado.comeco;
        var m = estado.meio;
        i = estado.comeco;

        while (c < estado.meio && m < estado.fim) {
          if (buffer[c] < buffer[m]) {
            lista[i] = buffer[c];
            ++i;
            ++c;
          } else {
            lista[i] = buffer[m];
            ++i;
            ++m;
          }
        }

        while (c < estado.meio) {
            lista[i] = buffer[c];
            ++i;
            ++c;
        }
        while (m < estado.fim) {
            lista[i] = buffer[m];
            ++i;
            ++m;
        }

        stack.pop();
    }
  }
}
```

