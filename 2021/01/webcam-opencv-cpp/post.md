Olá e bem vindos à mais um post. Hoje vamos aprender como criar um aplicativo de webcam (bem simples) com OpenCV, que é a mais completa biblioteca livre de Visão Máquina do momento.

A instalação é simples, para o windows você pode baixar um instalador [aqui](https://opencv.org/releases/), no ubuntu/debian/derivados mandar um `sudo apt install libopencv-dev` ou, no mac com [HomeBrew](https://brew.sh/), `brew install opencv`.

Para começar precisamos nos conectar à webcam. Podemos fazer isso criando um objeto `cv::VideoCapture`, devemos passar ao construtor o número da webcam que queremos conectar, começando do 0.

```cpp
#include <opencv2/videoio.hpp>

int main() {
    // Conecta à camera
    cv::VideoCapture cap(0);
}
```

Esse método tem um problema: ele não espera a camera estar disponivel. Se ela estiver sendo usada por outro programa ou não estiver conectada, o programa simplesmente não vai conseguir ler a imagem dela e falhará quando for tentar exibi-la. Para remediar isso vamos criar um loop que fica tentando conectar à câmera até conseguir.

```cpp
#include <opencv2/videoio.hpp>

int main() {
    // Tenta conectar à camera até conseguir
    cv::VideoCapture cap;
    while (!cap.isOpened()) {  // Enquanto não estiver aberta
        cap.open(0);  // Tenta abrir a camera 0
    }
}
```

Agora o que precisamos é de outro loop que lerá as imagens da webcam para exibir na tela. Para isso vamos usar a função `cv::VideoCapture::read()` que armazena a imagem em um `cv::Mat` e retorna se foi bem sucedido nessa operação. Aí para mostrar a imagem podemos usar a função `cv::imshow` que cria um nova janela do sistema operacional, se não existir, e coloca a imagem nela.


```cpp
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

int main() {
    // Tenta conectar à camera até conseguir
    cv::VideoCapture cap;
    while (!cap.isOpened()) {
        cap.open(0);
    }

    // Armazena a imagem atual da camera
    cv::Mat img;

    // Enquanto for possivel ler novas imagens
    while (cap.read(img)) {
        // Mostra a imagem na janela chamada "webcam"
        cv::imshow("webcam", img);
    }
}
```

Só com essa pequena quantidade de código já é possível usar a webcam. A compilação vai depender do seu sistema operacional e de como você instalou o opencv. O comando no linux/macos/winmg é

```bash
$ g++ main.cpp -o webcam -I/usr/include/opencv* -lopencv_core -lopencv_highgui -lopencv_videoio
```

Esse comando usa o `g++` pra compilar o arquivo `main.cpp` em um executável `webcam` e inclui arquivos da pasta `/usr/include/opencv*` e linka com as bibliotecas `opencv_core`, `opencv_highgui` e `opencv_videoio`. Infelizmente eu não sei fazer isso com o Visual Studio (Windows), mas não é pra ser difícil. [Aqui](https://docs.opencv.org/master/d3/d52/tutorial_windows_install.html) tem um tutorial que pode ajudar.

Depois de usar o comando você pode executar o programa com

```bash
$ ./webcam
```

Você pode fechá-lo com `Ctrl + C` no terminal.

Existe a chance que mesmo com a webcam conectada você não esteja conseguindo ver as imagens ainda, isso é porque seu computador consegue calcular coisas bem mais rápido do que consegue exibir imagens, então ele está fazendo o loop da camera tão rápido que não dá tempo das imagens aparecerem mesmo.

Podemos arrumar isso usando a função `cv::waitKey()` que vai esperar X millisegundos, ou até uma tecla ser apertada (se você passar 0 ela espera pra sempre). Isso vai dar uma pausa para que a imagem consiga aparecer.

```cpp
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

int main() {
    // Tenta conectar à camera até conseguir
    cv::VideoCapture cap;
    while (!cap.isOpened()) {
        cap.open(0);
    }

    // Armazena a imagem atual da camera
    cv::Mat img;

    // Enquanto for possivel ler novas imagens
    while (cap.read(img)) {
        // Mostra a imagem na janela chamada "webcam"
        cv::imshow("webcam", img);
        
        // Espera 10ms para dar tempo de a imagem aparecer
        cv::waitKey(10);
    }
}
```

Então é isso por hoje, bem simples. Um desafio pra você é conseguir fazer com que o app tire uma foto quando você apertar `f`. Uma dica é que a função `cv::waitKey()` retorna qual tecla foi pressionada no intervalo. E você vai precisar adicionar `-lopencv_imgcodecs` no comando de compilação quando for salvar a imagem.

Espero que você tenha aprendido uma coisa ou duas nesse tutorial, até semana que vem.
