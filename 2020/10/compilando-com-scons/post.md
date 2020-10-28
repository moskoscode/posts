
<!--
# Possíveis subtitulos:
    - Matador do make?
    -
-->

Recentemente fizemos um post sobre como usar o make para criar arquivos a
partir de outros (por exemplo criar um executável a partir de código-fonte).
Hoje vamos falar sobre o SConstruct que serve para esse mesmo propósito, mas
com um poder multiplicado por tipo 10. O que o torna tão especial é que ele é
escrito totalmente em python ao invés de em comandos do terminal. Isso permite
a ele ser muito mais portátil (não depende tanto dos programas instalados no
computador do usuário, ou do sistema operacional) e dá todo o poder da segunda
linguagem de programação mais popular do mundo ao seu processo de compilação.
Além de prover camadas de abstração que simplificam até um `Hello, World`.

Mas pra que alguém precisaria disso? Compilar é só transformar uns arquivos
`.c` em `.o` e juntar eles num executável né?

Pode ser... mas depende.

Existem casos que podem ser bem mais complexos como um programa que depende de
multiplas linguagens de programação e com várias dependencias, em casos assim o
scons destrói a concorrencia. Mas hoje vamos começar com o básico do básico: um
`Hello, World` que vamos colocar no arquivo `hello.c`:

```c
#include <stdio.h>

int main(void) {
    printf("Hello, World\n");
}
```

Uma Makefile para isso seria tipo assim:

```make
all: hello.out

%.out: %.c
	cc $< -o $@
```

Simples, mas com uns simbolos já meio estranhos. Essa é a saída:

```bash
$ make
cc hello.c -o hello.out
$ ./hello.out
Hello, World
```

Funciona, mas pra um programa um pouco mais complexo (tipo com mais arquivos)
já daria uma dificultada, teria que fazer gerar primeiro um `.o` e depois
juntar tudo, normalmente especificando cada arquivo à mão. Já vamos ver como
seria, mas esse é um post sobre SCons então vamos ver a SConstruct equivalente
(é a mesma lógica do make, você cria um arquivo com esse nome e roda `scons`).

```python
Program("hello.out", "hello.c")
```

Uma linha apenas. Vamos ver se funciona.

```bash
$ rm hello.out  # Primeiro remover arquivo que o make fez
$ scons
scons: Reading SConscript files ...
scons: done reading SConscript files.
scons: Building targets ...
gcc -o hello.o -c hello.c
gcc -o hello.out hello.o
scons: done building targets.
$ ./hello.out
Hello, World
```

Uau bem mais coisa. Tudo que está com "scons:" é mensagem do próprio scons
relatando progresso, podemos desativar elas com a opção `-Q`. Mas se as
ignorarmos podemos ver que ele roda o `gcc` quase do mesmo jeito que o make,
mas automaticamente gerando os arquivos `.o` intermediários.

Eu imagino que você já pode ver a vantagem do scons, mas se ainda não, vamos
aumentar um pouco a complexidade do nosso programa adicionando mais um arquivo
para ver como cada programa se sai.

hello.c:
```c
// Print com fim de linha
void println(const char*);

int main(void) {
	println("Hello, World");
}
```

println.c:
```c
#include <stdio.h>

// Print com fim de linha
void println(const char* texto) {
	puts(texto);
}
```

Nossa Makefile teria que ficar assim:

```make
all: hello.out

hello.out: hello.o println.o
	cc hello.o println.o -o $@

%.o: %.c
	cc -c $< -o $@
```

E ainda funciona.

```bash
$ make
cc -c hello.c -o hello.o
cc -c println.c -o println.o
cc hello.o println.o -o hello.out
$ ./hello.out
Hello, World
```

Mas já tivemos que escrever arquivos especificos tipo 2 vezes já, nas dependencias
e no comando em si. Vamos ver como o SCons se sai:

```python
Program("hello.out", ["hello.c", "println.c"])
```

Ainda ***uma*** linha. Só tivemos que adicionar o novo arquivo que queremos. Na
verdade mesmo podemos fazer ainda melhor.

```python
Program("hello.out", Glob("*.c"))
```

A função Glob olha os arquivos que você tem e retorna aqueles que se adequam à
string que você passou. No caso `"*.c"` encontra qualquer aquivo que termine em
`.c` na pasta atual. Assim você pode continuar aumentando o programa
indefinidamente e enquanto você não colocar as coisas em diretórios separados o
scons vai continuar compilando tudo perfeitamente sem mais alterações.

```bash
$ scons -Q
gcc -o hello.o -c hello.c
gcc -o println.o -c println.c
gcc -o hello.out hello.o println.o
$ ./hello.out
Hello, World
```

Então imagino que você já possa ver como scons é incrível. Nas próximas semanas
vou fazer um post mostrando como criar sua própria versão do `Program` para
usar outros comandos para processar arquivos próprios. E sobre como o SCons
simplificou **muito** um problema real na compilação de um dos meus programas.
Então não deixe de se inscrever na newsletter e nos acompanhar nas redes
sociais para não perder. Até lá.

