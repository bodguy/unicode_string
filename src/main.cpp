#include <iostream>

using namespace std;

unsigned int from_utf8(const unsigned char* utf8_data);

int main(int argc, char** argv) {
//  const char* test_file_path = "../res/sample.txt";
//  ifstream fs8(test_file_path);
//  if (!fs8.is_open()) {
//    cout << "Could not open " << test_file_path << endl;
//    return 0;
//  }
//
//  unsigned line_count = 1;
//  string line;
//  String str_result;
//
//  while (getline(fs8, line)) {
////    auto end_it = utf8::find_invalid(line.begin(), line.end());
////    if (end_it != line.end()) {
////      cout << "Invalid UTF-8 encoding detected at line " << line_count << "\n";
////      cout << "This part is fine: " << string(line.begin(), end_it) << "\n";
////    }
////
////    int length = utf8::distance(line.begin(), end_it);
////    total_length += length;
////
////    utf16line = utf8::utf8to16(line);
////    utf8line = utf8::utf16to8(utf16line);
////    cout << "utf8 len: " << utf8line.size() << "\n";
////    cout << utf8line << "\n";
////
////    if (utf8line != string(line.begin(), end_it))
////      cout << "Error in UTF-16 conversion at line: " << line_count << "\n";
//    str_result += line;
//
//    line_count++;
//  }
//
//  std::cout << "total length: " << str_result.length() << std::endl;
//  std::cout << "result: " << str_result << std::endl;
//  std::cout << str_result.replace_all("다.", "까?! ") << std::endl;
//
//  String str = "自家撞着";
//  std::cout << str << std::endl;
//  std::cout << str.length() << std::endl;
//  String str2 = "自家撞着";
//  std::cout << std::boolalpha << (str == str2) << std::endl;
//  String str3 = str2.substr(0, 2);
//  std::cout << str3[1] << std::endl;
//  std::cout << str3.starts_with("自") << std::endl;
//  std::cout << str3.ends_with("家") << std::endl;
//  std::cout << str3.contains("自家") << std::endl;
//  String str4 = "ABC";
//  std::cout << str4.equals_ignore_case("ABC") << std::endl;
//  std::cout << str.replace_all("撞着", "지와") << std::endl;
//  std::cout << str + str2 << std::endl;
//  String str5 = "한글입니다.한글입니다.한글입니다.한글입니다.한글입니다.한글입니다.한글입니다.한글입니다.";
//  std::cout << str5.replace_all("다.", "까?") << std::endl;
//  for (char16_t c : str2) {
//    std::cout << c << std::endl;
//  }
//  std::cout << String("\u5B66") << std::endl;
//  char16_t u16ch[2] = { 0xD83C, 0xDF7A };
//  char u8ch[4] = { static_cast<char>(0xF0), static_cast<char>(0x9F), static_cast<char>(0x8D), static_cast<char>(0xBA) };

//  std::string u8str = u8ch;
//  std::cout << u8str << std::endl;
//  std::u16string u16str = ch;
//  std::cout << u16str << std::endl;
//  std::cout << String(u16ch) << std::endl;
//  std::u32string str123123 = U"\u5B66";
//  std::cout << str123123.size() << std::endl;

//  FString strrrrr = "hello world";
//  FString strrrrr2 = "hello world2";
//  bool res = strrrrr == strrrrr2;
//  std::cout << std::boolalpha << res << std::endl;

  FILE* fp = fopen("../res/sample2.txt", "rb");
  if (fp == NULL) {
    std::cout << "file not found" << std::endl;
    return -1;
  }

  fseek(fp, 0, SEEK_END);
  size_t size = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  char* buffer = (char*)malloc(sizeof(char) * size);
  fread(buffer, size, 1, fp);
  buffer[size - 1] = 0x00; // replace line feed to null character
  printf("파일에서 읽은것: %s\n", buffer);
  unsigned int u32 = from_utf8((unsigned char *) buffer);
  free(buffer);
  printf("변환한것: %04X\n", u32); // D55C

  return 0;
}

unsigned int from_utf8(const unsigned char* utf8_data) {
  if (utf8_data[0] < 0x80) {
    // 1 byte
    return (unsigned int)utf8_data[0];
  } else if (utf8_data[0] < 0xE0) {
    // 2 byte
    return ((utf8_data[0] & 0x1F) << 6) + (utf8_data[1] & 0x3F); // 00111111
  } else if (utf8_data[0] < 0xF0) {
    // 3 byte
    return ((utf8_data[0] & 0xF) << 12) + ((utf8_data[1] & 0x3F) << 6) + (utf8_data[2] & 0x3F);
  } else {
    // 4 byte
    return ((utf8_data[0] & 0x7) << 18) + ((utf8_data[1] & 0x3F) << 12) + ((utf8_data[2] & 0x3F) << 6) + (utf8_data[3] & 0x3F);
  }
}