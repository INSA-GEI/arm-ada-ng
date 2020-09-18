###########################################################
## No user customization below this line
###########################################################

import GPS

def on_gps_started (hook_name):
    templates_addon_dir=GPS.File("/home/dimercur/arm-ada/templates")
    GPS.ProjectTemplate.add_templates_dir(templates_addon_dir)
    print (templates_addon_dir.name()+" added")

GPS.Hook ("gps_started").add (on_gps_started)
