#include "Screen.hpp"

Screen::Screen(lv_obj_t* parent, Screen* prev, Screen* next) : _parent(parent), _prev(prev), _next(next), _Objects(), _objects()
{
    if (nullptr == _parent)
    {
        _scr = lv_scr_act();
    }
    else
    {
        lv_tabview_t * tabview = (lv_tabview_t *)_parent;
        _tabIx = lv_tabview_get_cnt(_parent);
        _scr = lv_tabview_add_tab(_parent, "");
        //Serial.printf("Screen::Screen tab:%d\n", _tabIx);
    }
    //_scr = lv_obj_create(nullptr);
    _group = lv_group_create();
}

Screen::~Screen()
{
    for (auto o : _Objects)
    {
        lv_obj_del(o->get());
        delete o;
    }

    for (auto o : _objects)
    {
        lv_obj_del(o);
    }

    _Objects.clear();
    _objects.clear();
}

void Screen::load(lv_indev_t* indev)
{
    _indev = indev;
    lv_indev_set_group(indev, _group);
    if (nullptr == _parent)
    {
        //Serial.println("Screen::load");
        lv_scr_load(_scr);
    }
    else
    {
        //Serial.printf("Screen::load tab:%d\n", _tabIx);
        lv_tabview_set_act(_parent, _tabIx, LV_ANIM_OFF);
    }
}

void Screen::loadPrev()
{
    if (nullptr != _prev)
    {
        _prev->load(_indev);
    }
}

void Screen::loadNext()
{
    if (nullptr != _next)
    {
        //Serial.println("Screen::loadNext");
        _next->load(_indev);
    }
}

void Screen::setPrev(Screen* scr)
{
    _prev = scr;
}

void Screen::setNext(Screen* scr)
{
    _next = scr;
}

lv_obj_t* Screen::get()
{
    return _scr;
}

lv_obj_t* Screen::add(lv_obj_t* obj)
{
    _objects.push_back(obj);
    return obj;
}

lv_obj_t* Screen::add_group(lv_obj_t* obj)
{
    _objects.push_back(obj);
    lv_group_add_obj(_group, obj);
    return obj;
}

LvObject* Screen::add_group(LvObject* obj)
{
    lv_group_add_obj(_group, obj->get());
    return obj;
}

LvObject* Screen::addObject(lv_obj_t* parent)
{
    if (nullptr == parent)
        parent = get();

    LvObject* obj = new LvObject(lv_obj_create(parent));
    _Objects.push_back(obj);
    return obj;
}

LvObject* Screen::addRoller(lv_obj_t* parent)
{
    if (nullptr == parent)
        parent = get();

    LvObject* obj = new LvObject(lv_roller_create(parent));
    _Objects.push_back(obj);
    return obj;
}
