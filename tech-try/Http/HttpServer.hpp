#ifndef HTTP_SERVER_HPP
#define HTTP_SERVER_HPP

#include <string>
#include <map>
#include <mutex>
#include <thread>

namespace httplib {
    class Server;
}

class HttpServer {
public:
    HttpServer(int port = 8080);
    ~HttpServer();

    void start();
    void stop();

    void setParameter(const std::string& key, const std::string& value);
    std::string getParameter(const std::string& key);

private:
    void setupRoutes();
    
    int port_;
    httplib::Server* server_;
    std::thread server_thread_;
    
    std::map<std::string, std::string> parameters_;
    std::mutex param_mutex_;
};

#endif // HTTP_SERVER_HPP 