#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Segment_2 Segment;
typedef K::Ray_2 Ray;
typedef K::Point_2 Point;

using namespace std;

Ray ray;
bool set = false;

double floor_to_double(const K::FT& x) {
    double a = std::floor(CGAL::to_double(x));
    while (a > x) a -= 1;
    while (a+1 <= x) a += 1;
    return a;
}

void check_first(const Point p, Point &first){
    if(set){
        if(CGAL::squared_distance(ray.source(), p) < CGAL::squared_distance(ray.source(), first))
           first = p;
    } else {
        first = p;
        set = true;
    }
}

int main(){

    ios_base::sync_with_stdio(false);

    long x, y, a, b;
    long r, s, t, u;
    Segment segment;

    int n; cin >> n;
    while (n != 0){
        
        Point first;

        cin >> x >> y >> a >> b;
        ray = Ray(Point(x,y), Point(a,b));

        for (int i = 0; i < n; i++){
            cin >> r >> s >> t >> u;

            segment = Segment(Point(r, s), Point(t, u));
                
            if(CGAL::do_intersect(ray, segment)){
                auto intersection = CGAL::intersection(ray, segment);
                if (const Point* ip = boost::get<Point>(&*intersection)){
                    check_first(*ip, first);
                } else if (const Segment* is = boost::get<Segment>(&*intersection)){
                    check_first(is->source(), first);
                    check_first(is->target(), first);
                } else
                    exit(1);
            }
        }
        if (set){
            cout << floor_to_double(first.x()) << " " << floor_to_double(first.y()) << "\n";
        } else {
            cout << "no\n";
        }
        set = false;
        cin >> n;
    }
}