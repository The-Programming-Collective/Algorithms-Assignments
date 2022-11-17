#include <iostream>
#include <float.h>
#include <stdlib.h>
#include <math.h>
using namespace std;

// Node struct to act as a pair of two co-ordinates x and y
struct Point{
	int x, y;
};

// sort array according to x coordinates
int sortX(const void* a, const void* b){
	Point *p1 = (Point *)a, *p2 = (Point *)b;
	return (p1->x != p2->x) ? (p1->x - p2->x) : (p1->y - p2->y);
}
// sort array according to y coordinates
int sortY(const void* a, const void* b){
	Point *p1 = (Point *)a, *p2 = (Point *)b;
	return (p1->y != p2->y) ? (p1->y - p2->y) : (p1->x - p2->x);
}

float euclideanDistance(Point p1, Point p2){
	return sqrt( (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

// smallest distance between 3 points
float getMinDistance(Point P[], int n){
	float min = FLT_MAX;
	for (int i = 0; i < n; ++i)
		for (int j = i+1; j < n; ++j)
			if (euclideanDistance(P[i], P[j]) < min)
				min = euclideanDistance(P[i], P[j]);
	return min;
}

// getMin between 2 values
float min(float x, float y){
	return (x < y)? x : y;
}

float cStrip(Point strip[], int size, float d){
	float min = d; // Initialize the minimum distance as d

	// using the brute force method till the difference
	// between y coordinates is smaller than d.
	for (int i = 0; i < size; ++i)
		for (int j = i+1; j < size && (strip[j].y - strip[i].y) < min; ++j)
			if (euclideanDistance(strip[i],strip[j]) < min)
				min = euclideanDistance(strip[i], strip[j]);

	return min;
}

float closestUtil(Point Px[], Point Py[], int n){
    // base case
	if (n <= 3)
		return getMinDistance(Px, n);

	// Find the middle point
	int mid = n/2;
	Point midPoint = Px[mid];

	Point Pyl[mid]; 
	Point Pyr[n-mid]; 
	int li = 0, ri = 0; 
	for (int i = 0; i < n; i++){
	if ((Py[i].x < midPoint.x || (Py[i].x == midPoint.x && Py[i].y < midPoint.y)) && li<mid)
		Pyl[li++] = Py[i];
	else
		Pyr[ri++] = Py[i];
	}
	
	float dl = closestUtil(Px, Pyl, mid);
	float dr = closestUtil(Px + mid, Pyr, n-mid);

	// Find the smaller of two distances
	float d = min(dl, dr);

	Point strip[n];
	int j = 0;
	for (int i = 0; i < n; i++)
		if (abs(Py[i].x - midPoint.x) < d)
			strip[j] = Py[i], j++;

	return cStrip(strip, j, d);
}

float closest(Point P[], int n){
	Point Px[n];
	Point Py[n];
	for (int i = 0; i < n; i++){
		Px[i] = P[i];
		Py[i] = P[i];
	}

	qsort(Px, n, sizeof(Point), sortX);
	qsort(Py, n, sizeof(Point), sortY);

	return closestUtil(Px, Py, n);
}

int main(){
    int NOP,x,y;
	cout<<"Number of points : ";
	cin>>NOP;
    Point P[NOP];
	for(int i=0 ; i<NOP ; i++){
		cout<<"Enter x,y of point "<<i<<" : ";
		cin>>x>>y;
		P[i].x=x;
		P[i].y=y;
	}
	cout << "The smallest distance is " << closest(P, NOP);
	return 0;
}