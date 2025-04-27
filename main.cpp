#include <iostream>
#include <vector>
#include <string>
using std::vector, std::string;

enum Ring {
    SMALL = 0, // A small ring.
    MEDIUM = 1, // A medium-size ring.
    LARGE = 2 // A large ring.
};

class Tower {
    public:
    vector<Ring> rings;

    Tower(vector<Ring> __rings) {
        this->rings = __rings;
    }

    void print() {
        string res = "";

        for (int i = rings.size()-1; i >= 0; i--) {
            Ring ring = rings[i];
            for (int i = 0; i < ring + 1; i++) {
                res += "@";
            }
            res += "\n";
        }

        std::cout << res << "~~~\n";
    }

    Tower* copy() {
        return new Tower(rings);
    }
};

/*
    Moves ring `ringIndex` of `t1` to the bottom of `t2`.
*/
void move(Tower* t1, Tower* t2, int ringIndex) {
    Ring ring = t1->rings[ringIndex]; // when we're dealing with pointers to a class, we use `->` to get the item at the pointer address
    Tower* newT1 = t1;
    newT1->rings.erase(newT1->rings.begin() + ringIndex);
    *t1 = *newT1;
    t2->rings.push_back(ring);
}

/*
    Solves the Tower of Hanoi problem with `towers`.
    Moves all the rings in tower 1 to tower 3.
*/
void solve(vector<Tower*> towers) {
    Tower* initialTower = new Tower({Ring::LARGE, Ring::MEDIUM, Ring::SMALL});
    Tower* initialTowerReverse = new Tower({Ring::SMALL, Ring::MEDIUM, Ring::LARGE});
    size_t flip = -1;
    for (Ring ring : towers[0]->rings) {
        if (towers[1]->rings.size() > 1 && (towers[1]->rings[0] == initialTowerReverse->rings[0] && towers[1]->rings[1] == initialTowerReverse->rings[1])) {
            // this means we can just flip `towers[1]` over to get our desired result
            move(towers[0], towers[2], towers[0]->rings.size()-1);
            flip = 1;
        } else {
            move(towers[0], towers[1], towers[0]->rings.size()-1);
        }
    }

    if (flip >= 0) {
        for (int i = 0; i < 2; i++) move(towers[1], towers[2], towers[1]->rings.size()-1);
    }
}

Tower* tower1 = new Tower({Ring::LARGE, Ring::MEDIUM, Ring::SMALL});
Tower* tower2 = new Tower({});
Tower* tower3 = new Tower({});

int main() {
    solve({tower1, tower2, tower3});
    tower1->print();
    tower2->print();
    tower3->print();
    return 0;
}