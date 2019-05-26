db fgcd(db a, db b) {//eps = 1e-2
	if (fabs(b) < eps) return a;
	return fgcd(b, fmod(a, b));
}
