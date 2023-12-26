#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <iostream>  
using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

class ComynoTestProject {
public:
    ComynoTestProject() {
        listener_ = http_listener(L"http://localhost:8081/api/countI");
        listener_.support(methods::POST, std::bind(&ComynoTestProject::handle_post, this, std::placeholders::_1));
    }

    void start() {
        listener_.open().wait();
    }

    void stop() {
        listener_.close().wait();
    }

private:
    void handle_post(http_request request) {
        //Handle CORS headers
        request.headers().add(U("Access-Control-Allow-Origin"), U("*"));
        request.headers().add(U("Access-Control-Allow-Methods"), U("POST"));
        request.headers().add(U("Access-Control-Allow-Headers"), U("Content-Type"));
        request.headers().add(U("Access-Control-Allow-Headers"), U("Content-Type,Custom-Header"));
      
        if (request.method() == methods::OPTIONS) 
        {
            // Handle preflight request
            // Respond with CORS headers

            request.reply(status_codes::OK);
        }
        else 
        {           
            request.extract_json().then([=](json::value body) {
                if (body.is_object() && body.has_field(U("text"))) {
                    std::wstring text = body.at(U("text")).as_string();
                    int count = countLetterI(text);
                    http_response response(status_codes::OK);
                    json::value res;
                    res[U("count")] = json::value::number(count);

                    response.headers().set_content_type(U("application/json"));
                    response.headers().add(U("Access-Control-Allow-Origin"), U("*"));
                    response.headers().add(U("Access-Control-Allow-Methods"), U("POST"));
                    response.headers().add(U("Access-Control-Allow-Headers"), U("Content-Type"));
                    response.set_body(res);

                    request.reply(response);
                }
                else {
                    request.reply(status_codes::BadRequest, U("Invalid input format."));
                }
                }).wait();
        }
    }

    int countLetterI(const std::wstring& text) {
        int count = 0;
        for (wchar_t ch : text) {
            if (ch == L'I' || ch == L'i') {
                count++;
            }
        }
        std::cout << "Text received:" << text.c_str() << std::endl;
        std::cout << "I's counted:" << count << std::endl;
        return count;
    }

    http_listener listener_;
};

int main() {
    ComynoTestProject letterICounter;
    letterICounter.start();

    std::cout << "Press Enter to exit." << std::endl;
    std::string line;
    std::getline(std::cin, line);

    letterICounter.stop();
    return 0;
}
