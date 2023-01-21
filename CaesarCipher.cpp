#include <iostream>
#include <string>
#include <vector>
#include <limits>


void CreateHeaderText(std::string text);
void CreateDividerText();
void CreateErrorText(std::string text);
bool GetBoolUserInput(std::string text);

//Specific
void CaesarInit();
int CheckTextValidity(std::string text);
bool CaesarCipherEncrypt(std::string &text, int shift);
bool CaesarCipherDecrypt(std::string &text, int key);
bool IsSymbol(char c);
std::vector<char> AlphabetVect {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
std::vector<char> SymbolVect {'.','!','@','#','$','%','^','&','*','(',')','_','-','=','+','<','>','/','?','1','2','3','4','5','6','7','8','9','0',' ',',',':',';'};

int main() {
    std::cout << "\n\n";
    CreateHeaderText("=-= Caesar Cipher Encrypter/Decoder =-=");
    std::cout << "\n\n";
    CaesarInit();
    CreateHeaderText("=-= Thank you for using my tool =-=");
    return 0;
}

void CaesarInit() {
    std::string inputMessage;
    int shift;
    std::cout << "Input your text to encrypt/decode: ";
    std::getline (std::cin,inputMessage);
    int check = CheckTextValidity(inputMessage);
    if(check > 0) {
        return;
    }

    std::cout << "Input your text shift/key: ";
    std::cin >> shift;
    std::cin.clear();
    std::cin.sync();
    shift = (int)shift;
    if(shift <= 0) {
        CreateErrorText("Cannot use a shift of less than or equal to 0!");
        return;
    }
    
    if(GetBoolUserInput("Encrypt or decrypt?\nY = Encrypt\nN = Decrypt\n")) {
        bool didFinish = CaesarCipherEncrypt(inputMessage, shift);
        if(didFinish) {
            CreateHeaderText("=-= Output message: " + inputMessage + " =-=");
            if(GetBoolUserInput("Use tool again? Y/N\n")) {
                CaesarInit();
            }
        } else {
            if(GetBoolUserInput("Try again? Y/N\n")) {
                CaesarInit();
            }
        }
    } else {
        bool didFinish = CaesarCipherDecrypt(inputMessage, shift);
        if(didFinish) {
            CreateHeaderText("=-= Output message: " + inputMessage + " =-=");
            if(GetBoolUserInput("Use tool again? Y/N\n")) {
                CaesarInit();
            }
        } else {
            if(GetBoolUserInput("Try again? Y/N\n")) {
                CaesarInit();
            }
        }
    }
}

void CreateHeaderText(std::string text) {
    for (int i = 0; i < text.size(); i++) {
        std::cout << "=";
    }
    std::cout << "\n" << text << "\n";
    for (int i = 0; i < text.size(); i++) {
        std::cout << "=";
    }
    std::cout << "\n";
}

void CreateDividerText() {
    for (int i = 0; i < 20; i++) {
        std::cout << "=";
    }
    std::cout << "\n";
}

void CreateErrorText(std::string text) {
    std::string errorText = "[ERROR] : ";
    errorText += text;
    CreateHeaderText(errorText);
}

bool GetBoolUserInput(std::string text) {
    char input;
    while (toupper(input) != 'Y' && toupper(input) != 'N') {
        std::cout << text;
        std::cin >> input;
    }
    if(toupper(input) == 'Y') {
        return true;
    } else {
        return false;
    }
}

int CheckTextValidity(std::string text) {
    std::vector<char> invalidChars;
    for (int i = 0; i < text.size(); i++) {
        if(!(IsSymbol(text[i]))) {
            for (int j = 0; j < AlphabetVect.size(); j++) {
                if(toupper(text[i]) == AlphabetVect[j]) {
                    break;
                }
                if(j == (AlphabetVect.size() - 1) && (toupper(text[i]) != AlphabetVect[j])) {
                    invalidChars.push_back(text[i]);
                }
            }
        }
    }
    if(invalidChars.size() > 0) {
        std::string errorText = "Unaccepted character in message: ";
        for (int i = 0; i < invalidChars.size(); i++) {
            errorText.push_back(invalidChars[i]);
            if(i != (invalidChars.size() - 1)) {
                errorText += ", ";
            }
        }
        CreateErrorText(errorText);
        return 1;
    }
    return 0;
}

bool IsSymbol(char c) {
    for (int i = 0; i < SymbolVect.size(); i++) {
        if(c == SymbolVect[i]) {
            return true;
        }
    }
    return false;
}

bool CaesarCipherEncrypt(std::string &text, int shift) {
    for (char &letter : text)
    {
        if(!(IsSymbol(letter))) {
            char temp = letter;
            bool isUpper = (isupper(letter) != 0);
            for (int i = 0; i < AlphabetVect.size(); i++) {
                if(toupper(letter) == AlphabetVect[i]) {
                    if((i + shift) > 25) {
                        letter = AlphabetVect[((i + shift) - 26)];
                    } else {
                        letter = AlphabetVect[i + shift];
                    }
                    break;
                }
            }
            if(!isUpper) {
                letter = tolower(letter);
            }
            if(temp == letter) {
                CreateErrorText("Undefined error occurred.");
                return false;
            }
        }
    }
    return true;
}

bool CaesarCipherDecrypt(std::string &text, int key) {
    for (char &letter : text)
    {
        if(!(IsSymbol(letter))) {
            char temp = letter;
            bool isUpper = (isupper(letter) != 0);
            for (int i = 0; i < AlphabetVect.size(); i++) {
                if(toupper(letter) == AlphabetVect[i]) {
                    if((i - key) < 0) {
                        letter = AlphabetVect[((i - key) + 26)];
                    } else {
                        letter = AlphabetVect[i - key];
                    }
                    break;
                }
            }
            if(!isUpper) {
                letter = tolower(letter);
            }
            if(temp == letter) {
                CreateErrorText("Undefined error occurred.");
                return false;
            }
        }
    }
    return true;
}