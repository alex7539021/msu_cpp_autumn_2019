import subprocess

def run(command):
    process = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    out = process.stdout.readlines()
    code = process.wait()
    return out, code

def test(command, expected_code, result):
    out, code = run(command)
    if out != result:
        print('ERROR')
        return
    if code != expected_code:
        print('ERROR')
        return
    print('ok')

test('./calc 2', 0, [b'2'])
test('./calc "2"', 0, [b'2'])
test('./calc "2 + 2"', 0, [b'4'])
test('./calc "3*4"', 0, [b'12'])
test('./calc "  1+10 /2"', 0, [b'6'])
test('./calc "1*2*3      *4*  5"', 0, [b'120'])
test('./calc " 900-200 *3        -1"', 0, [b'299'])
test('./calc "9/10"', 0, [b'0'])
test('./calc "2--2"', 0, [b'4'])

test('./calc', 1, [b'error'])
test('./calc 5 * 5', 1, [b'error'])
test('./calc "2/0"', 1, [b'error'])
test('./calc "10/"', 1, [b'error'])
test('./calc "3 + i"', 1, [b'error'])