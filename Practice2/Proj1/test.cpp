#include <iostream>
#include <cassert>
#include <boost/chrono.hpp>
#include <gmpxx.h>
#include <ctime>


using namespace std;

double eps = 1e-5;
template<class Scalar>
struct point_2t
{
    Scalar x, y;
    point_2t(Scalar _x, Scalar _y)
    {
        x = _x;
        y = _y;
    }

};


template<class Scalar>
int orientation(point_2t<Scalar> a, point_2t<Scalar> b, point_2t<Scalar> c)
{
    point_2t<Scalar> p1(b.x - a.x, b.y - a.y);
    point_2t<Scalar> p2(c.x - a.x, c.y - a.y);
    Scalar ans = p1.x * p2.y - p2.x * p1.y;
    if (ans > 0)
    {
        return 1;
    }
    if (ans < 0)
    {
        return -1;
    }
    return 0;
}



void test1()
{
    double x1, x2, x3, y1, y2, y3;
    srand(time(0));
    int id = 0;
    for (int i = 0; i < 10; i++)
    {

        x1 = (double)rand();
        x2 = (double)rand();
        y1 = (double)rand();
        y2 = (double)rand();

        for (int j = 0; j < 5000; j++)
        {
            double t = (double)rand();
            x3 = t*x1 + x2*(1-t);
            y3 = t*y1 + y2*(1-t);
            id++;
            point_2t<double> a(x1, y1);
            point_2t<double> b(x2, y2);
            point_2t<double> c(x3, y3);

            point_2t<mpq_class> a2(x1, y1);
            point_2t<mpq_class> b2(x2, y2);
            point_2t<mpq_class> c2(x3, y3);


            int ans = orientation(a, b, c);
            int ans2 = orientation(a2, b2, c2);
            if (ans != ans2)
            {
                cout << "YEAH!! " << ans << " " << ans2  << " " << id << endl;
                return;
            }

        }





    }


}



void test()
{
    test1();
}

int main()
{
    boost::chrono::system_clock::time_point start = boost::chrono::system_clock::now();



    test();



    boost::chrono::duration<double> sec = boost::chrono::system_clock::now() - start;
    cout << "Time: " << sec.count() << endl;
    return 0;
}

