
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

#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>
#include "Exception.h"
#include "Disjoint_sets.h"

using namespace std;

struct edge_detail{
    int row;
    int column;
    double weight;
};

class Weighted_graph {
	private:
		static const double INF;
		double** graph;
		int num_nodes;
		int num_edges;
		

		// Do not implement these functions!
		// By making these private and not implementing them, any attempt
		// to make copies or assignments will result in errors
		Weighted_graph( Weighted_graph const & );
		Weighted_graph &operator=( Weighted_graph );

		// your choice

	public:
		Weighted_graph( int = 10 );
		~Weighted_graph();

		int degree( int ) const;
		int edge_count() const;
		std::pair<double, int> minimum_spanning_tree() const;

		bool insert_edge( int, int, double );
		bool erase_edge( int, int );
		void clear_edges();

	// Friends

	friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

//Allocate memory for the graph and initialize the graph
Weighted_graph::Weighted_graph(int n ) {
    graph = new double*[n];
    num_edges = 0;
    num_nodes = n;
    
    //actually initialize the matrix
    for (int i = 0; i < n; i++){
        graph[i] = new double[n];
        for (int j = 0; j < n; j++){
            graph[i][j] = INF;
        }
    }
    
    
}

// Deallocate memory for the graph
Weighted_graph::~Weighted_graph() {
    for(int i = 0; i < num_nodes; i++){
        delete [] graph[i];
    }
    delete [] graph;
    num_edges = 0;
    num_nodes = 0;

}

//Return the degree of vertex n
int Weighted_graph::degree(int u) const {
    //throw illegal_argument() for the wrong vertex
    
    if (u >= num_nodes || u < 0){
        throw illegal_argument();
    }
    
    int deg = 0;
    for (int i = 0; i < num_nodes; i++){
        if(graph[i][u] != INF){
            deg += 1;
        }
        if(graph[u][i] != INF){
            deg += 1;
        }
    }
    
	return deg;

}

//Return the number of edges in the graph
int Weighted_graph::edge_count() const {
	return num_edges;
}

//Delete the edge between vertices i and j. If there is not an edge between them, return false
bool Weighted_graph::erase_edge(int i, int j) {
    if (i >= num_nodes || j >= num_nodes || i < 0 || j < 0){
        throw illegal_argument();
    }
    if (i == j){
        return true;
    }
    if (graph[i][j] != INF && i < j){
        graph[i][j] = INF;
        num_edges -= 1;
        return true;
    }
    if (graph[j][i] != INF && i > j){
        graph[j][i] = INF;
        num_edges -= 1;
        return true;
    }
    return false;
}

//Delete all edges in the graph
void Weighted_graph::clear_edges() {
    for (int i = 0; i < num_nodes; i++){
        for (int j = 0; j < num_nodes; j++){
            graph[i][j] = INF;
        }
    }
    num_edges = 0;
    
}

//Insert the edge between i and j with an edge of weight d.
bool Weighted_graph::insert_edge( int i, int j, double d ) {
    
    if (d <= 0 || i < 0 || j < 0 || i >= num_nodes || j >= num_nodes){
        throw illegal_argument();
    }

    else if (i == j ){
        return false;
    }
    
    
    else{
        
        if (i > j) {
            if (graph[j][i] == INF) {
                graph[j][i] = d;
                num_edges += 1;
            }
            else if (graph[j][i] != INF){
                graph[j][i] = d;
            }
        }
        else{
            if (graph[i][j] == INF){
                graph[i][j] = d;
                num_edges += 1;
            }
            if (graph[i][j] != INF){
                graph[i][j] = d;
            }
        }
        return true;
    }

}

std::pair<double, int> Weighted_graph::minimum_spanning_tree() const {
    
    if (num_edges == 0){
        return std::pair<double,int>(0.0, 0);
    }
    
    edge_detail * edges = new edge_detail[num_edges];
    double total_weight = 0;
    int edge_checked = 0;
    int tracker = 0;
    
    for (int i = 0; i < num_nodes; i++){
        for (int j = 0; j < num_nodes; j++){
            if(graph[i][j] != INF){
                edges[tracker].row = i;
                edges[tracker].column = j;
                edges[tracker].weight = graph[i][j];
                tracker += 1;
            }
        }
    }
    
    //insertion sort
    edge_detail temp;
    int counter;
    for (int i = 0; i < num_edges; i++){
        counter = i;
        
        while ( counter > 0 && (edges[counter].weight < edges[counter - 1].weight)){
            temp = edges[counter];
            edges[counter] = edges[counter - 1];
            edges[counter - 1] = temp;
            counter -= 1;
        }
    }
    
    
    
    Disjoint_set disjoint_set(num_nodes);
    
    for (int i = 0; i < num_edges; i++){
        if (disjoint_set.num_sets() == 1){
            break;
        }
        edge_checked += 1;
        if (disjoint_set.find_set(edges[i].row) != disjoint_set.find_set(edges[i].column)){
            disjoint_set.union_sets(edges[i].row, edges[i].column);
            total_weight += edges[i].weight;
        }
        
    }
    
    
    
    delete [] edges;
    
    return std::pair<double,int>(total_weight , edge_checked);

}

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
	

	return out;
}


#endif
