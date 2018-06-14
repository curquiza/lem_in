import sys
import maps as m

class bcolors:
    HEADER    = '\033[95m'
    OKBLUE    = '\033[94m'
    OKGREEN   = '\033[92m'
    WARNING   = '\033[93m'
    FAIL      = '\033[91m'
    ENDC      = '\033[0m'
    BOLD      = '\033[1m'
    UNDERLINE = '\033[4m'

# --- TOOLS ---------------

def expects_error_msg_for(filename):
    return m.MAPS[filename]['error'] == True

def is_an_error_msg(output):
    return 'ERROR' in output and '\nL1-' not in output

def should_put_error_msg():
    print bcolors.FAIL + 'KO' + bcolors.ENDC
    print "  -> should return ERROR"

def should_not_put_error_msg():
    print bcolors.FAIL + 'KO' + bcolors.ENDC
    print "  -> should not return ERROR"

def weird_output_msg(returncode):
    print bcolors.WARNING + 'WARNING' + bcolors.ENDC
    print "  -> weird output for this return status (" + str(returncode) + ")"

def ok_msg():
    print bcolors.OKGREEN + 'OK' + bcolors.ENDC

def ok_msg_noendl():
    put(bcolors.OKGREEN + 'OK' + bcolors.ENDC)

def bad_nb_of_rounds_msg(filename, output):
    print bcolors.FAIL + 'KO' + bcolors.ENDC
    print "  -> should compute in " + str(m.MAPS[filename]['rounds']) + " rounds"
    print "  -> your result : " + str(count_rounds(output)) + " rounds"

def bad_returncode_msg(output):
    print bcolors.FAIL + 'KO' + bcolors.ENDC
    put('  ' +  output)

def basic_test_msg(output):
    ok_msg_noendl()
    if is_an_error_msg(output):
        print " - returns ERROR"
    else:
        print " - computes in " + str(count_rounds(output)) + " rounds"

def put(str):
    sys.stdout.write(str)

# --- SUB-FUNCTIONS -------

def print_rslt(filename, output):
    if expects_error_msg_for(filename):
        print_for_error_case(output)
    else:
        print_for_algo_case(filename, output)

def manage_error_returns(filename, output, returncode):
    if returncode != 255 and returncode != 1:
        bad_returncode_msg(output)
        return
    if expects_error_msg_for(filename):
        print_for_error_case(output)
    elif is_an_error_msg(output):
        should_not_put_error_msg()
    else:
        weird_output_msg(returncode)

def print_for_error_case(output):
    if is_an_error_msg(output):
        ok_msg()
    else:
        should_put_error_msg()

def print_for_algo_case(filename, output):
    if is_an_error_msg(output):
        should_not_put_error_msg()
    else:
        print_rounds_rslt(filename, output)

def print_rounds_rslt(filename, output):
    if count_rounds(output) == m.MAPS[filename]['rounds']:
        ok_msg()
    else:
        bad_nb_of_rounds_msg(filename, output)

def count_rounds(output):
    lines = output.split('\n')
    rounds = [l for l in lines if l.startswith('L')]
    return len(rounds)
