#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <float.h>
#include <string.h>

#define EPSILON 1e-9

typedef struct {
    double x;
    double y;
} Point2D;

typedef struct {
    Point2D p1;
    Point2D p2;
    double dist;
} ClosestPair;

int compare1D(const void *a, const void *b) {
    double diff = (*(double*)a - *(double*)b);
    if (fabs(diff) < EPSILON) return 0; 
    if (diff < 0) return -1;
    return 1;
}

void findClosest1D(const double *pts, int n) {
    double *pts_copy = (double *)malloc(n * sizeof(double));
    if (!pts_copy) {
        fprintf(stderr, "Memory allocation failed in findClosest1D\n");
        return;
    }
    memcpy(pts_copy, pts, n * sizeof(double));

    qsort(pts_copy, n, sizeof(double), compare1D);
    
    double min_dist = DBL_MAX;
    double p1 = 0, p2 = 0;
    
    for (int i = 0; i < n - 1; i++) {
        double dist = fabs(pts_copy[i+1] - pts_copy[i]);
        if (dist < min_dist) {
            min_dist = dist;
            p1 = pts_copy[i];
            p2 = pts_copy[i+1];
            
            if (min_dist < EPSILON) break; 
        }
    }
    
    printf("1D Closest Pair Results\n");
    printf("Point 1: (%.4f)\n", p1);
    printf("Point 2: (%.4f)\n", p2);
    printf("Minimum Distance: %.4f\n\n", min_dist);
    
    free(pts_copy);
}


double distSq2D(Point2D p1, Point2D p2) {
    return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
}

int compareX(const void *a, const void *b) {
    Point2D *p1 = (Point2D *)a;
    Point2D *p2 = (Point2D *)b;
    if (fabs(p1->x - p2->x) < EPSILON && fabs(p1->y - p2->y) < EPSILON) return 0;
    if (fabs(p1->x - p2->x) >= EPSILON) return (p1->x > p2->x) ? 1 : -1;
    return (p1->y > p2->y) ? 1 : -1;
}

int compareY(const void *a, const void *b) {
    Point2D *p1 = (Point2D *)a;
    Point2D *p2 = (Point2D *)b;
    if (fabs(p1->y - p2->y) < EPSILON && fabs(p1->x - p2->x) < EPSILON) return 0;
    if (fabs(p1->y - p2->y) >= EPSILON) return (p1->y > p2->y) ? 1 : -1;
    return (p1->x > p2->x) ? 1 : -1;
}

ClosestPair bruteForce(Point2D P[], int n) {
    ClosestPair min_pair = {{0, 0}, {0, 0}, DBL_MAX};
    
    if (n < 2) return min_pair; 
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double dSq = distSq2D(P[i], P[j]);
            if (dSq < min_pair.dist) {
                min_pair.dist = dSq;
                min_pair.p1 = P[i];
                min_pair.p2 = P[j];
                
                if (dSq < EPSILON) return min_pair; 
            }
        }
    }
    return min_pair;
}

