#include "Wordset.hpp"
#include <cmath>
#include <iostream>
#include <string>

// returns s, as a number in the given base, mod the given modulus
unsigned polynomialHashFunction(const std::string &s, unsigned base,
                                unsigned mod) {
  unsigned result = 0;
  for (unsigned i = 0; i < s.length(); i++) {
    result = (result * base + (s[i] - 'a' + 1)) % mod;
  }
  return result;
}

WordSet::WordSet(unsigned initialCapacity, unsigned evictionThreshold)
    : currentCapacity(initialCapacity), evictionThreshold(evictionThreshold),
      count(0), topArray(new std::string[initialCapacity]),
      bottomArray(new std::string[initialCapacity]) {}

WordSet::~WordSet() {
  // Delete the top and bottom arrays from dynamic memory
  delete[] topArray;
  delete[] bottomArray;
}

bool WordSet::isPrime(unsigned n) {

  // 0 and 1 are not prime
  if (n <= 1) {
    return false;
  }

  // Check if n is divisible by any number from 2 to sqrt(n) inclusively as
  // stated in the primalty test
  unsigned maxNum = sqrt(n) + 1;
  for (unsigned i = 2; i < maxNum; i++) {

    // If n is divisible by any number from 2 to sqrt(n) inclusively, then n is
    // not prime
    if (n % i == 0) {
      return false;
    }
  }

  // If n is not divisible by any number from 2 to sqrt(n) inclusively, then n
  // is prime and we return true
  return true;
}

unsigned WordSet::getPrime(unsigned n) {

  // Continue incrementing n until it is prime and return n
  while (!isPrime(n)) {
    n++;
  }
  return n;
}

void WordSet::resize() {
  // Store the previous capacity to use in the for loop of the array when
  // inserting the elements into the new arrays
  unsigned previousCapacity = currentCapacity;
  unsigned temp = currentCapacity * 2;
  currentCapacity = getPrime(temp);

  // Reset the count to 0 because we are going to reinsert all the elements into
  // the new arrays
  count = 0;

  // Create new arrays with the new capacity
  std::string *tempTopArray = topArray;
  std::string *tempBottomArray = bottomArray;
  topArray = new std::string[currentCapacity];
  bottomArray = new std::string[currentCapacity];

  // Insert the elements from the old arrays into the new arrays
  for (unsigned i = 0; i < previousCapacity; i++) {
    if (tempTopArray[i] != "") {
      insert(tempTopArray[i]);
    }

    if (tempBottomArray[i] != "") {
      insert(tempBottomArray[i]);
    }
  }

  // Delete the old arrays from dynamic memory
  delete[] tempTopArray;
  delete[] tempBottomArray;
}

void WordSet::insert(const std::string &s) {
  // If the string is already in the arrays or the string is empty, return
  if (contains(s) || s == "") {
    return;
  }

  // Create a temporary string to store the string that is being inserted
  std::string temp = s;

  // Create a variable to keep track of the number of evictions
  unsigned evictions = 0;

  // Continue inserting the string into the arrays until the eviction threshold
  // is reached or the string is inserted
  while (evictions < evictionThreshold) {

    // Get the key for the top array
    unsigned topKey = polynomialHashFunction(temp, BASE_H1, currentCapacity);

    // If the top array is empty, insert the string into the top array
    if (topArray[topKey] == "") {
      topArray[topKey] = temp;
      count++;
      return;

      // If the top array is not empty, swap the string in the top array with
      // the string being inserted and increment the number of evictions
    } else {
      std::swap(topArray[topKey], temp);
      evictions++;
    }

    // If the eviction threshold is reached, break out of the loop to resize
    if (evictions >= evictionThreshold) {
      break;
    }

    // Get the key for the bottom array
    unsigned bottomKey = polynomialHashFunction(temp, BASE_H2, currentCapacity);

    // If the bottom array is empty, insert the string into the bottom array
    if (bottomArray[bottomKey] == "") {
      bottomArray[bottomKey] = temp;
      count++;
      return;

      // If the bottom array is not empty, swap the string in the bottom array
      // with the string being inserted and increment the number of evictions
    } else {
      std::swap(bottomArray[bottomKey], temp);
      evictions++;
    }
  }

  // If the eviction threshold is reached, resize the arrays and insert the
  // string into the new arrays
  resize();
  insert(temp);
}

bool WordSet::contains(const std::string &s) const {

  // Check the top array for the string
  unsigned topKey = polynomialHashFunction(s, BASE_H1, currentCapacity);
  if (topArray[topKey] == s) {
    return true;
  }

  // Check the bottom array for the string
  unsigned bottomKey = polynomialHashFunction(s, BASE_H2, currentCapacity);
  if (bottomArray[bottomKey] == s) {
    return true;
  }

  // Return false if the string is not in either array
  return false;
}

unsigned WordSet::getCount() const { return count; }

unsigned WordSet::getCapacity() const { return currentCapacity; }
