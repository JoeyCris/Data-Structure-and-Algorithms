
#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#ifndef nullptr
#define nullptr 0
#endif


#include <limits>
#include "Exception.h"

using namespace std;

struct ll_entry; // represents each element of the linked list
struct set_info; // keeps track of the information (pointers to head and tail and the size of the set) of each set
//could we delete the above two lines?


struct ll_entry{ 
	int content;
	set_info* ptr_to_info; // ptr to the info entry of the corresponding set
	ll_entry* next;
	
};

struct set_info { 
	ll_entry* head;
	ll_entry* tail;
	int size;
};

class Disjoint_set {

private:
	ll_entry** nodes;
	set_info** sets;
	int set_counter;
	int initial_num_sets;
public:
	Disjoint_set(int);
	~Disjoint_set();
	int find_set(int) const;
	int num_sets() const;
	void union_sets(int, int);
};

//Initialize the nodes and the sets
Disjoint_set::Disjoint_set(int n) : nodes(new ll_entry*[n]), 
sets (new set_info*[n]), 
set_counter(n),
initial_num_sets(n) {

    for(int i = 0; i < n; i++){
        nodes[i] = new ll_entry();
        nodes[i]->content = i;
        nodes[i]->next = nullptr;
    }
    
    for(int i = 0; i < n; i++){
        sets[i] = new set_info();
        sets[i]->size = 1;
        sets[i]->head = nodes[i];
        sets[i]->tail = nodes[i];
    }
    
    for(int i = 0; i < n; i++){
        nodes[i]->ptr_to_info = sets[i];
    }
    
}


// Deallocate memory
Disjoint_set::~Disjoint_set() {
    for (int i = 0; i < initial_num_sets; i++){
        delete nodes[i];
        if (sets[i] != nullptr){
            delete sets[i];
        }
    }
    delete [] sets;
    delete [] nodes;
    set_counter = 0;
    initial_num_sets = 0;

}
int Disjoint_set::find_set(int item) const{
    if (item < 0 || item >= initial_num_sets){
        throw illegal_argument();
    }
    return nodes[item] -> ptr_to_info -> head -> content;
}

int Disjoint_set::num_sets() const {
	return set_counter;
}

void Disjoint_set::union_sets(int node_index1, int node_index2) {
	
	if (node_index1 == node_index2)
		return;
	
	set_info* si1 = nodes[node_index1]->ptr_to_info;
	set_info* si2 = nodes[node_index2]->ptr_to_info;

	// ni1: the index of the larger set, ni2: the index of the smaller index
	int ni1 = si1->size >= si2->size ? node_index1 : node_index2; 
	int ni2 = si1->size < si2->size ? node_index1 : node_index2;

    
    ll_entry * temp = nodes[ni2] -> ptr_to_info -> head;
    set_info * merger = nodes[ni1] -> ptr_to_info;
    merger -> tail -> next = temp; //Make the tail of the larger set point to the head of the smaller set
    merger -> size += nodes[ni2] -> ptr_to_info -> size; //Update the union_set's size
    
    
	/* iterate through the shorter list and modify the pointers
	while (has not reached the end of set) {
		....
	}*/
    
    while (temp != nullptr){
        if (temp -> next == nullptr){
            merger -> tail = temp;
        }
        temp -> ptr_to_info = merger;
        temp = temp -> next;
    }
    
    
	// do we need to modify anything else?
    set_counter -= 1;
	// delete the set_info entry that no longer exists
    if(sets[ni2]!=nullptr)                // if si2 is already deleted, not delete again
        delete si2;
    sets[ni2] = nullptr;
}


#endif
