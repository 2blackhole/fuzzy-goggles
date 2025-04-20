#pragma once

#include <godot_cpp/classes/object.hpp>

using namespace godot;

class Summator : public Object {
    GDCLASS(Summator, Object);
    int count;
protected:
    static void _bind_methods();

private:
    int get_total() const {
        return count;
    }
    void add(int p_val) {
        count += p_val;
    }
    void reset() {
        count = 0;
    }
    Summator() {
        count = 0;
    }
};