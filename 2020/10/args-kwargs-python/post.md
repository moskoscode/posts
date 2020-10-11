<!--

# Para escrever
  - [ ] Funções com argumentos variáveis
  - [ ] Encaminhamento de argumentos
  - [ ] Decoradores
  - [ ] Um formatador ingênuo

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


