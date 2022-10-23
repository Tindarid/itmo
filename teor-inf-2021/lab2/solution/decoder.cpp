#include "ar/decode.h"

int main(int argc, char **argv) {
  if (argc < 3) {
    return -1;
  }

  FILE *in = fopen(argv[1], "rb");
  assert(in);
  fseek(in, 0, SEEK_END);
  int size = ftell(in);
  auto *buf = (unsigned char *)malloc(size);
  fseek(in, 0, SEEK_SET);
  size = (int) fread(buf, 1, size, in);
  fclose(in);

  std::vector<unsigned char> output;
  int *i = (int *)buf;
  output = Decode(*i).decode(buf + sizeof(int), size - sizeof(int));
  free(buf);

  FILE *out = fopen(argv[2], "wb");
  assert(out);
  fwrite(output.data(), 1, output.size(), out);
  fclose(out);

  return 0;
}
