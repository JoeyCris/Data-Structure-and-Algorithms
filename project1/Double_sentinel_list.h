/*****************************************
 * UW User ID:  y2754wan
 * Student Name: Yifan Wang
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#ifndef DOUBLE_SENTINEL_LIST_H
#define DOUBLE_SENTINEL_LIST_H

#include <iostream>
#include "Exception.h"



template <typename Type>
class Double_sentinel_list {
	public:
		class Double_node {
			public:
				Double_node( Type const & = Type(), Double_node * = nullptr, Double_node * = nullptr );

				Type value() const;
				Double_node *previous() const;
				Double_node *next() const;

				Type         node_value;
				Double_node *previous_node;
				Double_node *next_node;
		};

		Double_sentinel_list();
		Double_sentinel_list( Double_sentinel_list const & );
		Double_sentinel_list( Double_sentinel_list && );
		~Double_sentinel_list();

		// Accessors

		int size() const;
		bool empty() const;

		Type front() const;
		Type back() const;

		Double_node *begin() const;
		Double_node *end() const;
		Double_node *rbegin() const;
		Double_node *rend() const;

		Double_node *find( Type const & ) const;
		int count( Type const & ) const;

		// Mutators

		void swap( Double_sentinel_list & );
		Double_sentinel_list &operator=( Double_sentinel_list );
		Double_sentinel_list &operator=( Double_sentinel_list && );

		void push_front( Type const & );
		void push_back( Type const & );

		void pop_front();
		void pop_back();

		int erase( Type const & );

	private:
		Double_node *list_head;
		Double_node *list_tail;
		int list_size;

		// List any additional private member functions you author here
        bool const illegal(Double_sentinel_list const &)const;
	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Double_sentinel_list<T> const & );
};

/////////////////////////////////////////////////////////////////////////
//                      Public member functions                        //
/////////////////////////////////////////////////////////////////////////


/*
The default constructor creates an empty list of list_size 0. The list_head and list_tail pointers point to a sentinel each.
*/
template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list():
// Updated the initialization list here
list_head( new Double_node ),
list_tail( new Double_node ),
list_size( 0 )
{
    list_head -> previous_node = nullptr;
    list_head -> next_node = list_tail;
    list_tail -> previous_node = list_head;
    list_tail -> next_node = nullptr;
    
}

/*
 The copy constructor creates a deep copy of the argument given list. If the list is illegal, the size is set to -1 to represent the invalidity with list_head and list_tail set to NULL.
 */

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> const &list ):
// Updated the initialization list here
list_head( new Double_node ),
list_tail( new Double_node ),
list_size( list.list_size )
{
    
    if( illegal(list) )
    {
        list_size = -1;
        list_head = list_tail = nullptr;
    }
    else
    {
        list_head -> previous_node = nullptr;
        list_tail -> next_node = nullptr;
        
        //if the list is empty, set list_head and list_tail to be NULL
        if(!list_size)
        {
            list_head -> next_node = list_tail;
            list_tail -> previous_node = list_head;
        }
        //else
        else
        {
            
            Double_node *curr = list.list_head -> next_node;
            int count = 0;
            
            
            while( count < list_size )
            {
                Double_node *replica = new Double_node;
                replica -> node_value = curr -> node_value;
                if(curr == list.list_head -> next_node)
                {
                    list_head -> next_node = replica;
                    list_tail -> previous_node = replica;
                    replica -> previous_node = list_head;
                    replica -> next_node = list_tail;
                }
                else
                {
                    replica -> previous_node = list_tail -> previous_node;
                    replica -> next_node = list_tail;
                    list_tail -> previous_node = replica;
                }
                count += 1;
                curr = curr -> next_node;
            }
            
        }
    }
    
    
    
    
}


/*
 The move constructor creates a sallow copy of the argument given list. It swaps the private variable values.
 The same is done to indicate an illegal list.
 */

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> &&list ):
// Updated the initialization list here
// Move Constructor
list_head( new Double_node ),
list_tail( new Double_node ),
list_size( list.list_size )
{
    if( illegal(list) )
    {
        list_size = -1;
        list_head = list_tail = nullptr;
    }
    else
    {
        swap(list);
    }
}

/*
 The destructor deletes all nodes in the list including all sentinels. Then the head and tail pointers are set to Null with list_size set to -1 to indicate that the list has been deleted.
 */
