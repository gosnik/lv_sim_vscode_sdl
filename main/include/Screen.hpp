#ifndef _Screen_hpp
#define _Screen_hpp

#include "lvgl.h"
#include "LvObject.hpp"
#include <vector>

class Screen
{
protected:
    lv_obj_t* _parent = nullptr;
    Screen* _prev = nullptr;
    Screen* _next = nullptr;
    std::vector<LvObject*> _Objects;
    std::vector<lv_obj_t*> _objects;
    lv_obj_t* _scr;
    lv_group_t* _group;
    lv_indev_t* _indev;
    uint16_t _tabIx = 0;

public:
    Screen(lv_obj_t* = nullptr, Screen* = nullptr, Screen* = nullptr);
    virtual ~Screen();

    virtual lv_obj_t* get();
    virtual lv_obj_t* add(lv_obj_t*);
    virtual lv_obj_t* add_group(lv_obj_t*);
    virtual LvObject* add_group(LvObject*);

    virtual LvObject* addObject(lv_obj_t* parent = nullptr);
    virtual LvObject* addRoller(lv_obj_t* parent = nullptr);

    virtual void load(lv_indev_t*);
    virtual void loadPrev();
    virtual void loadNext();

    virtual void setPrev(Screen*);
    virtual void setNext(Screen*);
};

#endif // _Screen_hpp