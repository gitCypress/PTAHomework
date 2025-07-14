#include "HttpServer.hpp"
#include "httplib.h"
#include <iostream>
#include <chrono>
#include "json.hpp"
#include <filesystem>

HttpServer::HttpServer(int port) : port_(port), server_(new httplib::Server()) {}

HttpServer::~HttpServer() {
    stop();
    delete server_;
}

void HttpServer::start() {
    setupRoutes();
    server_thread_ = std::thread([this]() {
        std::cout << "Starting HTTP server on port " << port_ << "..." << std::endl;
        if (!server_->listen("0.0.0.0", port_)) {
            std::cerr << "Error starting HTTP server on port " << port_ << std::endl;
        }
    });
}

void HttpServer::stop() {
    if (server_->is_running()) {
        server_->stop();
    }
    if (server_thread_.joinable()) {
        server_thread_.join();
    }
}

void HttpServer::setParameter(const std::string& key, const std::string& value) {
    std::lock_guard<std::mutex> lock(param_mutex_);
    parameters_[key] = value;
}

std::string HttpServer::getParameter(const std::string& key) {
    std::lock_guard<std::mutex> lock(param_mutex_);
    if (parameters_.count(key)) {
        return parameters_[key];
    }
    return "";
}

void HttpServer::setupRoutes() {
    // Set the base directory for static files
    std::filesystem::path base_path = "D:/Code/C++/PTAHomework/tech-try/Http";
    std::filesystem::path www_path = base_path / "res" / "www";
    if (std::filesystem::exists(www_path)) {
        server_->set_base_dir(www_path.string().c_str());
    } else {
        std::cerr << "Warning: Web content directory not found at " << www_path.string() << std::endl;
    }

    server_->Get("/status", [this](const httplib::Request&, httplib::Response& res) {
        nlohmann::json json_params;
        {
            std::lock_guard<std::mutex> lock(param_mutex_);
            for (const auto& pair : parameters_) {
                json_params[pair.first] = pair.second;
            }
        }
        res.set_content(json_params.dump(4), "application/json");
    });
} 