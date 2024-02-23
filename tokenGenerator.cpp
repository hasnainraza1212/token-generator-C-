#include <iostream>
#include <string>
#include <cstring>
#include <memory>

// Using namespace for convenience
using namespace std;

// Checks if the character is a delimiter
bool isDelimiter(char character) {
    const string delimiters = " +-*/,:;><=()[]{}";
    return delimiters.find(character) != string::npos;
}

// Checks if the string is a multi-character delimiter
bool isMultiCharDelimiter(const string& str) {
    return str == ":";
}

// Checks if the character is an operator
bool isOperator(char character) {
    const string operators = "+-*/><=";
    return operators.find(character) != string::npos;
}

// Returns the type of delimiter as a string
string getDelimiterType(char delimiter) {
    switch (delimiter) {
        case ' ': return "SPACE";
        case '+': return "PLUS";
        case '-': return "MINUS";
        case '*': return "TIMES";
        case '/': return "DIVIDE";
        case ',': return "COMMA";
        case ';': return "SEMICOLON";
        case '>': return "GREATER_THAN";
        case '<': return "LESS_THAN";
        case '=': return "EQUALS";
        case '(': return "LEFT_PAREN";
        case ')': return "RIGHT_PAREN";
        case '[': return "LEFT_BRACKET";
        case ']': return "RIGHT_BRACKET";
        case '{': return "LEFT_BRACE";
        case '}': return "RIGHT_BRACE";
        case ':': return "COLON";
        default: return "UNKNOWN";
    }
}

// Checks if the string is a valid identifier
bool isValidIdentifier(const string& str) {
    if (isdigit(str[0]) || isDelimiter(str[0])) return false;
    return true;
}

// Checks if the string is a keyword
bool isKeyword(const string& str) {
    const string keywords[] = {"if", "else", "while", "do", "break", "continue", "int",
                               "double", "float", "return", "char", "case", "sizeof", "long",
                               "short", "typedef", "switch", "unsigned", "void", "static", "struct", "goto"};
    for (const auto& keyword : keywords) {
        if (str == keyword) return true;
    }
    return false;
}

// Checks if the string is an integer literal
bool isInteger(const string& str) {
    if (str.empty() || (str[0] == '-' && str.size() == 1)) return false;
    for (char const &c : str) {
        if (!isdigit(c) && !(c == '-' && &c == &str[0])) return false;
    }
    return true;
}

// Checks if the string is a real number
bool isRealNumber(const string& str) {
    bool hasDecimal = false;
    if (str.empty() || (str[0] == '-' && str.size() == 1)) return false;
    for (char const &c : str) {
        if (!isdigit(c) && c != '.' && !(c == '-' && &c == &str[0])) return false;
        if (c == '.') {
            if (hasDecimal) return false; // Multiple decimals not allowed
            hasDecimal = true;
        }
    }
    return hasDecimal;
}

// Extracts the substring
string extractSubstring(const string& str, int left, int right) {
    return str.substr(left, right - left + 1);
}

// Parsing the input string
void parseInputString(const string& str) {
    int left = 0, right = 0;
    int len = str.length();

    while (right <= len && left <= right) {
        if (!isDelimiter(str[right])) right++;

        if (isDelimiter(str[right]) && left == right) {
            if (isOperator(str[right]))
                cout << "'" << str[right] << "' " << getDelimiterType(str[right]) << "\n";
            else if (isMultiCharDelimiter(str.substr(right, 2))) {
                cout << "'" << extractSubstring(str, right, right + 1) << "' " << getDelimiterType(':') << "\n";
                right++;  // Move the index an extra step for multi-character delimiter
            }
            else
                cout << "'" << str[right] << "' " << getDelimiterType(str[right]) << "\n";
            right++;
            left = right;
        } else if (isDelimiter(str[right]) && left != right || (right == len && left != right)) {
            string subStr = extractSubstring(str, left, right - 1);

            if (isKeyword(subStr))
                cout << "'" << subStr << "' KEYWORD\n";

            else if (isInteger(subStr))
                cout << "'" << subStr << "' INTLIT\n";

            else if (isRealNumber(subStr))
                cout << "'" << subStr << "' FLOAT-INT\n";

            else if (isValidIdentifier(subStr) && !isDelimiter(str[right - 1]))
                cout << "'" << subStr << "' IDENT\n";

            else if (!isValidIdentifier(subStr) && !isDelimiter(str[right - 1]))
                cout << "'" << subStr << "' NOTIDENT\n";
            left = right;
        }
    }
}

// DRIVER FUNCTION
int main() {
    string inputString;
    getline(cin, inputString);

    parseInputString(inputString);

    return 0;
}
