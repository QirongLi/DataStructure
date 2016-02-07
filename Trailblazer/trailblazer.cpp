// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: write comment header for this file; remove this comment

#include "costs.h"
#include "trailblazer.h"
#include "queue.h"
// TODO: include any other headers you need; remove this comment
using namespace std;

bool dfsHelper(BasicGraph& graph, Vertex* start, Vertex* end, Vector<Vertex*>& path);

Vector<Vertex*> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    Vector<Vertex*> path;
    graph.resetData();
    dfsHelper(graph, start, end, path);
    return path;
}

bool dfsHelper(BasicGraph& graph, Vertex* start, Vertex* end, Vector<Vertex*>& path){

    start->visited = true;
    path.add(start);
    start->setColor(GREEN);

    if(start==end) return true;

    for(Edge* e : start->arcs){
        if(!e->finish->visited)
            if(dfsHelper(graph, e->finish, end, path)) return true;
    }

    path.remove(path.size()-1);
    start->visited = false;
    start->setColor(GRAY);
    return false;

}

Vector<Vertex*> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    graph.resetData();

    Vector<Vertex*> path;

    Queue<Vertex*> queue;
    queue.enqueue(start);
    while(!queue.isEmpty()){
        Vertex* curr = queue.dequeue();
        curr->setColor(GREEN);
        if(curr==end){
            while(curr!=start){
                path.add(curr);
                curr = curr->previous;
            }
            path.add(start);
            return path;
        }
        for (Edge* e : curr->edges) {
            if(!e->finish->visited){
                e->finish->previous = e->start;
                e->finish->visited=true;
                queue.enqueue(e->finish);
            }
        }
    }

    return path;
}

Vector<Vertex*> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    Vector<Vertex*> path;
    return path;
}

Vector<Vertex*> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    Vector<Vertex*> path;
    return path;
}

Set<Edge*> kruskal(BasicGraph& graph) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty set so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    Set<Edge*> mst;
    return mst;
}
