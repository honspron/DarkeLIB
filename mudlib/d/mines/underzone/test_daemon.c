// This is a test daemon to help demonstrate the functions and
// properties of a daemon.

int x,y,z;
string foo, wibble, bar;

string set_foo(string str) { return foo = str; }
string query_foo() { return foo; }

int set_x(int num) { return x = num; }
int query_x() { return x;}
