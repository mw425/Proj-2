#include "ArrayBag.h"
#include "LinkedBag.h"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

// A list of common punctuation characters that might separate words in a title.
const string PUNCTUATION = " ,:;\t.()&";

// most of the papers are from 1967 - 2007, a 41-year span
const int OLDEST = 1967;
const int NEWEST = 2007;

int main()
{
  ifstream data;
  data.open("papers.lst");
  if (!data) {
    cout << "Sorry, could not open file: papers.lst\n";
    return 1;
  }

  ArrayBag<string> words; // a bag to hold all the words from the paper titles
  ArrayBag<string> *wordsByYear = new ArrayBag<string>[NEWEST - OLDEST + 1];

  while (true) {
    int year;
    data >> year;
    if (!data)
      break;

    string authors;
    getline(data, authors, ',');
    if (!data)
      break;

    string title;
    getline(data, title);
    if (!data)
      break;

    // ignore papers outside the range OLDEST to NEWEST
    if (year< OLDEST || year > NEWEST)
      continue;

    // ignore papers if the arraybag is already full
    if (wordsByYear[year-OLDEST].isFull())
      continue;

    bool moreWords = true;
    while (moreWords) {
      size_t pos = title.find_first_of(PUNCTUATION);
      string word;
      if (pos == string::npos) {
        word = title;
        moreWords = false;
      } else {
        word = title.substr(0, pos);
        title.erase(0, pos+1);
      }

      // ignore short words, like "A", or "the", which are mostly boring
      if (word.length() < 5)
        continue;

      // process word
      if (!wordsByYear[year-OLDEST].add(word)) {
        cout << "Oops, ArrayBag is now full.\n";
        break;
      }
    }
  }

  // Print frequency of each word, taking care to only print each word
  // (and frequency) once. That way, if "Machine" appears say 3 times
  // in the ArrayBag, we print "3 Machine", but we only print this the
  // first time that "Machine" is encountered in the ArrayBag. It
  // would be silly to print that three times!
  //
  // NOTE: This code should be changed to instead print the most popular words
  // by each year.
  ArrayBag<string> printed; // this bag keeps track of words already printed
  for (int i = 0; i < NEWEST - OLDEST + 1; i++){
    printed.clear();
    for (int j = 0; j < wordsByYear[i].getCurrentSize(); j++){
   // int n = words.getCurrentSize();
    //for (int i = 0; i < n; i++) {
      string word = wordsByYear[i].get(j);
      if (printed.contains(word)) {
        // if word was already printed, don't print again,
        // continue with next loop iteration instead
        continue;
      }
      int count = wordsByYear[i].getFrequencyOf(word);
      cout << i+OLDEST << setw(5) << count << " " << word << "\n";
      printed.add(word); // add the now-printed word to the bag 
    }
  }// end for
   
   for (int i = 0; i < NEWEST - OLDEST + 1; i++){
     printed.clear();
     // Most popular word for 1967 is Machines, which appeared 13 times,
    // among 566 total words for that year
       int bagSize = wordsByYear[i].getCurrentSize();
       int maxIndex = -1;
       int maxCount = 0;
      for (int j = 0; j < bagSize; j++){
         
           string word = wordsByYear[i].get(j);
           if (printed.contains(word)) {
             // if word was already printed, don't print again,
             // continue with next loop iteration instead
             continue;
           }
           if(wordsByYear[i].getFrequencyOf(word) > maxCount){
             maxCount = wordsByYear[i].getFrequencyOf(word);
             maxIndex = j;
           }
      }
     if(!wordsByYear[i].isEmpty()){
     cout << "Most popular word for " << i+OLDEST << " is " << 
       wordsByYear[i].get(maxIndex) << ", which appeared " << 
       maxCount << " times,\n" <<
       "among " << bagSize << " total words for that year\n";
     } else {
       cout << "There were no articles in  " << i+OLDEST << "!\n" ;
     }
  
       
   } // end for
  return 0;
}