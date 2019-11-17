#include <bits/stdc++.h>

using namespace std;

template<typename T>
T Min(T v) {
  return v;
}
template<typename T, typename... Args>
T Min(T first, Args... args) {
  return min(first , Min(args...));
}

int LevenshteinDistance(string str1 , string str2 , int m ,int n) 
{ 
	if (m == 0) return n; 
	if (n == 0) return m; 
	if (str1[m-1] == str2[n-1]) 
		return LevenshteinDistance(str1, str2, m-1, n-1); 
	return 1 + Min ( LevenshteinDistance(str1, str2, m, n-1),  
					LevenshteinDistance(str1, str2, m-1, n), 
					LevenshteinDistance(str1, str2, m-1, n-1)  
				); 
} 

bool isMatch(string str1 ,string str2){
    //str1 is the correct name while str2 is not correct
    transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
    string temp="";
    for(int i=0;i<str2.size();++i){
        if(str2[i]>='A'&&str2[i]<='Z')str2[i]-=32;
        if(str2[i]>='a'&&str2[i]<='z')temp+=str2[i];
    }
    str2=temp;
    int dist = LevenshteinDistance(str1, str2, str1.size(), str2.size());
    int countStr1[26];
    memset(countStr1,0,sizeof(countStr1));
    for(int i=0;i<str1.size();++i){
        countStr1[str1[i]-'a']++;
    }
    for(int i=0;i<str2.size();++i){
        countStr1[str2[i]-'a']--;
    }
    int check=0;
    for(int i=0;i<26;++i){
        check+=abs(countStr1[i]);
    }
    long double not_match = (long double)dist*check/str1.size()/str2.size();
    return not_match<=0.2?1:0;
}