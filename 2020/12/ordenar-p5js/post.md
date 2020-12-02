
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

// Enche a lista com numeros aleatorios
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

