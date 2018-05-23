import os, sys
# from os.path import basename
import subprocess

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

MAPS = {
    'mini_map_1':                  {'error': False, 'rounds': 7},
    'multi_ways_1':                {'error': False, 'rounds': 6},
    'multi_ways_2':                {'error': False, 'rounds': 0},
    'multi_ways_2_bis':            {'error': False, 'rounds': 8},
    'multi_ways_3':                {'error': False, 'rounds': 7},
    'multi_ways_4':                {'error': False, 'rounds': 7},
    'multi_ways_5':                {'error': False, 'rounds': 7},
    'multi_ways_6':                {'error': False, 'rounds': 8},
    'no_path_1':                   {'error': True,  'rounds': 0},
    'no_path_2':                   {'error': True,  'rounds': 0},
    'parsing_big_nb_of_ants':      {'error': True,  'rounds': 0},
    'parsing_comment_1':           {'error': False, 'rounds': 8},
    'parsing_comment_2':           {'error': False, 'rounds': 8},
    'parsing_comment_3':           {'error': False, 'rounds': 8},
    'parsing_comment_4':           {'error': False, 'rounds': 8},
    'parsing_comment_5':           {'error': False, 'rounds': 8},
    'parsing_comment_6':           {'error': False, 'rounds': 8},
    'parsing_comment_7':           {'error': False, 'rounds': 8},
    'parsing_empty_1':             {'error': True,  'rounds': 0},
    'parsing_empty_2':             {'error': True,  'rounds': 0},
    'parsing_empty_3':             {'error': True,  'rounds': 0},
    'parsing_empty_line_1':        {'error': True,  'rounds': 0},
    'parsing_empty_line_2':        {'error': True,  'rounds': 0},
    'parsing_empty_line_3':        {'error': False, 'rounds': 8},
    'parsing_empty_line_4':        {'error': False, 'rounds': 9},
    'parsing_no_ant':              {'error': False, 'rounds': 0},
    'parsing_no_end':              {'error': False, 'rounds': 0},
    'parsing_no_start':            {'error': False, 'rounds': 0},
    'parsing_no_start_no_end':     {'error': False, 'rounds': 0},
    'parsing_starts_in_tubes':     {'error': False, 'rounds': 0},
    'parsing_two_ends':            {'error': False, 'rounds': 0},
    'parsing_two_starts':          {'error': False, 'rounds': 0},
    'parsing_unknown_cmd_1':       {'error': False, 'rounds': 0},
    'parsing_unknown_cmd_2':       {'error': False, 'rounds': 0},
    'parsing_unknown_cmd_3':       {'error': False, 'rounds': 0},
    'parsing_unknown_cmd_comment': {'error': False, 'rounds': 0},
    'parsing_wrong_ants_line_1':   {'error': False, 'rounds': 0},
    'parsing_wrong_ants_line_2':   {'error': False, 'rounds': 0},
    'parsing_wrong_coord':         {'error': False, 'rounds': 0},
    'parsing_wrong_end_1':         {'error': False, 'rounds': 0},
    'parsing_wrong_end_2':         {'error': False, 'rounds': 0},
    'parsing_wrong_end_3':         {'error': False, 'rounds': 0},
    'parsing_wrong_start_1':       {'error': False, 'rounds': 0},
    'parsing_wrong_start_2':       {'error': False, 'rounds': 0},
    'parsing_wrong_start_3':       {'error': False, 'rounds': 0},
    'parsing_wrong_tube_1':        {'error': False, 'rounds': 0},
    'parsing_wrong_tube_2':        {'error': False, 'rounds': 0},
    'parsing_wrong_tube_3':        {'error': False, 'rounds': 0},
    'parsing_wrong_tube_4':        {'error': False, 'rounds': 0},
    'trap_1':                      {'error': False, 'rounds': 0},
    'trap_2':                      {'error': False, 'rounds': 0},
}

def when_error_expected(output):
    if 'ERROR' in output and '->' not in output:
        print bcolors.OKGREEN + 'OK' + bcolors.ENDC
    else:
        print bcolors.FAIL + 'KO' + bcolors.ENDC
        print "  -> should return ERROR"

def when_algo_expected(output):
    print bcolors.OKBLUE + 'wip' + bcolors.ENDC

all_files = sorted(os.listdir('maps/'))
maps = [f for f in all_files if f.endswith('.txt')]

for map in maps:
    filename = os.path.splitext(map)[0]
    sys.stdout.write(filename + ' ')
    output = subprocess.check_output(['./lem-in < maps/' + map], shell=True, stderr=subprocess.STDOUT)
    if MAPS[filename]:
        if MAPS[filename]['error'] == True:
            when_error_expected(output)
        else:
            when_algo_expected(output)      
    else:
        print 'Data not found for this map'
    # if 'ERROR' not in output
    # output = subprocess.check_output(['./lem-in < maps/' + map], shell=True)
    # print output
