
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
 *    None
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    None
 *****************************************/

#ifndef LEFTIST_NODE_H
#define LEFTIST_NODE_H

#include <algorithm>
// You may use std::swap and std::min

#ifndef nullptr
#define nullptr 0
#endif

template <typename Type>
class Leftist_node {
	private:
		Type element;
		Leftist_node *left_tree;
		Leftist_node *right_tree;
		int heap_null_path_length;

	public:
		Leftist_node( Type const & );

		Type retrieve() const;
		bool empty() const;
		Leftist_node *left() const;
		Leftist_node *right() const;
		int count( Type const & ) const;
		int null_path_length() const;

		void push( Leftist_node *, Leftist_node *& );
		void clear();
};

//The Constructor
template <typename Type>
Leftist_node<Type>::Leftist_node( Type const &obj ):
element( obj ),
left_tree( nullptr ),
right_tree( nullptr ),
heap_null_path_length( 0 ) {
	// does nothing
}


//Check whether it is an empty heap
template <typename Type>
bool Leftist_node<Type>::empty() const {
	return ( this == nullptr );
}

//Return the element stored in the node
template <typename Type>
Type Leftist_node<Type>::retrieve() const{
    return element;
}

//Return the address of the left subtree
template <typename Type>
Leftist_node<Type>* Leftist_node<Type>::left() const{
    return this -> left_tree;
}

//Return the address of the right subtree
template <typename Type>
Leftist_node<Type>* Leftist_node<Type>::right() const{
    return this -> right_tree;
}

//Return the null path length of the node. If it is empty, return -1
template <typename Type>
int Leftist_node<Type>::null_path_length() const{
    if (this != nullptr)
    {
        return heap_null_path_length;
    }
    else
    {
        return -1;
    }
}

//Return the number of instances of obj in the sub-tree. Using a recursion.
template <typename Type>
int Leftist_node<Type>::count(const Type & obj) const{
    int count = 0;
    if (this == nullptr)
    {
        return count;
    }
    else
    {
        if (left_tree != nullptr)
        {
            count += left_tree -> count(obj);
        }
        if (right_tree != nullptr)
        {
            count += right_tree -> count(obj);
        }
        if (element == obj)
        {
            count += 1;
        }
    }
    return count;
}

template <typename Type>
void Leftist_node<Type>::push(Leftist_node *new_heap, Leftist_node *&ptr_to_this)  {
    //If the new_heap is null return
    if (new_heap == nullptr)
    {
        return;
    }
    else
    {
        //If this is null, set the pointer to this to be the new heap and return
        if (this == nullptr)
        {
            ptr_to_this = new_heap;
            return;
        }
        //If the element of this node ≤  new_heap’s element, push the node into the right subree.
        if (ptr_to_this -> element <= new_heap -> element)
        {
            right_tree -> push(new_heap, right_tree);
            
            if ( (left_tree == nullptr) && (right_tree != nullptr) )
            {
                std::swap(ptr_to_this -> right_tree, ptr_to_this -> left_tree);
            }
            
            else if ( (left_tree != nullptr) && (right_tree != nullptr) )
            {
                // Update the null_path length
                heap_null_path_length = std::min (1 + left_tree -> null_path_length(), 1 + right_tree -> null_path_length() );
                // if the left sub-tree has a smaller null_path_length than the right sub-tree, swap the two sub-trees
                if ( ( ptr_to_this -> left_tree -> null_path_length() ) < ( ptr_to_this -> right_tree -> null_path_length() ) )
                {
                    std::swap(ptr_to_this -> right_tree, ptr_to_this -> left_tree);
                }

            }
            
            
        }
        //If the element of current node > new_heap’s element, set the pointer to this to be the new heap and push this node to the new heap
        else
        {
            ptr_to_this = new_heap;
            new_heap -> push(this, ptr_to_this);
        }

    }
    
}


//Call clear on the root node. Then reset the root node and heap size
template<typename Type>
void Leftist_node<Type>::clear(){
    //If new heap is null retur
    if (this == nullptr)
    {
        return;
    }
    // Call clear function on the left sub-tree
    // Call clear function on the right sub-tree
    // Delete this node
    else
    {
        left_tree -> clear();
        right_tree -> clear();
        delete this;
    }
}



#endif
