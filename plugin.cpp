#include "PCH.h"
#include "FaceRipper.h"

namespace {
    void InitializeLogging() {
        auto path = SKSE::log::log_directory();
        if (!path) {
            return;
        }

        *path /= "FaceRipper.log";
        auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);
        auto log = std::make_shared<spdlog::logger>("global log", std::move(sink));

        log->set_level(spdlog::level::info);
        log->flush_on(spdlog::level::info);

        spdlog::set_default_logger(std::move(log));
        spdlog::set_pattern("[%H:%M:%S] [%l] %v");

        SKSE::log::info("FaceRipper v1.0.0");
    }

    void MessageHandler(SKSE::MessagingInterface::Message* a_msg) {
        switch (a_msg->type) {
        case SKSE::MessagingInterface::kDataLoaded:
            {
                SKSE::log::info("Data loaded, registering Papyrus functions...");
                
                // Register our Papyrus function
                auto papyrus = SKSE::GetPapyrusInterface();
                if (!papyrus) {
                    SKSE::log::error("Failed to get Papyrus interface!");
                    return;
                }

                if (!papyrus->Register(FaceRipper::RegisterFunctions)) {
                    SKSE::log::error("Failed to register Papyrus functions!");
                    return;
                }
                
                SKSE::log::info("FaceRipper initialized! Use console command: cg FaceRipper.RipFace");
            }
            break;
        }
    }
}

SKSEPluginLoad(const SKSE::LoadInterface* skse) {
    InitializeLogging();

    auto* plugin = SKSE::PluginDeclaration::GetSingleton();
    auto version = plugin->GetVersion();
    
    SKSE::log::info("{} v{}", plugin->GetName(), version);

    SKSE::Init(skse);

    auto messaging = SKSE::GetMessagingInterface();
    if (!messaging->RegisterListener(MessageHandler)) {
        SKSE::log::critical("Failed to register message listener");
        return false;
    }

    return true;
}
