#include <iostream>
#include <ctime>
#include <future>

#include <boost/date_time/posix_time/posix_time.hpp>


#include "TreeWrapper.hpp"

#define VALUE 10000

int main( int , char** )
{
    ::Tree< ::std::string, ::std::any > tree;
    for (int idx = 0; idx < VALUE; idx++ )
    {
        ::std::string key1{ "KEY" + ::std::to_string(idx) };
        ::std::any value1 = ::std::make_any< ::std::string >( \
            "VALUE" + ::std::to_string(idx) );
        tree.add( key1, value1 );
    }

    ::std::string find = "KEY" + ::std::to_string( ::std::rand() % VALUE );

    ::std::future<void> f1 = ::std::async( ::std::launch::deferred,  [&](){ 
        ::boost::posix_time::ptime t1 = \
            ::boost::posix_time::microsec_clock::local_time();
        
        ::std::string value = ::std::any_cast<::std::string>( \
             tree.getObserver().getNode(find).data() );

        ::boost::posix_time::ptime t2 = \
            ::boost::posix_time::microsec_clock::local_time();

        ::boost::posix_time::time_duration diff = t2 - t1;

        ::std::cout << "Value : " << value \
                    << " found by OBSERVER in time : " << \
                    diff.total_microseconds() << ::std::endl;
        
    } );

    ::std::future<void> f2 = ::std::async( ::std::launch::deferred,  [&](){
        ::boost::posix_time::ptime t1 = \
            ::boost::posix_time::microsec_clock::local_time();
        
        ::std::string value = ::std::any_cast<::std::string>( \
            tree.find(find).data());

        ::boost::posix_time::ptime t2 = \
            ::boost::posix_time::microsec_clock::local_time();

        ::boost::posix_time::time_duration diff = t2 - t1;

        ::std::cout << "Value : " << value \
                    << " found by TREE ITSELF in time : " << \
                    diff.total_microseconds() << ::std::endl;
    } );

    f1.get();
    f2.get();

    if (
    ::std::any_cast<::std::string>( tree.getObserver().getNode(find).data() )
    !=
    ::std::any_cast<::std::string>( tree.find(find).data()) )

        return EXIT_FAILURE;

    return EXIT_SUCCESS;

}