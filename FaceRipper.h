#pragma once
#include <nlohmann/json.hpp>
#include <fstream>
#include <iomanip>

using json = nlohmann::json;

namespace FaceRipper {

    void RipFace(RE::StaticFunctionTag*) {
        SKSE::log::info("RipFace called!");
        
        auto player = RE::PlayerCharacter::GetSingleton();
        if (!player) {
            RE::DebugNotification("Error: Player not found");
            return;
        }

        // Get crosshair target
        auto crosshairPick = RE::CrosshairPickData::GetSingleton();
        if (!crosshairPick || !crosshairPick->target) {
            RE::DebugNotification("Error: No target in crosshair");
            return;
        }

        auto targetRef = crosshairPick->target.get();
        auto npc = targetRef->As<RE::Actor>();
        
        if (!npc) {
            RE::DebugNotification("Error: Target is not an NPC");
            return;
        }

        auto npcBase = npc->GetActorBase();
        if (!npcBase) {
            RE::DebugNotification("Error: Could not get NPC base data");
            return;
        }

        SKSE::log::info("Ripping face from: {}", npcBase->GetName());

        // Get face data
        auto faceData = npcBase->faceData;
        if (!faceData) {
            RE::DebugNotification("Error: NPC has no face data");
            return;
        }

        // Build RaceMenu .jslot format
        json jslot;
        
        // Basic info
        jslot["name"] = npcBase->GetName();
        jslot["race"] = npcBase->GetRace() ? npcBase->GetRace()->GetFormEditorID() : "Unknown";
        jslot["sex"] = npcBase->GetSex() == RE::SEX::kMale ? "Male" : "Female";
        
        // Face morphs (sliders)
        json morphs = json::array();
        if (faceData->morphs) {
            for (int i = 0; i < RE::TESNPC::FaceData::Morphs::kTotal; ++i) {
                morphs.push_back(faceData->morphs->values[i]);
            }
        }
        jslot["morphs"] = morphs;
        
        // Face parts
        json faceParts = json::object();
        if (faceData->parts) {
            faceParts["nose"] = faceData->parts->nose;
            faceParts["eyes"] = faceData->parts->eyes;
            faceParts["mouth"] = faceData->parts->mouth;
        }
        jslot["faceParts"] = faceParts;
        
        // Tint layers (makeup, scars, etc.)
        json tints = json::array();
        if (npcBase->headRelatedData && npcBase->headRelatedData->tintLayers) {
            auto& layers = *npcBase->headRelatedData->tintLayers;
            for (const auto& layer : layers) {
                if (layer) {
                    json tintData;
                    tintData["index"] = layer->tintIndex;
                    tintData["color"] = layer->tintColor.red | 
                                       (layer->tintColor.green << 8) | 
                                       (layer->tintColor.blue << 16) |
                                       (layer->tintColor.alpha << 24);
                    tintData["type"] = static_cast<int>(layer->type);
                    tints.push_back(tintData);
                }
            }
        }
        jslot["tints"] = tints;
        
        // Hair
        if (npcBase->headRelatedData && npcBase->headRelatedData->hairColor) {
            auto hairColor = npcBase->headRelatedData->hairColor;
            jslot["hairColor"] = hairColor->color.red | 
                                (hairColor->color.green << 8) | 
                                (hairColor->color.blue << 16);
        }
        
        // Save to file
        std::string filename = std::string("Data/SKSE/Plugins/FaceRipper/") + 
                              npcBase->GetName() + ".jslot";
        
        // Replace spaces and invalid characters
        std::replace(filename.begin(), filename.end(), ' ', '_');
        
        try {
            std::ofstream file(filename);
            if (!file.is_open()) {
                RE::DebugNotification("Error: Could not create file");
                SKSE::log::error("Failed to create file: {}", filename);
                return;
            }
            
            file << std::setw(4) << jslot << std::endl;
            file.close();
            
            std::string msg = "Face saved: " + std::string(npcBase->GetName()) + ".jslot";
            RE::DebugNotification(msg.c_str());
            SKSE::log::info("Face saved successfully: {}", filename);
            
        } catch (const std::exception& e) {
            RE::DebugNotification("Error: Failed to save file");
            SKSE::log::error("Exception: {}", e.what());
        }
    }

    bool RegisterFunctions(RE::BSScript::IVirtualMachine* vm) {
        vm->RegisterFunction("RipFace", "FaceRipper", RipFace);
        SKSE::log::info("Registered RipFace function");
        return true;
    }
}
