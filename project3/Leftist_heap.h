
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
 * None
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 * None
 *
 *****************************************/

#ifndef LEFTIST_HEAP_H
#define LEFTIST_HEAP_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Leftist_node.h"

template <typename Type>
class Leftist_heap {
	private:
		Leftist_node<Type> *root_node;
		int heap_size;

	public:
		Leftist_heap();
		~Leftist_heap();

		void swap( Leftist_heap &heap );
		

		bool empty() const;
		int size() const;
		int null_path_length() const;
		Type top() const;
		int count( Type const & ) const;

		void push( Type const & );
		Type pop();
		void clear();

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Leftist_heap<T> const & );
};

// some sample functions are given

template <typename Type>
Leftist_heap<Type>::Leftist_heap():
root_node( nullptr ),
heap_size( 0 ) {
	// does nothing
}



template <typename Type>
Leftist_heap<Type>::~Leftist_heap() {
	clear();  // might as well use it...
}

template <typename Type>
void Leftist_heap<Type>::swap( Leftist_heap<Type> &heap ) {
	std::swap( root_node, heap.root_node );
	std::swap( heap_size, heap.heap_size );
}



// Your implementation here
// STRONG HINT:  Write a default definition of each function, even if
// it only returns the default value (false, 0, or Type()).
//
// Once you have done this, you can proceed and implement the member functions
// one at a time.  If you do not, and just start implementing the member
// functions so that you can't compile and test your function, good luck. :-)

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Leftist_heap<T> const &heap ) {
	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

//Return the number of nodes in the heap
template <typename Type>
int Leftist_heap<Type>::size() const{
    return heap_size;
}

//Check if the heap is empty
template <typename Type>
bool Leftist_heap<Type>::empty() const{
    return (heap_size == 0);
}


// Return the heap_null_path_length of the root node
template <typename Type>
int Leftist_heap<Type>::null_path_length() const{
    if ( (root_node != nullptr) && (heap_size != 0) )
    {
        return root_node -> null_path_length();
    }
    else
    {
        return -1;
    }
}

// Return the number of instances of obj in the heap
template <typename Type>
int Leftist_heap<Type>::count(const Type &obj) const{
    int targets = root_node -> count(obj);
    return targets;
}


//Return the element at the top of the heap(root_node).
template <typename Type>
Type Leftist_heap<Type>::top() const{
    //if the tree is empty, throw an underflow
    if ( empty() )
    {
        throw underflow();
    }
    else
    {
        return root_node -> retrieve();
    }
}

//Works like an insertion. Insert the new element into the heap. Increment the heap size.
template <typename Type>
void Leftist_heap<Type>::push(const Type & obj)
{
    // Create a new leftist node
    Leftist_node <Type> *newNode = new Leftist_node<Type> (obj);
    // Call push on the root node and pass the new node and root node as the arguments
    root_node -> push(newNode, root_node);
    //Incerment the heap size
    heap_size += 1;
}


//Works like the extract-min.Pop out the least element in the heap and delete its node (extracts min from the heap). If the tree is empty, throws underflow(). Return the element in the popped node and decrement the heap size.
template <typename Type>
Type Leftist_heap<Type>::pop(){
    if( (root_node != nullptr) && (heap_size != 0) )
    {
        Type least = root_node -> retrieve();
        Leftist_node<Type> * temp = root_node;
        
        // The left sub-tree becomes the root node
        root_node = root_node -> left();
        
        // The right sub-tree is pushed into the new root node
        root_node -> push(temp -> right(), root_node);
        
        // Decrement the heap size
        heap_size -= 1;
        
        // Pop the least element and delete its node
        delete temp;
        return least;
    }
    // If the heap is empty throw underflow
    else
    {
        throw underflow();
    }
}

//Call the clear on the root node.Then reset the root node and heap size
template <typename Type>
void Leftist_heap<Type>::clear(){
    heap_size = 0;
    root_node -> clear();
    root_node = nullptr;
}

#endif
