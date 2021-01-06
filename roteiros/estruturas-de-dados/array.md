# Array

Olá pessoas, bem vindas!
No video de hoje vamos falar sobre a estrutura de dados mais simples de todas: o Array.
Mas antes de mais nada esse é o primeiro vídeo de uma série sobre estruturas de dados aqui no canal.
Nela vamos discutir o funcionamento e a aplicação das estruturas de dados mais usadas do mundo da programação.
Cada um desses vídeos também vai ser acompanhado de uma postagem no blog do Moskos' CodeField ensinando a implementar tais estruturas na linguagem de programação onipresente: C, então não se esquece de dar uma olhada lá se quiser aplicar na prática o que vamos ver hoje.
Bora pro vídeo.

Um Array nada mais é do que uma seção de dados consecutivos na memória.
Por exemplo um array de 5 Números Inteiros vai ser um espaço de 5 números, no qual você pode colocar o que quiser.
Essa característica de os dados serem consecutivos é muito útil por que permite um acesso muito rápido à posição que você quer.

Pra entender como, é preciso primeiro entender o que é um ponteiro de memória.
Um ponteiro nada mais é do que um número que indica uma posição na memória, por exemplo 10 indicaria o décimo byte na memória do seu computador e você pode acessar o valor que está guardado lá dereferenciando o ponteiro.
Dessa forma se você tiver um array, só é necessário guardar a posição do primeiro item, aí quando você quiser acessar o próximo é adicionar o tamanho do item que você está guardando ao ponteiro.
Um `int` em C tem 4 bytes normalmente, então se o primeiro item estiver na posição 10, o segundo vai estar na 14, o terceiro na 18 e assim por diante.

Outra coisa que faz o array ser tão rápido é a forma como o processador do computador acessa a memória dos programas.
O tipo mais conhecido de armazenamento dinamico é a memória RAM, ela geralmente é bem grande e armazena alguns gigabytes.
Mas ela tem o problema de ser bem mais lerda que o processador e estar bem longe dele (relativamente), então se a CPU fosse buscar as informações lá toda vez que precisa somar dois números nossos computadores seriam muito mais lerdos do que são hoje.
Para resolver esse problema de velocidade foram criadas memória mais rápidas, mas elas são muito muito mais caras.
Aí alguém teve a ideia: Ei o processador consegue acessar no máximo alguns bytes de cada vez, então não precisamos que toda a memória seja rápida, só a que vai ser usada em breve. Assim foi criado o cache do processador, que é um pouquinho de memória bem rápida bem perto do processador que reflete as porções que estão sendo usadas da memória RAM, aí quando ela para de ser usada ela é sincronizada com a RAM enquanto a CPU pode ir fazendo outra coisa.
Isso aumenta muito a performance dos programas, principalmente dos programas que são projetados com estruturas de dados que tiram proveito disso.
E o array é uma delas.
Veja bem: se o cache fosse sincronizar byte por byte da memória RAM com o cache a vantagem em relação à não ter cache seria pequena, por isso o computador tenta adivinhar quais partes da memória vão ser usadas daqui a pouco e sincroniza elas juntas.
E adivinha como ele tenta adivinhar?
Ele puxa memória próxima à que você pediu, que no caso do array seriam os próximos itens.
Por isso quando você precisa fazer operações em vários itens o array é em grande parte dos casos a opção mais rápida.

Mas isso tudo não significa que ele não tem desvantagens.
O array básico do C tem um tamanho fixo, ou seja, se você pediu 5 Inteiros não vai poder adicionar nem mais nem menos, o array vai ocupar esse espaço até ser liberado.
Por isso foram criados arrays dinâmicos que teoricamente aumentam e diminuem de tamanho.
Bom, na verdade eles não fazem isso não.
O funcionamento deles é que quando você precisa de mais itens, outro array maior é criado e todos os itens são copiados, mesma coisa quando você precisa ocupar menos espaço.
Isso tem como resultado que essas operações de aumentar de tamanho podem ser mais caras do que em outras estruturas de dados mais adequadas para isso.
Mas não tome isso como regra, o maior fator de lentidão dos computadores atuais são os acessos fragmentados à memória, que geralmente as estruturas que tentam diminuir o custo da adição/remoção de itens fazem um monte.
Então o melhor é sempre medir caso a caso.
Lembre-se: otimização prematura é a raiz de todo o mal (Donald Knuth).

Espero que você tenha gostado desse vídeo.
Se sim, não esquece de acessar o Moskos' CodeField pra aprender a implementar um Array dinâmico em C.
E se estiver se sentindo generoso nos apoie no catarse ou faça uma doação para nosso PIX `aparece o QR code e email`, os dados estão aqui aponta pro qr code e na descrição aponta pra baixo.
Até o próximo episódio.
