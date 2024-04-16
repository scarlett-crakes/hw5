#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <string>
#include <queue>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    //int n = in.size();
    std::string word = in;
    std::string floating_copy = floating;
    std::set<std::string> listOfWords;
    wordleHelper(floating_copy, dict, 0, word, listOfWords);
   /* for(auto s : listOfWords)
	  {
		if(listOfWords.find(s) == listOfWords.end())
		{
			cout << "JSDLFJLKSDJLFJKSD" << endl;
		}
        cout << s << endl;
    }*/
    return listOfWords;
}

// Define any helper functions here
bool wordleHelper(
    std::string floating,
    const std::set<std::string>& dict, int index, std::string word, std::set<std::string>& listOfWords)
{
    if(index == word.size())
    {
        //cout << "world" << endl;
        //cout << word << endl;
        if(dict.find(word) == dict.end())
        {
            //cout << "why is this failing" << endl;
            return false;
        }
        if (floating.length() != 0) {
            return false;
        }
        /*bool isValid = false;
        std::string word_copy = word;
        if(floating.size() != 0)
        {
            for(int j = 0; j <= floating.size(); j++)
            {
                isValid = false;
                for(int i = 0; i < word_copy.size(); i++)
                {
                    if(word_copy[i] == floating[j])
                    {
                        //cout << floating[j] << " " << i << endl;
                        //cout << word_copy << endl;
                        isValid = true;
                        word_copy.erase(word_copy.begin() + i);
                        //cout << word_copy << endl;
                        //cout << "break" << endl;
                        break;
                    }
                }
                if(isValid == false)
                {
                    return false;
                }
            }
        }
        //cout << "why is this failing" << endl;
        //cout << "done" << endl;*/
        listOfWords.insert(word);
        return true;
    }
    
    //std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    if(word[index] != '-')
    {
        //cout << in[index] << " " << index << endl; //-a- ""
        wordleHelper(floating, dict, index + 1, word, listOfWords);
        return true;
    }


    int count_spots = 0;//count spots how many blanks -- are left
    for(int i = 0; i < word.size(); i++)
    {
      if(word[i] == '-')
      {
        count_spots++;
      }
    }

    for(int j = 0; j < floating.size(); j++)
    {
      word[index] = floating[j];
        //alphabet.erase(remove(alphabet.begin(), alphabet.end(), floating[j]));
        //out << alphabet << endl;
      // cout << floating[j] << " " << index << endl; 
      std::string floatingCopy = floating.substr(0,j) + floating.substr(j+1); 
        //floatingCopy.erase(floatingCopy.begin() + j)
        //cout << "hello" << endl; -- a 
      wordleHelper(floatingCopy, dict, index + 1, word, listOfWords);
      // cout << index << endl;
        //cout << "minus " << index << " " << past_index << endl;
        //return true;
      }

    // cout << floating <<endl; 
    // cout << word <<endl;
    // cout << count_spots <<" " << floating.size() << endl;
    if(count_spots != floating.size()) 
    {
      checkEveryLetter(floating, dict, index, word, listOfWords);
    }
      // for(int i = 0)
        //checkEveryLetter(in, floating, dict, index, word, listOfWords);
        /*if(word.size() != floating.size() && floating.size() != in.size() ) //a a- 0 -1
        {
            checkEveryLetter(in, floating, dict, index, word, listOfWords)
        }*/
    
    
      //checkEveryLetter(in, floating, dict, index, word, listOfWords, count);
    //keep track of number of blanks left -- a -a
    
    
        //word.pop_back();
    return true;
}

void checkEveryLetter(std::string floating, const std::set<std::string>& dict, int index, std::string word, std::set<std::string>& listOfWords)
{
  for(char k = 'a'; k <= 'z'; k++)
  {
      //cout << k << " " << index << endl; 
      word[index] = k;
      //cout << word << endl;
      //index++; 
      wordleHelper(floating, dict, index+1, word, listOfWords);  
      //cout << index << endl;
      
      //index--;
  }
}
