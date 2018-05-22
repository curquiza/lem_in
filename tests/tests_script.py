import os
import subprocess

all_files = sorted(os.listdir('maps/'))
maps = [f for f in all_files if f.endswith('.txt')]

for map in maps:
    output = subprocess.check_output(['./lem-in < maps/' + map], shell=True)
    print output
