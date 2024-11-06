const double eps = 1e-9;

// necesita una función double f(double), 
// la función a minimizar.
double ternary_search(double L, double R){
  while (abs(R-L)>eps){
    double a=(L+L+R)/3.0;
    double b=(L+R+R)/3.0;
    if (f(a)-f(b)>=-eps) L=a;
    if (f(b)-f(a)>=-eps) R=b;
  }
  return L;
}


double ternary_search(double l, double r) {
   //set the error limit here)
    double eps = 1e-9;             
    while (r - l > eps) {
        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;
        //evaluates the function at m1
          //evaluates the function at m2
        double f1 = f(m1);      
        double f2 = f(m2);    
        if (f1 < f2)
            l = m1;
        else
            r = m2;
    }
    //return the maximum of f(x) in [l, r]
    return f(l);                    
}