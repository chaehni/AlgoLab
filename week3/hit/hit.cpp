#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Segment_2 Segment;
typedef K::Ray_2 Ray;
typedef K::Point_2 Point;

using namespace std;

int main(){

    ios_base::sync_with_stdio(false);

    long x, y, a, b;
    long r, s, t, u;
    bool intersect;
    Ray ray;
    Segment segment;

    int n; cin >> n;
    while (n != 0){
        
        cin >> x >> y >> a >> b;
        ray = Ray(Point(x,y), Point(a,b));

        intersect = false;
        for (int i = 0; i < n; i++){
            cin >> r >> s >> t >> u;

            segment = Segment(Point(r, s), Point(t, u));
                
            //test for intersection
            if(!intersect && CGAL::do_intersect(ray, segment)){
                intersect = true;
            }
        }
        
        if (intersect){
            cout << "yes\n";
        } else {
            cout << "no\n";
        }
        cin >> n;
    }
}