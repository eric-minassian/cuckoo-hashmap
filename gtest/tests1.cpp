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

TEST(AdditionalPart1, HashFunction7) {
  unsigned hv = polynomialHashFunction("abz", 5, 10);
  unsigned shouldBe = 1;
  EXPECT_EQ(hv, shouldBe);
}

TEST(AdditionalPart1, HashFunction8) {
  unsigned hv = polynomialHashFunction("jnmvmvspxcafzffrgsbu", 64432, 15277);
  unsigned shouldBe = 8234;
  EXPECT_EQ(hv, shouldBe);
}
TEST(AdditionalPart1, HashFunction9) {
  unsigned hv = polynomialHashFunction("egqxbojzirvnvzkzecxw", 56937, 27427);
  unsigned shouldBe = 13384;
  EXPECT_EQ(hv, shouldBe);
}
TEST(AdditionalPart1, HashFunction10) {
  unsigned hv = polynomialHashFunction("kqomgaqsffeauudrnxil", 64167, 4133);
  unsigned shouldBe = 3203;
  EXPECT_EQ(hv, shouldBe);
}
TEST(AdditionalPart1, HashFunction11) {
  unsigned hv = polynomialHashFunction("tcorviumpspuiswlfvms", 64565, 52453);
  unsigned shouldBe = 41256;
  EXPECT_EQ(hv, shouldBe);
}
TEST(AdditionalPart1, HashFunction12) {
  unsigned hv = polynomialHashFunction("nzxapfruaohbotgqtbcx", 61348, 61211);
  unsigned shouldBe = 37436;
  EXPECT_EQ(hv, shouldBe);
}
TEST(AdditionalPart1, HashFunction13) {
  unsigned hv = polynomialHashFunction(
      "lmsdadfrxggwyhlgklkobqdpwuwdgijajuhrbhcbigltjfyhieviarmlujxtockiojitlzdp"
      "nokqynpsmeqbrselzvpactmokhbahizjoxjzhzznpgqfcpdkfdtyazalkcffaozuqhkwnmay"
      "rkctphnwsxjbjquxcfbbyiqzsxlkxbofqonpwhuigilllxdsfhkzzdlh",
      51243, 65413);
  unsigned shouldBe = 37101;
  EXPECT_EQ(hv, shouldBe);
}
TEST(AdditionalPart1, HashFunction14) {
  unsigned hv = polynomialHashFunction(
      "lsyqciiqbpwtbcfmvrurzpzhwnywakylkxfszpwflpejbfychcjkwymfhpbgvxmdjxaukqoo"
      "quyjhqpiaforvxhauydcymrkqlootqubaomssdbcvuvpxnxrahwnlobuiacwomhqcgdflwud"
      "zjhaxedpjbcxuwwojmzamxnzhrmscsgqwvxqithzykllmybqqpcrlpfw",
      19013, 977);
  unsigned shouldBe = 582;
  EXPECT_EQ(hv, shouldBe);
}
TEST(AdditionalPart1, HashFunction15) {
  unsigned hv = polynomialHashFunction(
      "afydgiorwdctoiwqwaixoxcsvzgjaeburzbqgpqgsildugnujocwngjpfrtopqjkmywtsivc"
      "shfepftjtawzotwxzbpkvokpejaipuamewpyxsicdnsqbdrwnbcxvtinqmtxjxjdnicqyysu"
      "nejawgzufwamlumkjczfhbuzxkanblqhxicmssdprhzzdemvcxwsatgy",
      1492, 17509);
  unsigned shouldBe = 10063;
  EXPECT_EQ(hv, shouldBe);
}

TEST(AdditionalPart1, HashFunction16) {
  unsigned hv = polynomialHashFunction("antidisestablishmentarianism", 41, 10);
  unsigned shouldBe = 7;
  EXPECT_EQ(hv, shouldBe);
}

