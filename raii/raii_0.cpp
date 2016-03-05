#include <fstream>
#include <string>
#include <cstdio>
#include "logger.h"
#include <string.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

class File {
public:
  //const char * filename, const char * mode 
  File(const std::string& name, const std::string& mode);
  ~File();
  
  void read();
  void write(const std::vector<std::string>& lines);
  //std::fstream m_fsGet() { return m_fs; } //Почему-то не работает getter для поля m_fs
  std::string m_urlGet() { return m_url; } //Хотя геттер для m_url работает

  std::fstream m_fs;
private:
  std::string m_url;
  
  
  std::string m_md;
};

File::File(const std::string& name, const std::string& mode)
  : m_url(name), m_fs(name), m_md(mode) {
}

File::~File() {
  m_fs.close();
}

void File::read() {
  std::string line;
  if ( (m_fs != NULL) && (m_md.compare("r") == 0) ) {
    while (std::getline(m_fs, line)) {
      printf("%s\n", line.c_str());
    }
  } else {
    if (m_md.compare("r") != 0) ERR("You have no rights to read this file");
    if (m_fs != NULL) ERR("FILE DOESN'T EXIST");
  } 
}

void File::write(const std::vector<std::string>& lines) {  
  if ( (m_fs != NULL) && (m_md.compare("w") == 0) ) {
    std::fstream fs;
    fs.open(this->m_urlGet(), std::fstream::out);
    for (auto it = lines.begin(); it != lines.end(); ++it) {
      WRN("Trying to print string in file:");
      fs << it->c_str();
    }
    fs.close();

  } else {
    if (m_md.compare("w") != 0) ERR("You have no rights to write in this file");
    if (m_fs != NULL) ERR("FILE DOESN'T EXIST");
  } 
}

/* Main */
// ----------------------------------------------------------------------------
int main(int argc, char** argv) {
  DBG("[Lesson 3]: RAII 0");
  
  {
    INF("Enter block");

    File file("lorem.txt", "r");
    //if (file.m_fsGet() != NULL) printf("HI\n"); //Почему-то не работает getter для поля m_fs
    //if (file.m_urlGet() != "") printf("HIHIHO\n"); //Хотя геттер для m_url работает
    file.read();

    std::vector<std::string> array = {"Hello, ", "World!"};
    std::vector<std::string> & r_array = array;
    File file1("test.txt", "w");

    file1.write(r_array);


	INF("Exit block");
  }

  DBG("[Lesson 3]: RAII 0 [END]");
  return 0;
}
