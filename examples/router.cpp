#include <enginx/enginx.hpp>

int enginx_main(int argc,char ** argv)
{
    auto app = enginx::createApplication();
    auto router = enginx::createRoute();

    router.get('/hello',[](enginx::Context & ctx,enginx::NextHandler & next){
        ctx.end("Hello World");
    });

    app->use(router);
    enginx::register(app);
}
//http://localhost/hello    => Hello World