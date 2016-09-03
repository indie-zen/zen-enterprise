#include <Zen/Enterprise/I_Connection.hpp>

#define BOOST_TEST_MODULE MyTest
#include <boost/test/unit_test.hpp>

#include <memory>
#include <functional>

BOOST_AUTO_TEST_CASE( simple_factory_delete_example )
{
    // This test is actually not really a test.  It's an example of how to 
    // create a shared_ptr to an object that is managed by a factory.
    struct MyClass 
    {
    };

    struct MyFactory
    {
        void destroy(MyClass* _p)
        {
            delete _p;            
        }
        
        std::shared_ptr<MyClass> create()
        {
            auto deleter = std::bind(&MyFactory::destroy, this, std::placeholders::_1);
            return std::shared_ptr<MyClass>(new MyClass(), deleter);
        }
    };
    
    MyFactory factory;
    auto pClass = factory.create();
}
