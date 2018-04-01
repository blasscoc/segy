
#ifndef EBCDIC_H
#define EBCDIC_H

#include <string>
#include <vector>

std::vector<char> ebcdicToAscii (const std::vector<char>& bytes);
std::vector<char> read_ebcdic(const std::string& filename);

#endif 

