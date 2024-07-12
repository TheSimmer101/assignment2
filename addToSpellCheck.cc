#include <iostream>
#include <string>
#include <cctype>



//REDO R VALUE IN DOUBLE HASH
//copy this insertLetter into spell check
// Helper functions
std::string lowercase(const std::string& str) {
    std::string result;
    for (char c : str) {
        result += std::tolower(c);
    }
    return result;
}

std::string removePunctuation(const std::string& str) {
    std::string result;
    for (char c : str) {
        if (!std::ispunct(c)) {
            result += c;
        }
    }
    return result;
}

std::string insertLetter(const std::string& str, char letter, int position) {
    std::string result;
    for (int i = 0; i < str.length(); i++) {
        if (i == position) {
            result += letter;
        }
        result += str[i];
    }
    // Handle the case where the character is inserted at the end
    if (position == str.length()) {
        result += letter;
    }
    return result;
}

bool oneDiff(const std::string& s1, const std::string& s2) {
    std::string temp1 = lowercase(removePunctuation(s1));
    std::string temp2 = lowercase(removePunctuation(s2));

    // Ensure temp1 is the shorter string
    if (temp1.length() > temp2.length()) {
        std::swap(temp1, temp2);
    }

    // If the lengths differ by more than one, return false
    if (temp2.length() - temp1.length() != 1) {
        return false;
    }

    // Generate all possible strings by adding one character to temp1
    for (int pos1 = 0; pos1 <= temp1.length(); pos1++) {
        for (char c = 'a'; c <= 'z'; c++) {
            std::string word = insertLetter(temp1, c, pos1);
            std::cout << "word is: " << word << "\n";
            if (word == temp2) {
                return true;
            }
        }
    }

    return false;
}

int main() {
    if (oneDiff("cat", "cats")) {
        std::cout << "\n\ntrue";
    }
    return 0;
}