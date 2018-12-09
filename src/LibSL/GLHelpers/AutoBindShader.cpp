
#include <LibSL/GLHelpers/AutoBindShader.h>

// base64 decoding, see http://stackoverflow.com/questions/180947/base64-decode-snippet-in-c

static inline bool is_base64(unsigned char c)
{
  return (isalnum(c) || (c == '+') || (c == '/'));
}

static std::string base64_decode(std::string const& encoded_string)
{
  const std::string base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";
	int in_len = (int)encoded_string.size();
  int i = 0;
  int j = 0;
  int in_ = 0;
  unsigned char char_array_4[4], char_array_3[3];
  std::string ret;
  while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
    sl_assert(i<4);
    sl_assert(in_<(int)encoded_string.size());
    char_array_4[i++] = encoded_string[in_]; in_++;
    if (i == 4) {
      for (i = 0; i < 4; i++) {
        char_array_4[i] = (uchar)base64_chars.find(char_array_4[i]);
      }
      char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
      char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
      char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
      for (i = 0; (i < 3); i++) {
        ret += char_array_3[i];
      }
      i = 0;
    }
  }
  if (i) {
    sl_assert(i<4);
    for (j = i; j < 4; j++) {
      char_array_4[j] = 0;
    }
    for (j = 0; j < 4; j++) {
      char_array_4[j] = (uchar)base64_chars.find(char_array_4[j]);
    }
    char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
    char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
    char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
    for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
  }
  return ret;
}

// custom decode

std::string AutoBindShader::decode(const std::string& str)
{
  std::string unbased = base64_decode(str);
  return unbased;
}
