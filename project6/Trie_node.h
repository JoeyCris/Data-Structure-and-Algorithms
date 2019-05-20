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

#ifndef SINGLE_NODE_H
#define SINGLE_NODE_H

#ifndef nullptr
#define nullptr 0
#endif

#include <string>
#include <cctype>
#include "ece250.h"

class Trie;

class Trie_node {
private:
    Trie_node **children;
    bool is_terminal;
    static int const CHARACTERS = 26;
    
    
public:
    Trie_node();
    Trie_node *child( int ) const;
    
    bool noChildren();
    
    bool member( std::string const &, int ) const;
    
    bool insert( std::string const &, int );
    bool erase( std::string const &, int, Trie_node *& );
    void clear();
    
    friend class Trie;
    
    // if ptr is a pointer to a Trie_node object
    // in one of the friendly classes, you should:
    //    use   ptr->next_   to modify it
    //    use   ptr->next()      to access it
};

/*children( nullptr ),
 is_terminal( false ) {
 // empty constructor
 }*/

Trie_node::Trie_node(){
    is_terminal = false;
    children = nullptr;
}


Trie_node *Trie_node::child( int n ) const {
    if ( children == nullptr ) {
        return nullptr;
    }
    else {
        return children[n];
    }
}

bool Trie_node::noChildren(){
    int counter = 0;
    for(int i = 0; i < CHARACTERS; i++){
        if(children[i] != nullptr){
            counter++;
        }
    }
    if(counter == 0){
        return true;
    }
    else{
        return false;
    }
}

bool Trie_node::member( std::string const &str, int depth ) const {
    
    if(children == nullptr){
        return false;
    }
    char target_letter = str[depth-1];
    int position;
    //determine the child using ASCII Table
    if((int)target_letter >= 97 && (int)target_letter <= 122){
        target_letter -= 97;
        position = target_letter;
    }else{
        target_letter -= 65;
        position = target_letter;
    }
    if(depth == str.length()){
        //if the letter is in the trie and it's a terminal
        if(children[position] != nullptr && children[position]->is_terminal == true){                     return true;
        }
        //if we reach the last letter of a string and it's not a terminal, this string is a part of another word
        else{
            return false;
        }
    }else{
        //if the letter and all following letters are matched
        if(children[position] != nullptr && children[position]->member(str,depth+1)){
            return true;
        }
        else{
            return false;
        }
    }
    return false;
}

bool Trie_node::insert( std::string const &str, int depth ){
    if(children == nullptr){
        //If the curret node is a leaf, allocate children to it
        children = new Trie_node*[CHARACTERS];
        for(int i = 0; i < CHARACTERS; i++){
            children[i] = nullptr;
        }
    }
    char target_letter = str[depth-1];
    int position;
    bool success;
    if((int)target_letter >= 97 && (int)target_letter <= 122){
        position = (int)(target_letter - 97);        //Determine the child using ascii table
    }
    else{
        position = (int)(target_letter - 65);
    }
    
    if(children[position] == nullptr){
        children[position] = new Trie_node();
    }
    //if the letter is the last letter in the string, set is_terminal to true
    if(depth == str.length()){
        children[position]->is_terminal = true;
        return true;
    }
    //if the letter is not the last one, continue to insert the rest of the str
    else{
        success = children[position]->insert(str,depth+1);
    }
    if(success){
        return true;
    }
}

bool Trie_node::erase( std::string const &str, int depth, Trie_node *&ptr_to_this ){
    if(depth == str.length()){
        if(children == nullptr){
            //If the node is already a leaf, delete the node and return
            ptr_to_this = nullptr;
            delete this;
            return true;
        }
        else{
            //If this node is not a leaf, set is_terminal to false
            is_terminal = false;
            return true;
        }
    }
    else{
        char next_letter = str[depth];
        int position;
        if(next_letter >= 97 && next_letter <= 122){
            next_letter -= 97;
            position = next_letter;
        }else{
            //Convert char to int
            next_letter -= 65;
            position = next_letter;
        }
        //Erase the child
        bool success = children[position]->erase(str,depth+1,children[position]);
        if(success){
            //If it has no children, turn the current node to a leaf first
            if(noChildren()){
                delete[] children;
                children = nullptr;
                if(is_terminal){
                    return true;
                }
                ptr_to_this = nullptr;
                delete this;
                return true;
            }
            else{
                return true;
            }
        }
        else{
            return false;
        }
    }
}

void Trie_node::clear(){
    if(children == nullptr){
        delete this;
        return;
    }
    else{
        for(int i = 0; i < CHARACTERS; i++){
            if(children[i] != nullptr){
                children[i]->clear();
            }
        }
        delete[] children;
        delete this;
        return;
    }
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
