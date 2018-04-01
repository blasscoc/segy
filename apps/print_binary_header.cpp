


#include <binary_header.h>

#include <iostream>
#include <string>

int main(int argc, char **argv)
  {

    if(argc < 2)
    {
      std::cout << "Please provide a name of a segy file" << std::endl;
      return 1;
    }

  if(argc < 2)
    {
      std::cout << "Please provide a name of a segy file" << std::endl;
      return 1;
    }
  
  std::string filename(argv[1]);

  BinaryHeader bhdr = read_binary_header(std::string(argv[1]));
  print_bhdr(bhdr);
    
  }

