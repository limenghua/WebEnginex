# WebEnginX

 一款易于扩展的http server 框架，前端连接管理基于nginx,后端业务使用C++语言实现。

开发目标:

 * 易于应用编写，充分利用C++14的特性。
 * 高性能，高并发，充分利用nginx的高性能和C++语言的高性能。
 * 单线程，全异步，使用nginx线程，采用Microsoft Concurrency Library 简化异步操作,https://msdn.microsoft.com/en-us/library/dd504870.aspx


# 代码示例
```cpp
auto router = enginx::createRoute();
auto app = enginx::createApplication();
auto parser = enginx::defaultParser();

auto helloApi = [](enginx::Context & ctx,enginx::Next next){
     ctx.end("Hello World");
};

app.use(helloApi);
enginx::register(app);
```
