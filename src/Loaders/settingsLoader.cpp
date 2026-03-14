import json


'''Imports the meta settings from the "settings.json" file
currently this file stores :

- keybinds : with the corresponding scancodes

it returns a dict with the settings'''
def LoadSettings(path = "PlayerData/settings.json") -> dict:

    open('Text/debug.txt', 'a').write("| Parsing Settings...\n")

    try:
        settings = {}

        with open(path, "r") as f:
            data = json.load(f)

            settings["keybinds"] = ParseKeybinds(data["keybinds"])

            open('Text/debug.txt', 'a').write("| Done !!\n")
        
            return settings
        
    
    except Exception as e:
        open('Text/error.txt', 'w').write("Settings Parsing Failed : "+str(e))
        return {}


def ParseKeybinds(keybinds):
    open('Text/debug.txt', 'a').write("| | Parsing Keybinds... ")

    try:
        flipped_keybinds = {}

        for action, scancodes in keybinds.items():
            for scancode in scancodes:
                if not scancode in flipped_keybinds.keys():
                    flipped_keybinds[scancode] = []
                flipped_keybinds[scancode].append((action))

        open('Text/debug.txt', 'a').write("Done !!\n")

        return flipped_keybinds
        
    except Exception as e:
        open('Text/error.txt', 'w').write("Keybind Parsing Failed : "+str(e))

if __name__ == "__main__":
    print(LoadSettings())
