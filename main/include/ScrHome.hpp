#ifndef _ScrHome_hpp
#define _ScrHome_hpp

#include "Screen.hpp"

class ScrHome : public Screen
{
public:
    ScrHome(lv_obj_t* parent = nullptr, Screen* prev = nullptr, Screen* next = nullptr) : Screen(parent, prev, next)
    {
        lv_obj_t * labelTitle = add(lv_label_create(get()));

        lv_label_set_long_mode(labelTitle, LV_LABEL_LONG_SCROLL_CIRCULAR);
        lv_obj_set_height(labelTitle, 18);
        lv_obj_set_content_height(labelTitle, 18);
        lv_label_set_text(labelTitle, LV_SYMBOL_HOME " Home");
        lv_obj_align(labelTitle, LV_ALIGN_TOP_MID, 0, 0);
        //lv_obj_set_flex_flow(labelTitle, LV_FLEX_FLOW_ROW);

        lv_obj_t * cont_col = lv_obj_create(get());
        lv_obj_set_size(cont_col, 120, 150);
        lv_obj_align_to(cont_col, labelTitle, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
        lv_obj_set_flex_flow(cont_col, LV_FLEX_FLOW_COLUMN);
        add_group(cont_col);

        for (uint32_t i = 0; i < 10; i++) 
        {
            lv_obj_t * obj;
            lv_obj_t * label;
            obj = lv_btn_create(cont_col);
            lv_obj_set_size(obj, LV_PCT(100), LV_SIZE_CONTENT);
            

            label = lv_label_create(obj);
            lv_label_set_text_fmt(label, "Item: %d", i);
            lv_obj_center(label);        
        }
    }
};

#endif // _ScrHome_hpp