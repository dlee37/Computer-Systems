double f(int x, int y, int z);
int g(int x);

int main() {
    int x, y;
    double d;
    char c;

    x = 1;
    y = g(x);
    d = f(x, y, x-y);
    c = 'a';
}

double f(int x, int y, int z) {
    int w;
    double result;

    if (z < 0)
        result = y * 2.0;
    else
        result = y / 2.0;
    w  = g(y);
    return result;
}

int g(int x) {
    int result;

    result = 2 * x;
    return result;
}
