#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
  std::cout << rawWords << std::endl;
  rawWords = convToLower(rawWords);
  std::stringstream ss(rawWords);
  std::set<std::string> words;

  std::string currentWord;
  std::string substring;

  while(ss >> currentWord) {
    int start = 0;
    for(size_t i = 0; i<currentWord.size();i++){
      substring = currentWord.substr(start, i-start);
      if(ispunct(currentWord[i])) {
        if(substring.size() >= 2) {
          words.insert(substring);
        }
        start = start+(i-start) + 1;
      }
    }
    if(substring.size() >= 2) {
      words.insert(currentWord.substr(start, currentWord.size()-start));
    }
  }

  return words;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
