#include <iostream>
#include <fstream>
#include <string>
#define ALPH_SIZE 26
#define FIRST_CHAR ('a')
using namespace std;

char tabula_recta[ALPH_SIZE][ALPH_SIZE];

void set_tabula_recta() {
  for (int i = 0; i < ALPH_SIZE; ++i) {
    for (int j = 0; j < ALPH_SIZE; ++j) {
      tabula_recta[i][j] = (i + j) % ALPH_SIZE + FIRST_CHAR;
    }
  }
}

void encode(fstream& in, fstream& out, string& key) {
  int key_pos = 0;
  int size = 0;
  int key_size = key.size();

  string temp, term;
  temp.resize(key_size);

  while (true) {
    in >> term;
    if (in.eof()) {
      if (size != 0) {
        temp.resize(size);
        out << temp;
      }
      break;
    }
    for (int i = 0; i < term.size(); ++i) {
      if (!isalpha(term[i])) {
        continue;
      }
      temp[size++] = toupper(tabula_recta[tolower(term[i]) - FIRST_CHAR][key[key_pos] - FIRST_CHAR]);
      if (size == key.size()) {
        out << temp;
        size = 0;
      }
      key_pos = (key_pos + 1) % key_size;
    }
  }

  out << endl;
}

int main(int argc, char* argv[]) {
  if (argc != 3) {
    cout << "Usage: " + string(argv[0]) + " [filename] [keyword]" << endl;
    return 0;
  }
  set_tabula_recta();

  string input_file = argv[1];
  string key = argv[2];
  string output_file = input_file + "_encoded";

  fstream in(input_file, fstream::in);
  fstream out(output_file, fstream::out);

  if (!in.is_open()) {
    cout << "Cannot open input file: " + input_file << endl;
    return 0;
  }
  if (!out.is_open()) {
    cout << "Cannot create output file: " + output_file << endl;
    return 0;
  }
  for (int i = 0; i < key.size(); ++i) {
    if (!isalpha(key[i])) {
      cout << "Cannot encode: keyword has not alphabetic characters" << endl;
      return 0;
    }
    key[i] = tolower(key[i]);
  }
  
  encode(in, out, key);
}
