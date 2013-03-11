
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/r_c_shortest_paths.hpp>
#include <boost/shared_ptr.hpp>
using namespace boost;

#include <set>
#include <vector>
#include <iostream>
#include <string>
using namespace std;

namespace Plandipitous
{


struct VertProp
{
    VertProp(string site_name_="", bool is_wall_site_=false) : site_name(site_name_), is_wall_site(is_wall_site_) {}
    string site_name;
    bool is_wall_site;
};

struct ArcProp
{
    ArcProp(bool is_build_action_=false) : is_build_action(is_build_action_) {}
    bool is_build_action;
};

typedef adjacency_list<
    vecS,vecS,directedS,VertProp,ArcProp
> GraphType;

typedef GraphType::vertex_descriptor vertex_descriptor;


// ResourceContainer model
struct ResourceContainer
{
    int time;
    bool wall_is_built;

    ResourceContainer(int time_, bool wall_is_built_) : time(time_), wall_is_built(wall_is_built_) {}

    ResourceContainer& operator=( const ResourceContainer& other )
    {
        if( this == &other )
            return *this;
        this->~ResourceContainer();
        new( this ) ResourceContainer( other );
        return *this;
    }
};

bool operator==( const ResourceContainer& a,
                 const ResourceContainer& b )
{
    // TODO:  Return true iff all the resources in container 1 equal container 2.
    return (a.time == b.time) && (a.wall_is_built == b.wall_is_built);
}

bool operator<( const ResourceContainer& a,
                const ResourceContainer& b )
{
    // TODO:  Impose a total ordering on resource containers.  That is,
    // if resource X is the same, check resource Y, and so forth.
    return a.time == b.time? a.wall_is_built < b.wall_is_built : a.time < b.time;
}

// ResourceExtensionFunction model
class ResourceExtensionFunction
{
private:
    vertex_descriptor goal;
    shared_ptr<bool> reached_goal;

public:
    ResourceExtensionFunction(vertex_descriptor goal_) : goal(goal_), reached_goal(new bool) {}

