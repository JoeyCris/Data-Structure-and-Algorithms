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
 *    -none
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -none
 *****************************************/

#ifndef DYNAMIC_STACK_H
#define DYNAMIC_STACK_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Exception.h"
#include <iostream>
using namespace std;


class Dynamic_stack {

	private:
		int *array;
		int count;		
		int array_size;
		int initial_size;
	
	public:
		Dynamic_stack(int = 10);
		~Dynamic_stack();

		int top() const;
		int size() const;
		bool empty() const;
		int capacity() const;
			
		void push( int const & );
		int pop();
		void clear();		
};

Dynamic_stack::Dynamic_stack( int n ):
count( 0 ),
array_size( n ),
initial_size(n)
{
    if ( n < 1 )
    {
        array = new int[1];
        array_size = 1;
        initial_size = 1;
    }
    else
    {
        array = new int[array_size];
    }
}


Dynamic_stack::~Dynamic_stack() {
    count = 0;
    array_size = 0;
    delete []array;
}


int Dynamic_stack::top() const {
    if ( count == 0 )
    {
        throw underflow();
    }
    else
    {
        return array[count - 1];
    }
}


int Dynamic_stack::size() const {
	return  count;
}


bool Dynamic_stack::empty() const {
    return (count == 0);
}


int Dynamic_stack::capacity() const {
    return array_size;
}


void Dynamic_stack::push( int const &obj ) {
    if (count == array_size) //If the stack is full, reallocate it
    {
        array_size = 2 * array_size;
        int *newStack = new int[array_size];
        for ( int i = 0; i < count; i++ )
        {
            newStack[i] = array[i];
        }
        delete []array;
        array = newStack;
    }
    //push in the new element (obj) and update the count
    array[count] = obj;
    count += 1;
}


int Dynamic_stack::pop() {
    if ( count == 0 )
    {
        throw underflow();
    }
    else
    {
        //pop out the top element and update the count
        count -= 1;
        return array[count];
    }
}

void Dynamic_stack::clear() {
    count = 0; //Remove all elements from the stack
    if(array_size != initial_size) //Reallocate if the size of the stack is not changed
    {
        delete []array;
        array = new int[initial_size];
        array_size = initial_size;
    }
}
#endif
