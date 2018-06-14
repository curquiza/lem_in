import os
import subprocess
import sub_functions as ft

def launch_basic_tests(path):
    maps = sorted(os.listdir(path))
    for map in maps:
        filename = os.path.splitext(map)[0]
        ft.put(filename + ' ')
        try:
            output = subprocess.check_output(['./lem-in < ' + path + map], shell=True, stderr=subprocess.STDOUT)
        except subprocess.CalledProcessError as exc:
            if exc.returncode != 255 and exc.returncode != 1:
                ft.bad_returncode_msg(exc.output)
            else:
                ft.basic_test_msg(exc.output)
        else:
            ft.basic_test_msg(output)

launch_basic_tests('maps/cedric/tests/')
launch_basic_tests('maps/cedric/tests_2/')
launch_basic_tests('maps/dlancar/')