TEST(AdditionalPart1, HashFunction17) {
  unsigned hv = polynomialHashFunction("abc", 65535, 10);
  unsigned shouldBe = 8;
  EXPECT_EQ(hv, shouldBe);
}

TEST(AdditionalPart1, Insert1) {
  WordSet words(11);
  words.insert("abc");
  EXPECT_TRUE(words.contains("abc"));
}

TEST(AdditionalPart1, Insert2) {
  WordSet words(11);
  words.insert("abc");
  words.insert("def");
  EXPECT_TRUE(words.contains("abc"));
  EXPECT_TRUE(words.contains("def"));
}

TEST(AdditionalPart1, WordList) {
  WordSet words(11);
  std::ifstream in("words.txt");
  loadWordsIntoTable(words, in);

  EXPECT_EQ(words.getCount(), 38607);
  EXPECT_EQ(words.getCapacity(), 205759);

  std::string line, word;
  std::stringstream ss;

  while (getline(in, line)) {
    ss.clear();
    ss << line;
    while (ss >> word) {
      EXPECT_TRUE(words.contains(word));
    }
  }
}

// TEST(AdditionalPart1, InsertStressTest) {
//   WordSet words(11);
//   unsigned count = 0;

//   for (char c = 'a'; c <= 'z'; c++) {
//     for (char d = 'a'; d <= 'z'; d++) {
//       for (char e = 'a'; e <= 'z'; e++) {
//         for (char f = 'a'; f <= 'z'; f++) {
//           for (char g = 'a'; g <= 'z'; g++) {
//             count++;
//             std::string s = "";
//             s += c;
//             s += d;
//             s += e;
//             s += f;
//             s += g;
//             words.insert(s);
//           }
//         }
//       }
//     }
//   }

//   EXPECT_GE(words.getCapacity(), count);
//   EXPECT_EQ(count, words.getCount());
//   std::cout << "Size: " << words.getCount() << std::endl;

//   for (char c = 'a'; c <= 'z'; c++) {
//     EXPECT_FALSE(words.contains(std::string(1, c)));
//     for (char d = 'a'; d <= 'z'; d++) {
//       for (char e = 'a'; e <= 'z'; e++) {
//         EXPECT_FALSE(words.contains(std::string(1, c) + std::string(1, d) +
//                                     std::string(1, e)));
//         for (char f = 'a'; f <= 'z'; f++) {
//           for (char g = 'a'; g <= 'z'; g++) {
//             count++;
//             std::string s = "";
//             s += c;
//             s += d;
//             s += e;
//             s += f;
//             s += g;
//             EXPECT_TRUE(words.contains(s));
//             for (char h = 'a'; h <= 'd'; h++) {
//               EXPECT_FALSE(words.contains(s + std::string(1, h)));
//             }
//           }
//         }
//       }
//     }
//   }
// }

TEST(AdditionalPart2, ManToApe) {
  WordSet words(11);
  std::string WORD_ONE = "man";
  std::string WORD_TWO = "ape";
  auto CORRECT_LENGTH = 6;

  std::ifstream in("words.txt");
  loadWordsIntoTable(words, in);

  std::vector<std::string> r = convert(WORD_ONE, WORD_TWO, words);

  std::ifstream in2("words.txt");

  EXPECT_EQ(r.size(), CORRECT_LENGTH);
  EXPECT_TRUE(validConversion(r, WORD_ONE, WORD_TWO, in2));
}

TEST(AdditionalPart2, ColdToWarm) {
  WordSet words(11);
  std::string WORD_ONE = "cold";
  std::string WORD_TWO = "warm";
  auto CORRECT_LENGTH = 5;

  std::ifstream in("words.txt");
  loadWordsIntoTable(words, in);

  std::vector<std::string> r = convert(WORD_ONE, WORD_TWO, words);

  std::ifstream in2("words.txt");

  EXPECT_EQ(r.size(), CORRECT_LENGTH);
  EXPECT_TRUE(validConversion(r, WORD_ONE, WORD_TWO, in2));
}

