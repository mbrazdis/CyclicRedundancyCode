#include <iostream>
#include <string>
#include <vector>

//function for verify if a string is binary
bool isBinary (const std::string& str) {
    for(char c : str) {
        if(c != '0' && c != '1') return false;
    }
    return true;
}

void printVector(const std::vector<char>& vec) {
    for(char c : vec) {
        std::cout << c;
    }
    std::cout <<std::endl;
}

void printIntermediateStep(const std::vector<char>& message, const std::vector<char>& generator, int step, int position) {
    std::cout << "Pasul " << step << ":" << std::endl;
    printVector(message);
    for (int p = 0; p < position; ++p) {
        std::cout << " ";
    }
    for (char c : generator) {
        std::cout << c;
    }
    std::cout << std::endl;
    std::cout << "-----------" << std::endl;
}

std::vector<char> xorOperation(std::vector<char> message, const std::vector<char>& generator) {
    int generatorLength = generator.size();
    int step = 1;
    for (size_t i = 0; i <= message.size() - generatorLength; ++i) {
        if (message[i] == '1') {
            printIntermediateStep(message, generator, step++, i);
            for (int j = 0; j < generatorLength; ++j) {
                message[i + j] = (message[i + j] == generator[j]) ? '0' : '1';
            }
            printVector(message);
            std::cout << std::endl;
        }
    }
    return message;
}


int main() {
    std::string inputmessage, generatorPolynomial;
    std::cout << "Introduceti mesajul binar: ";
    std::cin >> inputmessage;
    std::cout << "Introduceti polinomul generator: ";
    std::cin >> generatorPolynomial;
    std::cout << std::endl;

    if(!isBinary(inputmessage) || !isBinary(generatorPolynomial)) {
        std::cout << "Mesajul si polinomul trebuie sa fie binare.\n";
        return 1;
    }

    int messageLenght = inputmessage.length();
    int generatorLenght = generatorPolynomial.length();

    if (messageLenght <= generatorLenght) {
        std::cout << "Lungimea mesajului trebuie sa fie mai mare decat numarul de coeficienti ai polinomului generator.\n";
        return 1;
    }
    std::vector<char> extendedMessage(inputmessage.begin(), inputmessage.end());
    for(int i = 0; i < generatorLenght - 1; ++i) {
        extendedMessage.push_back('0');
    }

    std::vector<char> generator(generatorPolynomial.begin(), generatorPolynomial.end());

    std::vector<char> remainder = xorOperation(extendedMessage, generator);

    std::vector<char> finalRemainder(remainder.end() - (generatorLenght - 1), remainder.end());

    std::vector<char> finalMessage(inputmessage.begin(), inputmessage.end());
    for(char bit : finalRemainder) {
        finalMessage.push_back(bit);
    }

    std::cout << "Rezultatul final: ";
    printVector(finalMessage);
    return 0;
}
