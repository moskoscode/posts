# Programação sem IF e ELSE?

<!-- subtítulo: Não tente isso na produção -->
<!-- subtítulo: Tente com a supervisão de um adulto -->

Já pensou escrever um programa inteiro sem `if`s ou `else`s ? Provavelmente não, mas isso não significa que não podemos fazer lógica sem eles, e as vezes bem mais rápido do que com.

O nome desse tipo de programação é `branchless programming`, programação sem ramos, já que não usa `if`, que criaria ramos de execução pro código.

Por que isso seria útil? No seu caso, provavelmente, só serviria para satisfazer a curiosidade. Mas em casos específicos, como código criptográfico, esse tipo de programação é absolutamente requerido já que a existência de 2 possíveis caminhos poderia resultar em tempos de execução diferentes para determinadas entradas o que, por sua vez, poderia causar o vazamento de informação sigilosa. Nesse caso programação `branchless` é usada como **medida de segurança**!

Outro uso legitimo é em determinados algoritmos de baixo nível que não podem desperdiçar o tempo que o `if` custa, dessa forma `branchless` teoricamente serve para deixar o programa **bem** mais rápido. Mas preste bastante atenção se quiser usá-lo para aumentar a performance: seu compilador é muito mais esperto que você, grandes são as chances que ao aplicar esse tipo de programação, ao invés de deixar seu programa mais rápido você vai torná-lo mais devagar ou não vai alterar a performance em nada. Lembre-se: Otimização prematura é a raiz de todo o mal (David Knuth). Então como saber se posso usar programação `branchless` para acelerar meu algoritmo? O melhor jeito é programar dos dois jeitos e medir a performance deles em uma situação parecida com à que vão ser usados. Por outro lado, para evitar todo esse trabalho, entender o porquê do `if` ser considerado tão devagar pode te ajudar a determinar se ele é um possível problema, se sim, aí você pode colocar a mão na massa e medir se o `branchless` vai te ajudar mesmo.

### Por que o if é tão devagar?

As CPUs modernas tem alta capacidade de paralelização, isto é, ao invés de executar uma instrução de cada vez, elas pegam as próximas linhas de código e decidem o que podem fazer ao mesmo tempo sem interferir no resultado final, aí fazem isso. Para que esse tipo de paralelização seja mais efetiva o caminho de código tem que ser o mais único (sem ramos) quanto possível. Mas como sabemos, não é assim que a maior parte de código é, tem if daqui, else de lá, switch dentro de loop e assim vai. Sabendo disso, os desenvolvedores de processadores criaram outro mecanismo para auxiliar o primeiro: o *branch predictor*, prevedor de ramos, que tem a capacidade de prever qual dos ramos vai ser tomado, antes mesmo de computar o resultado. Eles são excelentes, de verdade, com uma precisão de uns 95%, mas não são perfeitos. Assim, quando eles acertam o `if` tem um custo quase zero na execução, porém, quando erram ihh...

Já que o prevedor de ramos é a base pro funcionamento da execução paralela da CPU, quando ele erra todo o trabalho feito pelo outro ramo durante a paralelização tem que ser desfeito, as instruções certas tem que ser buscadas, para aí sim o ramo certo ser executado. Como eu disse, isso quase não acontece, já que o prevedor de ramos é muito bom, mas existem certos algoritmos que dificultam muito o trabalho dele. Por exemplo, uma função `min(a, b)` que determina qual o menor número entre `a` e `b` normalmente vai ser usada em números que tem 50% de probabilidade de cada um ser o maior.

```cpp
// A vai ser menor cerca de metade das vezes
int min(int a, int b) {
	if (a < b)
		return a;
	else
		return b;
}
```

Nesse caso, o prevedor de ramos não faz ideia de o que fazer e vai errar metade das vezes, o que resultaria em muito tempo gasto. Esse caso levantaria a suspeita de que uma abordagem `branchless` poderia aumentar a performance.

### Aplicando programação branchless

A programação sem ramos tem como base o fato de que o computador representa valores verdadeiros e falsos com os números 1 e 0, o que permite aplicarmos aritimética à eles. Dessa forma se temos dois possíveis cálculos à fazer e precisamos decidir entre eles com base em alguma condição, ao invés de usarmos

```
if (condicao):
	calculo1()
else:
	calculo2()
```

Uma abordagem branchless seria

```
calculo1()*condicao + calculo2()*(!condicao)
```

Ou seja, você multiplica o primeiro cálculo pela condição e o segundo cálculo pelo inverso da condição e soma. Isso funciona por que multiplicação por verdadeiro (um) resulta no próprio cálculo, ou seja, mantém ele e multiplicação por falso (zero) resulta em zero, ou seja, descarta o cálculo.

Se aplicarmos à função `min()` de antes, ela poderia ser assim:

```cpp
// A vai ser menor cerca de metade das vezes
int min(int a, int b) {
	return a * (a < b) + b * !(a < b);
}
```

Legal, conseguimos deixar bem pior de entender o que ela faz, agora se deixamos mais rápido mesmo só vamos saber se medirmos a performance.
