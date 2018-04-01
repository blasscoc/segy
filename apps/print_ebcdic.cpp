

#include <ebcdic.h>
#include <iostream>


int main(int argc, char **argv)
{

  if(argc < 2)
    {
      std::cout << "Please provide a name of a segy file" << std::endl;
      return 1;
    }
  
  std::string filename(argv[1]);

  std::vector<char> ebcdic = read_ebcdic(filename);
  
  std::string msg(&ebcdic[0]);

  std::cout << msg << std::endl;

}

