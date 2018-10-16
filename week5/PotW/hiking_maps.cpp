#include <iostream>
#include <set>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/enum.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Segment_2 Segment;
typedef K::Triangle_2 Tri;
typedef K::Point_2 Point;
typedef K::Line_2 Line;

using namespace std;

bool inside(vector<pair<Point, Point>> &t, pair<Point, Point> &s){
    
    //for each line in triangle, all other lines and the two points from leg have to be on the same side
    for (int i = 0; i < 3; i++){

        auto correct_side = CGAL::orientation(t[i].first, t[i].second, t[(i+1)%3].first);

        // both points of segment have to lie on correct_side or be collinear
        auto side = CGAL::orientation(t[i].first, t[i].second, s.first);
        if (side != correct_side){
            if(side != CGAL::COLLINEAR){
                return false;
            }
        }

        side = CGAL::orientation(t[i].first, t[i].second, s.second);
        if (side != correct_side){
            if(side != CGAL::COLLINEAR){
                return false;
            }
        }
    }
    return true;
}

Point* readPoint(){
    int x, y; cin >> x >> y;
    return new Point(x, y);
}

vector<pair<Point, Point>>* readTriangle(){

    int p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11;
    cin >> p0 >>  p1 >> p2 >> p3 >> p4 >> p5 >> p6 >> p7 >> p8 >> p9 >> p10 >> p11; 

    pair<Point, Point> pa = make_pair(Point(p0, p1), Point(p2, p3));
    pair<Point, Point> pb = make_pair(Point(p4, p5), Point(p6, p7));
    pair<Point, Point> pc = make_pair(Point(p8, p9), Point(p10, p11));

    return new vector<pair<Point, Point>>{pa, pb, pc};
}

void run(){

    int m; // m-1 legs
    int n; // n maps
    cin >> m >> n;

    vector<pair<Point, Point>> legs(m-1);
    vector<pair<Point, Point>> tri(3); //3 pairs of points for the 3 lines
    vector<set<int>> legs_in_map(n); //a set of all the legs in a given map

    // read the legs
    Point source = *readPoint();
    for(int i = 0; i < m-1; i++){
        Point target = *readPoint();
        legs[i] = make_pair(source, target);
        source = target;
    }

    // read the triangular maps
    for (int i = 0; i < n; i++){

        tri = *readTriangle();
   
        // iterate over all legs and check if they are contained in the triangle
        for (int j = 0; j < m-1; j++){
            if (inside(tri, legs[j])){
                legs_in_map[i].insert(j);
            }
        }
    }

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