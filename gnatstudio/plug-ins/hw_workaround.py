###########################################################
# No user customization below this line
###########################################################

import GPS
import sys


def on_debugger_cmd(hook, debugger, command):
    # GPS.Console("Messages").write("Debugger command: " + command+"\n")
    if command == "-exec-step":
        GPS.Console("Messages").write("Single step detected: patching\n")
        debugger.send("set $primask=0x1", True)
    elif command == "-exec-next":
        GPS.Console("Messages").write("Step over detected: patching\n")
        debugger.send("set $primask=0x1", True)
    elif command == "-exec-continue":
        GPS.Console("Messages").write("Run detected: patching\n")
        debugger.send("set $primask=0x0", True)
    elif command == "-exec-finish":
        GPS.Console("Messages").write("Run to exit detected: patching\n")
        debugger.send("set $primask=0x0", True)
    return ""


GPS.Hook("debugger_command_action_hook").add(on_debugger_cmd)
GPS.Console("Messages").write("Cortex-M7 bug plugin: Version 1.0 (15/09/20)\n")
GPS.Console("Messages").write("Cortex-M7 bug plugin: gdb commands patched\n")
print("Cortex-M7 bug plugin: Version 1.0 (15/09/20)")
print("Cortex-M7 bug plugin: gdb commands patched")
