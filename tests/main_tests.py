import os
import subprocess
import sub_functions as ft
import maps as m

all_files = sorted(os.listdir('maps/'))
maps = [f for f in all_files if f.endswith('.txt')]

for map in maps:
    filename = os.path.splitext(map)[0]
    ft.put(filename + ' ')
    if filename not in m.MAPS:
        print bcolors.WARNING + 'Data not found for this map' + bcolors.ENDC
        continue
    try:
        output = subprocess.check_output(['./lem-in < maps/' + map], shell=True, stderr=subprocess.STDOUT)
    except subprocess.CalledProcessError as exc:
        ft.manage_error_returns(filename, exc.output, exc.returncode)
    else:
        ft.print_rslt(filename, output)