ClosestPair closestUtil(Point2D Px[], Point2D Py[], int n, Point2D *strip) {
    if (n <= 3) return bruteForce(Px, n);

    int mid = n / 2;
    Point2D midPoint = Px[mid]; 
    Point2D *Pyl = (Point2D *)malloc(mid * sizeof(Point2D));
    Point2D *Pyr = (Point2D *)malloc((n - mid) * sizeof(Point2D));
    
    if (!Pyl || !Pyr) {
        fprintf(stderr, "Memory allocation failed in closestUtil\n");
        if (Pyl) free(Pyl);
        if (Pyr) free(Pyr);
        exit(1);
    }

    int allowed_left_eq = 0;
    for (int i = 0; i < mid; i++) {
        if (fabs(Px[i].x - midPoint.x) < EPSILON) allowed_left_eq++;
    }

    int li = 0, ri = 0;
    for (int i = 0; i < n; i++) {
        if (Py[i].x < midPoint.x - EPSILON) {
            Pyl[li++] = Py[i];
        } else if (Py[i].x > midPoint.x + EPSILON) {
            Pyr[ri++] = Py[i];
        } else {
            if (allowed_left_eq > 0) {
                Pyl[li++] = Py[i];
                allowed_left_eq--;
            } else {
                Pyr[ri++] = Py[i];
            }
        }
    }

    ClosestPair dl = closestUtil(Px, Pyl, mid, strip);
    ClosestPair dr = closestUtil(Px + mid, Pyr, n - mid, strip);

    ClosestPair d = (dl.dist < dr.dist) ? dl : dr;

    if (d.dist < EPSILON) {
        free(Pyl);
        free(Pyr);
        return d;
    }

    int j = 0;
    for (int i = 0; i < n; i++) {
        double xDist = Py[i].x - midPoint.x;
        if (xDist * xDist < d.dist) {
            strip[j++] = Py[i];
        }
    }

    for (int i = 0; i < j; i++) {
        for (int k = i + 1; k < j && (strip[k].y - strip[i].y)*(strip[k].y - strip[i].y) < d.dist; k++) {
            double d_stripSq = distSq2D(strip[i], strip[k]);
            if (d_stripSq < d.dist) {
                d.dist = d_stripSq;
                d.p1 = strip[i];
                d.p2 = strip[k];
            }
        }
    }

    free(Pyl);
    free(Pyr);

    return d;
}

void findClosest2D(Point2D *pts, int n) {
    Point2D *Px = (Point2D *)malloc(n * sizeof(Point2D));
    Point2D *Py = (Point2D *)malloc(n * sizeof(Point2D));
    Point2D *strip = (Point2D *)malloc(n * sizeof(Point2D)); 
    
    if (!Px || !Py || !strip) {
        fprintf(stderr, "Memory allocation failed in findClosest2D\n");
        if(Px) free(Px);
        if(Py) free(Py);
        if(strip) free(strip);
        return;
    }
    
    for (int i = 0; i < n; i++) {
        Px[i] = pts[i];
        Py[i] = pts[i];
    }

    qsort(Px, n, sizeof(Point2D), compareX);
    qsort(Py, n, sizeof(Point2D), compareY);

    ClosestPair result = closestUtil(Px, Py, n, strip);
    
    result.dist = sqrt(result.dist); 
    
    printf("--- 2D Closest Pair Results (Divide & Conquer) ---\n");
    printf("Point 1: (%.4f, %.4f)\n", result.p1.x, result.p1.y);
    printf("Point 2: (%.4f, %.4f)\n", result.p2.x, result.p2.y);
    printf("Minimum Distance: %.4f\n\n", result.dist);

    free(Px);
    free(Py);
    free(strip);
}

int main() {
    int n;
    
    printf("Enter the number of points (2 <= n <= 10000000): ");
    if (scanf("%d", &n) != 1 || n < 2 || n > 10000000) {
        printf("Error: Please enter a valid integer between 2 and 10,000,000.\n");
        return 1;
    }

    double *points1D = (double *)malloc(n * sizeof(double));
    Point2D *points2D = (Point2D *)malloc(n * sizeof(Point2D));

    if (points1D == NULL || points2D == NULL) {
        printf("Memory allocation failed in main!\n");
        if (points1D) free(points1D);
        if (points2D) free(points2D);
        return 1;
    }

    srand((unsigned int)time(NULL));

    for (int i = 0; i < n; i++) {
        points1D[i] = ((double)rand() / RAND_MAX) * 100.0;
        points2D[i].x = ((double)rand() / RAND_MAX) * 100.0;
        points2D[i].y = ((double)rand() / RAND_MAX) * 100.0;
    }

    if (n <= 10) {
        printf("\n[Generated 1D Points]:\n");
        for (int i = 0; i < n; i++) {
            printf("%.2f  ", points1D[i]);
        }
        printf("\n\n[Generated 2D Points]:\n");
        for (int i = 0; i < n; i++) {
            printf("(%.2f, %.2f)  ", points2D[i].x, points2D[i].y);
        }
        printf("\n\n");
    }

    findClosest1D(points1D, n);
    findClosest2D(points2D, n);

    free(points1D);
    free(points2D);

    return 0;
}