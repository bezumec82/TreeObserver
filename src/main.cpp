#include <iostream>
#include <ctime>
#include <future>
#include <any>

#include <boost/date_time/posix_time/posix_time.hpp>


#include "TreeWrapper.hpp"

#define WIDTH 100

int main( int , char** )
{
    ::Tree< ::std::string, ::std::any > root;
    ::Tree< ::std::string, ::std::any > branches[WIDTH];
    ::Tree< ::std::string, ::std::any > sub_branches[WIDTH];

    for (int idx = 0; idx < WIDTH; idx++ )
    {
        ::std::string key{ "KEY" + ::std::to_string(idx) };
        ::std::any value = ::std::make_any< ::std::string >( \
            "VALUE " + ::std::to_string(idx) );
        root.add( key, value );

        /* Create branch */        
        ::std::string branch_key{ key + "BRANCH" };
        ::std::any branch_value = ::std::make_any< ::std::string >( \
            "BRANCH VALUE " + ::std::to_string(idx) );        
        branches[idx].add( branch_key, branch_value );    

        ::std::string sub_branch_key{ branch_key + "SUBBRANCH" };
        ::std::any sub_branch_value = ::std::make_any< ::std::string >( \
            "SUBBRANCH VALUE " + ::std::to_string(idx) );
        sub_branches[idx].add( sub_branch_key, sub_branch_value );

        branches[idx].add_child( branch_key,  sub_branches[idx] );
        root.add_child( key, branches[idx] );
    }

    ::std::string find = "KEY" + ::std::to_string( ::std::rand() % WIDTH );

    /* Find through Observer */
    ::std::future<void> f1 = ::std::async( ::std::launch::deferred,  [&](){ 
        ::boost::posix_time::ptime t1 = \
            ::boost::posix_time::microsec_clock::local_time();
        
        ::std::string value = ::std::any_cast<::std::string>( \
             root.getObserver().getNode(find).data() );

        ::boost::posix_time::ptime t2 = \
            ::boost::posix_time::microsec_clock::local_time();

        ::boost::posix_time::time_duration diff = t2 - t1;

        ::std::cout << "Value : " << value \
                    << " found by OBSERVER in time : " << \
                    diff.total_microseconds() << ::std::endl;
    } );

    /* Find using internal Tree algorithms */
    ::std::future<void> f2 = ::std::async( ::std::launch::deferred,  [&](){
        ::boost::posix_time::ptime t1 = \
            ::boost::posix_time::microsec_clock::local_time();
        
        ::std::string value = ::std::any_cast<::std::string>( \
            root.find(find).data());

        ::boost::posix_time::ptime t2 = \
            ::boost::posix_time::microsec_clock::local_time();

        ::boost::posix_time::time_duration diff = t2 - t1;

        ::std::cout << "Value : " << value \
                    << " found by TREE ITSELF in time : " << \
                    diff.total_microseconds() << ::std::endl;
    } );

    
    ::std::string find_branch = \
        "KEY" + ::std::to_string( ::std::rand() % WIDTH ) + "BRANCH" + "SUBBRANCH";
        // "KEY" + ::std::to_string( ::std::rand() % WIDTH ) + ".BRANCH" + ".SUBBRANCH";
    /* Find sub-branch through Observer */
    ::std::future<void> f3 = ::std::async( ::std::launch::deferred,  [&](){ 
        ::boost::posix_time::ptime t1 = \
            ::boost::posix_time::microsec_clock::local_time();
        
        ::std::string value = ::std::any_cast< ::std::string >( \
             root.getObserver().getNode(find_branch).data() );

        ::boost::posix_time::ptime t2 = \
            ::boost::posix_time::microsec_clock::local_time();

        ::boost::posix_time::time_duration diff = t2 - t1;

        ::std::cout << "Branch : " << value \
                    << " found by OBSERVER in time : " << \
                    diff.total_microseconds() << ::std::endl;
    } );


    /* Find sub-branch using internal Tree algorithms */
    ::std::future<void> f4 = ::std::async( ::std::launch::deferred,  [&](){
        ::boost::posix_time::ptime t1 = \
            ::boost::posix_time::microsec_clock::local_time();
        
        ::std::string value = ::std::any_cast<::std::string>( \
            root.find(find_branch).data() );

        ::boost::posix_time::ptime t2 = \
            ::boost::posix_time::microsec_clock::local_time();

        ::boost::posix_time::time_duration diff = t2 - t1;

        ::std::cout << "Value : " << value \
                    << " found by TREE ITSELF in time : " << \
                    diff.total_microseconds() << ::std::endl;
    } );


    f1.get();
    f2.get();
    // f3.get();
    f4.get();

    if (
    ::std::any_cast<::std::string>( root.getObserver().getNode(find).data() )
    !=
    ::std::any_cast<::std::string>( root.find(find).data()) )
        return EXIT_FAILURE;

    return EXIT_SUCCESS;

}