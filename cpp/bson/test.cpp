#include "stdio.h"
#include "stdlib.h"
#include <iostream>
#include "bson.h"

using namespace std;

void print(const char* fmt) {
    cout << fmt << endl;
}

int main() {
    cout << "Hello" << endl;
    print("abgvc" "basdf");

    bson_t bson;
    char *str;

    bson_init (&bson);
    BSON_APPEND_UTF8 (&bson, "0", "foo");
    BSON_APPEND_UTF8 (&bson, "1", "bar");

    str = bson_as_json (&bson, NULL);
    /* Prints
     *     * { "0" : "foo", "1" : "bar" }
     *         */
    printf ("%s\n", str);
    bson_free (str);

    bson_destroy (&bson);

    return 0;
}
