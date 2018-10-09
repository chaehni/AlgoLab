#include <iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h> 
#include <CGAL/Min_circle_2.h> 
#include <CGAL/Min_circle_2_traits_2.h>
#include <vector>

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef K::Point_2 Point;
typedef CGAL::Min_circle_2_traits_2<K> Traits;
typedef CGAL::Min_circle_2<Traits> Min_circle;

using namespace std;

double ceil_to_double(const K::FT& x) {
    double a = std::floor(CGAL::to_double(x));
    while (a < x) a += 1;
    while (a-1 >= x) a -= 1;
    return a;
}

int main(){

    ios_base::sync_with_stdio(false);
    cout << fixed << setprecision(0);

     
    int n; cin >> n;

    while (n != 0){
        
        vector<Point> points(n);
        long x, y;
        for (int i = 0; i < n; i++){
            cin >> x >> y;
            points[i] = Point(x, y);    
        }

        Min_circle mc(points.begin(), points.end(), true);
        
        cout << ceil_to_double(sqrt(mc.circle().squared_radius())) << "\n";

        cin >> n;
        
    }
}
