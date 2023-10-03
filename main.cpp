#include <iostream>
# include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <iomanip>

using namespace std;

class AdjacencyList {
private:
    void insert(string from, string to);
    void pIteration(int power);
    void rank0Update();
    map<string, vector<string>> graph;
    map<string, float> ranks;
    map<string, float> oldRanks;
    map<string, int> outDegrees;
public:
    void PageRank();
    void iterHelper(int power);
    void insertHelper(string from, string to);
};

void AdjacencyList::PageRank(){
    //In this function, I just go through all the buckets of my rank map which store the rank.
    //I also set precision to 2 decimal points.
    for (auto it=ranks.begin();it!=ranks.end();it++) {
        cout<<it->first<<" ";
        cout<< fixed<< showpoint;
        cout<<setprecision(2);
        cout<<it->second<<endl;
    }
} // prints the PageRank of all pages after p powerIterations in ascending alphabetical order of webpages and rounding rank to two decimal places

void AdjacencyList::insertHelper(string from, string to){
    //this is the insert helper to access the private elements in the adjacency list class.
    insert(from,to);
}

void AdjacencyList::insert(string from, string to) {
    //In this function, to is used as a key in the graph map, and from is pushed backed into its value.
    graph[to].push_back(from);
    if (graph.find(from) == graph.end()){
        graph[from] = {};
    }
    //I also updated the ranks of from and to using map. At this point, I don't know how many vertexes would be in the graph, so I just updated the value with 0.
    ranks[from] = 0;
    if (ranks.find(to) == ranks.end()){
        ranks[to] = {};
    }
    //Everytime I insert the edge, I updated the outdegree of from. Also I check if to is existed in the map. If not, I assign 0 to it.
    outDegrees[from]++;
    if (outDegrees.find(to) == outDegrees.end()){
        outDegrees[to] = 0;
    }
}

void AdjacencyList::iterHelper(int power) {//This is a helper function for my power iteration.
    rank0Update();
    pIteration(power);
}

void AdjacencyList::pIteration(int power) {
    //In this function, I updated the rank by dividing the from key's rank with its outdegree.
    //Then I access all the element in the vector of my graph value, and did the calculation, add to the result. I repeat until the end of vector.
    string currentKey;
    vector<string> pairVector;
    float updatedRank=0;
    for (int i = 0; i < (power-1); ++i) {
        for (auto it=graph.begin(); it!= graph.end();it++) {
            currentKey = it->first;
            pairVector = it->second;
            for (int j = 0; j < pairVector.size(); ++j) {
                string from = pairVector.at(j);
                int fromOutDegree = outDegrees[from];
                auto itFrom = oldRanks.find(from);
                updatedRank+= (itFrom->second/fromOutDegree);
            }
            ranks[currentKey] = updatedRank;
            updatedRank=0;
        }
        oldRanks = ranks;
    }
}

void AdjacencyList::rank0Update() {
    //In this function, I got the total number of vertexes and updated the rank of every vertex in my graph.
    //This is technically the 0th iteration of my power iteration.
    int size = graph.size();
    float rank_0it = 1/(float)size;
    for (auto it=ranks.begin();it!=ranks.end();it++) {
        ranks[it->first] = rank_0it;
        oldRanks[it->first] = rank_0it;
    }
}

int main()
{
    int no_of_lines, power_iterations;
    string from, to;
    cin >> no_of_lines;
    cin >> power_iterations;
    AdjacencyList graph;
    for(int i = 0;i < no_of_lines; i++)
    {
        cin >> from;
        cin >> to;
        graph.insertHelper(from,to);
// Do Something
    }
    graph.iterHelper(power_iterations);
    graph.PageRank();
    return 0;
}

