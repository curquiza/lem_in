import os, sys
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

def print_rslt(filename, output):
    if expects_error_msg_for(filename):
        print_for_error_case(output)
    else:
        print_for_algo_case(output)

def manage_error_returns(filename, output, returncode):
    if returncode != -1 and returncode != 1:
        print bcolors.FAIL + 'KO' + bcolors.ENDC
        put('  ' +  output)
        return
    if expects_error_msg_for(filename):
        print_for_error_case(output)
    elif is_an_error_msg(output):
        should_put_error_msg()
    else:
        weird_output_msg(returncode)

def print_for_error_case(output):
    if is_an_error_msg(output):
        print bcolors.OKGREEN + 'OK' + bcolors.ENDC
    else:
        should_put_error_msg()

def print_for_algo_case(output):
    if is_an_error_msg(output):
        should_put_error_msg()
    else:
        print bcolors.OKBLUE + 'wip' + bcolors.ENDC

def expects_error_msg_for(filename):
    MAPS[filename]['error'] == True

def is_an_error_msg(output):
    'ERROR' in output and '->' not in output

def should_put_error_msg():
    print bcolors.FAIL + 'KO' + bcolors.ENDC
    print "  -> should return ERROR"

def should_not_put_error_msg():
    print bcolors.FAIL + 'KO' + bcolors.ENDC
    print "  -> should not return ERROR"

def weird_output_msg(returncode):
    print bcolors.WARNING + 'WARNING' + bcolors.ENDC
    print "  -> weird output for this return status (" + str(returncode) + ")"

def put(str):
    sys.stdout.write(str)

# --- MAIN ----------------

all_files = sorted(os.listdir('maps/'))
maps = [f for f in all_files if f.endswith('.txt')]

for map in maps:
    filename = os.path.splitext(map)[0]
    put(filename + ' ')
    if filename not in MAPS:
        print bcolors.WARNING + 'Data not found for this map' + bcolors.ENDC
        continue
    try:
        output = subprocess.check_output(['./lem-in < maps/' + map], shell=True, stderr=subprocess.STDOUT)
    except subprocess.CalledProcessError as exc:
        manage_error_returns(filename, exc.output, exc.returncode)
    else:
        print_rslt(filename, output)
