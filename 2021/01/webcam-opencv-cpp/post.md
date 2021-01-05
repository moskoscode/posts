Olá e bem vindos à mais um post. Hoje vamos aprender como criar um aplicativo
de webcam (bem simples) com OpenCV, que é a mais completa biblioteca livre de
Visão Máquina do momento.

A instalação é simples, para o windows você pode baixar um instalador
[aqui](https://opencv.org/releases/), mandar um `sudo apt install
libopencv-dev` no ubuntu/debian/derivados ou `brew install opencv` no mac (com
[HomeBrew](https://brew.sh/)).

Para começar precisamos nos conectar à webcam. Podemos fazer isso criando um
objeto `cv::VideoCapture`, devemos passar ao construtor o número da webcam que
queremos conectar, começando do 0.

```cpp
#include <opencv2/videoio.hpp>

int main() {
    // Conecta à camera
    cv::VideoCapture cap(0);
}
```

Esse método tem um problema: ele não espera a camera estar disponivel. Se ela
estiver sendo usada por outro programa ou não estiver conectada, o programa
simplesmente não vai conseguir ler a imagem dela e falhará quando for tentar
exibi-la. Para remediar isso vamos criar um loop que fica tentando conectar à
camera até conseguir.

```cpp
#include <opencv2/videoio.hpp>

int main() {
    // Tenta conectar à camera até conseguir
    cv::VideoCapture cap;
    while (!cap.isOpened()) {
        cap.open(0);
    }
}
```

Agora o que precisamos é de outro loop que lerá as imagens da webcam para
exibir na tela. Para isso vamos usar a função `cv::VideoCapture::read()` que
armazena a imagem no `cv::Mat` que passarmos e retorna se for bem sucedido
nessa operação. Já para mostrar a imagem podemos usar a função `cv::imshow` que
cria um nova janela do sistema operacional se não existir.


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

Só com essa pequena quantidade de código já é possivel usar a webcam. A
compilação vai depender do seu sistema operacional e de como você instalou o opencv

