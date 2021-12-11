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

 struct PathElement {
   Branch* branch;
   typename map<E, Node*>::iterator iterator;

   bool operator==(const PathElement& rhs) const {
     return branch == rhs.branch && iterator == rhs.iterator;
   }

   bool operator!=(const PathElement& rhs) const {
     return !(rhs == *this);
   }
 };

 typedef vector<PathElement> Path;

public:
 class TrieIterator {
   typedef TrieIterator iterator;

  private:
   Path path;

  public:
   explicit TrieIterator(Path path): path(path) {
   }

   value_type operator *() {
     return static_cast<Leaf*>(path[path.size() - 1].iterator->second)->data;
   }

   bool operator !=(const iterator& rhs) const {
     return !(*this == rhs);
   }

   bool operator ==(const iterator& rhs) const {
     return path == rhs.path;
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
   return root->empty();
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
   function<void(Branch*, const key_type&)> remove = [&remove](Branch* branch, const key_type& value){
     if (value.size() == 0) {
       E key = FINAL_SYMBOL;

       const auto childIterator = branch->children.find(key);

       if (childIterator != branch->children.end()) {
         delete childIterator->second;
         branch->children.erase(key);
       }
     } else {
       E key = value.at(0);

       const auto childIterator = branch->children.find(key);

       if (childIterator != branch->children.end()) {
         auto child = static_cast<Branch*>(childIterator->second);

         remove(child, value.substr(1));

         if (child->empty()) {
           delete child;
           branch->children.erase(key);
         }
       }
     }
   };

   remove(root, value);
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

template <class T, class E>
ostream& operator << (ostream& ostr, const Trie<T, E>& trie)     {trie.printOn(ostr); return ostr;}



#endif /* SRC_TRIE_H_ */
