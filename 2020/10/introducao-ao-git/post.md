
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
-> Produção -> Venda`, aí quando um aparelho é lançado, recomeçam com um novo
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

# Como instalar

No o linux/BSD instalar o git é muito fácil, normalmente basta um

```yaml
$ sudo {gerenciador de pacotes} {instalar} git
```

no ubuntu isso se traduziria para `sudo apt install git` (mais possíveis
comandos [aqui](https://git-scm.com/download/linux)).

Já se você não têm a sorte de usar um sistema operacional livre, você pode
baixar instaladores para [MacOS](https://git-scm.com/download/mac) ou
[Windows](https://gitforwindows.org/)

Um aviso: **NÃO ENTRE EM PÂNICO**. Tudo que vamos fazer aqui vai ser na linha
de commando, mas eu te garanto que vai ser bem simples e tranquilo.

Para testar a instalação, abra o terminal (Git BASH, no Windows) e digite

```yaml
$ git --version
```

Se aparecer qualquer coisa diferente do que sua versão, provavelmente aconteceu
algo de errado na instalação e você deve dar uma olhada nisso antes de
continuar. No meu caso o resultado é o seguinte:

```yaml
$ git --version
git version 2.20.1
```

Como você pode ver, minha versão é um tanto desatualizada (a mais atual no
momento é a 2.28.0), mas não tem problema por que nesse tutorial só vamos ver coisas básicas
e, além disso, o git é, geralmente, bastante retrocompatível.


