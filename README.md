# WebEnginX

 一款易于扩展的C++ rest server 后端框架，类似于nodejs中的express
 前端暂时定位nginx
 后端业务使用C++语言实现。

开发目标:

 * 易于应用编写，充分利用C++14的特性。
 * 高性能，高并发，充分利用nginx的高性能和C++语言的高性能。
 * 异步处理，采用Microsoft Concurrency Library （PPL）作为异步库：https://msdn.microsoft.com/en-us/library/dd504870.aspx

 * 简易的中间件开发

# 代码示例
```cpp
auto app = enginx::createApplication();

auto helloApi = [](enginx::Context & ctx,enginx::Next next){
     ctx.end("Hello World");
};

app->use(helloApi);
enginx::register(app);
```
