
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

Esse algoritimo parte de 2 ideias base: A primeira é que se tivermos 2 listas
pré-ordenadas podemos mescla-las com (muito) menos comparações do que
precisáriamos pra ordenar uma lista do mesmo tamanho. Como? Se sabemos que o
primeiro item das duas listas são os menores que há, só precisamos saber qual
deles é o mais menor e já teremos **certeza** que esse será o primeiro da lista
final. A segunda ideia é que cada número em si pode ser considerado uma lista
de apenas um item, tal qual está **sempre** em ordem.

Desses princípios parte a conclusão: se cada número é uma lista, se eu mesclar
dois deles vou ter uma lista maior, a qual eu vou depois poder mesclar com
outra, o que me daria uma lista ainda maior. Aí posso mesclar essa e meclar e
mesclar até que eventualmente vou chegar em uma lista ordenada do tamanho da
lista original. E já que o tempo para mesclar é tão mais rápido assim, todo
esse processo ainda vai demorar menos do que ordenar comparando item por item.

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

```javascript
// Ordena a lista com MergeSort em loop
function merge_sort_loop(lista, comeco = 0, fim = lista.length) {
  var buffer = [];
  buffer.length = lista.length; // JavaScript ¯\_(ツ)_/¯

  // Cria a stack de partes à serem ordenadas
  var stack = [];

  // Manda ordenar a lista inteira
  stack.push(new Estado(comeco, fim, md.ORDENAR));

  // Enquanto tiverem itens na stack
  while (stack.length > 0) {
    var estado = ultimo(stack);  // Pega o estado atual

    switch (estado.modo) {
      case md.ORDENAR:  // Caso o modo seja ordenar
        if (estado.fim - estado.comeco < 2) {  // Se só tiver um item, já está ordenado
          stack.pop();
          break;
        }
        // Manda ordenar cada metade
        stack.push(new Estado(estado.comeco, estado.meio));
        stack.push(new Estado(estado.meio, estado.fim));

        // Manda mesclar as metades ordenadas
        estado.modo = md.MESCLAR;
        break;

      case md.MESCLAR:  // Caso o modo seja mesclar
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

        // Marca como ordenada
        stack.pop();
    }
  }
}

// Guarda os possíveis modos de operação
const md = {
  ORDENAR: 'o',
  MESCLAR: 'm'
}

// Cria um novo estado do merge sort
function Estado(comeco, fim, modo = md.ORDENAR) {
  this.comeco = comeco;
  this.meio = floor((comeco + fim) / 2);
  this.fim = fim;
  this.modo = modo;
}

// Retorna o último item da lista
function ultimo(lista) {
  return lista[lista.length - 1];
}
```

Mas ainda precisamos adaptar essa versão para acontecer em passos ao invés de
de uma vez só.

```javascript
var buffer = null;
var stack = null;

// Ordena a lista com MergeSort em loop
function passo_merge_sort(lista, comeco = 0, fim = lista.length) {
  if (buffer === null) {
    buffer = [];
    buffer.length = lista.length; // JavaScript ¯\_(ツ)_/¯
  }

  if (stack === null) {
    // Cria a stack de partes à serem ordenadas
    stack = [];

    // Manda ordenar a lista inteira
    stack.push(new Estado(comeco, fim, md.ORDENAR));
  }

  // Se tiverem itens na stack
  if (stack.length > 0) {
    var estado = ultimo(stack); // Pega o estado atual

    switch (estado.modo) {
      case md.ORDENAR: // Caso o modo seja ordenar
        if (estado.fim - estado.comeco < 2) { // Se só tiver um item, já está ordenado
          stack.pop();
          break;
        }
        // Manda ordenar cada metade
        stack.push(new Estado(estado.comeco, estado.meio));
        stack.push(new Estado(estado.meio, estado.fim));

        // Manda mesclar as metades ordenadas
        estado.modo = md.MESCLAR;
        break;

      case md.MESCLAR: // Caso o modo seja mesclar

        // Se estado.c não tiver sido definido (não tiver começado a mesclar)
        if (estado.c === undefined) {
          // Copia a seção da lista pro buffer
          for (var i = estado.comeco; i < estado.fim; ++i) {
            buffer[i] = lista[i];
          }

          // Mescla as duas metades ordenadas
          estado.c = estado.comeco;
          estado.m = estado.meio;
          estado.i = estado.comeco;
        }


        if (estado.c < estado.meio && estado.m < estado.fim) {
          if (buffer[estado.c] < buffer[estado.m]) {
            lista[estado.i] = buffer[estado.c];
            ++estado.i;
            ++estado.c;
          } else {
            lista[estado.i] = buffer[estado.m];
            ++estado.i;
            ++estado.m;
          }
        } else if (estado.c < estado.meio) {
          lista[estado.i] = buffer[estado.c];
          ++estado.i;
          ++estado.c;
        } else if (estado.m < estado.fim) {
          lista[estado.i] = buffer[estado.m];
          ++estado.i;
          ++estado.m;
        } else {
          // Marca como ordenada
          stack.pop();
        }

    }
  }
}
```

