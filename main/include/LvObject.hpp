#ifndef _LvObject_hpp
#define _LvObject_hpp

#include <lvgl.h>
#include <functional>
#include <unordered_map>
#include <vector>

namespace std {
  template <> struct hash<lv_event_code_t> {
    size_t operator() (const lv_event_code_t &t) const { return size_t(t); }
  };
}

typedef std::unordered_map<lv_event_code_t,std::function<void(lv_event_t*)>> LvObjectCbMap;

class LvObject
{
    std::vector<LvObject*> _Objects;
    LvObjectCbMap _callbacks;
    lv_obj_t* _obj;

public:

    LvObject(lv_obj_t* obj);

    virtual ~LvObject();

    lv_obj_t* get();

    lv_coord_t x()
    {
      return lv_obj_get_x(_obj);
    }

    void x(lv_coord_t val)
    {
      return lv_obj_set_x(_obj, val);
    }

    lv_coord_t y()
    {
      return lv_obj_get_y(_obj);
    }

    void y(lv_coord_t val)
    {
      return lv_obj_set_y(_obj, val);
    }

    lv_coord_t width()
    {
      return lv_obj_get_width(_obj);
    }

    void width(lv_coord_t val)
    {
      return lv_obj_set_width(_obj, val);
    }

    lv_coord_t height()
    {
      return lv_obj_get_height(_obj);
    }

    void height(lv_coord_t val)
    {
      return lv_obj_set_height(_obj, val);
    }

    void align(lv_align_t align, lv_coord_t x_ofs, lv_coord_t y_ofs)
    {
      lv_obj_align(_obj, align, x_ofs, y_ofs);
    }

    void align_to(const lv_obj_t * base, lv_align_t align, lv_coord_t x_ofs, lv_coord_t y_ofs)
    {
      lv_obj_align_to(_obj, base, align, x_ofs, y_ofs);
    }

    void align_to(LvObject* base, lv_align_t align, lv_coord_t x_ofs, lv_coord_t y_ofs)
    {
      lv_obj_align_to(_obj, base->get(), align, x_ofs, y_ofs);
    }

    void del(LvObject*);

    virtual LvObject* addObject(lv_obj_t* parent = nullptr);
    virtual LvObject* addLabel(lv_obj_t* parent = nullptr);
    virtual LvObject* addRoller(lv_obj_t* parent = nullptr);

    size_t childCount();
    LvObject* child(size_t);

    void handleEvent(lv_event_t*);

    //lv_event_dsc_t*
    void add_event_cb(std::function<void(lv_event_t*)> event_cb, lv_event_code_t filter);
};

#endif //_LvObject_hpp