template <typename Type>
Double_sentinel_list<Type>::~Double_sentinel_list() {
    Double_node *behind = list_head;
    Double_node *forward = list_head;
    
    list_head = list_tail = nullptr;
    list_size = -1;
    
    while(forward != nullptr)
    {
        forward = forward -> next_node;
        delete behind;
        behind = forward;
        
    }
}

/*
 Returns the size of the list.
 */
template <typename Type>
int Double_sentinel_list<Type>::size() const {
    if(illegal(*this))
    {
        return -1;
    }
    return list_size;
}


/*
 Returns a boolean value of whether the list is empty. Simply check if the size is 0 or not.
 */
template <typename Type>
bool Double_sentinel_list<Type>::empty() const {
    if( list_size <= 0 ){
        return true;
    }
    return false;
}

/*
 Returns the value of the first node pointed to by the head sentinel's next pointer. Should throw an underflow if the list is empty.
 */
template <typename Type>
Type Double_sentinel_list<Type>::front() const {
//returns the node_value of the first node in the list
    if ( empty() )
    {
        throw underflow();
    }
    if ( illegal(*this ) )
    {
        return Type();
    }
    return list_head -> next_node ->node_value;
}

/*
 Returns the value of the first node pointed to by the tail sentinel's previous pointer. Should throw an underflow if the list is empty.
 */

template <typename Type>
Type Double_sentinel_list<Type>::back() const {
    if ( empty() )
    {
        throw underflow();
    }
    if (illegal (*this))
    {
        return Type();
    }
    return list_tail -> previous_node ->node_value;
}

/*
 Returns the address stored pointed to by the head sentinel's next pointer.
 */
template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::begin() const {
    if (illegal( *this ))
    {
        return nullptr;
    }
    return list_head -> next_node;
}

/*
 Returns the address of the tail sentinel.
 */
template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::end() const {
    if (illegal (*this) )
    {
        return nullptr;
    }
    return list_tail;
}

/*
 Returns the address pointed to by the tail sentinel's previous pointer.
 */
template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rbegin() const {
    if (illegal (*this))
    {
        return nullptr;
    }
    return list_tail -> previous_node;
}

/*
 Returns the address of the head sentinel node.
 */

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rend() const {
    if (illegal (*this) )
    {
        return nullptr;
    }
    return list_head;
}

/*
 Returns the address of the first node. Returns empty() if none is found.
 */

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::find( Type const &obj ) const {
    if ( illegal (*this) )
    {
        return nullptr;
    }
    if (empty())
    {
        return end();
    }
    for(Double_node *curr = list_head -> next_node; curr -> next_node != nullptr; curr = curr ->next_node)
    {
        if(curr -> node_value == obj)
        {
            return curr;
        }
    }
    
    
}

/*
 Returns number of nodes in the list that store a value equal to the given obj.
 */

template <typename Type>
int Double_sentinel_list<Type>::count( Type const &obj ) const {
    int count = 0;
    if( illegal(*this) )
    {
        return -1;
    }
    for(Double_node *curr = list_head -> next_node; curr -> next_node != nullptr; curr = curr ->next_node)
    {
        if(curr -> node_value == obj){
            count += 1;
        }
    }
    
    return count;
}

template <typename Type>
void Double_sentinel_list<Type>::swap( Double_sentinel_list<Type> &list ) {
	// This is done for you
	std::swap( list_head, list.list_head );
	std::swap( list_tail, list.list_tail );
	std::swap( list_size, list.list_size );
}

// The assignment operator
template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> rhs ) {
	// This is done for you
	swap( rhs );

	return *this;
}

// The move operator
template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> &&rhs ) {
	// This is done for you
	swap( rhs );

	return *this;
}

/*
 Create a new node that contains a value equal to the given obj at the beginning of the list.
 */
template <typename Type>
void Double_sentinel_list<Type>::push_front( Type const &obj ) {
    if(illegal(*this))
    {
        return;
    }
    Double_node *newOne = new Double_node;
    newOne -> node_value = obj;
    Double_node *originalFirstOne = list_head -> next_node;
    
    list_head -> next_node = newOne;
    newOne -> previous_node = list_head;
    newOne -> next_node = originalFirstOne;
    originalFirstOne ->previous_node = newOne;
    
    list_size += 1;
    
}

/*
 Create a new node that cotains a value equal to the given obj at the end of the list.
 */