E agora é só colocar no `draw()` e visualizar:

<iframe style="width: 400px; height: 200px; overflow: hidden;" scrolling="no" frameborder="10"
src="https://editor.p5js.org/eduardommosko@gmail.com/embed/kalsei6o9"></iframe>

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

  for (var i = 0; i < 20; ++i)
    passo_merge_sort(lista);

  desenhar(lista);

  if (stack.length == 0) {
    frameRate(1);
    desenhar(lista);
    encher(lista);
    stack = null;

  } else {
    frameRate(15);
    desenhar(lista);
  }
}
```

# Algoritimo EXTRA!

Lembra que no começo do post eu falei que existem algoritimos de ordenação com
os propósito mais estranhos? Esse é um deles, o **BogoSort**. Ele nunca é usado
na prática por ser extremamente ineficiente, mas ele é divertido de implementar.

Ele parte do princípio que existe *alguma* permutação ordenada dos valores de
uma lista. Assim se olharmos todas elas, indo de uma a outra aleatóriamente,
uma hora vamos encontrar a ordenada.

A implementação é basicamente assim:
 1. Se a lista estiver ordenada retorne, se não continue.
 2. Gere um ordem aleatória de itens.
 3. Volte para o passo 1.

Em javascript:

```javascript
// Ordena uma lista com BogoSort
function bogo_sort(lista) {
  while (!esta_ordenada(lista)) {  // Enquanto não estiver ordenada
    ordem_aleatoria(lista);  // Gere uma ordem aleatória
  }
}

// Gera uma permutação aleatória para uma lista
function ordem_aleatoria(lista) {
  for (var ultimo = lista.length; ultimo > 1; --ultimo) {
    troca(lista, ultimo, floor(random(0, ultimo)));
  }
}

// Checa se uma lista está ordenada
function esta_ordenada(lista) {
  for (var i = 0; i < lista.length-1; ++i) {
    if (lista[i] > lista[i+1]) {
      return false;
    }
  }
  return true;
}
```

E obviamente, é bem fácil de adaptar para passos:

```javascript
// Ordena uma lista com BogoSort
function passo_bogo_sort(lista) {
  if (!esta_ordenada(lista)) {  // Se não estiver ordenada
    ordem_aleatoria(lista);  // Gere uma ordem aleatória
  }
}
```

Então vamos visualizar, me manda um print se - por acaso - o algoritimo
consiguiu ordenar a lista enquanto você lê o post (Se sim, a visualização vai
ser só a lista ordenada parada).

<iframe style="width: 400px; height: 200px; overflow: hidden;" scrolling="no" frameborder="10"
src="https://editor.p5js.org/eduardommosko@gmail.com/embed/agbapc1kn"></iframe>

```javascript
var lista = [];
const tamanho = 400;

// Inicializa programa
function setup() {
  createCanvas(tamanho, 200);
  encher(lista);
}

// Desenha visualização
function draw() {
  background(220);

  for (var i = 0; i < 20; ++i)
    passo_bogo_sort(lista);

  lista = lista.filter(Number);  // Arruma um bug estranho
  desenhar(lista);
}
```

Mas então é isso galera. Obrigado por ler, espero que tenha aprendido uma coisa
ou duas, e até semana que vem. Não se esqueca de se inscrever na newsletter e nos
apoiar no catarse se achou o conteúdo interessante.

