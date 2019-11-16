#include <iostream>
#include <vector>
#include <algorithm>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt SK;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef K::Point_2 Point;

using namespace std;

SK::FT to_hours(SK::FT s)
{
    return ceil(CGAL::to_double(CGAL::sqrt((CGAL::sqrt(s) - 1) / 2)));
}

void run(int n)
{
    int l, b, r, t;
    cin >> l >> b >> r >> t;

    vector<Point> bac(n);
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        bac[i] = Point(x, y);
    }

    Triangulation tri;
    tri.insert(bac.begin(), bac.end());

    vector<K::FT> dies;
    dies.reserve(n);

    // iterate over all points and find the min_dist to either another bacteria or the wall
    for (auto vit = tri.finite_vertices_begin(); vit != tri.finite_vertices_end(); vit++)
    {
        // min dist to sides of dish
        K::FT min_horizontal = min(vit->point().x() - l, r - vit->point().x());
        K::FT min_vertical = min(vit->point().y() - b, t - vit->point().y());
        K::FT min_dist = min(min_horizontal, min_vertical);

        // square twice the dist
        min_dist = 4 * min_dist * min_dist;

        // iterate over all edges to find closest neighbour
        auto eit = tri.incident_edges(vit);
        if (!eit.is_empty())
        {
            do
            {
                if (!tri.is_infinite(eit))
                    min_dist = min(min_dist, tri.segment(*eit).squared_length());
            } while (++eit != tri.incident_edges(vit));
        }

        // calculate time of death for this cell
        dies.push_back(min_dist);
    }

    sort(dies.begin(), dies.end());

    cout << to_hours(SK::FT(dies[0])) << " " << to_hours(SK::FT(dies[n / 2])) << " " << to_hours(SK::FT(dies[n - 1])) << "\n";
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    while (true)
    {
        int n;
        cin >> n;
        if (n == 0)
            break;
        run(n);
    }
}