#include <enginx/enginx.hpp>

int enginx_main(int argc,char ** argv)
{
    auto app = enginx::createApplication();

    auto helloApi = [](enginx::Context & ctx,enginx::MiddleWare & next){
        ctx.end("Hello World");
    };

    app->use(helloApi);
    enginx::register(app);
}
//http://localhost/    => Hello World