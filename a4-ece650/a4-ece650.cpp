#include "minisat/core/SolverTypes.h"
#include "minisat/core/Solver.h"

#include <iostream>
#include <vector>
#include <string>

#include <algorithm>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <sstream>

using namespace std;


class Graph {
   public:
      // constructor
      Graph() {

      }
      
      // AdjList method
      vector<list< int > > adjList (int adjListSize, vector< vector<int> > const & edges)
      {
        vector < list<int> > adjList(adjListSize);
        
        //vector<int>::iterator v = edges[0].begin();
        for (int i = 0; i < edges.size(); i++)
        {
          int digit = 0;
          int first;
          int second;
          for (int num = 0; num < edges[i].size(); num++)
          {
            if (digit == 0)
            {
              // cout<< edges[i][num] <<endl;

              //adjList[i].push_back(edges[i][num]);
              first = edges[i][num];

              digit +=1;
            }
            else if (digit == 1)
            {
              // cout<< edges[i][num] <<endl;
              second = edges[i][num];
              digit +=1;
              //cout <<"\n"<< first << second <<"here \n";
            }

            // Issue was an else if instead of if
            if (digit == 2)
            {

              //cout <<"\n"<< first << second <<"here \n";
              adjList[first].push_back(second);
              adjList[second].push_back(first);
              // adjList[0].push_back(2)
              // adjList[2].push_back(0)

              adjList[first].unique();
              adjList[second].unique();
              // remove any duplicate elements from either list!


              digit = 0;
            }
            
            
          }
          // if (edges[i].size() > 0)
          //   cout<<"\n\n";

          
        }


        // if (!adjList.empty())
        //   cout << "Passed\n\n";

        

        
        return adjList;

        
      }

      // Dijkstra via AdjList method
      stack<int> dijkstraAdjList (vector<list< int > >Graph, int start, int end)
      {
        // Begin
        
        // Stack to be returned with inverted path or empty
        stack <int> S;

        // Graph size
        int length = Graph.size();


        vector <signed int> prev(length);//(length);

        
        vector <signed int> unvisited(length); // vertex set Q
        vector <long int> dist(length);
        
        for (int v = 0; v < length; v++)
        {
          
          dist[v] = 100001;
          
          // dist.push_back(10000);
          prev[v] = -1;

          
          // unvisited.push_back(v);
          unvisited[v] = v;
        
          // dist[start] = 0;
        }
        
        
        dist[start] = 0;
        
        
        int counter = length; 
        
        // while(!unvisited.empty())
        while (counter > 0)
        {
          
          
          // cout << "dist.size() is " << dist.size() << "\n";
          // return index of lowest value in dist[]
          int smallest = 1000000; // dist[0];
          // cout<< "smallest is "<< smallest <<endl;
          int location = 1000000;
          // for ( int i=1;  i < sizeof(dist)/sizeof(dist[0]);  ++i )
          
          for (int w = 0; w < length; w++)
          {
              if (( dist[w] < smallest ) && ( unvisited[w] >= 0) && (dist[w]<100000)) // last condition means reachable since initially 100001
              {
                  smallest = dist[w] ;
                  // cout<< "smallest is "<< smallest <<endl;
                  location = w;
              }// freeGift = r;
          }
          counter --; 
          
          

        int u = smallest;
        
          
          if (location==1000000)
          {
            while(!S.empty())
            S.pop();
            
            // End
            return S;
        }
          
          // YOU ARE HERE
        if (location == end)
          {
            int target = location;
            if (prev[target] > -1 || target == end)
            //{
            {
              while (target > -1)
              {
                
                S.push(target);
                // cout << "target is "<<target<<"\n";
                
                
                if (target == start)
                {
                  // cout << "HERE\n";
                  
                  
                  
                  return S;
                  
                }
                
                target = prev[target];
              }
            }	
            
          }
          
      
          
          unvisited[location] = -1;
          
          
          list <int> l = Graph[location];
          
          // std::vector<int> v{ std::begin(l), std::end(l) };
          vector <int> listElems;
          
          list <int> :: iterator it; 
          for(it = l.begin(); it != l.end(); ++it) 
          {
              //cout << '\t' << *it; 
              listElems.push_back(*it);
          }
          // cout << '\n'; 
          
        
              
              
          for (int V = 0; V < Graph[location].size(); V++){	// just means 1 times  
              // std::cout << n << '\n';
              int newDist = dist[location] + 1;
              
              
              
              // if (newDist < dist[Graph[location][V]])// dist[V]) I want Vth element in Graph[location] == l list E.g. [Graph[location][V]]
              if (newDist < dist[listElems[V]] )
          {
                // cout << "Poopers" << endl;
                dist[listElems[V]] = newDist;
                prev[listElems[V]] = location;
              }
          }
          

        // Clear
        // ================
        listElems.clear();
        l.clear();
        // ================

        }

        // return empty stack
        while(!S.empty())
          S.pop();

        // Clear
        // ================
        prev.clear();
        unvisited.clear();
        dist.clear();
        // ================
        

        // End
        return S;
      }
         
      
      
};



