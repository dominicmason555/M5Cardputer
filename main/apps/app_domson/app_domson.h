/**
 * @file app_hello.h
 * @author Logimancer
 * @brief 
 * @version 0.1
 * @date 2024-02-27
 * 
 * @copyright Copyright (c) 2024
 */

#include <mooncake.h>
#include "../../hal/hal.h"
#include "../utils/theme/theme_define.h"
#include "../utils/anim/anim_define.h"
#include "../utils/icon/icon_define.h"

#include "assets/domson_big.h"
#include "assets/domson_small.h"

namespace MOONCAKE
{
    namespace APPS
    {
        class AppDomson : public APP_BASE
        {
            private:
                struct Data_t
                {
                    HAL::Hal* hal = nullptr;

                    int last_key_num = 0;
                    char string_buffer[100];
                    std::string repl_input_buffer;
                    bool is_caps = false;
                    char* value_buffer = nullptr;
                };
                Data_t _data;
                void _display_helloworld();
                void _update_input();

            public:
                void onCreate() override;
                void onResume() override;
                void onRunning() override;
                void onDestroy() override;
        };

        class AppDomson_Packer : public APP_PACKER_BASE
        {
            std::string getAppName() override { return "DOMSON"; }
            void* getAppIcon() override { return (void*)(new AppIcon_t(image_data_domson_big, image_data_domson_small)); }
            void* newApp() override { return new AppDomson; }
            void deleteApp(void *app) override { delete (AppDomson*)app; }
        };
    }
}
