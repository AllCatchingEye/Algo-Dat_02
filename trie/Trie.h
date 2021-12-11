/*
* Trie.h
*
*  Created on: 17.09.2020
*      Author: Max Fischer
*/

#ifndef SRC_TRIE_H_
#define SRC_TRIE_H_

#include <iostream>

using namespace std;

template <class T, class E=char>
class Trie {
public:
 typedef basic_string<E> key_type; //string=basic_string<char>
 typedef pair<const key_type, T> value_type;
 typedef T mapped_type;

private:
 static const E FINAL_SYMBOL = '\0';

 class Node {
  public:

   virtual ~Node() = default;
   virtual bool empty() const = 0;
 };

 class Leaf : public Node {
  public:
   value_type data;

   explicit Leaf(value_type data) : data(data) {

   }

   ~Leaf() = default;

   bool empty() const override {
     return false;
   }
 };

 class Branch: public Node {
  public:
   map<E, Node*> children;

   ~Branch() {
     for (auto it = children.begin(); it != children.end(); it++) {
       delete it->second;
     }
   }

   bool empty() const override {
     return children.empty();
   }
 };

 Branch *root;

public:

 class TrieIterator {
   typedef TrieIterator iterator;

  public:
   TrieIterator() {
   }

   value_type operator *() {
     return value_type(); //FIXME Dummy-Implementierung korrigieren
   }

   bool operator !=(const iterator& rhs) const {
     auto tmp(rhs);      //FIXME Dummy-Implementierung korrigieren
     return false;       //FIXME Dummy-Implementierung korrigieren
   }

   bool operator ==(const iterator& rhs) const {
     auto tmp(rhs);      //FIXME Dummy-Implementierung korrigieren
     return false;       //FIXME Dummy-Implementierung korrigieren
   }

   iterator& operator ++() {
     static iterator res; //FIXME Dummy-Implementierung korrigieren
     return res;          //FIXME Dummy-Implementierung korrigieren
   }

   iterator operator ++(int) { // postfix operator, dummy parameter
     return iterator();  //FIXME Dummy-Implementierung korrigieren
   }
 };

 Trie() {
   root = new Branch();
 }

 ~Trie() {
   delete root;
 }

 typedef TrieIterator iterator;

 bool empty() const {
   return true;    //FIXME Dummy-Implementierung korrigieren
 }

 void insert(const value_type& value) {
   E finalSymbol = FINAL_SYMBOL;

   auto key = value.first;
   Branch* branch = root;

   for (auto keyIt = key.begin(); keyIt != key.end(); keyIt++) {
     const auto childIt = branch->children.find(*keyIt);

     if (childIt != branch->children.end()) {
       branch = static_cast<Branch*>(childIt->second);
     } else {
       auto newBranch = new Branch();
       branch->children[*keyIt] = newBranch;
       branch = newBranch;
     }
   }

   const auto childIt = branch->children.find(finalSymbol);

   if (childIt != branch->children.end()) {
     delete childIt->second;
     childIt->second = new Leaf(value);
   } else {
     branch->children[finalSymbol] = new Leaf(value);
   }
 }

 void erase(const key_type& value) {
   auto tmp(value); //FIXME Dummy-Implementierung korrigieren
 }

 void clear() {
   delete root;
   root = new Branch();
 }

 iterator find(const key_type& testElement) {
   auto tmp(testElement);
   return iterator();  //FIXME Dummy-Implementierung korrigieren
 }

 iterator begin() {
   return iterator();  //FIXME Dummy-Implementierung korrigieren
 }

 iterator end() {
   return iterator();  //FIXME Dummy-Implementierung korrigieren
 }

 void printOn(ostream& ostr) const {
   function<void(Branch*, int)> print = [&print, &ostr](Branch* branch, int depth){
     for (auto childIt = branch->children.begin(); childIt != branch->children.end(); childIt++) {
       for (int i = 0; i < depth; i++) {
         ostr << "  ";
       }

       if (childIt->first != FINAL_SYMBOL) {
         ostr << childIt->first << endl;
         print(static_cast<Branch*>(childIt->second), depth + 1);
       } else {
         ostr << ":" << static_cast<Leaf*>(childIt->second)->data.second << endl;
       }
     }
   };

   print(root, 0);
 }
};

template <class E>
ostream& operator << (ostream& ostr, const Trie<E>& trie)     {trie.printOn(ostr); return ostr;}



#endif /* SRC_TRIE_H_ */