// Parser Class

class Parser {
   public:
      // constructor
      Parser() {
         numVertices = 0;
         highestVertex = 0;
         numCoors = 0;
      }

      // Integer extractor method from GeeksForGeeks
      vector<int> extractIntegerWords(string str) 
      { 
        stringstream ss;     

        /* Storing the whole string into string stream */
        ss << str; 

        /* Running loop till the end of the stream */
        string temp; 
        int found;
        vector<int> V; 
        
        while (!ss.eof()) { 

            /* extracting word by word from stream */
            ss >> temp; 

            /* Checking the given word is integer or not */
            if (stringstream(temp) >> found)
            { 
                // cout << found << " +\n"; 
                V.push_back(found);
            }

            /* To save from space at the end of string */
            temp = ""; 
        } 
        return V;
      } 

      int vParse(string v)
      {
        
        if (v[0] == 's')
        {
          // cout << "S spotted\n";
          // cout << numVertices << "\n";
          return numVertices;
        }

        if (v[0] == 'E')
        {
          return numVertices;
        }

        if (v.size()<2)
        {
          numVertices = 0;
          return numVertices;
        }


        if ((v[0]== 'V') && (v[1] = ' '))
        {

          vector <int> Verts = extractIntegerWords(v);
          if (Verts.size() > 0)
          { 
          numVertices=Verts[0];
          // check for if numVertices is 0
            if (numVertices == 0)
            {
              return numVertices;
            }// natural else below due to above return statement
          highestVertex = numVertices - 1;
          return numVertices;
          }
          else // no numbers in V found
          {
            return numVertices;
          }
        } 
        else
        {
          return numVertices;
        }

      }

      
      stack <int> eParse(string e)
      {
        while (!edgeStack.empty())
        {
          edgeStack.pop();
        }

        if (e.size()<4)
        {
          return edgeStack;
        }

        if ((e[0]== 'E') && (e[1] = ' ') && (e[2] == '{'))
        {

          // cout << e << " is old e\n";
          for (string::iterator it = e.begin(); it != e.end(); ++it) {
            if ((*it == '<') ||(*it == ',') || (*it == '>')) {
                *it = ' ';
            }
            else{ continue; }
          }
          // cout << e << " is new e\n";
          vector <int> Edg = extractIntegerWords(e);
          numCoors = Edg.size();
          for (int i =0 ; i<Edg.size(); i++)
          {
            if (Edg[i] > highestVertex)
            {
            // cout<< "Edge point(s) entered out of range\n";
            while (!edgeStack.empty())
            {
              edgeStack.pop();
            }
            return edgeStack;
            }
            else // if everything is fine, push to the Stack
            {
              edgeStack.push(Edg[i]);
            }
          }
          return edgeStack;
        }
        else{
          // std::cout << "Format incorrect" << std::endl;

          // continue keyword (in while) goes here

          //placeholder
          while (!edgeStack.empty())
          {
            edgeStack.pop();
          }
          return edgeStack;
          
        }
      }



      vector <int> sParse(string s)
      {
        vector <int> emptyVector;

        if (s.size()<2)
        {
          return emptyVector;
        }

        if (s[0] == 'E')
        {
          return emptyVector;
        }

        if ((s[0]== 'S') && (s[1] = ' '))
        {
          return emptyVector;
        }

        if ((s[0]== 's') && (s[1] = ' '))
        {

          vector <int> journey = extractIntegerWords(s);

          int start,end;


          if(journey.size() > 1){
            start = journey[0];
            end = journey[1];
          }
          else{
            // cout<< "Shortest path points provided are not valid\n";
            return emptyVector;
          }

          if ((start < 0) || (start > highestVertex) || (end < 0) || (end > highestVertex))
          {
            // cout<< "At least one vertex chosen for shortest path calculation is out of range\n";
            return emptyVector;
          }

          // cout<<"start is "<< start <<"\n";
          // cout<<"end is "<< end <<"\n";
          return journey;
        }
        else{
          return emptyVector;
        }
        
      }
      
      

      int getNumVertices() {
         return numVertices;
      };

      void setNumVertices(int n){
        numVertices = n;
      }

      int getHighestVertex(){
        return highestVertex;
      }