TEST(AdditionalPart2, FoolToSage) {
  WordSet words(11);
  std::string WORD_ONE = "fool";
  std::string WORD_TWO = "sage";
  auto CORRECT_LENGTH = 7;

  std::ifstream in("words.txt");
  loadWordsIntoTable(words, in);

  std::vector<std::string> r = convert(WORD_ONE, WORD_TWO, words);

  std::ifstream in2("words.txt");

  EXPECT_EQ(r.size(), CORRECT_LENGTH);
  EXPECT_TRUE(validConversion(r, WORD_ONE, WORD_TWO, in2));
}

TEST(AdditionalPart2, ElectroencephalogramToNondeterministically) {
  WordSet words(11);
  std::string WORD_ONE = "electroencephalogram";
  std::string WORD_TWO = "nondeterministically";
  auto CORRECT_LENGTH = 0;

  std::ifstream in("words.txt");
  loadWordsIntoTable(words, in);

  std::vector<std::string> r = convert(WORD_ONE, WORD_TWO, words);

  for (auto s : r) {
    std::cout << s << std::endl;
  }

  std::ifstream in2("words.txt");

  EXPECT_EQ(r.size(), CORRECT_LENGTH);
  EXPECT_FALSE(validConversion(r, WORD_ONE, WORD_TWO, in2));
}

TEST(AdditionalPart2, AnthropomorphicallyToIncomprehensibility) {
  WordSet words(11);
  std::string WORD_ONE = "anthropomorphically";
  std::string WORD_TWO = "incomprehensibility";
  auto CORRECT_LENGTH = 0;

  std::ifstream in("words.txt");
  loadWordsIntoTable(words, in);

  std::vector<std::string> r = convert(WORD_ONE, WORD_TWO, words);

  for (auto s : r) {
    std::cout << s << std::endl;
  }

  std::ifstream in2("words.txt");

  EXPECT_EQ(r.size(), CORRECT_LENGTH);
  EXPECT_FALSE(validConversion(r, WORD_ONE, WORD_TWO, in2));
}

TEST(AdditionalPart2, BoyishToPaunch) {
  WordSet words(11);
  std::string WORD_ONE = "boyish";
  std::string WORD_TWO = "paunch";
  auto CORRECT_LENGTH = 0;

  std::ifstream in("words.txt");
  loadWordsIntoTable(words, in);

  std::vector<std::string> r = convert(WORD_ONE, WORD_TWO, words);

  std::ifstream in2("words.txt");

  EXPECT_EQ(r.size(), CORRECT_LENGTH);
  EXPECT_FALSE(validConversion(r, WORD_ONE, WORD_TWO, in2));
}

TEST(AdditionalPart2, BoyishToPaunch2) {
  WordSet words(11);
  std::string WORD_ONE = "boyish";
  std::string WORD_TWO = "paunchw";
  auto CORRECT_LENGTH = 0;

  std::ifstream in("words.txt");
  loadWordsIntoTable(words, in);

  std::vector<std::string> r = convert(WORD_ONE, WORD_TWO, words);

  std::ifstream in2("words.txt");

  EXPECT_EQ(r.size(), CORRECT_LENGTH);
  EXPECT_FALSE(validConversion(r, WORD_ONE, WORD_TWO, in2));
}

TEST(AdditionalPart2, EmptyToEmpty) {
  WordSet words(11);
  std::string WORD_ONE = "";
  std::string WORD_TWO = "";
  auto CORRECT_LENGTH = 0;

  std::ifstream in("words.txt");
  loadWordsIntoTable(words, in);

  std::vector<std::string> r = convert(WORD_ONE, WORD_TWO, words);

  std::ifstream in2("words.txt");

  EXPECT_EQ(r.size(), CORRECT_LENGTH);
  EXPECT_FALSE(validConversion(r, WORD_ONE, WORD_TWO, in2));
}

} // namespace
