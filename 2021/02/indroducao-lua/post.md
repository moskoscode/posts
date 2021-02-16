# Uma brevíssima introdução/referência para Lua

Lua é uma linguagem de programação que comecei a usar semana passada. Ela é muito simples e me lembra de python, só que muito menor. O post de hoje é em parte uma introdução à linguagem e em parte uma pequena referência de sintaxe para aqueles, que como eu, estão começando a aprender sobre ela.

Primeiro de tudo, como instalar? Lua é distribuída em pacotes de código fonte (tarball) que devem ser compilados. Felizmente ela é escrita em ANSI C puro, sem dependências, então pode ser compilada em qualquer sistema com um compilador C. Você pode baixar o código fonte [aqui](https://www.lua.org/ftp/), se você estiver no windows vai precisar de um software como [7zip](https://www.7-zip.org/) para descompactar.

Para aqueles de nós que não são tão chegados em compilar software, podemos baixar arquivos binários dos repositórios de (quase) todos os sistemas operacionais existentes. Se você estiver usando linux/BSD, use o comando que você normalmente usa para instalar as coisas. No mac você pode usar [MacPorts](https://www.macports.org/) ou [HomeBrew](https://brew.sh/). E no Windows você pode usar o [Subsistema do Windows para Linux](https://docs.microsoft.com/en-us/windows/wsl/install-win10), [Cygwin](https://www.cygwin.com/) ou [Chocolatey](https://chocolatey.org/packages?q=lua).

Agora que está tudo devidamente instalado podemos começar a programar. Primeiro de tudo o clássico "Hello, World!":

```lua
print("Hello, World!")
```

Muito fácil né? A linguagem inteira é assim.

Para rodar podemos salvar isso em um aquivo `.lua` e rodar com

```bash
$ lua main.lua
Hello, World!
```

Comentários são partes do arquivo que são totalmente ignoradas pelo interpretador e são feitos com `--` para uma linha, comentários de múltiplas linhas podem ser feitos com ``--[[ comentário ]]--`.

```lua
print("Hello, World!")  -- Isso é um comentário

--[[
	Isso é um comentário
	de várias linhas.
]]--

print("Tchau, Mundo!")  -- O interpretador só vê os "print"s
```

Agora vamos criar umas variáveis. Lua tem duas categorias delas: local e global. Por padrão as variáveis são globais e você deve especificar `local` para torná-las locais.

```lua
i = 10        -- Variável global
local j = 20  -- Variável local
```

No geral variáveis locais são consideradas de melhor estilo, já que só são visíveis para o escopo atual (função, módulo, loop) e por isso dificultam que alguma alteração inesperada seja feita à ela. Além disso variáveis locais são marginalmente mais rápidas. Para facilitar a questão de escopo vamos ver esse exemplo:

```lua
local var1 = "Escopo de módulo"   -- Só é visível nesse módulo (arquivo)
var2 = "Global"                   -- Pode ser vista e alterada por qualquer módulo (arquivo)

do  -- Marca o início de um escopo
	local var3 = "Escopo até o end"  -- Visível até o "end"
	var4       = "Global"            -- Mesmo escopo de var2

end -- Fim do escopo

print(var1)  -- Funciona
print(var2)  -- Funciona
print(var3)  -- Não Funciona
print(var4)  -- Funciona
```

Os operadores matemáticos são os mesmos de outras linguagens: `+, -, / e *`. Não existem operadores de mudar o valor de uma variável no lugar, como `+=` ou `++`. O operador mais diferente é o de concatenar texto: `..`

```lua
-- Operadores matemáticos
print(1 + 2)  -- 3
print(1 - 2)  -- -1
print(1 / 2)  -- 0.5
print(1 * 2)  -- 2
print(2 ^ 2)  -- 4.0

-- Concatenar texto
print("1 + 2 é " .. "3")  -- 1 + 2 é 3
print("1 + 2 é " .. 1 + 2)  -- 1 + 2 é 3

```

