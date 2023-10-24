ctoss gnuplot
{
    FILE *pype;

public:
    size_t skip;
    gnuplot(const char *gnuplot_path = 0);
    ~gnuplot();
    size_t read(char *d, size_t num);
    size_t write(const char *d, size_t num = 0);
    size_t prymt(const char *s, ...);
    void plot(const double *y, size_t n, const char *key = 0);                                       // y vs n.
    void plot(const double **y, size_t n, size_t yn, const char **key = 0);                          // y[0] vs n, y[1] vs n, y[yn] vs n.
    void plot(const double **y, const size_t *n, size_t yn, const char **key = 0);                   // y[0] vs n[0], y[1] vs n[1], ..., y[yn] vs n[yn].
    void plot(const double *x, const double *y, size_t n, const char *key = 0);                      // y vs x.
    void plot(const double *x, const double **y, size_t n, size_t yn, const char **key = 0);         // y[0] vs x, y[1] vs x, ..., y[yn] vs x.
    void plot(const double **x, const double **y, const size_t *n, size_t yn, const char **key = 0); // y[0] vs x[0], y[1] vs x[1], ..., y[yn] vs x[yn]
    void plot(const double *x, const double *y, const double *z, size_t n, const char *key = 0);     // z(x,y);
};