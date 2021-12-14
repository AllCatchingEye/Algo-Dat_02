/*
* Trie.h
*
*  Created on: 17.09.2020
*      Author: Max Fischer
*/

#ifndef SRC_TRIE_H_
#define SRC_TRIE_H_

#include <iostream>
#include <stack>

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

 Branch *root = nullptr;

public:
 class TrieIterator {
  private:
   friend Trie;

   typedef TrieIterator iterator;

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

   typedef stack<PathElement> Path;

   Path path;

  public:
   TrieIterator() {
   }

   value_type operator *() {
     return static_cast<Leaf*>(path.top().iterator->second)->data;
   }

   bool operator !=(const iterator& rhs) const {
     return !(*this == rhs);
   }

   bool operator ==(const iterator& rhs) const {
     return path == rhs.path;
   }

   iterator& operator ++() {
     PathElement* element = &path.top();
     ++element->iterator;

     while(true) {
       if (element->iterator != element->branch->children.end()) {
         if (element->iterator->first == FINAL_SYMBOL) {
           return *this;
         } else {
           PathElement newElement;
           newElement.branch = static_cast<Branch*>(element->iterator->second);
           newElement.iterator = newElement.branch->children.begin();
           path.push(newElement);

           element = &path.top();
         }
       } else {
         path.pop();

         if (path.empty()) {
           return *this;
         } else {
           element = &path.top();
           ++element->iterator;
         }
       }
     }
   }

   iterator operator ++(int) { // postfix operator, dummy parameter
     iterator it = iterator(*this);
     ++(*this);
     return it;
   }
 };

 Trie() {

 }

 ~Trie() {
   delete root;
 }

 typedef TrieIterator iterator;

 bool empty() const {
   return root == nullptr;
 }

 void insert(const value_type& value) {
   if (empty()) {
     root = new Branch();
   }

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
   if (empty()) {
     return;
   }

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

   if (root->empty()) {
     clear();
   }
 }

 void clear() {
   delete root;
   root = nullptr;
 }

 iterator find(const key_type& testElement) {
   for (iterator it = begin(); it != end(); ++it) {
     if ((*it).first == testElement) {
       return it;
     }
   }

   return end();
 }

 iterator begin() {
   if (empty()) {
     return end();
   }

   typename iterator::PathElement element;
   element.branch = root;
   element.iterator = root->children.begin();

   typename iterator::Path path;
   path.push(element);

   while (true) {
     element = path.top();

     if (element.iterator->first == FINAL_SYMBOL) {
       iterator it;
       it.path = path;
       return it;
     } else {
       typename iterator::PathElement nextElement;
       nextElement.branch = static_cast<Branch*>(element.iterator->second);
       nextElement.iterator = nextElement.branch->children.begin();

       path.push(nextElement);
     }
   }
 }

 iterator end() {
   return iterator();
 }

 void printOn(ostream& ostr) const {
   if (!root) {
     return;
   }

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
