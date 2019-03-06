#include "DataHub.hpp"

using std::cout;
using std::endl;

int main (void) {
    DataHub* a = new DataHub("10.17.110.69", 8090);
    a->SendData(1, "data");
    delete a;
    getchar();
    return 0;
}