      void setHighestVertex(int n){
        highestVertex = n;
      }

      int getNumCoors(){
        return numCoors;
      }

      void setNumCoors(int n){
        numCoors = n;
      }

      stack <int> getEdgeStack(){
        return edgeStack;
      }
      
   private:
      int numVertices;
      signed int highestVertex;
      int numCoors;
      stack <int> edgeStack;
};

// UPDATE
#include<stdlib.h> 
#include<unistd.h> 
#include<stdio.h> 
#include<fcntl.h> 

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
// Below helps with wait
#include <sys/types.h>
#include <sys/wait.h>
// using ofstream constructors.
#include <iostream>
#include <fstream>


int main() {
    using Minisat::mkLit;
    using Minisat::lbool;
    using Minisat::Var;

    Parser parser;

	int verticesTotal = 0;
	stack<int>edgePoints;
	vector<int>trip;

	int numEdgePoints = 0;

	int start = 0;
	int end = 0;
    

    


while(!(cin.eof()))
{    

	// for n*k matrix

    // int V = 3; // Vertices

    std::string input; // = "V 3";
  	getline (std::cin,input);

	if (input.empty())
	{
	  return 0;
	}


	int V = parser.vParse(input);




	// vector<vector<int>> edges { {0,4},{4,1},{0,3},{3,4},{3,2},{1,3} };
    // vector<vector<int> > edges{ { 3, 7 }, 
    //                         { 3, 8 }, 
    //                         { 3, 9 },
    //                         { 3, 1 }, 
    //                         { 1, 6 }, 
    //                         { 1, 2 }, 
    //                         { 2, 10 }, 
    //                         { 6, 0 },
    //                         { 6, 4 }, 
    //                         { 4, 5 }
    //                         };  
    // vector<vector<int> > edges{ { 0, 1 }, 
    //                         { 0, 2 }, 
    //                         { 2, 0 },
    //                         { 2, 1 }, 
    //                         }; 

    // vector<vector<int> > edges;


    // = E {<0,1>,<0,2>,<2,0>,<2,1>}
  	getline (std::cin,input);
    edgePoints = parser.eParse(input); // edgePoints is a stack

    int count = 1;
    vector<vector<int> > edges;
    while (!edgePoints.empty())
    {
    	vector<int> edge;
    	while (count < 3 && !edgePoints.empty())
    	{
		    // cout << edgePoints.top() << endl;
		    edge.push_back(edgePoints.top());

		    edgePoints.pop();

		    count+=1;
		}
	    edges.push_back(edge);
      count = 1;
	}

    // cout << endl;

    // send stack variables to edges vector



    int n = V;
    // int k = 4; // from 1 to n actually
    int k = 1;


// place all of this (below) where you would have looked for s (replace s loop with this one)
while(k <= n)
{		
	Minisat::Solver solver;
	std::vector<int> nVec;
	Minisat::Var matrix[n][k]; // Note: rows then cols Thus 5 rows 3 col

	// Example
	//{1} {5}  /*  initializers for row indexed by 0 */
    //{5} {1}  /*  initializers for row indexed by 1 */
    //{9} {1}  /*  initializers for row indexed by 2 */

	int rows = n;
	int cols = k;

	// Variable allocation
	// void Solver::init_variables() {
	    for (int r = 0; r < rows; ++r) 
	    {
	        for (int c = 0; c < cols; ++c) 
	        {
                // auto var = solver.newVar();
                matrix[r][c] = solver.newVar();
	        }
	    }
	//}

	// Note : Standard variable allocation below

    // auto A = solver.newVar();
    // auto B = solver.newVar();
    // auto C = solver.newVar();


	// Assume variables have been allocated to the solver correctly (above)

	// Next is to apply the rules and push appropriate clauses to solver


	// for sudoku #FOLLOW STRUCTURE, NOT IMPLEMENTATION
	// ====================================================================
	// for (int row = 0; row < rows; ++row) {
	//     for (int value = 0; value < values; ++value) {
	//         Minisat::vec<Minisat::Lit> literals;
	//         for (int column = 0; column < columns; ++column) {
	//             literals.push(Minisat::mkLit(toVar(row, column, value)));
	//         }
	//         exactly_one_true(literals);
	//     }
	// }
	// ====================================================================


	

	// for (int row = 1; row < rows; ++row) {
	// 	Minisat::vec<Minisat::Lit> literals;
	// 	for (int column = 1; column < cols; ++column) {
	// 		// literals.push(Minisat::mkLit(toVar(row, column, value)));
	// 		literals.push(Minisat::mkLit(matrix[row][column]));
	// 	}
	// 	solver.addClause(literals);
	// 	// exactly_one_true(literals);// this passes the literals into individual clauses
	// }



	// cout<< "k = " << k <<endl;

	// for n*k matrix
	
	// Rule #1

	for (int column = 0; column < k; ++column) 
	{
		Minisat::vec<Minisat::Lit> literals;
		for (int row = 0; row < n; ++row) 
		{
			// std::cout<<"X"<<"["<<row<<","<<column<<"]"<<" U ";
			literals.push(Minisat::mkLit(matrix[row][column]));
		}
		// std::cout<<std::endl;
		solver.addClause(literals);
		literals.clear();
	}


    // std::cout<<std::endl;
    
    // Rule #2

    // for (int row = 0; row < n; ++row) 
    for (int row = 0; row < n; ++row)
    {
    	
        // for (int column = 0; column < k; ++column)
        for (int column = 0; column < k-1; ++column) 
        {
        	Minisat::vec<Minisat::Lit> literals;
        	literals.push(~Minisat::mkLit(matrix[row][column]));
        	literals.push(~Minisat::mkLit(matrix[row][column+1]));
            // cout<<"~X"<<"["<<row<<","<<column<<"]"<<" U "<<"~X"<<"["<<row<<","<<column+1<<"]"<<" U " <<endl;
            solver.addClause(literals);
            literals.clear();
        }
        //cout<<endl;
        
    }
    
    // cout<<endl;


    // Rule #3
    
    // for (int column = 0; column < k; ++column)
    // {
    // 	Minisat::vec<Minisat::Lit> literals;
    //     for (int row = 0; row < n; ++row)
    //     {
    //     	literals.push(Minisat::mkLit(matrix[row][column]));
    //         cout<<"~X"<<"["<<row<<","<<column<<"]"<<" U "<<"~X"<<"["<<row+1<<","<<column<<"]"<<" U ";
    //     }
    //     cout<<endl;
    //     solver.addClause(literals);
    // } 
    
    // cout<<endl;


    for (int column = 0; column < k; ++column)
    {
    	
        for (int row = 0; row < n; ++row)
        {	
        	for (int nextRow = row + 1; nextRow < n; ++nextRow)
        	{	
        	Minisat::vec<Minisat::Lit> literals;
        	literals.push(~Minisat::mkLit(matrix[row][column]));
        	literals.push(~Minisat::mkLit(matrix[nextRow][column]));
            // cout<<"~X"<<"["<<row<<","<<column<<"]"<<" U "<<"~X"<<"["<<nextRow<<","<<column<<"]"<<" U "<<endl;
            solver.addClause(literals);
            literals.clear();
        	}
        }
        //cout<<endl;
        
    } 
    
    // cout<<endl;

    // Rule #4
    
    for (int i = 0; i < edges.size(); i++) 
    { 
    	Minisat::vec<Minisat::Lit> literals;
        for (int j = 0; j < edges[i].size(); j++)
        {
            for (int column = 0; column < k; ++column)
            {
            	
            	literals.push(Minisat::mkLit(matrix[edges[i][j]][column]));
            	// cout<<"X"<<"["<<edges[i][j]<<","<<column<<"]"<<" U ";
            }
        }
        // cout<<endl;
        solver.addClause(literals);
    } 

    // cout<<endl;
    
    // Check for solution and retrieve model if found
    auto sat = solver.solve();
    if (sat) {
    	// std::clog << "True\n";
        for (int row = 0; row < n; ++row)
        {
        	for (int column = 0; column < k; ++column)
        	{
        		if(solver.modelValue(matrix[row][column]) == Minisat::l_True)
        		{
        			// cout << "n = " << row << " k = "<< column <<endl;
        			nVec.push_back(row);
        		}
        		// cout<<endl;
        	}
        }

	    int vectorCover[nVec.size()];
	    for(int i = 0; i < nVec.size(); i++)
	    {
	    	vectorCover[i] = nVec[i];
	    }
	    int n = sizeof(vectorCover)/sizeof(vectorCover[0]); 

	    for (int i = 0; i < n; ++i)
	    {
	      cout << vectorCover[i] << " "; 
	    }
      // cout << "About to..." << endl;
	    cout<<endl;

    } else {
        // std::clog << "False\n";//"UNSAT\n";
        // return 1;
        k+=1;
        // solver.reset(new Minisat::Solver());
        continue;
    }

    // solver.reset(new Minisat::Solver());
    //k+=1;
    // cout << "About to break" << endl;
    break;
}//endWhile which loops over Binary Search ks (above line depends on this)
    
    // NEXT below!
    // return vertexCover;
//cout << "Here" << endl;

// getline (std::cin,input);

} // end of while not eof

    //return 0;
}