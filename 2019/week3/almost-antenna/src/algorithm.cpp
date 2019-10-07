#include <iostream>
#include <vector>

#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef CGAL::Min_circle_2_traits_2<K> Traits;
typedef CGAL::Min_circle_2<Traits> Min_circle;
typedef K::Point_2 P;

using namespace std;

double ceil_to_double(const K::FT &x)
{
    double a = std::floor(CGAL::to_double(x));
    while (a < x)
        a += 1;
    while (a - 1 >= x)
        a -= 1;
    return a;
}

void run(int n)
{
    vector<P> points(n);
    for (int i = 0; i < n; i++)
    {
        long x, y;
        cin >> x >> y;
        points[i] = P(x, y);
    }

    Min_circle minc(points.begin(), points.end(), true);
    K::FT smallest = minc.circle().squared_radius();

    // iterate over boundary points and remove each and recalculate min circle
    for (auto sp = minc.support_points_begin(); sp != minc.support_points_end(); sp++)
    {
        vector<P> temp;
        for (int i = 0; i < n; i++)
        {
            if (points[i] != *sp)
                temp.push_back(points[i]);
        }
        Min_circle min_approx(temp.begin(), temp.end(), true);
        smallest = min(smallest, min_approx.circle().squared_radius());
    }

    cout << ceil_to_double(CGAL::sqrt(smallest)) << endl;
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    cout << fixed << setprecision(0);
    while (true)
    {
        int n;
        cin >> n;
        if (n == 0)
            break;
        run(n);
    }
}
