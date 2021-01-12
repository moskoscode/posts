# Programação sem IF e ELSE?

<!-- subtítulo: Não tente isso na produção -->
<!-- subtítulo: Tente com a supervisão de um adulto -->

Já pensou escrever um programa inteiro sem `if`s ou `else`s ? Provavelmente não, mas isso não significa que não podemos fazer lógica sem eles, e as vezes bem mais rápido do que com.

O nome desse tipo de programação é `branchless programming`, programação sem ramos, já que não usa `if`, que criaria ramos de execução pro código.

Por que isso seria útil? No seu caso, provavelmente, só serviria para satisfazer a curiosidade. Mas em casos específicos, como código criptográfico, esse tipo de programação é absolutamente requerido já que a existência de 2 possíveis caminhos poderia resultar em tempos de execução diferentes para determinadas entradas o que, por sua vez, poderia causar o vazamento de informação sigilosa. Nesse caso programação `branchless` é usada como **medida de segurança**!

Outro uso legitimo é em determinados algoritmos de baixo nível que não podem desperdiçar o tempo que o `if` custa, dessa forma `branchless` teoricamente serve para deixar o programa **bem** mais rápido. Mas preste bastante atenção se quiser usá-lo para aumentar a performance: seu compilador é muito mais esperto que você, grandes são as chances que ao aplicar esse tipo de programação, ao invés de deixar seu programa mais rápido você vai torná-lo mais devagar ou não vai alterar a performance em nada. Lembre-se: Otimização prematura é a raiz de todo o mal (David Knuth). Então como saber se posso usar programação `branchless` para acelerar meu algoritmo? O melhor jeito é programar dos dois jeitos e medir a performance deles em uma situação parecida com à que vão ser usados. Por outro lado, para evitar todo esse trabalho, entender o porquê do `if` ser considerado tão devagar pode te ajudar a determinar se ele é um possível problema, se sim, aí você pode colocar a mão na massa e medir se o `branchless` vai te ajudar mesmo.

### Por que o if é tão devagar?

As CPUs modernas tem alta capacidade de paralelização, isto é, ao invés de executar uma instrução de cada vez, elas pegam as próximas linhas de código e decidem o que podem fazer ao mesmo tempo sem interferir no resultado final, aí fazem isso. Para que esse tipo de paralelização seja mais efetiva o caminho de código tem que ser o mais único (sem ramos) quanto possível. Mas como sabemos, não é assim que a maior parte de código é, tem if daqui, else de lá, switch dentro de loop e assim vai.