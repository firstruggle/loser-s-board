db Cross(Point A, Point B) {
    return A.x * B.y - A.y * B.x;
}

Point a, b;//Ax + By + C = 0

db A = b.y - a.y, B = a.x - b.x, C = Cross(b, a);
db calc = fabs((A * X + B * Y + C * n) / sqrt(A * A + B * B));//点到直线距离公式
