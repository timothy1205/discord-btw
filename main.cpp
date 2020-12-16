#include <csignal>
#include <unistd.h>
#include "discord.h"

namespace {
  bool interrupted = false;
}

int main() {
    discord::Core* core{};
    discord::Core::Create(745854717954883694, DiscordCreateFlags_NoRequireDiscord, &core);
    discord::Activity activity{};
    activity.SetDetails("www.archlinux.org");
    activity.GetAssets().SetLargeImage("logo");
    core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {});

    std::signal(SIGINT, [](int) {interrupted = true; });

    while (!interrupted) {
        try {
            core->RunCallbacks();
        } catch (discord::Result result) {}
        sleep(16);
    }
    return 0;
}