template <typename Type>
void Double_sentinel_list<Type>::push_back( Type const &obj ) {
    if (illegal (*this))
    {
        return;
    }
    Double_node *newOne = new Double_node;
    newOne -> node_value = obj;
    Double_node *originalLastOne = list_tail -> previous_node;
    
    list_tail -> previous_node = newOne;
    originalLastOne -> next_node = newOne;
    newOne -> previous_node = originalLastOne;
    newOne -> next_node = list_tail;
    
    list_size += 1;
}

/*
   Delete the first node that is pointed to by the head sentinel's next pointer. Should throw an underflow if the list is empty.
 */

template <typename Type>
void Double_sentinel_list<Type>::pop_front() {
    if(illegal(*this))
    {
        return;
    }
    if(empty())
    {
        throw underflow();
    }
    Double_node *originalFirstOne = list_head -> next_node;
    Double_node *originalSecondOne = originalFirstOne -> next_node;
    
    list_head -> next_node = originalSecondOne;
    originalSecondOne -> previous_node = list_head;
    
    delete originalFirstOne;
    
    list_size -= 1;
    
}

/*
 Delete the first node that is pointed to by the tail sentinel's previous pointer. Should throw an underflow if the list is empty.
 */

template <typename Type>
void Double_sentinel_list<Type>::pop_back() {
    if (illegal(*this))
    {
        return;
    }
    if (empty())
    {
        throw underflow();
    }
    Double_node *originalLastOne = list_tail -> previous_node;
    Double_node *originalSecondOne = originalLastOne -> previous_node;
    
    list_tail -> previous_node = originalSecondOne;
    originalSecondOne -> next_node = list_tail;
    
    delete originalLastOne;
    
    list_size -= 1;
}


/*
 Delete all nodes that cotain the value equal to the given obj in the list. Return the number of nodes been deleted.
 */
template <typename Type>
int Double_sentinel_list<Type>::erase( Type const &obj ) {
	if(illegal (*this) )
    {
        return -1;
    }
    if (empty())
    {
        return 0;
    }
    Double_node *curr = list_head -> next_node;
    int count = 0;
    while (curr -> next_node != nullptr)
    {
        if(curr -> node_value == obj)
        {
            Double_node *nextOne = curr -> next_node;
            count += 1;
            nextOne -> previous_node = curr -> previous_node;
            curr -> previous_node -> next_node = nextOne;
            delete curr;
            curr = nextOne;
            list_size -= 1;
        }
        else
        {
            curr = curr -> next_node;
        }
    }
    return count;
}

template <typename Type>
Double_sentinel_list<Type>::Double_node::Double_node(
	Type const &nv,
	typename Double_sentinel_list<Type>::Double_node *pn,
	typename Double_sentinel_list<Type>::Double_node *nn ):
// Updated the initialization list here
node_value( nv ), // This assigns 'node_value' the default value of Type
previous_node( pn ),
next_node( nn )
{
    //None
}

template <typename Type>
Type Double_sentinel_list<Type>::Double_node::value() const {
	return node_value;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::previous() const {
	return previous_node;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::next() const {
	return next_node;
}

/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

/*
 A function to check whether the list that is passed in is legal or not.
 */
template <typename Type>
bool const Double_sentinel_list<Type>::illegal(Double_sentinel_list <Type> const &list )const{
    Double_node* myHead = list.list_head;
    Double_node* myTail = list.list_tail;
    int mySize = list.list_size;
    if(myHead == nullptr || myHead -> previous_node != nullptr || myHead -> next_node == nullptr || myTail == nullptr || myTail -> next_node != nullptr || myTail -> previous_node == nullptr)
    {
        return true;
    }
    if (mySize < 0)
    {
        return true;
    }
    return false;
}

// If you author any additional private member functions, include them here

/////////////////////////////////////////////////////////////////////////
//                               Friends                               //
/////////////////////////////////////////////////////////////////////////

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Double_sentinel_list<T> const &list ) {
	out << "head";

	for ( typename Double_sentinel_list<T>::Double_node *ptr = list.rend(); ptr != nullptr; ptr = ptr->next() ) {
		if ( ptr == list.rend() || ptr == list.end() ) {
			out << "->S";
		} else {
			out << "->" << ptr->value();
		}
	}

	out << "->0" << std::endl << "tail";

	for ( typename Double_sentinel_list<T>::Double_node *ptr = list.end(); ptr != nullptr; ptr = ptr->previous() ) {
		if ( ptr == list.rend() || ptr == list.end() ) {
			out << "->S";
		} else {
			out << "->" << ptr->value();
		}
	}

	out << "->0";

	return out;
}

#endif
