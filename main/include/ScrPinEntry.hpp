#ifndef _ScrPinEntry_hpp
#define _ScrPinEntry_hpp

#include "Screen.hpp"

class ScrPinEntry : public Screen
{
public:
    ScrPinEntry(lv_obj_t* parent = nullptr, Screen* prev = nullptr, Screen* next = nullptr) : Screen(parent, prev, next)
    {
        static lv_style_t style_frame;
        lv_style_init(&style_frame);
        lv_style_set_border_width(&style_frame, 0);

        lv_obj_t * labelTitle = add(lv_label_create(get()));

        lv_label_set_long_mode(labelTitle, LV_LABEL_LONG_SCROLL_CIRCULAR);
        lv_obj_set_height(labelTitle, 18);
        lv_obj_set_content_height(labelTitle, 18);
        lv_label_set_text(labelTitle, LV_SYMBOL_WARNING " Unlock");
        lv_obj_set_style_text_align(labelTitle, LV_TEXT_ALIGN_CENTER, 0);
        lv_obj_align(labelTitle, LV_ALIGN_TOP_MID, 0, 0);

        LvObject* cont_col = addObject();
        lv_obj_set_size(cont_col->get(), 120, 76);
        lv_obj_align_to(cont_col->get(), labelTitle, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
        lv_obj_set_flex_flow(cont_col->get(), LV_FLEX_FLOW_ROW_REVERSE);
        lv_obj_set_scroll_snap_x(cont_col->get(), LV_SCROLL_SNAP_START);

        LvObject *pad = cont_col->addObject();
        lv_obj_set_style_border_width(pad->get(), 0, LV_PART_MAIN);
        pad->width(18);

        LvObject *roller1 = add_group(cont_col->addRoller());
        lv_roller_set_options(roller1->get(),
                            "0\n"
                            "1\n"
                            "2\n"
                            "3\n"
                            "4\n"
                            "5\n"
                            "6\n"
                            "7\n"
                            "8\n"
                            "9\n"
                            LV_SYMBOL_OK,
                            LV_ROLLER_MODE_INFINITE);

        lv_roller_set_visible_row_count(roller1->get(), 3);
        lv_roller_set_selected(roller1->get(), rand() % 9, LV_ANIM_OFF);
        roller1->height(60);
        lv_obj_center(roller1->get());
        lv_group_focus_obj(roller1->get());
        lv_group_focus_freeze(_group, true);
        lv_obj_add_flag(roller1->get(), LV_OBJ_FLAG_SNAPPABLE);
        //roller1->align(LV_ALIGN_LEFT_MID, 0, 0);
        //lv_obj_align(roller1->get(), LV_ALIGN_LEFT_MID, 0, 0);
        //lv_obj_set_flex_grow(roller1->get(), 1);

        // lv_obj_t * label1 =  lv_label_create(get());
        // lv_label_set_long_mode(label1, LV_LABEL_LONG_SCROLL_CIRCULAR);
        // lv_obj_set_width(label1, 120);
        // lv_obj_set_height(label1, 18);
        // lv_obj_set_content_height(label1, 18);
        // lv_label_set_text(label1, "At vero eos et accusamus et iusto odio dignissimos ducimus qui blanditiis praesentium voluptatum deleniti atque corrupti quos dolores. ");
        // lv_obj_align(label1, LV_ALIGN_BOTTOM_MID, 0, 0);

        roller1->add_event_cb([&, roller1, cont_col](lv_event_t* event)->void
        {
            lv_event_code_t code = lv_event_get_code(event);
            lv_obj_t * obj = lv_event_get_target(event);
            if(code == LV_EVENT_VALUE_CHANGED) 
            {
                char buf[32];
                lv_roller_get_selected_str(obj, buf, sizeof(buf));
                if (0 == strcmp(LV_SYMBOL_OK, buf))
                {
                    // TODO: check pin
                    loadNext();
                }
                else
                {
                    LvObject* c = cont_col->addObject();
                    //style_frame
                    //lv_obj_set_local_style_prop(c->get(), LV_STYLE_BORDER_WIDTH, 0, LV_PART_INDICATOR | LV_STATE_FOCUSED);
                    lv_obj_set_style_border_width(c->get(), 0, LV_PART_MAIN);
                    LvObject* l = c->addLabel();
                    lv_label_set_text(l->get(), LV_SYMBOL_EYE_CLOSE);
                    l->width(18);
                    l->height(18);
                    c->width(18);
                    c->height(60);
                    lv_obj_center(l->get());
                    lv_obj_clear_flag(c->get(), LV_OBJ_FLAG_SNAPPABLE);
                    lv_obj_clear_flag(c->get(), LV_OBJ_FLAG_SCROLLABLE);
                    //lv_obj_set_flex_align(c->get(), LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
                    //l->y(cont_col->height()/2-l->height()/2);

                    /*
                    size_t count = cont_col->childCount();
                    if (count > 1)
                    {
                        LvObject* last = cont_col->child(count-1);
                        l->align_to(last, LV_ALIGN_RIGHT_MID, 0, 0);
                        //l->x(last->x()+last->width());
                    }
                    else
                    {
                        l->align(LV_ALIGN_LEFT_MID, 0, 0);
                    }
                    */

                    //roller1->x(l->x()+l->width());
                    //roller1->align_to(l, LV_ALIGN_RIGHT_MID, 0, 0);
                    lv_group_focus_obj(roller1->get());
                    lv_roller_set_selected(obj, rand() % 9, LV_ANIM_OFF);
                    lv_obj_scroll_to_x(cont_col->get(), roller1->x()+roller1->width(), LV_ANIM_OFF);
                    printf("X:%d\n", roller1->x());
                }
            }
        }, LV_EVENT_VALUE_CHANGED);

        roller1->add_event_cb([&, roller1, cont_col](lv_event_t* event)->void
        {
            lv_event_code_t code = lv_event_get_code(event);
            lv_obj_t * obj = lv_event_get_target(event);
            if(code == LV_EVENT_CANCEL) 
            {
                size_t count = cont_col->childCount();
                if (count > 2)
                {
                    LvObject* last = cont_col->child(count-1);
                    cont_col->del(last);

                    // count = cont_col->childCount();
                    // if (count > 2)
                    // {
                    //     LvObject* last = cont_col->child(count-1);
                    //     roller1->x(last->x()+last->width());
                    // }
                    // else
                    // {
                    //     roller1->x(0);
                    // }
                    lv_obj_scroll_to_x(cont_col->get(), roller1->x()+roller1->width(), LV_ANIM_OFF);
                    printf("X:%d\n", roller1->x());
                }
                else
                {
                    loadPrev();
                }
            }
        }, LV_EVENT_CANCEL);
    }
};

#endif // _ScrPinEntry_hpp