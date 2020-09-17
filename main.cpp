#include <unistd.h>
#include "discord.h"

int main() {
    discord::Core* core{};
    discord::Core::Create(745854717954883694, DiscordCreateFlags_NoRequireDiscord, &core);
    discord::Activity activity{};
    activity.SetDetails("www.archlinux.org");
    activity.GetAssets().SetLargeImage("logo");
    core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {});

    while (true) {
        try {
            core->RunCallbacks();
        } catch (discord::Result result) {}
        sleep(1);
    }
    return 0;
}
