# Exceções em C++

Às vezes não dá pra fazer alguma coisa. Por exemplo, dividir 10 por 0 é impossível, ou seja, isso é uma exceção ao funcionamento da conta de divisão. Por isso, se você tivesse programado uma função `dividir(a, b)`, os casos em que `b` são zero seriam os exemplos perfeitos de quando levantar uma exceção.

Fazer isso seria muito simples:

```cpp
double dividir(double a, double b) {
	if (b == 0)
		throw std::logic_error("Não é possível dividir por zero!");
	
	return a/b;
}
```

Mas aí o que fazer com isso? Deixar o programa terminar toda vez que uma exceção aparece? Não, né!

Lidar com elas é simples e elegante, foram criadas especificamente para que você possa processar os erros em um lugar separado do código principal. Digamos que você tenha usado essa função de dividir em um programa de calculadora.

```cpp
#include <iostream>

int main() {
	std::cout << "Insira uma conta: " << std::endl;
    int primeiro, segundo;
    char operador;
    std::cin >> primeiro >> operador >> segundo;

    switch (operador) {
        case '/':
            std::cout << dividir(primeiro, segundo) << std::endl;
            break;
        case '*':
            std::cout << primeiro * segundo << std::endl;
            break;
        case '+':
            std::cout << primeiro + segundo << std::endl;
            break;
        case '-':
            std::cout << primeiro - segundo << std::endl;
            break;
    }
}

```

Ao invés de deixar o programa terminar com erro (como acontece agora), é possível capturar todos os erros que qualquer cálculo possa dar e reportá-los ao usuário de uma forma uniforme e pedir para inserir a operação novamente. Essa captura dos erros se dá com um bloco `try/catch` (tente/capture) que vai, como o nome diz, *tentar* fazer alguma coisa e *capturar* qualquer erro que dê.

```cpp
int main() {
	bool bem_sucedido = false;

	while (!bem_sucedido) {
		std::cout << "Insira uma conta: " << std::endl;

    	int primeiro, segundo;
    	char operador;
    	std::cin >> primeiro >> operador >> segundo;

		// Tente
		try {
		    switch (operador) {
		        case '/':
		            std::cout << dividir(primeiro, segundo) << std::endl;
		            break;
		        case '*':
		            std::cout << primeiro * segundo << std::endl;
		            break;
		        case '+':
		            std::cout << primeiro + segundo << std::endl;
		            break;
		        case '-':
		            std::cout << primeiro - segundo << std::endl;
		            break;
		    }

			// Não chega aqui se tiver dado erro
			bem_sucedido = true;

		} catch (std::exception& ex) {  // Capture qualquer exceção
			std::cout << "ERRO: " << ex.what() << ", por favor tente novamente" << std::endl;
		}
	}
}
```

Então, antes ficava assim:

```bash
$ g++ main.cpp && ./a.out                                                                                                                                                
Insira uma conta:                                                                                                                                                        
5 / 0                                                                                                                                                                    
terminate called after throwing an instance of 'std::logic_error'    
  what():  Não é possível dividir por zero    
Aborted (core dumped)
$
```

Mas com o gerenciamento de erros, fica assim:

```bash
$ g++ aa.cpp && ./a.out                                                                                                                                                  
Insira uma conta:                                                                                                                                                        
5 / 0                                                                                                                                                                    
ERRO: Não é possível dividir por zero, por favor tente novamente                                                                                                         
Insira uma conta:

```

Apesar de facilitar bastante a vida do programador que não tem que checar e lidar com o mesmo erro 500 vezes, já que as exceções se propagam pelas funções até serem capturadas onde realmente são relevantes, e de aumentar a segurança porque garante que nenhum erro será ignorado por esquecimento, muitas pessoas não gostam delas. Por quê? Elas são um jeito lerdo de lidar com erros - teoricamente.

Existem casos que elas são mais rápidas, principalmente quando o substituto realmente tem o mesmo poder que elas, mas de forma geral elas são realmente muito devagar. Por isso é necessário bom senso para usá-las, afinal são chamadas de `exceções` porque foram feitas para serem usadas em casos que são exceções à regra, ou seja, que não acontecem muito. Qualquer função que jogue exceções mais do que 5% das vezes está usando elas de forma errada!

Se um caso de não funcionamento da função é normal, como uma senha que não atende aos critérios de segurança no formulário de cadastro, uma exceção **não** é o jeito certo de lidar com isso. O melhor que você pode fazer é redesenhar a aplicação para que haja uma verificação antes de enviar a senha para o servidor, e aí sim, se depois de enviada a senha ainda é fraca, pode mandar uma exceção que provavelmente você encontrou uma falha de segurança no seu sistema.

Muito obrigado por ler, espero que você tenha gostado desse post! Até semana que vem, com mais um post aqui no Moskos' CodeField.