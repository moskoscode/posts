Um Array é um bloco de memória que pode armazenar mais do que um item de determinado tipo. Ele facilita o gerenciamento de grandes quantidades de valores e pode aumentar muito a performance do seu programa quando usado corretamente. No video de hoje vamos falar sobre como funciona e como tirar maior proveito dessa estrutura de dados que é a mais simples e talvez mais útil de todas.

Mas antes de mais nada, esse é o primeiro vídeo de uma série sobre estruturas de dados que estamos começando aqui no canal, nela vamos discutir o funcionamento e a aplicação das estruturas de dados mais usadas na programação. Cada um desses vídeos vai ser acompanhado de uma postagem no blog do Moskos' CodeField ensinando a implementar cada uma delas na linguagem de programação onipresente: C, então não se esquece de dar uma olhada lá se quiser aplicar na prática o que vamos ver hoje. Bora pro vídeo.

O Array pode ser entendido como uma série de dados consecutivos na memória. Por exemplo um array de 5 Números Inteiros vai ser um bloco de memória com espaço pra 5 Números um seguido do outro. Essa característica é muito útil por que permite um acesso muito rápido à posição que você quiser, já que ao invés de ter que ir item por item, tipo to no primeiro, to no segundo, to no terceiro, pronto tá aqui o quarto; você pode pegar o endereço na memória do primeiro, somar 4 espaços e pronto achou o item.

Outra coisa que faz o array ser tão rápido é a forma como o processador do computador acessa a memória dos programas.

Você pode imaginar a memória do computador como a página de um livro e a CPU como nosso olho: só conseguimos focar em uma coisa de cada vez, umas duas ou três letras, mas ainda assim temos uma visão periférica da linha em que estamos, dessa forma é fácil acharmos as próximas letras de cada palavra e continuarmos lendo. Por outro lado, toda vez que precisamos, pular para outra parte da página, quando estamos procurando uma citação, por exemplo, demoramos um tempo a mais. Da mesma forma funciona o computador, se todos os dados que você precisa estão próximos na memória é bem mais rápido de processar. Inclusive, nos computadores atuais, esse tempo de pular entre lugares distantes da memória é tão grande que geralmente se torna a operação que mais toma tempo da execução de um programa! E é por isso que o Array, que mantém os itens próximos, aumenta tanto a performance quando ele é usado para guardar itens que tem que vão ser processados em sequencia.

Mas isso tudo não significa que o Array é perfeito para todas as situações. A forma básica dele, em C, tem um tamanho fixo, ou seja, se você pediu 5 Inteiros não vai poder adicionar nem mais nem menos, o array vai ocupar esse espaço até ser liberado. Por isso foram criados Arrays dinâmicos que teoricamente aumentam e diminuem de tamanho. Mas na pratica eles não fazem exatamente isso. O funcionamento deles é que quando você precisa de mais espaço, outro array maior é criado e todos os itens são copiados e aí o array antigo é liberado, mesma coisa quando você precisa ocupar menos espaço. Isso tem como resultado que essas operações de aumentar de tamanho podem ser mais caras do que em outras estruturas de dados. Mas não tome isso como regra, como eu disse antes o maior fator de lentidão dos computadores atuais são os acessos fragmentados à memória e geralmente as estruturas que tentam diminuir o custo da adição/remoção de itens fazem um monte deles. Então você tem que sempre considerar se você vai precisar acessar os itens com mais frequência do que adicionar ou se você vai precisar adicionar e remover várias vezes, mas não vai acessá-los muito. 

De qualquer forma, lembre-se: otimização prematura é a raiz de todo o mal (Donald Knuth). O melhor mesmo é primeiro usar a estrutura de dados que parece mais fácil e adequada e só quando um problema na performance for identificado, aí medir a performance das possíveis alternativas para escolher a estrutura de dados mais adequada. 

Por isso que é tão importante conhecer à fundo o funcionamento de cada estrutura, para você poder desenvolver uma intuição de quais podem ser úteis em cada situação e não perder tempo testando várias delas que não tem nada a ver com o que você precisa. Então se quiser se aprofundar no funcionamento do Array, temos uma postagem no blog do Moskos' CodeField ensinando a implementar um Array dinâmico em C. O link está aqui na descrição.

Espero que você tenha aprendido uma coisa ou duas nesse vídeo, e se estiver se sentindo generoso considere nos apoiar no catarse, o link está na descrição. Até o próximo vídeo.