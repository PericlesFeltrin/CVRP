float distancia(int xa, int ya, int xb, int yb){
	return sqrt(fabs( pow((xb - xa), 2.0) + pow((yb - ya), 2.0)));
}