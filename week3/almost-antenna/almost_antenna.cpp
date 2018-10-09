#include <iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h> 
#include <CGAL/Min_circle_2.h> 
#include <CGAL/Min_circle_2_traits_2.h>
#include <CGAL/squared_distance_2.h>
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

    K::FT min_radius;
    bool set = false;
    int n; cin >> n;

    while (n != 0){
        
        vector<Point> points(n);
        long x, y;
        for (int i = 0; i < n; i++){
            cin >> x >> y;
            points[i] = Point(x, y);    
        }

        // we need support points of original data
        Min_circle mc1(points.begin(), points.end(), true);

        //shuffle data since we are inserting them one at a time
        random_shuffle(points.begin(), points.end());

        //for every support point insert all other points and calculate squared radius
        for (int i = 0; i < mc1.number_of_support_points(); i++){
            auto j = find(points.begin(), points.end(), mc1.support_point(i));
            Min_circle mc2;
            mc2.insert(points.begin(), j);
            mc2.insert(j+1, points.end());
            if (mc2.circle().squared_radius() < min_radius || !set){
                min_radius = mc2.circle().squared_radius();
                set = true;
            }
        }
        
        cout << ceil_to_double(sqrt(min_radius)) << "\n";
        set = false;

        cin >> n;
        
    }
}
