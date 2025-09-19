#include "MyMap.h"
#include <iostream>
#include <string>

// Count character frequencies into map
void get_char_frequency(MyMap<char, int>& in_tree) {
    std::string line;
    while (std::getline(std::cin, line)) {
        for (char c : line) {
            in_tree[c] += 1;   // operator[] creates or updates counts
        }
    }
}

int main() {
    MyMap<char, int> map_obj;

    // Read the first line separately (just as your original code did)
    std::string first_line;
    std::getline(std::cin, first_line);

    // Process the rest of the input
    get_char_frequency(map_obj);

    std::cout << "Character frequencies from input:\n";
    for (char c : first_line) {
        std::cout << "'" << c << "' : " << map_obj[c] << "\n";
    }

    std::cout << "\nTotal unique characters: " << map_obj.size() << "\n";

    return 0;
}
