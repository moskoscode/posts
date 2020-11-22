Olá e bem vindos à mais um post. Hoje vamos falar sobre dados e como
armazená-los ou comunicá-los efetivamente. Hoje vamos falar sobre JSON e
mais especificamente sobre como trabalhar com ele na linguagem de
programação C++.

JSON nada mais é do que um formato de arquivos (.json) e comunicação de dados.
Significa *JavaScript Objecr Notation* (Notação de Objeto do JavaScript) e se
originou como uma forma de facilitar a comunicação de servidores com páginas da
web (que normalmente são programadas em JavaScript), e já que a web se tornou
tão grande como é hoje, virtualmente **todas** as linguagens de programação
ganharam uma biblioteca de serialização de JSON. Aqui está uma amostra de como
são armazenados dados nesse formato:

```json
{
    "chave": "valor",
    "lista": [1, 2, 3, "quatro", 5, [6, 7]],
    "objeto": {
        "item1": "valor",
        "item2": "batata",
        "item3": null
    },
    "verdadeiro": true,
    "falso": false
}
```

Mas, é claro, ele também pode ser usado para armazenar coisas mais úteis, como
dados de um cliente.

```json
{
    "cliente": "Super Max Eletro CO.",
    "endereço": {
        "rua": "Rua São Carlos",
        "bairo": "Guarapé",
        "complemento": null,
        "CEP": 34254890
    },
    "temEntradaCaminhao": false,
    "crédito": 20.53,
    "compras": [
        {
            "valor": 34.23,
            "data": "20/03/2020"
        },
        {
            "valor": 11.99,
            "data": "20/03/2020"
        },
        {
            "valor": 105.87,
            "data": "20/03/2020"
        }
    ]
}
```

Algumas das grandes vantagens em usar esse formato para armazenar suas
informações ao invés de algo como o que foi apresentado no nosso post sobre
como [trabalhar com arquivos em
c++](https://moskoscode.com/trabalhando-com-arquivos-em-c/) são:
 - Portabilidade: Os arquivos podem ser lidos a partir de várias linguagens de
   programação de uma maneira mais fácil.
 - Retrocompatibilidade: Como os valores são acessados por chaves, uma futura
   reorganização dos dados ou adição de mais valores é improvável de quebrar um
   versão anterior do programa
 - Facilidade. É muito mais simples de usar uma biblioteca de JSON do que
   *fstream*s (para esse propósito)

Gostou? Então vamos aprender a usar. Primeiro você vai querer agarrar uma cópia
da [biblioteca de header
único](https://moskoscode.com/bibliotecas-de-header-unico/)
[`nlohmann/json`](https://github.com/nlohmann/json), é só clicar
[aqui](https://raw.githubusercontent.com/nlohmann/json/master/single_include/nlohmann/json.hpp)
para a versão estável mais recente.



