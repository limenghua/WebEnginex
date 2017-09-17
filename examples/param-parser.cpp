#include <enginx/enginx.hpp>

int enginx_main(int argc,char ** argv)
{
    auto app = enginx::createApplication();
    auto router = enginx::createRoute();
    auto parser = enginx::createDefaultParser();

    auto addApi = parser.wrap([](int a,int b)->int{return a+b;});

    router.get('/add',addApi);

    app->use(router);
    enginx::register(app);
}
//http://localhost/add/3/5    => 8