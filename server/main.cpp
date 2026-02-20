#include <iostream>
#include <chrono>
#include "discord-rpc/include/discord_rpc.h"
#include "discord-rpc/include/discord_register.h"
#include "httplib.h"

int main(){
  DiscordEventHandlers handlers;
  memset(&handlers, 0, sizeof(handlers));
  Discord_Initialize("1474342359537025141", &handlers, 1, NULL);

  httplib::Server svr;
  svr.Options(R"(\/hianimedrp)",
    [&](const auto& req, auto& res)
    {
      res.set_header("Access-Control-Allow-Origin", "*");
      res.set_header("Access-Control-Allow-Headers", "*");
      res.set_header("Access-Control-Allow-Methods", "*");
      res.status = 200;
    }
  );

  svr.Get("/hianimedrp",
    [&](const auto& req, auto& res)
    {
      res.status = 200;
      if (req.has_param("info"))
      {
        auto time = std::chrono::system_clock::now();
        DiscordRichPresence pr;
        memset(&pr, 0, sizeof(pr));
        pr.state = "";
        pr.details = req.get_param_value("info").c_str();
        pr.startTimestamp = std::chrono::duration_cast<std::chrono::milliseconds>(time.time_since_epoch()).count();
        pr.largeImageKey = "logo";
        pr.largeImageText = "hianime-drp";
        Discord_UpdatePresence(&pr);
      }
    }
  );

  svr.listen("localhost", 9293);
  Discord_Shutdown();
  return 0;
}