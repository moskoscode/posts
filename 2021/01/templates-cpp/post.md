# Templates em C++

Templates são uma ferramenta muita poderosa que permite programação genérica, ou seja, idependente de tipos. Isso permite a diminuição da repetição de código, que leva à uma base de código mais limpa e menos propensa à bugs. Além disso, já que o sistema de templates é turing completo, também permite a criação de código muito avançado que roda durante a compilação. Por isso o uso de templates muitas vezes também resulta em programas muito mais rápidos.

Mas nem por isso ele é sem desvantagens. Dependendo de como forem usados, templates podem aumentar bastante o tamanho do executável de um programa e/ou deixar a compilação bem mais demorada. Também são duramente criticados (por mim) pela sintaxe bastante repetitiva e verbosa.

Sem mais delongas vamos ver como usá-los para criar uma função `clamp` que vai permitir limitar um número à um valor entre um minimo e máximo, idependentemente do tipo de número.

```cpp
// Limita um número à um valor entre um mínimo e máximo
template<typename T>
T clamp(T num, T min, T max) {
    return (num < min)? min : (num > max)? max : num;
}
```

A parte básica do template é `template<...>` que diz que a próxima função/váriavel/classe pode ser usada com argumentos que serão processados em tempo de compilação. Eles podem ser tipos, inteiros, ponteiros, enums, packs de parametros e mais recentemente, desde o C++20, números de ponto flutuante ou classes literais (com [restrições](https://en.cppreference.com/w/cpp/language/template_parameters)).

Você determina o parametro com `typename` ou `class` para tipos ou o tipo do parametro para os outros, seguido do nome. No caso do `clamp` aceitamos um parametro de tipo com o nome `T` e todos os lugares que usamos `T` são substituídos com o parametro que passamos. Por exemplo:

```cpp
// Podemos usar com doubles
clamp<double>(1.5, -1, 1);  // Retorna 1.0

// Com ints
clamp<int>(3, 1, 10);  // Retorna 3

// Com qualquer tipo que defina os operadores < e >
clamp<std::string>("correr", "aaa", "bbb");  // Retorna "bbb"
```

Além disso a parte mais legal é que temos dedução de tipos, então poderiamos ter escrito assim:

```cpp
clamp(1.5, -1, 1);  // Retorna 1.0
clamp(3, 1, 10);  // Retorna 3

// Nesse caso as strings seriam deduzidas como const char[]
// que não tem os operadores < e >, por isso haveria uma falha de
// compilação
clamp("correr", "aaa", "bbb");  // Falha de compilação
```

Essa é a base dos templates, mas eles são muito mais poderosos. Se estiver interessado, dê uma olhada no nosso post sobre `stack_string` que são um tipo especial de string que eu desenvolvi que tem alocação na stack e permite formatação com o tamanho determinado em tempo de compilação - tudo isso usando templates e um pouco de constexpr.

Espero que tenha aprendido uma coisa ou duas e até semana que vêm!


