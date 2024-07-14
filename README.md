# asio_http

### About

***

ASIO_HTTP is a free, cross-platform HTTP server framework that uses Boost::asio to handle network services. Its API is similar to the Python Django framework.





#### 使用的cpp库 
***
```
boost::asio boost::json
```

### Simple

***

1、在webapp/urls.cpp中添加,"/uploda"是路由，savefile是views.cpp中的函数。
```c++

std::map<std::string, std::function<std::string (request&)>> urlpatterns = {
        {"/main.cpp", render},
        {"/upload", savefile},
};

```



2、views.cpp中的函数例子
```c++
std::string savefile(request &req) {

    print_req(req);
    std::string filetype;


        save_file(req.content, "./uploaded_file." + filetype);

        json::object response_json;
        response_json["filesave"] = "Ture";
        std::string json_str = json::serialize(response_json);
        
        return json_str;
}

```

request结构为
```c++

        struct request
        {
//            request();
            std::string method;
            std::string uri;
            int http_version_major;
            int http_version_minor;
            std::vector<header> headers;
            std::string body;
            int content_length;
            std::string boundary;
            std::string content;
            std::vector<header> body_headers;
            std::string body_hstr;


            std::string get_boundary() ;
            std::string extract_content();
            

        };

```


3、run
"Usage: http_server <address> <port> <doc_root>

```shell

cd cmake-build-debug 
make 

./asio_http 0.0.0.0 8090 doc_root

```