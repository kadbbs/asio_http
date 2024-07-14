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

std::map<std::string, std::function<void (request&)>> urlpatterns = {
        {"/upload", savefile},
};

```



2、views.cpp中的函数例子
```c++
void savefile(h_context &c) {
        utils::print_req(c.request_);
        std::string filename;



        for(auto it:c.request_.body_vhs){
            if(std::string::npos!=it.find("filename=")){
                filename = extract_filename(it);
            }
        }

        save_file(c.request_.content, filename);

        json::object response_json;
        response_json["h"] = "Ture";
        std::string json_str = json::serialize(response_json);


        c.reply_.josnstr(json_str);


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
            std::vector<std::string> body_vhs;

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