#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <sstream>
// #include "a2-ece650.h"

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
  Graph graph;
  Parser parser;

  int verticesTotal = 0;
  stack<int>edgePoints;
  vector<int>trip;

  int numEdgePoints = 0;

  int start = 0;
  int end = 0;
   
  // // For future use
  // // ===========================================
  // // save stdin
  // int savestdin = dup(0);

  // // save stdout
  // int savestdout = dup(1);
  // // ===========================================
  // // just call dup2() correctly to restore above

  std::string input; // = "V 15";
  // cout << "Vertices command:\n";
  getline (std::cin,input);

  if (input.empty())
  {
    return 0;
  }

  // std::string v; // = "V 15";
  // cout << "Vertices command:\n";
  // getline (std::cin,v);

  verticesTotal = parser.vParse(input);

  do{
    // Damage control
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    // verticesTotal
    if (input[0] == ' ')
    {
      break;
    }

    if (cin.eof())
    {
      break;
    }

    if (input[0] == 'E' || input[0] == 's')
    {
      // Refresh crew
      // =========================
      parser.setNumVertices(0);
      parser.setHighestVertex(0);
      parser.setNumCoors(0);
      // =========================

      // Read in new input
      getline (std::cin,input);

      if (input.empty())
      {
        return 0;
      }

      verticesTotal = parser.vParse(input);
      // placeholder
      // return 0;
      continue;
    }

    if (verticesTotal < 0) // was less than 2
    {
      cout<< "Error: Invalid vertice input given for graph.\n" << std::flush;

      // Refresh crew
      // =========================
      parser.setNumVertices(0);
      parser.setHighestVertex(0);
      parser.setNumCoors(0);
      // =========================

      // Read in new input
      getline (std::cin,input);

      if (input.empty())
      {
        return 0;
      }

      verticesTotal = parser.vParse(input);
      // placeholder
      // return 0;
      continue;
    }
    else{  // # UPDATE HERE
      cout<<input<<"\n"<< std::flush;
    }

    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    // std::string e; // = "E {<0,2>,<2,1>,<2,14>,<3,4>,<4,1>}";
    // cout << "Edges command:\n";
    getline (std::cin,input);

    if (input.empty())
    {
      return 0;
    }


    edgePoints = parser.eParse(input);

    // Damage control
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // edgePoints

    if (cin.eof())
    {
      break;
    }

    // if (input[0] == 'V')
    // {
    //   // Refresh 
    //   // =========================
    //   parser.setNumVertices(0);
    //   parser.setHighestVertex(0);
    //   parser.setNumCoors(0);
    //   // =========================

    //   getline (std::cin,input);

    //   if (input.empty())
    //   {
    //     return 0;
    //   }

    //   verticesTotal = parser.vParse(input);

    //   // useful code
    //   // cout << verticesTotal << "\n";
    //   // if (verticesTotal == 0)
    //   // {
    //   //   break;
    //   // }

    //   // placeholder
    //   // return 0;
    //   continue;
    // }

    // if (edgePoints.empty())
    // {
    //   std::cout << "Error: Edge coordinates entered are invalid or format is invalid\n"<< std::flush;

    //   // Refresh 
    //   // =========================
    //   parser.setNumVertices(0);
    //   parser.setHighestVertex(0);
    //   parser.setNumCoors(0);
    //   // =========================

    //   // Read in new input
    //   getline (std::cin,input);
    //   // edgePoints = parser.vParse(input);


    //   // ERROR @ E GOES BACK TO V
    //   verticesTotal = parser.vParse(input);
    //   // placeholder
    //   // return 0;
    //   continue;
    // }  // # UPDATE HERE 
    // else{
       cout<<input<<"\n"<< std::flush;
    // }

    if (parser.getNumCoors()%2 == 0)
    {
      // std::cout << "even" << std::endl;
      // std::cout << "good coordinates" << std::endl;
    }
    else
    {
      // std::cout << "odd" << std::endl;
      std::cout << "Error: Incorrect format/number of coordinates entered\n" << std::flush;

      // Refresh 
      // =========================
      parser.setNumVertices(0);
      parser.setHighestVertex(0);
      parser.setNumCoors(0);
      // =========================

      getline (std::cin,input);

      if (input.empty())
      {
        return 0;
      }

      verticesTotal = parser.vParse(input);

      // useful code
      // cout << verticesTotal << "\n";
      // if (verticesTotal == 0)
      // {
      //   break;
      // }

      // placeholder
      // return 0;
      continue;
    }
    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


    
    // Remember to loop here (as many Shortest path commands as user desires)


    
    getline (std::cin,input);

    if (input.empty())
    {
      return 0;
    }
    // else if (input == "s 0 0")
    // {
    //   continue;
    // }

    trip = parser.sParse(input);

    if (cin.eof())
    {
      break;
    }
    // if input = 's'...while...
    do
    {

      if (input[0] == 'V')
      {
        break;
      }
      else if (input[0] == 'E')
      {
        break;
      }

      // getline (std::cin,input);
      // trip = parser.sParse(input);

      // Damage control
      // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
      // trip
      if (trip.empty())
      {
        cout<< "Error: Points provided are out of range or invalid\n"<< std::flush;
        getline (std::cin,input);

        if (input.empty())
        {
          return 0;
        }

        trip = parser.sParse(input);
        // placeholder
        // return 0;
        continue;
      }
      // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

      // i


      numEdgePoints = edgePoints.size(); // or parser.getNumCoors()
      vector < vector <int> > edges(numEdgePoints);

      

      // ==========================================================

      

      stack <int> tempEdgePoints = edgePoints;
      for (int i = 0; i<parser.getNumCoors()/2; i++) // count/2 == number of edges
      {
        // int k = i;
        for (int j = 0; j<2; j++) // 0 and 1 passes for both coors
        {
          // find the next int
          if (!tempEdgePoints.empty()){
            edges[i].push_back(tempEdgePoints.top());
            // cout << tempEdgePoints.top()<< " is tempEdgePoints.top() for "<<i;
            // cout<<"\n";
          }
          if (!tempEdgePoints.empty()){
            tempEdgePoints.pop();
          }

        }
      }

      // ==========================================================


      vector<list< int > > aJList = graph.adjList(verticesTotal, edges);


      if(trip.size()>0){
        // cout << "N2.1\n";
        start = trip[0];
        // cout << "N2.15\n";
      }
      else{
        // cout << "N2.2\n";
      }

      if(trip.size()>1){
        // cout << "N2.3\n";
        end = trip[1];
        // cout << "N2.35\n";
      }
      else{
        // cout << "N2.4\n";
      }

      // cout << "N3\n";

      if ((start < 0) || (start > aJList.size()-1))
      {
        // does not exist, react appropriately
        cout << "Error: "<< start << " does not exist in graph!\n\n"<< std::flush;
        // continue perhaps;
      }
      else
        {
          // exists, react (E.g. print and stay or exit) appropriately
          // appropriately does nothing given all is well
        }

      if ((end < 0) || (end > aJList.size()-1))
      {
        // does not exist, react appropriately
        cout << "Error: "<< end << " does not exist in graph!\n\n"<< std::flush;
        // break;
      }
      else
        {
          // exists, react (E.g. print and stay or exit) appropriately
          // appropriately does nothing given all is well
        }

      // ==========================================================


      stack <int> result = graph.dijkstraAdjList(aJList, start, end);

      vector <int> shrtpath(result.size());

      if (result.size() <= 0){  // OR if (shrtpath.size() == 0)
        // there is no path between start and end
        // behave appropriately and restart loop for s _ _ (break)
        cout << "Error: No path exists between " << start << " and " << end <<"!\n"<< std::flush;
        // loop below instead
        getline (std::cin,input);
        if (input.empty())
        {
          return 0;
        }
        trip = parser.sParse(input);
        // placeholder
        // return 0;
        continue;
      }

      // if (result.size() > 0){
      else{
        // vector <int> shrtpath(result.size());
      
      // cout << "Shortest path is: ";
        while (!result.empty())
        {
          // shrtpath.push_back(result.top());
          if (result.size() == 1)
          {
            cout << result.top()<< std::flush;
            result.pop();
          }
          else{
            cout << result.top() << "-"<< std::flush;
            result.pop();
          }
        }
        cout<<"\n"<< std::flush;
      }

      // CLEAR MEMORY HERE
      // =========================================
      trip.clear();
      shrtpath.clear();
      aJList.clear();
      // =========================================

      getline (std::cin,input);
      if (input.empty())
      {
        return 0;
      }
      trip = parser.sParse(input);


      if ((input[0]== 'V') && (input[1] = ' '))
      {
        break;
      }

      


    } while ((input[0]== 's') && (input[1] = ' ')); 
    // Error below since V is already read in input
    // getline (std::cin,input);

    // Refresh
    parser.setNumVertices(0);
    parser.setHighestVertex(0);
    parser.setNumCoors(0);

    verticesTotal = parser.vParse(input);
    // cout << verticesTotal <<"\n";
    // if (verticesTotal == 0)
    // {
    //   continue;
    // }
    if ((input[0]== 'V') && (input[1] = ' '))
    {
      // do nothing appropriately
    }
    else if (input[0]== ' ')
    {
      // end program gracefully
      break;
    }
  } // while ((input[0]== 'V') && (input[1] = ' '));
  // while(input[0] != ' ');
  // while (std::getline(cin, input));
  while(!(cin.eof()));


  return 0;
}