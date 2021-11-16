#include <sstream>
#include "testTrie.h"
#include "gtest/gtest.h"

TEST(BasicTest, ConstructDestructEmpty) {
    Trie<int> trie;
    EXPECT_TRUE(trie.empty());
    Trie<int>* t = new Trie<int>;
    EXPECT_TRUE(t->empty());
    delete t;
}

TEST(BasicTest, InsertSimple) {
    Trie<string> trie;
    Trie<string>::value_type t("wer", "who");
    trie.insert(t);
    EXPECT_FALSE(trie.empty());
}

TEST(BasicTest, InsertPrint) {
    Trie<string> trie;
    Trie<string>::value_type t("wer", "who");
    trie.insert(t);
    stringstream strstr;
    strstr << trie;
    string res("w\n"
               "  e\n"
               "    r\n"
               "      :who\n");
    EXPECT_STREQ(res.c_str(), strstr.str().c_str());
}

TEST(BasicTest, InsertComplex) {
    Trie<string> trie;
    Trie<string>::value_type t1("wer", "who");
    Trie<string>::value_type t2("wir", "we");
    Trie<string>::value_type t3("wird", "will");
    trie.insert(t1);
    trie.insert(t2);
    trie.insert(t3);
    stringstream strstr;
    strstr << trie;
    string res("w\n"
               "  e\n"
               "    r\n"
               "      :who\n"
               "  i\n"
               "    r\n"
               "      :we\n"
               "      d\n"
               "        :will\n");
    EXPECT_STREQ(res.c_str(), strstr.str().c_str());
}


TEST(BasicTest, InsertDouble) {
    Trie<string> trie;
    Trie<string>::value_type t1("wer", "woh");
    Trie<string>::value_type t2("wer", "who");
    trie.insert(t1);
    trie.insert(t2);
    stringstream strstr;
    strstr << trie;
    string res("w\n"
               "  e\n"
               "    r\n"
               "      :who\n");
    EXPECT_STREQ(res.c_str(), strstr.str().c_str());
}

TEST(BasicTest, EraseSimple) {
    Trie<string> trie;
    Trie<string>::value_type t1("wer", "who");
    trie.insert(t1);
    trie.erase("wer");
    EXPECT_TRUE(trie.empty());
}

TEST(BasicTest, EraseFail) {
    Trie<string> trie;
    Trie<string>::value_type t1("wer", "who");
    trie.insert(t1);
    trie.erase("was");
    EXPECT_FALSE(trie.empty());
}

TEST(BasicTest, EraseComplex) {
    Trie<string> trie;
    Trie<string>::value_type t1("wer", "who");
    Trie<string>::value_type t2("wir", "we");
    Trie<string>::value_type t3("wird", "will");
    trie.insert(t1);
    trie.insert(t2);
    trie.insert(t3);
    trie.erase("wir");
    stringstream strstr;
    strstr << trie;
    string res("w\n"
               "  e\n"
               "    r\n"
               "      :who\n"
               "  i\n"
               "    r\n"
               "      d\n"
               "        :will\n");
    EXPECT_STREQ(res.c_str(), strstr.str().c_str());
}

TEST(BasicTest, Clear) {
    Trie<string> trie;
    Trie<string>::value_type t1("wer", "who");
    Trie<string>::value_type t2("wir", "we");
    Trie<string>::value_type t3("wird", "will");
    trie.insert(t1);
    trie.insert(t2);
    trie.insert(t3);
    trie.clear();
    EXPECT_TRUE(trie.empty());
}

TEST(IteratorTest, Begin) {
    Trie<string> trie;
    Trie<string>::value_type t1("wer", "who");
    trie.insert(t1);
    EXPECT_TRUE(trie.begin() != trie.end());
}

TEST(IteratorTest, Star) {
    Trie<string> trie;
    Trie<string>::value_type t1("wer", "who");
    trie.insert(t1);
    Trie<string>::iterator it = trie.begin();
    EXPECT_STREQ((*it).first.c_str(), "wer");
    EXPECT_STREQ((*it).second.c_str(), "who");
}

TEST(IteratorTest, PlusPlus) {
    Trie<string> trie;
    Trie<string>::value_type t1("wer", "who");
    trie.insert(t1);
    Trie<string>::iterator it = trie.begin();
    Trie<string>::iterator it2 = it;
    EXPECT_TRUE(it == it2);
    Trie<string>::iterator it3 = it++;
    EXPECT_TRUE(it3 == trie.begin());
    EXPECT_TRUE(it == trie.end());
    Trie<string>::iterator it4 = ++it3;
    EXPECT_TRUE(it4 == trie.end());
}

TEST(IteratorTest, ForLoop) {
    Trie<string> trie;
    Trie<string>::value_type t1("wer", "who");
    Trie<string>::value_type t2("wir", "we");
    Trie<string>::value_type t3("wird", "will");
    trie.insert(t1);
    trie.insert(t2);
    trie.insert(t3);
    size_t count = 0;
    for ( Trie<string>::iterator it = trie.begin(); it != trie.end(); ++it ){
        switch( count ) {
            case 0:
                EXPECT_STREQ((*it).first.c_str(), "wer");
                EXPECT_STREQ((*it).second.c_str(), "who");
                break;
            case 1:
                EXPECT_STREQ((*it).first.c_str(), "wir");
                EXPECT_STREQ((*it).second.c_str(), "we");
                break;
            case 2:
                EXPECT_STREQ((*it).first.c_str(), "wird");
                EXPECT_STREQ((*it).second.c_str(), "will");
                break;
            default:
                ASSERT_TRUE(true);
                break;
        }
        count++;
    }
    EXPECT_TRUE(count==3);
}


TEST(FindTest, Found) {
    Trie<string> trie;
    Trie<string>::value_type t1("wer", "who");
    Trie<string>::value_type t2("wir", "we");
    Trie<string>::value_type t3("wird", "will");
    trie.insert(t1);
    trie.insert(t2);
    trie.insert(t3);

    Trie<string>::iterator it = trie.find("wird");
    ASSERT_NE(it, trie.end());
    EXPECT_STREQ((*it).second.c_str(), "will");
}

TEST(FindTest, NotFound) {
    Trie<string> trie;
    Trie<string>::value_type t1("wer", "who");
    Trie<string>::value_type t2("wir", "we");
    Trie<string>::value_type t3("wird", "will");
    trie.insert(t1);
    trie.insert(t2);
    trie.insert(t3);

    Trie<string>::iterator it = trie.find("unknown_key");
    EXPECT_EQ(it, trie.end());
}

