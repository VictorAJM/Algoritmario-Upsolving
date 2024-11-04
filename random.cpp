// Para generar randoms

// La distribución de los numeros, 
// intervalos inclusivos
uniform_int_distribution<int>dist(0, n); 

// La distribución de los numeros,
// intervalos inclusivos
uniform_real_distribution<double>dist(0, n); 

// Tarda en ejecutarse, genera buenos random,
// perfecto para usar como semilla
random_device rd; 

// Rapido de ejecutar, 
// necesita una semilla que aporta rd()
mt19937 engine(rd()); 
