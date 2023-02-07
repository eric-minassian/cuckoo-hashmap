#include "Wordset.hpp"
#include "convert.hpp"
#include "ver.hpp"
#include "gtest/gtest.h"
#include <fstream>
#include <string>

namespace {

// NOTE:  these are not intended as exhaustive tests.
// This should get you started testing.
// You MAY use validConversion in unit tests (i.e., this file and any other unit
// tests in this folder you add), but you MAY NOT use it in your code otherwise.

TEST(RequiredPart1, Hf1) {
  unsigned hv = polynomialHashFunction("dbc", 37, 100000);
  unsigned shouldBe = 4 * 37 * 37 + 2 * 37 + 3;
  EXPECT_EQ(hv, shouldBe);
}

TEST(RequiredPart1, Tab1) {
  WordSet ws(11);
  ws.insert("dbc");
  EXPECT_TRUE(ws.contains("dbc"));
  EXPECT_EQ(ws.getCapacity(), 11);
}

TEST(RequiredPart1, Tab2) {
  WordSet ws(11);
  ws.insert("sleepy");
  ws.insert("happy");
  ws.insert("dopey");
  ws.insert("sneezy");
  ws.insert("datalink");
  ws.insert("australia");
  ws.insert("guacamole");
  ws.insert("phylum");
  EXPECT_TRUE(ws.contains("happy"));
  EXPECT_TRUE(ws.contains("dopey"));
  EXPECT_EQ(ws.getCapacity(), 11);
}

TEST(ResizeTest, Tab3) {
  WordSet ws(11);
  ws.insert("sleepy");
  ws.insert("happy");
  ws.insert("dopey");
  ws.insert("sneezy");
  ws.insert("datalink");
  ws.insert("australia");
  ws.insert("guacamole");
  ws.insert("phylum");
  EXPECT_TRUE(ws.contains("happy"));
  EXPECT_TRUE(ws.contains("dopey"));
  ws.insert("salsa");
  ws.insert("sloth");
  ws.insert("colossus");
  ws.insert("synergize");
  ws.insert("monday");
  ws.insert("tuesday");
  ws.insert("wednesday");
  ws.insert("thursday");
  ws.insert("friday");
  ws.insert("saturday");
  ws.insert("sunday");
  EXPECT_TRUE(ws.contains("monday"));
  EXPECT_TRUE(ws.contains("sunday"));
  EXPECT_EQ(ws.getCapacity(), 23);
}

TEST(RequiredPart2, AntToArt) {
  WordSet words(11);
  std::ifstream in("words.txt");
  loadWordsIntoTable(words, in);

  std::vector<std::string> r = convert("ant", "art", words);

  // this was a success if r was a valid conversion of length 2.
  std::ifstream in2("words.txt");
  EXPECT_EQ(r.size(), 2);
  EXPECT_TRUE(validConversion(r, "ant", "art", in2));
}

TEST(RequiredPart2, AntToEat) {
  WordSet words(11);
  std::ifstream in("words.txt");
  loadWordsIntoTable(words, in);

  std::vector<std::string> r = convert("ant", "eat", words);

  std::ifstream in2("words.txt");

  EXPECT_EQ(r.size(), 5);
  EXPECT_TRUE(validConversion(r, "ant", "eat", in2));
}

TEST(SampleTests, PuttersToHampers) {
  WordSet words(11);
  std::string WORD_ONE = "putters";
  std::string WORD_TWO = "hampers";
  auto CORRECT_LENGTH = 14;

  std::ifstream in("words.txt");
  loadWordsIntoTable(words, in);

  std::vector<std::string> r = convert(WORD_ONE, WORD_TWO, words);

  std::ifstream in2("words.txt");

  EXPECT_EQ(r.size(), CORRECT_LENGTH);
  EXPECT_TRUE(validConversion(r, WORD_ONE, WORD_TWO, in2));
}

TEST(SampleTests, BankingToBrewing) {
  WordSet words(11);
  std::string WORD_ONE = "banking";
  std::string WORD_TWO = "brewing";
  auto CORRECT_LENGTH = 15;

  std::ifstream in("words.txt");
  loadWordsIntoTable(words, in);

  std::vector<std::string> r = convert(WORD_ONE, WORD_TWO, words);

  std::ifstream in2("words.txt");

  EXPECT_EQ(r.size(), CORRECT_LENGTH);
  EXPECT_TRUE(validConversion(r, WORD_ONE, WORD_TWO, in2));
}

TEST(SampleTests, ChangesToGlasses) {
  WordSet words(11);
  std::string WORD_ONE = "changes";
  std::string WORD_TWO = "glasses";
  auto CORRECT_LENGTH = 48;

  std::ifstream in("words.txt");
  loadWordsIntoTable(words, in);

  std::vector<std::string> r = convert(WORD_ONE, WORD_TWO, words);

  std::ifstream in2("words.txt");

  EXPECT_EQ(r.size(), CORRECT_LENGTH);
  EXPECT_TRUE(validConversion(r, WORD_ONE, WORD_TWO, in2));
}

TEST(SampleTests, ChangesToSmashed) {
  WordSet words(11);
  std::string WORD_ONE = "changes";
  std::string WORD_TWO = "smashed";
  auto CORRECT_LENGTH = 48;

  std::ifstream in("words.txt");
  loadWordsIntoTable(words, in);

  std::vector<std::string> r = convert(WORD_ONE, WORD_TWO, words);

  std::ifstream in2("words.txt");

  EXPECT_EQ(r.size(), CORRECT_LENGTH);
  EXPECT_TRUE(validConversion(r, WORD_ONE, WORD_TWO, in2));
}

TEST(SampleTests, BoostedToClasses)

{
  WordSet words(11);
  std::string WORD_ONE = "boosted";
  std::string WORD_TWO = "classes";
  auto CORRECT_LENGTH = 44;

  std::ifstream in("words.txt");
  loadWordsIntoTable(words, in);

  std::vector<std::string> r = convert(WORD_ONE, WORD_TWO, words);

  std::ifstream in2("words.txt");

  EXPECT_EQ(r.size(), CORRECT_LENGTH);
  EXPECT_TRUE(validConversion(r, WORD_ONE, WORD_TWO, in2));
}

// Additional Tests
// Part 1

TEST(AdditionalPart1, HashFunction1) {
  unsigned hv = polynomialHashFunction("abc", 37, 100000);
  unsigned shouldBe = 1 * 37 * 37 + 2 * 37 + 3;
  EXPECT_EQ(hv, shouldBe);
}

TEST(AdditionalPart1, HashFunction2) {
  unsigned hv = polynomialHashFunction("abc", 37, 10);
  unsigned shouldBe = (1 * 37 * 37 + 2 * 37 + 3) % 10;
  EXPECT_EQ(hv, shouldBe);
}

TEST(AdditionalPart1, HashFunction3) {
  unsigned hv = polynomialHashFunction("abc", 12, 100000);
  unsigned shouldBe = 1 * 12 * 12 + 2 * 12 + 3;
  EXPECT_EQ(hv, shouldBe);
}

TEST(AdditionalPart1, HashFunction4) {
  unsigned hv = polynomialHashFunction("abc", 12, 10);
  unsigned shouldBe = (1 * 12 * 12 + 2 * 12 + 3) % 10;
  EXPECT_EQ(hv, shouldBe);
}

TEST(AdditionalPart1, HashFunction5) {
  unsigned hv = polynomialHashFunction("zzzz", 10, 5);
  unsigned shouldBe = 1;
  EXPECT_EQ(hv, shouldBe);
}

TEST(AdditionalPart1, HashFunction6) {
  unsigned hv = polynomialHashFunction("jjj", 10, 3);
  unsigned shouldBe = 0;
  EXPECT_EQ(hv, shouldBe);
}

} // namespace
