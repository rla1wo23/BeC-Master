#include <iostream>
#include <locale>
#include <string>

int main() {
  // 로케일을 설정하여 유니코드 입력을 지원하도록 함
  std::locale::global(std::locale(""));

  std::wcout
      << L"------------------------------------------------------------\n";
  std::wcout << L"Cout is an object of ostream. By using the std namespace, "
                L"we can use abstracted input and output through this global "
                L"object.\n";
  std::wcout << L"We can take advantage of many useful functions already "
                L"created for strings.\n";
  std::wcout
      << L"------------------------------------------------------------\n\n";

  std::wcout << L"Step 1: Using String '+' operation\n";
  std::wcout << L"Please input some strings (only English or numbers). I will "
                L"use the cin object "
                L"which can only deal with character types: ";

  std::wstring str;
  std::wcin >> str;

  std::wcout << L"\nThen, I inserted ',' between every character. I "
                L"implemented this with "
                L"'+' operations:\nHere: ";

  std::wstring tmp = L"";
  for (int i = 0; i < str.size(); i++) {
    tmp += str[i];
    tmp += L",";
  }
  std::wcout << tmp << L"\n";
  std::wcout
      << L"------------------------------------------------------------\n\n";

  std::wcout
      << L"Now, we're going to use the wstring object. You can now enter "
         L"any Unicode character (such as Korean).\n";

  // 버퍼를 비움
  std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');

  std::wstring input;

  std::wcout << L"Input Unicode string: ";
  std::getline(std::wcin, input);

  std::wcout << L"\nYour input: " << input << std::endl;
  std::wcout << L"------------------------------------------------------------"
                L"\n Good job. This step is done";

  return 0;
}
