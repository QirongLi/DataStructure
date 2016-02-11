// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: write comment header for this file; remove this comment

#include "costs.h"
#include "trailblazer.h"
#include "queue.h"
#include "pqueue.h"
// TODO: include any other headers you need; remove this comment
using namespace std;

bool dfsHelper(BasicGraph& graph, Vertex* start, Vertex* end, Vector<Vertex*>& path);
void tracePath(Vertex* start, Vertex* end, Vector<Vertex*>& path);
void reverseVector(Vector<Vertex*>& path);
Vector<Vertex*> aStarHelper(BasicGraph& graph, Vertex* start, Vertex* end, bool useHeuristic);
void mergeVertexSet(Edge* e, Vector<Set<Vertex *> > &clusters, Set<Edge *> &mst);

Vector<Vertex*> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    Vector<Vertex*> path;
    graph.resetData();
    dfsHelper(graph, start, end, path);
    return path;
}

bool dfsHelper(BasicGraph& graph, Vertex* start, Vertex* end, Vector<Vertex*>& path){

    start->visited = true;
    path.add(start);
    start->setColor(GREEN);

    if(start==end){
        path.add(start);
        return true;
    }

    for(Edge* e : start->edges){
        if(!e->finish->visited)
            if(dfsHelper(graph, e->finish, end, path)) return true;

    }

    path.remove(path.size()-1);
    //start->visited = false;
    start->setColor(GRAY);
    return false;

}

void tracePath(Vertex* start, Vertex* end, Vector<Vertex*>& path){
    if(end == start){        
        path.add(start);
        return;
    }
    path.add(end);
    tracePath(start, end->previous, path);
}

void reverseVector(Vector<Vertex*>& path){
    int i = 0;
    int j = path.size()-1;

    while(i>=0&&j<path.size()&&i<=j){
        Vertex* temp = path[i];
        path[i] = path[j];
        path[j] = temp;
        i++;
        j--;
    }
}

Vector<Vertex*> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();

    Vector<Vertex*> path;

    Queue<Vertex*> queue;
    //Add first vertex to queue
    start->setColor(YELLOW);
    start->visited = true;
    queue.enqueue(start);

    //bfs
    while(!queue.isEmpty()){
        Vertex* curr = queue.dequeue();
        curr->setColor(GREEN);

        if(curr==end){
            curr->setColor(GREEN);
            tracePath(start, curr, path);
            reverseVector(path);
            return path;
        }

        for (Edge* e : curr->edges) {
            if(!e->finish->visited) {
                e->finish->previous = curr;
                e->finish->visited = true;
                queue.enqueue(e->finish);
                e->finish->setColor(YELLOW);
            }
        }
    }

    return path;
}

Vector<Vertex*> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    return aStarHelper(graph, start, end, false);
}

Vector<Vertex*> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    return aStarHelper(graph, start, end, true);
}


Vector<Vertex*> aStarHelper(BasicGraph& graph, Vertex* start, Vertex* end, bool useHeuristic){
    graph.resetData();

    Vector<Vertex*> path;
    PriorityQueue<Vertex*> pqueue;
    for(Vertex* v:graph.getVertexSet()){
        v->cost = POSITIVE_INFINITY;
    }

    start->cost = 0.0;
    double priority = useHeuristic ? heuristicFunction(start, end) : 0.0;
    pqueue.enqueue(start, priority);

    while(!pqueue.isEmpty()){
        Vertex* curr = pqueue.dequeue();
        curr->setColor(GREEN);
        curr->visited = true;

        if(curr==end){
            curr->setColor(GREEN);
            tracePath(start, curr, path);
            reverseVector(path);
            return path;
        }

        for(Edge* e : curr->edges){
            Vertex* next = e->finish;
            double cost = curr->cost + e->cost;
            if(cost < next->cost){
                double priority = useHeuristic ? cost + heuristicFunction(next, end) : cost;
                next->cost = cost;
                next->previous = curr;
                if(next->getColor() == YELLOW){
                    pqueue.changePriority(next, priority);
                }else{
                    pqueue.enqueue(next, priority);
                }
                next->setColor(YELLOW);
            }
        }
    }
    return path;
}

void mergeVertexSet(Edge* e, Vector<Set<Vertex*> >& clusters, Set<Edge*>& mst){
    int start, end;
    for(int i=0; i<clusters.size(); i++){
        if(clusters[i].contains(e->start)) start=i;
        if(clusters[i].contains(e->finish)) end = i;
    }

    if(start==end) return;

    clusters[start] += clusters[end];
    clusters.remove(end);
    mst.add(e);
}

Set<Edge*> kruskal(BasicGraph& graph) {
    Set<Edge*> mst;
    Vector<Set<Vertex*> > clusters;

    for(Vertex* v: graph.getVertexSet()){
        Set<Vertex*> s;
        s.add(v);
        clusters.add(s);
    }

    PriorityQueue<Edge*> pqueue;
    for(Edge* e : graph.getEdgeSet()){
        pqueue.enqueue(e, e->cost);
    }

    while(!pqueue.isEmpty()&&clusters.size()>=2){
        Edge* e = pqueue.dequeue();
        mergeVertexSet(e, clusters, mst);
    }

    return mst;
}
