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
    std::set<std::string> mySet;
    string singleWord;
    int count = 0;

    string cleanRawWords = convToLower(trim(rawWords));
    istringstream processingWords(cleanRawWords);


    while(processingWords >> singleWord){
        for(size_t i = 0; i < singleWord.size(); i++){
            if(ispunct(singleWord[i])){
                if (count >= 2){
                    mySet.insert(singleWord.substr(i - count, count));
                    count = 0;
                } else if (count < 2){
                    count = 0;
                }
            } else {
                count++;
            }
        }

        if(count >= 2){
            mySet.insert(singleWord.substr(singleWord.size() - count, count));
        } 

        count = 0;
    }

    return mySet;
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
