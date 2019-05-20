/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  y2754wan@uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  Fall 2018
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef TRIE_H
#define TRIE_H

#ifndef nullptr
#define nullptr 0
#endif

#include "ece250.h"
#include "Trie_node.h"
#include "Exception.h"
#include <iostream>
#include <string>
#include <cctype>
#include <stdlib.h>

class Trie {
private:
    Trie_node *root_node;
    int trie_size;
    
public:
    Trie();
    ~Trie();
    
    // Accessors
    
    bool valid_string( std::string const & ) const;
    int size() const;
    bool empty() const;
    bool member( std::string const & ) const;
    Trie_node *root() const;
    // Mutators
    
    bool insert( std::string const & );
    bool erase( std::string const & );
    void clear();
    
    // Friends
    
    friend std::ostream &operator<<( std::ostream &, Trie const & );
};

Trie::Trie(){
    root_node = nullptr;
    trie_size = 0;
}

Trie::~Trie() {
    if(root_node != nullptr){
        root_node -> clear();
    }
}

bool Trie::valid_string(std::string const &str) const {
    char letter;
    for(int i = 0; i < str.length(); i++){
        letter = str[i];
        if(!((letter >= 'a' && (int)letter <= 'z') || ((int)letter >= 'A' && (int)letter <= 'Z'))){
            return false;
        }
    }
    return true;
}

int Trie::size() const {
    return trie_size;
}

bool Trie::empty() const {
    return ( size() == 0 );
    
}

Trie_node *Trie::root() const {
    //return a pointer to the root_node
    return root_node;
}

bool Trie::member( std::string const &str ) const {
    if(!valid_string(str)){
        throw illegal_argument();
    }
    if(empty()){
        return false;
    }
    if(root_node->member(str,1)){
        return true;
    }else{
        return false;
    }
}

bool Trie::insert( std::string const &str ) {
    //if the str is already in the trie
    if(member(str)){
        return false;
    }
    if(valid_string(str) == false){
        throw illegal_argument();
    }
    else{
        //calling insert on the root.
        if(root_node == nullptr){
            //if the root_node is null, create an instance of the Trie_node class,
            root_node = new Trie_node();
        }
        //and assign it to the root first.
        bool inserted = root_node->insert(str,1);
        if(inserted){
            trie_size += 1;
        }
        return inserted;
    }
}

bool Trie::erase( std::string const &str ) {
    //if the str is not in the tree, return false
    if(empty()){
        return false;
    }
    if(valid_string(str) == false){
        throw illegal_argument();
    }
    else if(root_node->member(str,1) == false){
        return false;
    }
    else{
        bool deleted = root_node->erase(str,0,root_node);
        if(deleted){
            trie_size -= 1;
        }
        return deleted;
    }
}

void Trie::clear() {
    if(root_node == nullptr){
        return;
    }
    //call clear on the root_node
    root_node->clear();
    root_node = nullptr;
    trie_size = 0;
}

std::ostream &operator<<( std::ostream &out, Trie const &trie ) {
    
    return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
