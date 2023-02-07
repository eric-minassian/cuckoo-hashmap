#include "convert.hpp"
#include "Wordset.hpp"
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <sys/ucontext.h>
#include <vector>

// You should not need to change this function.
void loadWordsIntoTable(WordSet &words, std::istream &in) {
  std::string line, word;
  std::stringstream ss;

  while (getline(in, line)) {
    ss.clear();
    ss << line;
    while (ss >> word) {
      words.insert(word);
    }
  }
}

// You probably want to change this function.
std::vector<std::string> convert(const std::string &s1, const std::string &s2,
                                 const WordSet &words) {

  // Initialize result vector, queue, and map for finding the path from s1 to s2
  std::vector<std::string> result = {};
  std::queue<std::string> queue;
  std::map<std::string, std::string> map;

  // Push s1 to the queue and map it to an empty string because it has no parent
  queue.push(s1);
  map[s1] = "";

  // BFS
  while (!queue.empty()) {
    // Pop the first element in the queue and store it in node
    std::string node = queue.front();
    queue.pop();

    // If the node is s2, then we have found the path from s1 to s2
    if (node == s2) {
      std::string temp = node;

      // Push the path from s1 to s2 into the result vector
      while (temp != "") {
        result.push_back(temp);
        temp = map[temp];
      }
      // Reverse the vector since the map stores the path from s2 to s1
      for (unsigned i = 0; i < result.size() / 2; i++) {
        std::swap(result[i], result[result.size() - i - 1]);
      }

      // Return the result vector
      return result;
    }

    // If the node is not s2, then we need to find all the words that are one
    // letter different from the node and push them into the queue
    for (unsigned i = 0; i < node.length(); i++) {
      for (char c = 'a'; c <= 'z'; c++) {
        // Create a temporary string that is one letter different from the node
        std::string temp = node;
        temp[i] = c;
        // If the temporary string is in the word set and it has not been
        // visited, then push it into the queue and map it to its parent
        if (words.contains(temp) && map.count(temp) == 0) {
          queue.push(temp);
          map[temp] = node;
        }
      }
    }
  }

  // Return an empty vector if there is no path from s1 to s2
  return result;
}
