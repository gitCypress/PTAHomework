#include "HttpServer.hpp"
#include <random>

using namespace std;

class Random {  
    random_device rd_;  
    mt19937 gen_mt_;  
  
public:  
    Random() : gen_mt_(mt19937(rd_())) {  
    };  

	// 返回一个范围内的 int 随机数
    int uniform_int(const int low, const int high) {  
        uniform_int_distribution<int> uid(low, high);  
        return uid(gen_mt_);  
    }  
};

int main() {
    HttpServer server(8081);
    server.start();

    Random random;
    while (true) {
        int random_number = random.uniform_int(-200, 200);
        int random_number2 = random.uniform_int(20, 100);
        server.setParameter("random_number", std::to_string(random_number));
        server.setParameter("random_number2", std::to_string(random_number2));
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    return 0;
}