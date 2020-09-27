
<!---

# A ser abordado
 - [X] O que é e por que usar o git
 - [X] Como instalar
 - [X] Criando um repositório
 - [ ] Commitando arquivos
 - [ ] Editando arquivos
 - [ ] Ramificando
 - [ ] Mesclando alterações
 - [ ] Clonar, Pull & Push

# Ideias de Tĩtulo
### Tĩtulo
 - Git para iniciantes
 - Introdução ao Git
 - Mas o que carvalhos é Git?

### Subtĩtulo
 - Uma breve introdução à gerenciamento de versão
 - Imagine viajar no tempo - com Git isso é *quase* possível

-->

# O que é e por que usar o git

Muitas áreas de trabalho tem um ciclo de produção que gira em torno de novos
produtos. Por exemplo o desenvolvimento de celulares segue basicamente `Projeto
-> Produção -> Venda`, aí quando um aparelho é lançado, recomeçam com um novo
projeto. Mas em software a história é bem diferente: Um programa bem sucedido
muito raramente é reescrito, ele normalmente é alterado de pouco em pouco,
possívelmente para todo o sempre. Olhe o Linux como exemplo: é o mesmo software
desde 1991! Por esse motivo, se torna praticamente impossível trabalhar sem
nenhum gerenciamento de versão em qualquer projeto maior que algumas centenas
de linhas. Afinal imagine que você acabou de lançar a versão 1.0 de um programa
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
de comando, mas eu te garanto que vai ser bem simples e tranquilo.

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
momento é a 2.28.0), mas não tem problema por que nesse tutorial só vamos ver
coisas básicas e, além disso, o git é, geralmente, bastante retrocompatível.

# Criando seu primeiro repositório

Para começar vamos precisar de um repositório (que é basicamente uma pasta do
projeto, só que com um histórico de todas as mudanças). Criar um é bem simples:
basta criar uma pasta e colocar o comando `git init` nela.

<!-- spell-checker: disable -->
```yaml
$ mkdir meu-repositorio  # Cria uma pasta pela linha de comando
$ cd meu-repositorio     # Entra na pasta
$ git init               # Inicializa o repositório
Initialized empty Git repository in /home/eduardo/moskoscode/posts/2020/10/introducao-ao-git/meu-repositorio/.git/
```
<!-- spell-checker: enable -->

E simples assim, temos um repositório.

Vamos ver alguns comandos do git então. Para obtermos informações sobre o
estado atual do nosso repo, podemos usar o `git status`

<!-- spell-checker: disable -->
```yaml
$ git status
On branch master

No commits yet

nothing to commit (create/copy files and use "git add" to track)
```
<!-- spell-checker: enable -->

No caso o git está nos dizendo que estamos no ramo "master" (vamos ver isso
depois) e que não temos *commits* ainda.

Um commit é basicamente um "salvar", mas um pouco diferente, é mais tipo "se
comprometer". Isso por que quando você faz um *commit*, você está *se
compromissando* com o estado dos arquivos no repositório, que a partir dali vão
ser salvos como um momento ao qual você vai poder voltar.

Vamos ver na prática para entender melhor.

# Commitando Arquivos

Vamos criar um arquivo simples pra começar, uma receita (pra variar).

```markdown
# Ingredientes
 - 1 Xícara de Batata Doce
 - 200 mg de Água
 - 5 moléculas de Nitrato de Cálcio

# Modo de preparo
Coloque a Batata Doce em uma tigela e amasse até ficar bem pastosa, aí adicione
a água e misture. Coloque em um acelerador de partículas seguido do Nitrato de
Cálcio e ligue por 10 minutos à 1/10 da velocidade da luz.

Rende 3 porções
```

<!-- spell-checker: disable-next-line -->
Podemos dar ao arquivo o nome de `pure-de-batata-monstro.md` e salvar.

Agora, se dermos git status de novo

<!-- spell-checker: disable -->
```yaml
$ git status
On branch master

No commits yet

Untracked files:
  (use "git add <file>..." to include in what will be committed)

        pure-de-batata-monstro.md

nothing added to commit but untracked files present (use "git add" to track)
```
<!-- spell-checker: enable -->

Podemos ver que nosso arquivo apareceu, ele está na sessão dos arquivos
**untracked** que são arquivos que o git não administra por que não há nenhum
commit que os inclua. Podemos mudar isso usando o `git add` para adicionar esse
arquivo para nossa *staging area* (área de preparação) na qual preparamos o
commit que vamos fazer.

```yaml
$ git add pure-de-batata-monstro.md
```

```yaml
$ git status
On branch master

No commits yet

Changes to be committed:
  (use "git rm --cached <file>..." to unstage)

        new file:   pure-de-batata-monstro.md

```

Agora podemos ver que o arquivo foi para um lugar diferente, para "Changes to
be commited" (mudanças a serem commitadas) e está marcado como um arquivo novo
(new file). Então, como tudo parece certo, podemos commitar nossa receita.

```yaml
$ git commit -m "Criada receita de Pure de Batata Monstro"
[master (root-commit) 4400893] Criada receita de Pure de Batata Monstro
 1 file changed, 11 insertions(+)
 create mode 100644 pure-de-batata-monstro.md
```

Nesse relatório podemos ver que o `pure-de-batata-monstro.md` foi criado e que
ele teve 11 linhas inseridas.

