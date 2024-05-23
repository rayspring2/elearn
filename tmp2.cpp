#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

int main() {
    string x;
    getline(cin, x);
    try {
        throw runtime_error("222222222");
    } catch (const runtime_error &ev) {
        cout << ev.what();
    }
    cout << "----------------------------\n";
    return 0;
}
