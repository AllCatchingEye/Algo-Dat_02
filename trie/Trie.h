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
	}

	~Trie() {
	}

	typedef TrieIterator iterator;

	bool empty() const {
	    return true;    //FIXME Dummy-Implementierung korrigieren
	}

	void insert(const value_type& value) {
	    auto tmp(value); //FIXME Dummy-Implementierung korrigieren
	}

	void erase(const key_type& value) {
	    auto tmp(value); //FIXME Dummy-Implementierung korrigieren
	}

	void clear() {
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
	  ostr << std::endl;   //FIXME Dummy-Implementierung korrigieren
	}
};

template <class E>
ostream& operator << (ostream& ostr, const Trie<E>& trie)     {trie.printOn(ostr); return ostr;}



#endif /* SRC_TRIE_H_ */
