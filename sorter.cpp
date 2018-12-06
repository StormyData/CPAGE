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
//string t("iVBORw0KGgoAAAANSUhEUgAAACYAAAAQCAYAAAB6Hg0eAAAAAXNSR0IArs4c6QAAAARnQU1BAACxjwv8YQUAAAAJcEhZcwAADsMAAA7DAcdvqGQAAACLSURBVFQ");
int main(){
    char buff[50];
fstream slogn("slogn.txt",ios::trunc|ios::out);
fstream logn("logn.txt");
string s;
int n;
vector<int> logv;
vector<string> lognv;
while(!logn.eof()){
    logn>>n;
    logv.push_back(n);
    logn>>s;
  //  s.erase(0,t.size());
    lognv.push_back(s);
}
logn.close();
bool is=1;
vector<string> tab[1000];
for(int i=0;i<logv.size();i++){
    n=logv[i];
    s=lognv[i];
    is=1;
    for(int j=0;j<tab[n].size();j++){
        if(tab[n][j]==s)
            is=0;
    }
    if(is)
        tab[n].push_back(s);
}
for(int i=0;i<1000;i++){
    sprintf(buff,"%03d ",i);
    for(int j=0;j<tab[i].size();j++){
        slogn<<buff<<tab[i][j]<<"\n";
    }
}
}
