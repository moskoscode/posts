<!--

# Para escrever
  - [X] Funções com argumentos variáveis
  - [X] Encaminhamento de argumentos

# Ideias de títulos
  - O que são os *args e **kwargs em python?
  - O que fazem os asteriscos em python?

# Ideias de subtítulos
  - Argumentos variáveis!
  - A beleza e condenação das linguagens dinâmicas

-->

Se você já leu uma quantidade razoável de código python, deve ter se deparado
com algo como `def processar(*args, **kwargs)` e se perguntou *Mas o que é
isso?*

É bem simples: é um jeito de uma função aceitar um número arbitrário de
argumentos, com ou sem palavra chave. Mais específicamente é um jeito de você
pegar uma lista (no caso do `*`) ou um dicíonario (no caso do `**`) e usar os
conteúdos dele como se você tivesse escrito os conteúdos por extenso.

Por exemplo se eu tiver uma lista `a` e usar print para mostrar os resultados,
vai ficar assim:

```python
>>> a = [1, 2, 3, 4]
>>> print(a)
[1, 2, 3, 4]
```

Vai ter uma formatação para indicar que estou imprimindo uma lista, não vários
números. Se eu fosse imprimir os números em si, seria assim:

```python
>>> print(1, 2, 3, 4)
1 2 3 4
```

E aí o `*` é um jeito de passar o conteúdo da lista **como se** eu tivesse
escrito eles um depois do outro.

```python
>>> print(*a)
1 2 3 4
```

E note que esse operador se aplica à qualquer iterável: `set`s, `list`s,
`tuple`s e até `dict`s, `generator`s e classes próprias

```python
>>> print( *set([10, 20, 2, 4, 10, 5]) )                # Set
2 4 5 10 20
>>> print( *[1, 2, 3] )                                 # List
1 2 3
>>> print( *(4,2,5) )                                   # Tuple
4 2 5
>>> print( *{"nome": 1, "aa": 2} )                      # Dict
nome aa
>>> print( *range(0, 10, 2) )                           # Range
0 2 4 6 8
>>> print( *(a if a == 2 else 7 for a in [1, 2, 3]) )   # Generator
7 2 7
```

Além disso podemos usar o `*` para receber uma quantidade qualquer de
argumentos em uma função. Por exemplo o próprio `print()` que estamos usando
aceita desde 1 até infinitos argumentos, podemos imitar isso com uma definição
assim:

<!-- spell-checker: disable -->
```python
def argumentos_variaveis(arg, *args):
    print(f"Argumento 1: {arg}, Restante: {args}")
```
<!-- spell-checker: enable -->

E aí podemos usar essa função com quantos argumentos quisermos (no minímo 1)

<!-- spell-checker: disable -->
```python
>>> argumentos_variaveis(1, 2, 3, 4, 5, 6)
Argumento 1: 1, Restante: (2, 3, 4, 5, 6)
>>> argumentos_variaveis("batatinha")
Argumento 1: batatinha, Restante: ()
>>> argumentos_variaveis((2700))
Argumento 1: 2700, Restante: ()
>>> argumentos_variaveis((2700,), (37, 5), 6)
Argumento 1: (2700,), Restante: ((37, 5), 6)
```
<!-- spell-checker: enable -->

Por causa dessas duas possibilidades (passar argumentos e recebe-los) que o
`*args` é tão usado em decoradores ou qualquer função que "embrulhe" outra. Por
exemplo, se quiséssemos saber exatamente **quando** cada print foi chamado
podemos usar isso.

```python
import time

def print_quando(*args):  # Aceita argumentos quaisqueres
    print("[", time.asctime(), "]:  ", *args)

```

E ai alem da saida normal do print, quando chamarmos essa função vamos ver o
horário dessa execução.

```python
>>> print_quando(10, 20, 30)
[ Sun Oct 11 20:51:17 2020 ]:   10 20 30
>>> print_quando("Uma mensagem pra vocês aí")
[ Sun Oct 11 20:52:45 2020 ]:   Uma mensagem pra vocês aí
```

Tá, até agora só falamos do `*args` e o `**kwargs`?

Pois é, eu me enrolei... mas é que eles são basicamente a mesma coisa!

A única diferença é que o `**` é bom pra `dict`s porque ele mantém as palavras
chave. Por exemplo se tivermos uma função `dar_nota()` e tentar encaminhar
argumentos para ela com `encaminhar()`, sendo que elas são assim:

```python
def dar_nota(aluno="", nota=0):
    print(f"A nota do {aluno} foi {nota}")

def encaminhar(*args):
    dar_nota(*args)
```

Não vamos conseguir. Tipo... Até vamos, mas não totalmente, olha:

```python
>>> dar_nota("Eduardo", 2000)
A nota do Eduardo foi 2000
>>> encaminhar("Nicolas", 2)
A nota do Nicolas foi 2
```

Nesse caso básico funciona, mas já se quisermos usar as palavras chave não vai
dar.

```python
>>> dar_nota(nota=20, aluno="Pedro Cássio")
A nota do Pedro Cássio foi 20
>>> encaminhar(nota=623, aluno="Terroso Carlos")
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
TypeError: encaminhar() got an unexpected keyword argument 'nota'
```

Levamos um `TypeError` na cara, mas felizmente existe o `**kwargs` que preserva
o nome dos argumentos. Se redeclararmos `encaminhar()` usando-o resolvemos
todos os erros:

```python
>>> def encaminhar(*args, **kwargs):
...     dar_nota(*args, **kwargs)
...
>>> encaminhar(nota=623, aluno="Terroso Carlos")
A nota do Terroso Carlos foi 623
```

E... é isso, como tudo em python, super duper simples. Até semana que vem.

