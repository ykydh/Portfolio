#include "MyMap.h"
#include <iostream>
#include <string>

// Function to build a map of character counts
void get_char_frequency(MyMap<char, int>& in_tree) {
    std::string file_input;
    while(std::getline(std::cin,file_input))
    {
      for(int i = 0; i < static_cast<int>(file_input.size());i++)
      {
        in_tree[file_input[i]] += 1;
      }
    }
}

int main() {
  MyMap<char, int> map_obj;
  std::string first_line;
  std::getline(std::cin,first_line);
  
  get_char_frequency(map_obj);
  for(int i =0;i <static_cast<int>(map_obj.size());i++)
  {
    std::cout<<static_cast<char>(map_obj[first_line[i]]);
  }
  std::cout<<"\n";
    return 0;
}

