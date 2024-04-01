/**
 * @file app_hello.cpp
 * @author Logimancer
 * @brief 
 * @version 0.1
 * @date 2024-02-27
 * 
 * @copyright Copyright (c) 2024
 */

#include "app_domson.h"
#include "spdlog/spdlog.h"
#include "../utils/theme/theme_define.h"
#include "../utils/esp_now_wrap/esp_now_wrap.h"

using namespace MOONCAKE::APPS;

#define _canvas _data.hal->canvas()
#define _canvas_update _data.hal->canvas_update
#define _canvas_clear() _canvas->fillScreen(THEME_COLOR_BG)

void AppDomson::_display_helloworld()
{
    _canvas->print("Dasonic Domson");
    _canvas_update();
}

void AppDomson::onCreate()
{
    spdlog::info("{} onCreate", getAppName());

    // Get hal
    _data.hal = mcAppGetDatabase()->Get("HAL")->value<HAL::Hal *>();
}

void AppDomson::onResume()
{
    spdlog::info("{} onResume", getAppName());

    ANIM_APP_OPEN();

    _canvas_clear();
    _canvas->setTextScroll(true);
    _canvas->setBaseColor(THEME_COLOR_BG);
    _canvas->setTextColor(THEME_COLOR_REPL_TEXT, THEME_COLOR_BG);
    _canvas->setFont(FONT_REPL);
    _canvas->setTextSize(FONT_SIZE_REPL);

    // Avoid input panel 
    _canvas->setCursor(0, 0);
    
    //run function once
    _display_helloworld();

    espnow_wrap_init();
}

void AppDomson::_update_input()
{
    // If changed
    if (_data.hal->keyboard()->keyList().size() != _data.last_key_num)
    {
        // If key pressed
        if (_data.hal->keyboard()->keyList().size() != 0)
        {
            // Update states and values
            _data.hal->keyboard()->updateKeysState();

            //spdlog::info("{} {}", _data.hal->keyboard()->keyList().size(), _data.last_key_num);
            auto key0 = _data.hal->keyboard()->keysState().hidKey[0];
            spdlog::info("Pressed {}", key0);

            if (_data.hal->keyboard()->keysState().enter)
            {
                spdlog::info("Pressed the enter key");
                uint32_t msg = 1234;
                espnow_single_send((uint8_t*)&msg, sizeof(msg));
            }

            // Update last key num
            _data.last_key_num = _data.hal->keyboard()->keyList().size();
        }
        else
        {
            // Reset last key num
            _data.last_key_num = 0;
        }
    }
}

void AppDomson::onRunning()
{
    _update_input();
    if (_data.hal->homeButton()->pressed())
    {
        _data.hal->playNextSound();
        spdlog::info("quit hello");
        destroyApp();
    }
}

void AppDomson::onDestroy() {
    _canvas->setTextScroll(false);
}
