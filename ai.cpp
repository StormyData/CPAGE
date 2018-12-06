#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
using namespace std;
#include <vector>
#include <string>
#include <windows.h>
#include<time.h>
typedef unsigned char BYTE;

std::string base64_encode(BYTE const* buf, unsigned int bufLen);
std::vector<BYTE> base64_decode(std::string const&);
static const std::string base64_chars =
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";


static inline bool is_base64(BYTE c) {
  return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string base64_encode(BYTE const* buf, unsigned int bufLen) {
  std::string ret;
  int i = 0;
  int j = 0;
  BYTE char_array_3[3];
  BYTE char_array_4[4];

  while (bufLen--) {
    char_array_3[i++] = *(buf++);
    if (i == 3) {
      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
      char_array_4[3] = char_array_3[2] & 0x3f;

      for(i = 0; (i <4) ; i++)
        ret += base64_chars[char_array_4[i]];
      i = 0;
    }
  }

  if (i)
  {
    for(j = i; j < 3; j++)
      char_array_3[j] = '\0';

    char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
    char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
    char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
    char_array_4[3] = char_array_3[2] & 0x3f;

    for (j = 0; (j < i + 1); j++)
      ret += base64_chars[char_array_4[j]];

    while((i++ < 3))
      ret += '=';
  }

  return ret;
}

std::vector<BYTE> base64_decode(std::string const& encoded_string) {
  int in_len = encoded_string.size();
  int i = 0;
  int j = 0;
  int in_ = 0;
  BYTE char_array_4[4], char_array_3[3];
  std::vector<BYTE> ret;

  while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
    char_array_4[i++] = encoded_string[in_]; in_++;
    if (i ==4) {
      for (i = 0; i <4; i++)
        char_array_4[i] = base64_chars.find(char_array_4[i]);

      char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
      char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
      char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

      for (i = 0; (i < 3); i++)
          ret.push_back(char_array_3[i]);
      i = 0;
    }
  }

  if (i) {
    for (j = i; j <4; j++)
      char_array_4[j] = 0;

    for (j = 0; j <4; j++)
      char_array_4[j] = base64_chars.find(char_array_4[j]);

    char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
    char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
    char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

    for (j = 0; (j < i - 1); j++) ret.push_back(char_array_3[j]);
  }

  return ret;
}
int main(){
    char buff[50];
string outs;
fstream logn("logn.txt");
fstream in("input.txt",ios::in);
fstream out;
string s;
int t=0;
int n;
vector<int> logv;
vector<string> lognv;
while(!logn.eof()){
    logn>>n;
    logv.push_back(n);
    logn>>s;
    lognv.push_back(s);
}
logn.close();
logn.open("logn.txt",ios::in|ios::out|ios::trunc);
bool is=0;
for(int i=0;i<logv.size();i++){
    sprintf(buff,"%03d",logv[i]);
    logn<<buff<<" "<<lognv[i]<<"\n";
}
while(!in.eof()){
    Sleep(1);
    getline(in,s);
    if(s.empty())
        break;
    if(s.find("data:image/gif;base64,")!=string::npos)
        s.erase(0,22);
    is=0;
    for(int i=0;i<lognv.size();i++){
        if(s==lognv[i])
         is=1;
    }
    if(is)
        continue;
out.open("tmp.png",ios::out|ios::trunc|ios::binary);
vector<BYTE> v=base64_decode(s);
for(int i=0;i<v.size();i++)
    out.write((char*)(&(v[i])),1);
out.close();
system("tmp.png");
cin>>t;
lognv.push_back(s);
sprintf(buff,"%03d",t);
logn<<buff<<" "<<s<<"\n";
system("del tmp.png");
s.clear();
}
return 0;
}
