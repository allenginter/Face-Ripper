# Face-Ripper
Removing an NPCs face data, adding it to the character, and exporting as JSLOT
![Face Ripper](https://github.com/user-attachments/assets/9ff59285-92d5-41b1-8e76-121d7fad1e4f)
# FaceRipper - NPC Face Extractor

Extract any NPC's face data and save it as a RaceMenu .jslot preset for your own characters.

## Features

- Extract face morphs (all sliders)
- Extract face parts (nose, eyes, mouth)
- Extract tint layers (makeup, scars, dirt)
- Extract hair color
- Saves as RaceMenu-compatible .jslot file

## Requirements

- Skyrim Special Edition
- SKSE64
- RaceMenu (to use the extracted presets)

## Installation

### Mod Organizer 2
1. Install via MO2
2. Enable the mod
3. Done!

### Manual
1. Extract to Skyrim SE folder
2. Merge Data folder

## Usage

### Method 1: Console Command
1. Look at an NPC (crosshair on them)
2. Open console (~)
3. Type: `cg FaceRipper.RipFace`
4. Press Enter
5. You'll get a notification: "Face saved: [NPC_Name].jslot"

### Method 2: Hotkey (Requires additional mod)
Create a simple Papyrus script with a hotkey that calls `FaceRipper.RipFace()`

## Output Location

Extracted faces are saved to:
```
Data/SKSE/Plugins/FaceRipper/[NPC_Name].jslot
```

## Using Extracted Faces

1. Copy the .jslot file to:
   ```
   Data/SKSE/Plugins/CharGen/Presets/
   ```

2. In RaceMenu:
   - Press F9 to open preset menu
   - Load the preset
   - Adjust as needed

## What Gets Extracted

✅ **Facial Features:**
- All face morphs/sliders
- Nose shape
- Eye shape  
- Mouth shape

✅ **Appearance:**
- Tint layers (makeup, scars)
- Hair color

❌ **Not Included:**
- Hair style (mesh)
- Body morphs
- Equipment/clothing

## Troubleshooting

**"No target in crosshair"**
- Make sure you're looking directly at an NPC
- Try getting closer

**"Target is not an NPC"**
- You're looking at an object, not a character
- Look at the NPC's face/body

**"Could not create file"**
- Check that Data/SKSE/Plugins/FaceRipper/ folder exists
- Check file permissions

## Limitations

- Only works on NPCs with face data (most humanoid NPCs)
- Cannot extract from:
  - Creatures
  - Faceless NPCs
  - NPCs without FaceGen data

## Compatibility

- Compatible with all NPC mods
- Compatible with RaceMenu
- Compatible with appearance overhauls (extracts the modified face)

## Credits

- SKSE team
- CommonLibSSE-NG
- RaceMenu for the .jslot format

## Version History

### v1.0.0
- Initial release
- Extract face morphs
- Extract tint layers
- Extract hair color
- Save as .jslot format

---

**Enjoy collecting NPC faces!** 👤✨

SteamVikings
