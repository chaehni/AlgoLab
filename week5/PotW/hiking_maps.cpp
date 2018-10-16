#include <iostream>
#include <set>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Segment_2 Segment;
typedef K::Triangle_2 Tri;
typedef K::Point_2 Point;
typedef K::Line_2 Line;

using namespace std;

bool inside(Tri* triangle, Segment* segment){
    if(CGAL::do_intersect(*triangle, *segment)){
        auto in = CGAL::intersection(*triangle, *segment);
        if (const Segment* s2 = boost::get<Segment>(&*in)){
            return *s2 == *segment;
        }
    }
    return false;
}

Point* readPoint(){
    int x, y; cin >> x >> y;
    return new Point(x, y);
}

Tri* readTriangle(){

    int p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11;
    cin >> p0 >>  p1 >> p2 >> p3 >> p4 >> p5 >> p6 >> p7 >> p8 >> p9 >> p10 >> p11; 

    Line ln1 = Line(Point(p0, p2), Point(p2, p3));
    Line ln2 = Line(Point(p4, p5), Point(p6, p7));
    Line ln3 = Line(Point(p8, p9), Point(p10, p11));

    auto ia = CGAL::intersection(ln1, ln2);
    auto ib = CGAL::intersection(ln2, ln3);
    auto ic = CGAL::intersection(ln1, ln3);

    Point* a = boost::get<Point>(&*ia);
    Point* b = boost::get<Point>(&*ib);
    Point* c = boost::get<Point>(&*ic);

    return new Tri(*a, *b, *c);
}

void run(){

    int m; // m-1 legs
    int n; // n maps
    cin >> m >> n;

    vector<Segment> legs(m-1);
    Tri* tri;
    vector<set<int>> legs_in_map(n); //a set of all the legs in a given map
    

    // read the legs
    Point source = *readPoint();
    for(int i = 0; i < m-1; i++){
        Point target = *readPoint();
        legs[i] = Segment(source, target);
        source = target;
    }

    // read the triangular maps
    for (int i = 0; i < n; i++){

        tri = readTriangle();

        // iterate over all legs and check if they are contained in the triangle
        for (int j = 0; j < m-1; j++){
            if (inside(tri, &legs[j])){
                legs_in_map[i].insert(j);
            }
        }
    }
    cout << (*tri).vertex(0) << " " << (*tri).vertex(1) << " " << (*tri).vertex(2) << endl;

    int min_cost = n;
    int e = 0;
    int b = 0;
    set<int> all_legs; //collects all the legs found so far in current sequence
    vector<int> leg_ocurrences(m-1, 0); // counts the number of times a leg occurs in a map

    while(e < n){

        // move forward with e until all segments are covered
        do {
            // add legs of current map to all_legs and increase inclusion counter for added legs
            for (auto l: legs_in_map[e]){
                all_legs.insert(l);
                leg_ocurrences[l]++;
            }
            e++;
        } while (all_legs.size() != m-1);

        // if we have all legs in map b included in subsequent maps, increase b (do not include b in sequence)
        bool redundant = true;
        while (redundant){
            for (auto l: legs_in_map[b]){
                if (leg_ocurrences[l] <= 1)
                    redundant = false; // at least one leg occurs only in this map, we need it
            }
            if (redundant){ // all legs occur multiple times
                for(auto l: legs_in_map[b]){
                    leg_ocurrences[l]--; //we delete map b, decrease occurence of legs in this map
                }
                b++;
            }
        }

        // we have now a minimal sequence of maps, update cost
        if (e-b < min_cost){
            min_cost = e-b;
        }

        //e is already advanced to next position, start over loop
    }

    cout << min_cost << "\n";
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int tests; cin >> tests;
    while (tests--){
        run();
    }
}