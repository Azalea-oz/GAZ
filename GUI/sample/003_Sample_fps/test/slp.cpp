#include <cstdlib>
#include <chrono>
#include <thread>

using namespace std;

int main(int argc, char *argv[])
{
        const size_t nloop = atol(argv[1]);
        for (size_t i = 0; i < nloop; i++)
                std::this_thread::sleep_for(std::chrono::microseconds(1));
}