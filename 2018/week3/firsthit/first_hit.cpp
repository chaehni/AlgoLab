#include <iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Segment_2 Segment;
typedef K::Ray_2 Ray;
typedef K::Point_2 Point;

double floor_to_double(const K::FT &x)
{
    double a = std::floor(CGAL::to_double(x));
    while (a > x)
        a -= 1;
    while (a + 1 <= x)
        a += 1;
    return a;
}

using namespace std;

void run(int n)
{

    long x, y, a, b;
    long r, s, t, u;

    cin >> x >> y >> a >> b;
    Ray ray = Ray(Point(x, y), Point(a, b));
    Segment clipped_ray;
    bool hit = false;
    vector<Segment> segments(n);

    for (int i = 0; i < n; i++)
    {
        cin >> r >> s >> t >> u;
        segments[i] = Segment(Point(r, s), Point(t, u));
    }

    // shuffle vector to not fail on a mean input
    random_shuffle(segments.begin(), segments.end());

    for (auto seg : segments)
    {
        if (!hit && CGAL::do_intersect(ray, seg)) // we are operating with original ray
        {
            hit = true;
            auto intersection = CGAL::intersection(ray, seg);
            if (const Point *ip = boost::get<Point>(&*intersection))
            {
                clipped_ray = Segment(ray.source(), *ip);
            }
            else if (const Segment *is = boost::get<Segment>(&*intersection))
            {
                if (is->direction() == ray.direction())
                    clipped_ray = Segment(ray.source(), is->source());
                else
                    clipped_ray = Segment(ray.source(), is->target());
            }
        }
        if (hit && CGAL::do_intersect(clipped_ray, seg)) // after first intersection ray was clipped to a segment to reduce number of intersections
        {
            auto intersection = CGAL::intersection(clipped_ray, seg);
            if (const Point *ip = boost::get<Point>(&*intersection))
            {
                clipped_ray = Segment(clipped_ray.source(), *ip);
            }
            else if (const Segment *is = boost::get<Segment>(&*intersection))
            {
                if (is->direction() == clipped_ray.direction())
                    clipped_ray = Segment(clipped_ray.source(), is->source());
                else
                    clipped_ray = Segment(clipped_ray.source(), is->target());
            }
        }
    }
    if (hit)
        cout << floor_to_double(clipped_ray.target().x()) << " " << floor_to_double(clipped_ray.target().y()) << "\n";
    else
        cout << "no\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cout << fixed << setprecision(0);
    int n;
    while (true)
    {
        cin >> n;
        if (n == 0)
            break;
        run(n);
    }
}