#include <iostream>
#include <tensorflow/lite/c/c_api.h>

int main() {

    std::cout << "Hello, World!" << TfLiteVersion() << std::endl;
    return 0;
}
