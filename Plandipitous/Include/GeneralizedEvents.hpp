

class GeneralizedEvents_impl;



// A handle to a generalized event.
// Abbreviated for convenience, because this
// will be the most commonly used type here.
class GEv
{
private:
    vertex_type from;
    vertex_type to;
    edge_type link;
    friend class GeneralizedEvents_impl;
};

class World
{
private:
    GeneralizedEvents_impl* impl;
public:
    World();

    GEv add(std::string name);
    GEv meet(std::string name, GEv a, GEv b);
    GEv meet(std::string name, GEv a, GEv b, GEv c);
    GEv before(GEv e);
    GEv after(GEv e);
    GEv during(GEv e);
    GEv with(GEv actor, GEv actee);
};

void example()
{
    World w;
    GEv wizard = w.add("wizard");
    GEv castle = w.add("castle");
    GEv wizardAtCastle = w.meet("goes to", wizard, castle);

    GEv dragon = w.add("dragon");
    GEv treasure = w.add("treasure");
    w.meet(castle, treasure, "holds");
    GEv dragonOwnsTreasure = w.meet("guards", dragon, treasure, castle);

    GEv magic = w.add("magic");

    GEv fight = w.meet("fight", wizard, dragon);
    GEv endFight = w.meet("kills", w.with(wizard, magic), dragon, w.during(fight));

    GEv wizardOwnsTreasure = w.meet("takes", wizard, treasure, w.after(endFight));
}

