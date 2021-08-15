#include "LvObject.hpp"
#include <algorithm>

LvObject::LvObject(lv_obj_t* obj) : _Objects(), _obj(obj)
{

}

LvObject::~LvObject()
{
    lv_obj_del(_obj);
    _obj = nullptr;
}


lv_obj_t* LvObject::get()
{
    return _obj;
}

LvObject* LvObject::addObject(lv_obj_t* parent)
{
    if (nullptr == parent)
        parent = get();

    LvObject* obj = new LvObject(lv_obj_create(parent));
    _Objects.push_back(obj);
    return obj;
}

LvObject* LvObject::addRoller(lv_obj_t* parent)
{
    if (nullptr == parent)
        parent = get();

    LvObject* obj = new LvObject(lv_roller_create(parent));
    _Objects.push_back(obj);
    return obj;
}

LvObject* LvObject::addLabel(lv_obj_t* parent)
{
    if (nullptr == parent)
        parent = get();

    LvObject* obj = new LvObject(lv_label_create(parent));
    _Objects.push_back(obj);
    return obj;
}

size_t LvObject::childCount()
{
    return _Objects.size();
}

LvObject* LvObject::child(size_t ix)
{
    return _Objects[ix];
}

void LvObject::del(LvObject* obj)
{
    auto it = std::find(_Objects.begin(), _Objects.end(), obj);
    if (it != _Objects.end())
    {
        _Objects.erase(it);
        delete *it;
    }
}

void LvObject::handleEvent(lv_event_t *e)
{
    auto iter = _callbacks.find(e->code);
    if (iter != _callbacks.end())
    {
        iter->second(e);
        return;
    }

    iter = _callbacks.find(LV_EVENT_ALL);
    if (iter != _callbacks.end())
    {
        iter->second(e);
        return;
    }
}

static void event_handler(lv_event_t *e)
{
    ((LvObject*)e->user_data)->handleEvent(e);
}

void LvObject::add_event_cb(std::function<void(lv_event_t*)> event_cb, lv_event_code_t filter)
{
    _callbacks[filter] = event_cb;
    lv_obj_add_event_cb(_obj, event_handler, filter, this);
}