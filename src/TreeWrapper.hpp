#include <iostream>
#include <any>

#include <boost/property_tree/ptree.hpp>
#include <boost/unordered_map.hpp>

template< typename Observer, typename Key, typename Value >
class TreeWrapper;

/* Observer provides facility to find
 * some nodes inside tree using hash algorithm. */
template< typename Tree >
class Observer
{
    template< typename Observer, typename Key, typename Value >
    friend class TreeWrapper;

public :
    using Node = Tree;
    using Key = typename Tree::key_type;
    using Value = typename Tree::data_type;

public :
    void putValue( const Key& key, const Node& node_ref )
    {
        
    }
    void addValue( const Key& key, const Node& node_ref )
    {
        //::std::cout << "Added node with key : " << key << ::std::endl;
        m_key_map.emplace( key, node_ref );
    }

    const Node& getNode( const Key& key )
    {
        return m_key_map.find(key)->second;
    }

private :
    //::std::unordered_map< Key, const Node& > m_key_map;
    ::boost::unordered_map< Key, const Node& >m_key_map;
};



template< typename Observer, typename Key, typename Value >
class TreeWrapper
{
    using Tree = typename ::boost::property_tree::basic_ptree< Key, Value >;
    using Node = Tree;
    using SelfType = TreeWrapper;

public :
    /* Set the value of the node at the given path to the supplied value. 
     * If the node doesn't exist, it is created, including all its missing parents.  */

    void put( const Key& key, const Value& value )
    {
        m_observer.putValue( key, \
            m_tree.put( key, value ) );
    }

    void add( const Key& key, const Value& value )
    {
        m_observer.addValue( key, \
            m_tree.add( key, value ) );
    }

    void add_child( const Key& path, SelfType child )
    {
        m_observer.m_key_map.merge( child.m_observer.m_key_map );
        m_tree.add_child( path , child.m_tree );
    }

    const Node& find( const Key& key )
    {
        return m_tree.find( key )->second;
    }

    Observer& getObserver( void )
    {
        return m_observer;
    }



private :
    Tree m_tree;
    Observer m_observer;
};

template< typename Key, typename Value >
using _Tree = ::boost::property_tree::basic_ptree< Key, Value >;

template< typename Key, typename Value >
using Tree = TreeWrapper< Observer< _Tree< Key, Value > >, Key, Value >;
