
# A ser abordado
 - O que é e por que usar o git
 - Como instalar
 - Criando um repositorio
 - Editando arquivos
 - Ramificando
 - Mesclando alterações
 - Clonar, Pull & Push

# O que é e por que usar o git

Muitas áreas de trabalho tem um ciclo de produção que gira em torno de novos
produtos. Por exemplo o desenvolvimento de celulares segue basicamente `Projeto
-> Producao -> Venda`, aí quando um aparelho é lançado, recomeçam com um novo
projeto. Mas em software a história é bem diferente: Um programa bem suscedido
muito raramente é reescrito, ele normalmente é alterado de pouco em pouco,
possívelmente para todo o sempre. Olhe o Linux como exemplo: é o mesmo software
desde 1991! Por esse motivo, se torna praticamente impossível trabalhar sem
nenhum gerenciamento de versão em qualquer projeto maior que algumas centenas
de linhas. Afinal imagine que você acabou de lancar a versão 1.0 de um programa
que vendeu 10 cópias, e continuou o desenvolvimento, é bem provável que
enquanto a versão 2.0 estiver sendo escrita alguns problemas vão surgir na 1.0,
possivelmente problemas de segurança que realmente precisam ser arrumados
**urgentemente**. Sem nenhum tipo de gerenciamento de versão o que acontece?
*"Ah, eu sei que pode ser que você seja invadido, mas a versão 2.0 ainda está
muito instável"*. Assim não dá né? Com o git você poderia rapidamente *voltar
no tempo* para o código da versão 1.0 e arrumar o problema, criando uma versão
1.1.

Outro problema bastante recorrente que o git resolve é o de colaboração: E se
dois desenvolveres precisarem editar o mesmo arquivo *ao mesmo tempo*, o que
acontece? Normalmente seria necessário escolher uma das versões, ou manualmente
ir atrás de *cada uma* das mudanças pra tentar encaixa-las em um
frankenarquivo. Mas com o git esse problema quase que desaparece: ele vem com
poderosas capacidades de mesclagem automática, que permitem facilmente juntar
várias versões de um arquivo - desde que as alterações não tenham acontecido na
mesma linha (nesse caso o git pede sua ajuda pra resolver o conflito).

Tudo isso parece ótimo, então como usar? Primeiro precisamos instalar o git.

