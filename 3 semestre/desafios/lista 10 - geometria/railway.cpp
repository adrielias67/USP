#include <bits/stdc++.h>
using namespace std;

using coord = double;

const double EPS = 1e-9;

int sign(coord x) { return (x > EPS) - (x < -EPS); }


struct point {
	coord x, y;

	point() : x(0), y(0) {}
	point(coord x, coord y) : x(x), y(y) {}

	double norm() { return sqrt(norm2()); }
	coord norm2() { return (*this) * (*this); }

	point operator+(const point& rhs) const { return point(x+rhs.x, y+rhs.y); }
	point operator-(const point& rhs) const { return point(x-rhs.x, y-rhs.y); }
	point operator*(const coord t) const { return point(x*t, y*t); }
	point operator/(const coord t) const { return point(x/t, y/t); }

	// produto escalar (dot product)
	coord operator*(const point& rhs) const { return x*rhs.x + y*rhs.y; }

	// produto vetorial (cross product)
	coord operator^(const point& rhs) const { return x*rhs.y - y*rhs.x; }

	// rotaciona 90 graus em sentido horario
	point perp(){ return point(-y, x); }
	point rot(point rhs) { return point((*this)^rhs, (*this)*rhs); }
	point rot(double ang) { return rot(point(sin(ang), cos(ang))); }
};

ostream& operator<<(ostream& os, point p) {
	return os<<"("<<p.x<<","<<p.y<<")";
}



struct line {
	point v; // v = q-p
	coord c;

	line(point v, coord c) : v(v), c(c) {}
	line(coord a, coord b, coord c) : v({b,-a}), c(c) {}
	line(point p, point q) : v(q-p), c(v^p) {}

	// > 0: acima, < 0: abaixo, =0: colinear
	coord side(point p) { return (v^p)-c; }
	coord dist(point p) { return abs(side(p))/v.norm(); }
	coord dist2(point p) { return side(p)*side(p)/v.norm2(); }

	line perp(point p) { return line(p, p+v.perp()); }
	point proj(point p) { return p - v.perp()*side(p)/v.norm2(); }
};

// true se existe interseccao, e q eh a ponto de interseccao
bool inter(line l1, line l2, point &q){
	coord d = l1.v^l2.v;
	if(d == 0) return false;
	q = (l2.v*l1.c - l1.v*l2.c)/d;
	return true;
}


struct segment {
	point p,q;

	segment(point p, point q) : p(p), q(q) {};

	// > 0: acima, < 0: abaixo, =0: colinear
	coord side(point r) { return (r-p)^(q-p); }
	bool inDisk(point r){ return (p-r)*(q-r) < EPS; }
	bool contains(point r) { return abs(side(p)) < EPS and inDisk(r); }

	coord len() { return (q-p).norm(); }
	coord len2() { return (q-p).norm2(); }

	line getline() { return line(p,q); }
};

// point.rot(ccw90) eh equivalente a rotacionar 
// o ponto 90 graus em sentido anti-horario
point ccw90(1,0);





int bruh(){
    coord xm, ym;
    coord menor, menorx, menory;
    if(scanf("%lf", &xm)!=1) return 0;
    cin >> ym;
    point pm(xm, ym);

    int n;
    cin >> n;


    coord x[n+1], y[n+1];

    cin >> x[0] >> y[0];
    cin >> x[1] >> y[1];
    point p1fuck(x[0], y[0]), p2fuck(x[1], y[1]);
    segment seguimentofuck(p1fuck, p2fuck);
    line linhafuck(p1fuck, p2fuck);
    
    point projecaofuck = linhafuck.proj(pm);
    if(seguimentofuck.contains(projecaofuck)){
        segment aux(pm, projecaofuck);
        menor = aux.len();
        menorx = projecaofuck.x;
        menory = projecaofuck.y;
    }
    else{
        segment aux(pm, p1fuck);
        menor = aux.len();
        menorx = p1fuck.x;
        menory = p1fuck.y;
        segment aux2(pm, p2fuck);
        if(aux2.len()<menor){
            menor = aux2.len();
            menorx = p2fuck.x;
            menory = p2fuck.y;
        }
    }


    for(int i=2; i<=n; i++){
        cin >> x[i] >> y[i];
        point p1(x[i-1], y[i-1]), p2(x[i], y[i]);
        segment seguimento(p1, p2);
        line linha(p1, p2);

        point projecao = linha.proj(pm);
        if(seguimento.contains(projecao)){
            segment aux(pm, projecao);
            if(aux.len()<menor){
                menor = aux.len();
                menorx = projecao.x;
                menory = projecao.y;
            }
        }
        else{
            segment aux(pm, p1);
            if(aux.len()<menor){
                menor = aux.len();
                menorx = p1.x;
                menory = p1.y;
            }
            segment aux2(pm, p2);
            if(aux2.len()<menor){
                menor = aux2.len();
                menorx = p2.x;
                menory = p2.y;
            }
        }

    }

    cout << setprecision(4) << fixed << menorx << endl << menory << endl;
    return 1;
}



int main(){
    while(bruh() != 0);
}