    inline bool operator()( const GraphType& g,
                            ResourceContainer& new_cont,
                            const ResourceContainer& old_cont,
                            graph_traits<GraphType>::edge_descriptor ed
    ) const
    {
        const ArcProp& arc_prop = get( edge_bundle, g )[ed];
        const VertProp& vert_prop = get( vertex_bundle, g )[target( ed, g )];

        // TODO:  new container resources = old container resources + action costs.
        // (I think costs have to be added rather than subtracted because the dominance
        // function is using the <= operator to look for lower resource consumptions.)

        new_cont.time = old_cont.time + 1;
        new_cont.wall_is_built |= arc_prop.is_build_action;

        if (arc_prop.is_build_action)
            std::cout << "Time " << new_cont.time << " building wall " << vert_prop.site_name << std::endl;

        // TODO:  Return true iff the extension is feasible.
        bool feasible = !vert_prop.is_wall_site || !new_cont.wall_is_built;

        // Don't allow goal state to be reached until the wall is built.
        if (target(ed,g) == goal && !new_cont.wall_is_built)
            feasible = false;

        //if (feasible && target(ed,g) == goal)
        //    return *reached_goal = true;
        //else
        //    return feasible && !*reached_goal;
        return feasible;
    }
};

// DominanceFunction model
class DominanceFunction
{
public:
  inline bool operator()( const ResourceContainer& res_cont_1,
                          const ResourceContainer& res_cont_2 ) const
  {

    // TODO:  Return true if all the resources in container 1 are <= to container 2.
    // (Or == for nominal (non-numeric) properties.)
    bool dominated = res_cont_1.time <= res_cont_2.time && res_cont_1.wall_is_built == res_cont_2.wall_is_built ;

    return dominated;

    // must be "<=" here!!!
    // must NOT be "<"!!!
    // this is not a contradiction to the documentation
    // the documentation says:
    // "A label $l_1$ dominates a label $l_2$ if and only if both are resident
    // at the same vertex, and if, for each resource, the resource consumption
    // of $l_1$ is less than or equal to the resource consumption of $l_2$,
    // and if there is at least one resource where $l_1$ has a lower resource
    // consumption than $l_2$."
    // one can think of a new label with a resource consumption equal to that
    // of an old label as being dominated by that old label, because the new
    // one will have a higher number and is created at a later point in time,
    // so one can implicitly use the number or the creation time as a resource
    // for tie-breaking
  }
};

void do_test_2()
{
    GraphType g;

    typedef GraphType::vertex_descriptor vd;

    vd start = add_vertex( VertProp("start"), g );
    vd before = add_vertex( VertProp("before wall site"), g );
    vd middle = add_vertex( VertProp("wall site", true), g );
    vd after = add_vertex( VertProp("after wall site"), g );
    vd goal = add_vertex( VertProp("goal"), g );

    typedef GraphType::edge_descriptor ed;

    add_edge( start, middle, ArcProp(), g );
    add_edge( middle, goal, ArcProp(), g);

    add_edge( start, before, ArcProp(true), g );
    add_edge( before, start, ArcProp(), g );

    add_edge( middle, after, ArcProp(true), g );
    add_edge( after, goal, ArcProp(), g );

  std::vector< std::vector<ed> > opt_solutions;

  std::vector<std::vector<ed> >   opt_solutions_spptw;
  std::vector<ResourceContainer> pareto_opt_rcs_spptw;

  r_c_shortest_paths
  ( g,
    get( vertex_index, g ),
    get( vertex_index, g ),
    start,
    goal,
    opt_solutions_spptw,
    pareto_opt_rcs_spptw,
    ResourceContainer( 0, 0 ),
    ResourceExtensionFunction(goal),
    DominanceFunction(),
    std::allocator
      <r_c_shortest_paths_label
        <GraphType, ResourceContainer> >(),
          default_r_c_shortest_paths_visitor() );

  std::cout << "Number of optimal solutions: ";
  std::cout << static_cast<int>( opt_solutions.size() ) << std::endl;
  for( int i = 0; i < static_cast<int>( opt_solutions.size() ); ++i )
  {
    std::cout << "The " << i << "th shortest path is: ";
    std::cout << std::endl;
    for( int j = static_cast<int>( opt_solutions_spptw[i].size() ) - 1;
         j >= 0;
         --j )
        std::cout << source( opt_solutions_spptw[i][j], g ) << std::endl;
    std::cout << "time: " << pareto_opt_rcs_spptw[i].time << std::endl;
  }

  // utility function check_r_c_path example
  std::cout << std::endl;
  bool b_is_a_path_at_all = false;
  bool b_feasible = false;
  bool b_correctly_extended = false;
  ResourceContainer actual_final_resource_levels( 0, 0 );
  ed ed_last_extended_arc;
  check_r_c_path( g,
                  opt_solutions_spptw[0],
                  ResourceContainer( 0, 0 ),
                  true,
                  pareto_opt_rcs_spptw[0],
                  actual_final_resource_levels,
                  ResourceExtensionFunction(goal),
                  b_is_a_path_at_all,
                  b_feasible,
                  b_correctly_extended,
                  ed_last_extended_arc );
  if( !b_is_a_path_at_all )
    std::cout << "Not a path." << std::endl;
  if( !b_feasible )
    std::cout << "Not a feasible path." << std::endl;
  if( !b_correctly_extended )
    std::cout << "Not correctly extended." << std::endl;
  if( b_is_a_path_at_all && b_feasible && b_correctly_extended )
  {
    std::cout << "Actual final resource levels:" << std::endl;
    std::cout << "Time: " << actual_final_resource_levels.time << std::endl;
    std::cout << "OK." << std::endl;
  }

}


}
