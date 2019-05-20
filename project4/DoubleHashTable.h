#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H


/****************************************
 * UW User ID:  y2754wan@uwaterloo.ca
 * Submitted for ECE 250
 * Semester of Submission:  Fall 2018
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 ****************************************/

#include "Exception.h"
#include "ece250.h"

enum state { EMPTY, OCCUPIED, DELETED };

template<typename T>
class DoubleHashTable {
	private:
		int count;
		int power;
		int array_size;
		T *array;
		state *array_state;

		int h1( T const & ) const; // first hash function
		int h2( T const & ) const; // second hash function

	public:
		DoubleHashTable( int = 5 );
		~DoubleHashTable();
		int size() const;
		int capacity() const;		
		bool empty() const;
		bool member( T const & ) const;
		T bin( int ) const;

		void print() const;

		void insert( T const & );
		bool remove( T const & );
		void clear();
};

template<typename T >
DoubleHashTable<T >::DoubleHashTable( int m ):
count( 0 ), power( m ),
array_size( 1 << power ),
array( new T [array_size] ),
array_state( new state[array_size] ) {

	for ( int i = 0; i < array_size; ++i ) {
		array_state[i] = EMPTY;
	}
}

//Deallocate the memory that is allocated for the hash table, and also the state of the elements stored
template<typename T >
DoubleHashTable<T >::~DoubleHashTable() {
    delete []array;
    delete []array_state;
}

//Return the number of elements that are currently stored in the hash table
template<typename T >
int DoubleHashTable<T >::size() const {
    return count;
}

//Return the number of bins that are in the hash table
template<typename T >
int DoubleHashTable<T >::capacity() const {
	return array_size;
}


//Check whether there is element in the hash table
template<typename T >
bool DoubleHashTable<T >::empty() const {
	return (size() == 0);
}

//The first hash function. The obj is statically cast as an int. If the value is negative, add M to it
template<typename T >
int DoubleHashTable<T >::h1( T const &obj ) const {
    
    //obj statically cast as an integer
    int i = static_cast<int>(obj);
    
    int value = i % array_size;
    
    if ( value < 0 )
    {
        value += array_size;
    }
    return value;
}

//The second hash function which defines the jump size.
template<typename T >
int DoubleHashTable<T >::h2( T const &obj ) const {
    //obj statically cast as an integer
    int i = static_cast<int>(obj);
    
    //check if (i/M)%M is negative, then check whether (i/M)%M is even,if so add 1+M. Otherwise, add M to make the value be nonnegative.
    if ( (i/array_size) % array_size < 0)
    {
        if ( ((i/array_size) % array_size) % 2 == 0 )
        {
            return ( (i/array_size)%array_size + array_size + 1);
        }
        else
        {
            return ((i/array_size)%array_size + array_size);
        }
    }
    else
    {
        if ( ((i/array_size) % array_size) % 2 == 0 )
        {
            return ( (i/array_size)%array_size +  1);
        }
        else
        {
            return ( (i/array_size) % array_size );
        }
    }
    
    
}

//Search whether an obj is in the hash table.
template<typename T >
bool DoubleHashTable<T >::member( T const &obj ) const {
	//initialize the hash functions
    int probe = h1(obj);
    int jump = h2(obj);
    int tracker = 0;
    
    if (empty())
    {
        return false;
    }
    
    //Traverse the hash table using hash functions
    while (array_state[probe] == OCCUPIED)
    {
        if(array[probe] == obj && array_state[probe] == OCCUPIED)
        {
            return true;
        }
    
        if (tracker == array_size)
        {
            //Looped through all the bins and did not find the obj
            return false;
        }
    
        //Double hashing
        tracker += 1;
        probe = (probe + jump) % array_size;
        
        
    }
    return false;
}

//Return the entry at the desired bin of the hash table
template<typename T >
T DoubleHashTable<T >::bin( int n ) const {
	return array[n];
}

//Insert the object into the hash table
template<typename T >
void DoubleHashTable<T >::insert( T const &obj ) {
    
    //If the array is full, throws an overflow
    if (size() == array_size)
    {
        throw overflow();
    }
    
    int probe = h1(obj);
    int jump = h2(obj);
    
    //Insert the obj into an empty bin
    
    while (array_state[probe] == OCCUPIED)
    {
        probe = (probe + jump) % array_size;
    }
    array_state[probe] = OCCUPIED;
    array[probe] = obj;
    count += 1;
}

//Search for and remove a desired obj from the hash table. Change its state to be DELETED and return true. If it is not found, return false
template<typename T >
bool DoubleHashTable<T >::remove( T const &obj ) {
    int probe = h1(obj);
    int jump = h2(obj);
    
    int tracker = 0;
    
    while (tracker < array_size)
    {
        int theProbe = (tracker * jump + probe) % array_size;
        
        if (array[theProbe] == obj && array_state[theProbe] == OCCUPIED)
        {
            array_state[theProbe] = DELETED;
            count -= 1;
            return true;
        }
        tracker += 1;
    }
    
    return false;
}

//Clear the hash table. Upodate each bin's state and the value of count
template<typename T >
void DoubleHashTable<T >::clear() {
    for (int i = 0; i < array_size; i++)
    {
        array_state[i] = EMPTY;
    }
    count = 0;
}

template<typename T >
void DoubleHashTable<T >::print() const {
    for (int i=0; i<array_size; i++)
    {
        std::cout<<","<<array[i];
    }
    std::cout<<" | "<<std::endl;
    for (int j=0; j<array_size; j++)
    {
        std::cout<<","<<array_state[j];
    }
    std::cout<<" | ";
}

#endif
