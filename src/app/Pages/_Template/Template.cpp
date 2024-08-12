#include "Template.h"
#include <Arduino.h>
using namespace Page;


unsigned char *emoji_buffer;

Template::Template()
{
}

Template::~Template()
{

}

void Template::onCustomAttrConfig()
{
	SetCustomCacheEnable(true);
	SetCustomLoadAnimType(PageManager::LOAD_ANIM_FADE_ON, 500, lv_anim_path_bounce);
}

void Template::onViewLoad()
{
	View.Create(root);
	// lv_label_set_text(View.ui.labelTitle, "Page/BOT");

	AttachEvent(root);
	AttachEvent(View.ui.canvas);

	Model.TickSave = Model.GetData();
}

void Template::onViewDidLoad()
{

}

void Template::onViewWillAppear()
{
	Param_t param;
	param.color = lv_color_make(0,0,0);
	param.time = 100;

	PAGE_STASH_POP(param);

	lv_obj_set_style_bg_color(root, param.color, LV_PART_MAIN);
	lv_obj_add_flag(View.ui.labelTick, LV_OBJ_FLAG_HIDDEN);
	// timer = lv_timer_create(onTimerUpdate, param.time, this);
	timer = lv_timer_create(onTimerUpdate, LV_DISP_DEF_REFR_PERIOD, this);

	emoji_buffer = (unsigned char *)malloc(EMOJI_SIZE);
    if (emoji_buffer == nullptr) {
		LV_LOG_ERROR("emoji_buffer malloc failed!\n");
	}
        
	// lv_timer_ready(timer);
}

void Template::onViewDidAppear()
{

}

void Template::onViewWillDisappear()
{

}

void Template::onViewDidDisappear()
{
	lv_timer_del(timer);
	if (emoji_buffer) {
		free(emoji_buffer);
	}
}

void Template::onViewDidUnload()
{

}

void Template::AttachEvent(lv_obj_t* obj)
{
	lv_obj_set_user_data(obj, this);
	lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

void Template::Update()
{

	// lv_label_set_text_fmt(View.ui.labelTick, "tick = %d save = %d", Model.GetData(), Model.TickSave);
	
	// View.update_emoji(emoji_buffer);
}

void Template::onTimerUpdate(lv_timer_t* timer)
{
	Template* instance = (Template*)timer->user_data;

	instance->Update();
}

void Template::onEvent(lv_event_t* event)
{
	lv_obj_t* obj = lv_event_get_target(event);
	lv_event_code_t code = lv_event_get_code(event);
	auto* instance = (Template*)lv_obj_get_user_data(obj);

	if (code == LV_EVENT_PRESSED)
	{
		instance->Manager->Push("Pages/Menu");
	}
}
