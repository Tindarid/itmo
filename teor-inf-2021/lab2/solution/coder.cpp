#include "ar/encode.h"

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

  int best_i = -1;
  std::vector<unsigned char> output;
  size_t min_size = size;
  for (int i = 1; i <= 256 * 256; i <<= 1) {
    auto result = Encode(i).encode(buf, size);
    if (result.size() < min_size || size == min_size) {
      output = std::move(result);
      min_size = output.size();
      best_i = i;
    }
  }
  free(buf);

  FILE *out = fopen(argv[2], "wb");
  assert(out);
  if (best_i != -1) {
    fwrite(&best_i, 1, sizeof(int), out);
  }
  fwrite(output.data(), 1, output.size(), out);
  fclose(out);

  return 0;
}
